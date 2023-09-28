#ifndef SLIDE_MODEL_H
#define SLIDE_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "slide.h"

class SlideModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(SlideModel)

public:
    enum Role {
        Id = Qt::UserRole + 1,
        Title,
        Link,
        Url,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<Slide>&& model);

    void removeById(const int id);

private:
    SlideModel() = default;

    std::vector<Slide> m_data;

public:
    static SlideModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static SlideModel* getInstance();
};

#endif // SLIDE_MODEL_H
