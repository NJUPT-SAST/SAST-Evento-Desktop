#include "undertaking_evento_model.h"

UndertakingEventoModel::UndertakingEventoModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int UndertakingEventoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant UndertakingEventoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
