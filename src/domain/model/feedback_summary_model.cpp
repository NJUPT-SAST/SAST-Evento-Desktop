#include "feedback_summary_model.h"

int FeedbackSummaryModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant FeedbackSummaryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto &element = m_data.at(index.row());

    switch (role)
    {
    case Role::EventId:
        return element.eventId;
    case Role::Title:
        return element.title;
    case Role::FeedbackNum:
        return element.feedbackNum;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> FeedbackSummaryModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty())
    {
        roles.insert(EventId, "eventId");
        roles.insert(Title, "title");
        roles.insert(FeedbackNum, "feedbackNum");
    }
    return roles;
}

void FeedbackSummaryModel::resetModel(std::vector<FeedbackSummary> model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}

FeedbackSummaryModel *FeedbackSummaryModel::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

FeedbackSummaryModel *FeedbackSummaryModel::getInstance()
{
    static FeedbackSummaryModel singleton;
    return &singleton;
}
