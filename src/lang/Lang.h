#ifndef LANG_H
#define LANG_H

#include <QObject>
#include <QtQml>

class Lang : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(Lang)
    QML_SINGLETON

public:
    enum LanguageMode {
        System,
        Chinese,
        English,
    };
    Q_ENUM(LanguageMode)
public:
    Q_INVOKABLE void changeLangMode(LanguageMode) {}
};

#endif // LANG_H
