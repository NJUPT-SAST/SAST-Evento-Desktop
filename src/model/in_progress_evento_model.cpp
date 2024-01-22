#include "in_progress_evento_model.h"

int InProgressEventoModel::rowCount(const QModelIndex& parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant InProgressEventoModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    switch (role) {
    case Role::Id:
        return element.id;
    case Role::Title:
        return element.title;
    case Role::Time:
        return element.time;
    case Role::Location:
        return element.location;
    case Role::Department:
        return element.department;
    case Role::Image:
        return element.image;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> InProgressEventoModel::roleNames() const {
    static QHash<int, QByteArray> roles;

    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(Title, "title");
        roles.insert(Time, "time");
        roles.insert(Location, "location");
        roles.insert(Department, "department");
        roles.insert(Image, "image");
    }
    return roles;
}

void InProgressEventoModel::resetModel(std::vector<EventoInProgress>&& model) {
    QMetaObject::invokeMethod(this, [this, data = std::move(model)]() {
        beginResetModel();
        m_data = std::move(data);
        endResetModel();
    });
}

InProgressEventoModel* InProgressEventoModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

InProgressEventoModel* InProgressEventoModel::getInstance() {
    static InProgressEventoModel singleton;
    return &singleton;
}
