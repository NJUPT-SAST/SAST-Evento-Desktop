#ifndef USERBRIEFMODEL_H
#define USERBRIEFMODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "user_brief.h"

class UserBriefModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(UserBriefModel)

public:
    enum Role {
        UserId = Qt::UserRole + 1,
        EMail,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<UserBrief>&& model);

private:
    UserBriefModel() = default;

    std::vector<UserBrief> m_data;

    std::mutex m_mutex;

public:
    static UserBriefModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static UserBriefModel* getInstance();
};

#endif // USERBRIEFMODEL_H
