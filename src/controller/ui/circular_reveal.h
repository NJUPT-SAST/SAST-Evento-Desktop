#ifndef CIRCULARREVEAL_H
#define CIRCULARREVEAL_H

#include "src/lang/stdafx.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QtQml>

class CircularReveal : public QQuickPaintedItem {
    Q_OBJECT
    QML_NAMED_ELEMENT(CircularReveal)
    Q_PROPERTY_AUTO(QQuickItem*, target)
    Q_PROPERTY_AUTO(int, radius)
public:
    CircularReveal(QQuickItem* parent = nullptr);
    void paint(QPainter* painter) override;
    Q_INVOKABLE void start(int w, int h, const QPoint& center, int radius);
    Q_SIGNAL void imageChanged();
    Q_SIGNAL void animationFinished();
    Q_SLOT void handleGrabResult();

private:
    QImage _source;
    QPropertyAnimation _anim = QPropertyAnimation(this, "radius", this);
    QPoint _center;
    QSharedPointer<QQuickItemGrabResult> _grabResult;
};

#endif // CIRCULARREVEAL_H
