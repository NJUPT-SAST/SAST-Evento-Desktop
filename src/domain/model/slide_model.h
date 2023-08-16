#ifndef SLIDE_MODEL_H
#define SLIDE_MODEL_H

#include <QAbstractListModel>
#include <mutex>

#include "slide.h"

class SlideModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        Id = Qt::UserRole + 1,
        Title,
        Link,
        Url,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<Slide>& model);

    static SlideModel* getInstance();

    SlideModel(const SlideModel&) = delete;
    SlideModel& operator=(const SlideModel&) = delete;

private:
    explicit SlideModel(QObject *parent = nullptr);

    std::vector<Slide> m_data;

    std::mutex m_mutex;
};

#endif // SLIDE_MODEL_H
