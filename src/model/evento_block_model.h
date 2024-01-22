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
        Start,
        End,
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
    std::array<std::array<int, 32>, 7> z_map = {};
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

    enum Z_MAP_FLAG : uint32_t {
        AM_8 = 1u << 0,
        AM_8_30 = 1u << 1,
        AM_9 = 1u << 2,
        AM_9_30 = 1u << 3,
        AM_10 = 1u << 4,
        AM_10_30 = 1u << 5,
        AM_11 = 1u << 6,
        AM_11_30 = 1u << 7,
        AM_12 = 1u << 8,
        AM_12_30 = 1u << 9,
        PM_1 = 1u << 10,
        PM_1_30 = 1u << 11,
        PM_2 = 1u << 12,
        PM_2_30 = 1u << 13,
        PM_3 = 1u << 14,
        PM_3_30 = 1u << 15,
        PM_4 = 1u << 16,
        PM_4_30 = 1u << 17,
        PM_5 = 1u << 18,
        PM_5_30 = 1u << 19,
        PM_6 = 1u << 20,
        PM_6_30 = 1u << 21,
        PM_7 = 1u << 22,
        PM_7_30 = 1u << 23,
        PM_8 = 1u << 24,
        PM_8_30 = 1u << 25,
        PM_9 = 1u << 26,
        PM_9_30 = 1u << 27,
        PM_10 = 1u << 28,
        PM_10_30 = 1u << 29,
        After_PM_11 = 1u << 30,
        Before_AM_8 = 1u << 31,
        INIT = 0
    };
    static constexpr const Z_MAP_FLAG dict[] = {
        AM_8,  AM_8_30,  AM_9, AM_9_30, AM_10, AM_10_30, AM_11,       AM_11_30,
        AM_12, AM_12_30, PM_1, PM_1_30, PM_2,  PM_2_30,  PM_3,        PM_3_30,
        PM_4,  PM_4_30,  PM_5, PM_5_30, PM_6,  PM_6_30,  PM_7,        PM_7_30,
        PM_8,  PM_8_30,  PM_9, PM_9_30, PM_10, PM_10_30, After_PM_11, Before_AM_8,
    };

private:
    void arrange_pipeline(QDate monday);

public:
    static EventoBlockModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    static EventoBlockModel* getInstance();
};

#endif // EVENTO_BLOCK_MODEL_H
