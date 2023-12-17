#include "lesson_model.h"

#include "movable_lambda.h"

int LessonModel::rowCount(const QModelIndex& parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant LessonModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    switch (role) {
    case Role::Id:
        return element.id;
    case Role::DepTitle:
        return element.departments.size() == 1 ? element.departments.front()
                                               : element.departments.join('/') + "联合授课";
    case Role::Topic:
        return element.topic;
    case Role::Time:
        return element.time;
    case Role::Location:
        return element.location;
    case Role::Icon:
        return element.image;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> LessonModel::roleNames() const {
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(DepTitle, "title");
        roles.insert(Topic, "topic");
        roles.insert(Time, "time");
        roles.insert(Location, "loc");
        roles.insert(Icon, "icon");
    }
    return roles;
}

void LessonModel::resetModel(std::vector<EventoLesson>&& model) {
    QMetaObject::invokeMethod(
        this, MovableLambda(std::move(model), [this](std::vector<EventoLesson>&& data) {
            beginResetModel();
            m_data = std::move(data);
            endResetModel();
        }));
}

LessonModel* LessonModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

LessonModel* LessonModel::getInstance() {
    static LessonModel instance;
    return &instance;
}
