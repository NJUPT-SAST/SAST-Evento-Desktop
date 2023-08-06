#ifndef SLIDESMODEL_H
#define SLIDESMODEL_H

#include <QAbstractListModel>
#include <mutex>

class Slides;

class SlidesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        Url =  Qt::UserRole + 1,
    };

    static SlidesModel* getInstance();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(const std::vector<Slides>& model);
    void append(const Slides& item);
    void removeBySlideID(const QString& id);
    void changeItemBySlideID(const QString& id, const Slides& item);

private:
    explicit SlidesModel(QObject *parent = nullptr);

    std::vector<Slides> m_data;

    std::mutex m_mutex;
};

#endif // SLIDESMODEL_H
