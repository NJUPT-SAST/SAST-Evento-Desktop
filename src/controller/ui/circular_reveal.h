#ifndef CIRCULARREVEAL_H
#define CIRCULARREVEAL_H

/*
Copyright (c) 2023 zhuzichu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <QPainter>
#include <QPropertyAnimation>
#include <QQuickPaintedItem>
#include <QtQml>

class CircularReveal : public QQuickPaintedItem {
    Q_OBJECT
    QML_NAMED_ELEMENT(CircularReveal)
    Q_PROPERTY(QQuickItem* target MEMBER _target NOTIFY targetChanged)
    Q_PROPERTY(int radius MEMBER _radius NOTIFY radiusChanged)
public:
    CircularReveal(QQuickItem* parent = nullptr);

protected:
    void paint(QPainter* painter) override;

public:
    Q_INVOKABLE void start(int w, int h, const QPoint& center, int radius);

signals:
    void targetChanged();
    void radiusChanged();
    void imageChanged();
    void animationFinished();
public slots:
    void handleGrabResult();

private:
    QQuickItem* _target;
    int _radius;
    QImage _source;
    QPropertyAnimation _anim = QPropertyAnimation(this, "radius", this);
    QPoint _center;
    QSharedPointer<QQuickItemGrabResult> _grabResult;
};

#endif // CIRCULARREVEAL_H
