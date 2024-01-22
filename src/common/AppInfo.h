#ifndef APPINFO_H
#define APPINFO_H

#include "Version.h"
#include <QtQml>

class AppInfo : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(AppInfo)
    QML_SINGLETON

    Q_PROPERTY(QString version MEMBER version CONSTANT)
public:
    inline static QString version = QStringLiteral(APPLICATION_VERSION);
};

#endif // APPINFO_H
