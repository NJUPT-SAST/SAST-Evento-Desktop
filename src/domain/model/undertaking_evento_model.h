#ifndef UNDERTAKING_EVENTO_MODEL_H
#define UNDERTAKING_EVENTO_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "undertaking_evento.h"

class UndertakingEventoModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(UndertakingEventoModel)

public:
    enum Role {
        Id = Qt::UserRole + 1,
        Title,
        Time,
        Location,
        Department,
        Image,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<UndertakingEvento>&& model);

private:
    UndertakingEventoModel() = default;

    std::vector<UndertakingEvento> m_data;

public:
    static UndertakingEventoModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static UndertakingEventoModel* getInstance();
};

#endif // UNDERTAKING_EVENTO_MODEL_H
