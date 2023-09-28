#ifndef LATEST_EVENTO_MODEL_H
#define LATEST_EVENTO_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "latest_evento.h"

class LatestEventoModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(LatestEventoModel)

public:
    enum Role {
        Id = Qt::UserRole + 1,
        Title,
        Time,
        Description,
        Department,
        Url,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<LatestEvento>&& model);

private:
    LatestEventoModel() = default;

    std::vector<LatestEvento> m_data;

    std::mutex m_mutex;

public:
    static LatestEventoModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static LatestEventoModel* getInstance();
};

#endif // LATEST_EVENTO_MODEL_H
