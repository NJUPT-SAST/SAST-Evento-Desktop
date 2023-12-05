#include "location_model.h"

decltype(std::bind(std::declval<int (DTO_Location::*)() const>(),
                   std::placeholders::_1)) DTO_Location::functor =
    std::bind(&DTO_Location::count, std::placeholders::_1);

int LocationModel::rowCount(const QModelIndex& parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.count();
}

QVariant LocationModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    int num = index.row();
    const auto& element = m_data.at(num);

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

    return QVariant();
}

void LocationModel::click(const QModelIndex& index) {
    if (!index.isValid())
        return;

    int num = index.row();
    const DTO_Location& element = m_data.at(num);

    if (!num) {
        setProperty("selected", element.id);
        if (!element.expanded) {
            beginInsertRows(index.parent(), index.row() + 1,
                            index.row() + 1 + element.count_children());
            element.expand();
            endInsertRows();
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

void LocationModel::resetModel(DTO_Location&& model) {
    QMetaObject::invokeMethod(
        this,
        [&]() {
            beginResetModel();
            m_data = std::move(model);
            endResetModel();
        },
        Qt::BlockingQueuedConnection);
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
