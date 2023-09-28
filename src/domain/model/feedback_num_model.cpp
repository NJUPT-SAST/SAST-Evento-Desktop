#include "feedback_num_model.h"

FeedbackNumModel* FeedbackNumModel::getInstance() {
    static FeedbackNumModel instance;
    return &instance;
}

FeedbackNumModel* FeedbackNumModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

int FeedbackNumModel::rowCount(const QModelIndex& parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant FeedbackNumModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    switch (role) {
    case Role::EventId:
        return element.eventId;
    case Role::Title:
        return element.title;
    case Role::FeedbackCount:
        return element.feedbackCount;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> FeedbackNumModel::roleNames() const {
    static QHash<int, QByteArray> roles;

    if (roles.isEmpty()) {
        roles.insert(EventId, "eventId");
        roles.insert(Title, "title");
        roles.insert(FeedbackCount, "feedbackCount");
    }
    return roles;
}

void FeedbackNumModel::resetModel(std::vector<FeedbackNum>&& model) {
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}
