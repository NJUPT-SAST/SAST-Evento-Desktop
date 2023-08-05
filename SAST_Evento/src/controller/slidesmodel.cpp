#include "slidesmodel.h"
#include "src/domain/slides.h"

SlidesModel::SlidesModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

SlidesModel* SlidesModel::getInstance()
{
    static SlidesModel instance;
    return &instance;
}

int SlidesModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant SlidesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case Role::Url:
        return m_data[index.row()].getLink();
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> SlidesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    // TODO: reflect
    roles.insert(Url, "url");
    return roles;
}

void SlidesModel::resetModel(const std::vector<Slides>& model)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}

void SlidesModel::append(const Slides& item)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.emplace_back(item);
    endInsertRows();
}

void SlidesModel::removeBySlideID(const QString& id)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto iter = std::find_if(m_data.begin(), m_data.end(),
                             [&id](const Slides& ele) {
                                 return ele.getSlideID() == id;
                             });
    if (iter == m_data.end()) return;
    auto idx = std::distance(m_data.begin() ,iter);
    beginRemoveRows(QModelIndex(), idx, idx);
    m_data.erase(iter);
    endRemoveRows();
}

void SlidesModel::changeItemBySlideID(const QString& id, const Slides& item)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto iter = std::find_if(m_data.begin(), m_data.end(),
                             [&id](const Slides& ele) {
                                 return ele.getSlideID() == id;
                             });
    if (iter == m_data.end()) return;
    auto idx = std::distance(m_data.begin() ,iter);
    m_data.emplace(iter, item);
    emit dataChanged(index(idx), index(idx));
}

