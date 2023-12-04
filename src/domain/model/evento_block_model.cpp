#include "evento_block_model.h"

#include "convertor.h"

int EventoBlockModel::rowCount(const QModelIndex& parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant EventoBlockModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= pipeline.size())
        return QVariant();

    const auto& element = m_data.at(pipeline[index.row()]);

    switch (role) {
    case Role::Id:
        return element.id;
    case Role::IsAllDay:
        return element.column_or_flag < 0;
    case Role::Title:
        return element.title;
    case Role::Time:
        return periodConvertor(element.gmtEventStart, element.gmtEventEnd);
    case Role::Column:
        return element.column_or_flag;
    case Role::Start:
        return TimePoint::to_float(element.start);
    case Role::End:
        return TimePoint::to_float(element.end);
    case Role::Editable:
        return element.editable;
    case Role::Depth:
        return element.depth;
    case Role::DepthMax:
        return element.column_or_flag < 0 ? all_day_line_max
                                          : z_map[element.column_or_flag][element.start.major];
    }

    return QVariant();
}

QHash<int, QByteArray> EventoBlockModel::roleNames() const {
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(IsAllDay, "is_all_day");
        roles.insert(Title, "title");
        roles.insert(Time, "time");
        roles.insert(Column, "column");
        roles.insert(Start, "start");
        roles.insert(End, "end");
        roles.insert(Editable, "editable");
        roles.insert(Depth, "depth");
        roles.insert(DepthMax, "depth_max");
    }
    return roles;
}

void EventoBlockModel::resetModel(QDate monday, std::vector<EventoBlock>&& model) {
    QMetaObject::invokeMethod(
        this,
        [=]() {
            beginResetModel();
            m_data = std::move(model);
            arrange_pipeline(monday);
            endResetModel();
        },
        Qt::BlockingQueuedConnection);
}

EventoBlockModel* EventoBlockModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

EventoBlockModel* EventoBlockModel::getInstance() {
    static EventoBlockModel instance;
    return &instance;
}

void EventoBlockModel::arrange_pipeline(QDate monday) {
    std::vector<std::vector<int>> bucket;
    std::vector<int> all_day;
    std::vector<ALL_DAY_MAP_FLAG> all_day_map;
    std::array<std::vector<Z_MAP_FLAG>, 7> z_map_layout = {};
    std::array<std::array<Z_MAP_FLAG, 15>, 7> z_map_rel = {};
    auto max = m_data.size();

    for (auto& i : z_map_layout)
        i.push_back(INIT);
    bucket.emplace_back();

    // Generate Depth Infos
    for (auto i = 0; i < max; ++i) {
        auto& element = m_data[i];
        element.fresh(monday);
        if (element.column_or_flag < 0) {
            ALL_DAY_MAP_FLAG flag = NUL;
            for (auto index = element.start.major; index <= element.end.major; ++index)
                flag = ALL_DAY_MAP_FLAG(flag | all_day_dict[index]);
            int max = all_day_map.size();
            int j;
            for (j = 0; j < max; j++)
                if (!(flag & all_day_map[j])) {
                    all_day_map[j] = ALL_DAY_MAP_FLAG(flag | all_day_map[j]);
                    element.depth = j;
                    break;
                }
            if (j == max) {
                all_day_map.push_back(flag);
                element.depth = max;
            }
            all_day.push_back(i);
        } else {
            auto end = element.end.major;
            if (!end) {
                element.depth = 0;
                continue;
            }
            if (!element.end.fraction)
                end--;
            Z_MAP_FLAG flag = INIT;
            for (auto index = element.start.major; index <= end; ++index)
                flag = Z_MAP_FLAG(flag | dict[index]);
            auto& rel = z_map_rel[element.column_or_flag];
            for (auto index = element.start.major; index <= end; ++index)
                rel[index] = Z_MAP_FLAG(rel[index] | flag);
            auto& layout = z_map_layout[element.column_or_flag];
            auto max = layout.size();
            std::size_t j;
            for (j = 0; j < max; j++)
                if (!(flag & layout[j])) {
                    layout[j] = Z_MAP_FLAG(flag | layout[j]);
                    element.depth = j;
                    break;
                }
            if (j == max) {
                layout.push_back(flag);
                element.depth = max;
                bucket.emplace_back();
            }
            auto& col = z_map[element.column_or_flag];
            for (auto index = element.start.major; index <= end; ++index)
                if (col[index] < element.depth)
                    col[index] = element.depth;
            bucket[element.depth].push_back(i);
        }
    }

    // Genarate Piepeline
    pipeline = std::move(all_day);
    for (auto& i : bucket)
        std::copy(i.begin(), i.end(), std::back_inserter(pipeline));

    // update all_day_line_num
    this->setProperty("all_day_line_num", (quint64)all_day_map.size());
    // update z_map
    for (auto col = 0; col < 7; col++) {
        Z_MAP_FLAG processed = INIT;
        Z_MAP_FLAG current_set;
        int max;
        for (auto i = 0; i < 15; i++)
            if (!(processed & dict[i])) {
                current_set = dict[i];
                max = z_map[col][i];
                auto rel = z_map_rel[col][i];
                auto will_visit = Z_MAP_FLAG(rel & (rel ^ current_set));
                if (!will_visit) {
                    processed = Z_MAP_FLAG(processed | current_set);
                    continue;
                }
                int count = 14;
                auto& map = z_map[col];
                while (will_visit) {
                    if (will_visit & dict[count]) {
                        if (max < map[count])
                            max = map[count];
                        current_set = Z_MAP_FLAG(current_set | dict[count]);
                        rel = Z_MAP_FLAG(rel | z_map_rel[col][count]);
                        will_visit = Z_MAP_FLAG(rel & (rel ^ current_set));
                    }
                    if (!count)
                        count = 14;
                    else
                        count--;
                }
                for (count = 0; count < 15; count++)
                    if (processed & dict[count])
                        map[count] = max;
                processed = Z_MAP_FLAG(processed | current_set);
            }
    }
}
