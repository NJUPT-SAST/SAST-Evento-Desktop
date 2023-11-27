#include "department_model.h"

int DepartmentModel::rowCount(const QModelIndex& parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant DepartmentModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    switch (role) {
    case Role::Id:
        return element.id;
    case Role::Title:
        return element.name;
    case Role::Subscribed:
        return element.subscribed;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> DepartmentModel::roleNames() const {
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(Title, "title");
        roles.insert(Subscribed, "subscribed");
    }
    return roles;
}

void DepartmentModel::resetModel(std::vector<Department>&& model) {
    QMetaObject::invokeMethod(
        this,
        [&]() {
            beginResetModel();
            m_data = std::move(model);
            endResetModel();
        },
        Qt::BlockingQueuedConnection);
}

DepartmentModel* DepartmentModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

DepartmentModel* DepartmentModel::getInstance() {
    static DepartmentModel instance;
    return &instance;
}
