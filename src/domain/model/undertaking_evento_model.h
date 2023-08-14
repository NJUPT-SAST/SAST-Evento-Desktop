#ifndef UNDERTAKING_EVENTO_MODEL_H
#define UNDERTAKING_EVENTO_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "undertaking_evento.h"

class UndertakingEventoModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON

public:
    enum Role {
        Id = Qt::DisplayRole + 1,
        Title,
        Time,
        Location,
        Department,
        Url,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<UndertakingEvento>& model);

    static UndertakingEventoModel* getInstance();

    UndertakingEventoModel(const UndertakingEventoModel&) = delete;
    UndertakingEventoModel& operator=(const UndertakingEventoModel&) = delete;

private:
    explicit UndertakingEventoModel(QObject *parent = nullptr);

    std::vector<UndertakingEvento> m_data;

    std::mutex m_mutex;
};

#endif // UNDERTAKING_EVENTO_MODEL_H
