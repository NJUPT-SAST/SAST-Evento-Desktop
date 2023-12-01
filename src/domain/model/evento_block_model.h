#ifndef EVENTO_BLOCK_MODEL_H
#define EVENTO_BLOCK_MODEL_H

#include <QAbstractListModel>
#include <QtQml>

#include "evento_block.h"

class EventoBlockModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(EventoBlockModel)

    Q_PROPERTY(int all_day_line_num MEMBER all_day_line_max NOTIFY lineChanged)

signals:
    void lineChanged();

public:
    enum Role {
        Id = Qt::UserRole + 1,
        IsAllDay,
        Title,
        Time,
        Column,
        Row,
        Start,
        End,
        StartFloat,
        EndFloat,
        Editable,
        Depth,
        DepthMax
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void resetModel(QDate monday, std::vector<EventoBlock>&& model);

private:
    EventoBlockModel() = default;

    std::vector<EventoBlock> m_data;
    std::vector<int> pipeline;
    std::array<std::array<int, 16>, 7> z_map = {};
    int all_day_line_max;

    enum ALL_DAY_MAP_FLAG : uint8_t {
        NUL = 0,
        MON = 1,
        TUE = 2,
        WED = 4,
        THU = 8,
        FRI = 16,
        SAT = 32,
        SUN = 64,
    };
    static constexpr const ALL_DAY_MAP_FLAG all_day_dict[] = {MON, TUE, WED, THU, FRI, SAT, SUN};

    enum Z_MAP_FLAG : uint16_t {
        AM_8 = 1 << 0,
        AM_9 = 1 << 1,
        AM_10 = 1 << 2,
        AM_11 = 1 << 3,
        AM_12 = 1 << 4,
        PM_1 = 1 << 5,
        PM_2 = 1 << 6,
        PM_3 = 1 << 7,
        PM_4 = 1 << 8,
        PM_5 = 1 << 9,
        PM_6 = 1 << 10,
        PM_7 = 1 << 11,
        PM_8 = 1 << 12,
        PM_9 = 1 << 13,
        PM_10 = 1 << 14,
        INIT = 0
    };
    static constexpr const Z_MAP_FLAG dict[] = {
        AM_8, AM_9, AM_10, AM_11, AM_12, PM_1, PM_2,  PM_3,
        PM_4, PM_5, PM_6,  PM_7,  PM_8,  PM_9, PM_10,
    };

private:
    void arrange_pipeline(QDate monday);

public:
    static EventoBlockModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static EventoBlockModel* getInstance();
};

#endif // EVENTO_BLOCK_MODEL_H
