#ifndef LESSON_MODEL_H
#define LESSON_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "lesson.h"

class LessonModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(LessonModel)

public:
    enum Role {
        Id = Qt::UserRole + 1,
        DepTitle,
        Topic,
        Time,
        Location,
        Icon,
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(std::vector<EventoLesson>&& model);

private:
    LessonModel() = default;

    std::vector<EventoLesson> m_data;

public:
    static LessonModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static LessonModel* getInstance();
};

#endif // LESSON_MODEL_H
