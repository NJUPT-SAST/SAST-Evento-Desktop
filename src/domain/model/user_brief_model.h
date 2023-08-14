#ifndef USERBRIEFMODEL_H
#define USERBRIEFMODEL_H

#include <QAbstractListModel>
#include <mutex>

#include "user_brief.h"

class UserBriefModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        UserId = Qt::UserRole + 1,
        StudentId,
        OpenId
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<UserBrief>& model);

    static UserBriefModel* getInstance();

    UserBriefModel(const UserBriefModel&) = delete;
    UserBriefModel& operator=(const UserBriefModel&) = delete;

private:
    explicit UserBriefModel(QObject *parent = nullptr);

    std::vector<UserBrief> m_data;

    std::mutex m_mutex;
};

#endif // USERBRIEFMODEL_H
