#include "location_model.h"

#include "movable_lambda.h"

decltype(std::bind(std::declval<int (DTO_Location::*)() const>(),
                   std::placeholders::_1)) DTO_Location::functor =
    std::bind(&DTO_Location::count, std::placeholders::_1);

int LocationModel::rowCount(const QModelIndex& parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return std::transform_reduce(m_data.cbegin(), m_data.cend(), 0, std::plus{},
                                 DTO_Location::functor);
}

QVariant LocationModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    int num = index.row();
    for (const auto& i : m_data) {
        const auto& element = i.at(num);
        if (!num)
            switch (role) {
            case Role::Id:
                return element.id;
            case Role::Title:
                return element.name;
            case Role::Expanded:
                return element.expanded;
            case Role::Depth:
                return element.depth;
            default:
                break;
            }
    }
    return QVariant();
}

void LocationModel::click(const QModelIndex& index) {
    int num = index.row();
    for (const auto& i : m_data) {
        const auto& element = i.at(num);
        if (!num) {
            setProperty("selected", element.id);
            if (!element.expanded) {
                num = index.row();
                auto add = element.count_children();
                if (!add)
                    return;
                beginResetModel();
                element.expand();
                endResetModel();
            }
        }
    }
}

QHash<int, QByteArray> LocationModel::roleNames() const {
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(Title, "title");
        roles.insert(Expanded, "expanded");
        roles.insert(Depth, "depth");
    }
    return roles;
}

void LocationModel::resetModel(std::vector<DTO_Location>&& model) {
    QMetaObject::invokeMethod(
        this, MovableLambda(std::move(model), [this](std::vector<DTO_Location>&& model) {
            beginResetModel();
            m_data = std::move(model);
            update_depth();
            endResetModel();
        }));
}

LocationModel* LocationModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

LocationModel* LocationModel::getInstance() {
    static LocationModel instance;
    return &instance;
}
