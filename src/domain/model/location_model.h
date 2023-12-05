#ifndef LOCATION_MODEL_H
#define LOCATION_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include <dto/location.h>

class LocationModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(LocationModel)

    Q_PROPERTY(LocationID selected MEMBER selected NOTIFY selectedChanged)

public:
    enum Role {
        Id = Qt::UserRole + 1,
        Title,
        Expanded,
        Depth,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(DTO_Location&& model);

    Q_INVOKABLE void click(const QModelIndex& index);

signals:
    void selectedChanged();

private:
    LocationModel() = default;

    DTO_Location m_data;
    LocationID selected = -1;

public:
    static LocationModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static LocationModel* getInstance();
};

#endif // LOCATION_MODEL_H
