#ifndef EVENTO_BRIEF_MODEL_H
#define EVENTO_BRIEF_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "evento_brief.h"

class EventoBriefModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(EventoBriefModel)

public:
    enum Role {
        Id = Qt::UserRole + 1,
        Title,
        Description,
        Time,
        Location,
        Department,
        Url,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<EventoBrief>&& model);

private:
    EventoBriefModel() = default;

    std::vector<EventoBrief> m_data;

public:
    static EventoBriefModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static EventoBriefModel* getInstance();
};

#endif // EVENTO_BRIEF_MODEL_H
