#ifndef EVENTO_BRIEF_MODEL_H
#define EVENTO_BRIEF_MODEL_H

#include <QAbstractListModel>
#include <QtQml>
#include <mutex>

#include "evento_brief.h"

class EventoBriefModel : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(EventoBriefModel)

public:
    enum Role {
        Id = Qt::DisplayRole + 1,
        Title,
        State,
        Description,
        Time,
        Url,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<EventoBrief>& model);

private:
    EventoBriefModel() = default;

    std::vector<EventoBrief> m_data;

    std::mutex m_mutex;
public:
    static EventoBriefModel *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        return getInstance();
    }
    inline static EventoBriefModel *getInstance()
    {
        static EventoBriefModel singleton;
        return &singleton;
    }
};

#endif // EVENTO_BRIEF_MODEL_H
