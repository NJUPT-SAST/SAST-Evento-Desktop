#ifndef SLIDESMODEL_H
#define SLIDESMODEL_H

#include <QAbstractListModel>
#include <mutex>
#include "src/domain/slides.h"

class SlidesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        Url =  Qt::DisplayPropertyRole + 1,
    };

    static std::shared_ptr<SlidesModel> getInstance();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    explicit SlidesModel(QObject *parent = nullptr);

    static std::mutex m_mutex;

    QList<Slides> m_data;
};

#endif // SLIDESMODEL_H
