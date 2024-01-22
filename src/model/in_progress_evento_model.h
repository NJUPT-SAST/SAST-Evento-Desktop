#ifndef IN_PROGRESS_EVENTO_MODEL_H
#define IN_PROGRESS_EVENTO_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "evento_in_progress.h"

class InProgressEventoModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(InProgressEventoModel)

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

    void resetModel(std::vector<EventoInProgress>&& model);

private:
    InProgressEventoModel() = default;

    std::vector<EventoInProgress> m_data;

public:
    static InProgressEventoModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static InProgressEventoModel* getInstance();
};

#endif // IN_PROGRESS_EVENTO_MODEL_H
