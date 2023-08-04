#include "slidesmodel.h"

SlidesModel::SlidesModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

std::shared_ptr<SlidesModel> SlidesModel::getInstance()
{
    static std::shared_ptr<SlidesModel> instance = nullptr;
    if (instance)
        return instance;
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!instance)
        instance = std::make_shared<SlidesModel>(nullptr);
    return instance;
}

int SlidesModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.count();
}

QVariant SlidesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case Role::Url:
        return m_data[index.row()].getLink();
    default:
        ;
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

bool SlidesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags SlidesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}
