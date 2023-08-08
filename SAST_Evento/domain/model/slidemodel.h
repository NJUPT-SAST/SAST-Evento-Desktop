#ifndef SLIDEMODEL_H
#define SLIDEMODEL_H

#include <QAbstractListModel>
#include <mutex>

class Slide;

class SlideModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        Id = Qt::DisplayRole + 1,
        Title,
        Link,
        Url,
    };

    static SlideModel* getInstance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<Slide>& model);

private:
    explicit SlideModel(QObject *parent = nullptr);

    std::vector<Slide> m_data;

    std::mutex m_mutex;
};

#endif // SLIDEMODEL_H
