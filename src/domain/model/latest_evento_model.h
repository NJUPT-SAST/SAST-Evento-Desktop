#ifndef LATEST_EVENTO_MODEL_H
#define LATEST_EVENTO_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "latest_evento.h"

class LatestEventoModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    enum Role {
        Id = Qt::DisplayRole + 1,
        Title,
        Time,
        Description,
        Department,
        Url,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<LatestEvento>& model);

    static LatestEventoModel* getInstance();

    LatestEventoModel(const LatestEventoModel&) = delete;
    LatestEventoModel& operator=(const LatestEventoModel&) = delete;

private:
    explicit LatestEventoModel(QObject *parent = nullptr);

    std::vector<LatestEvento> m_data;

    std::mutex m_mutex;
};

#endif // LATEST_EVENTO_MODEL_H
