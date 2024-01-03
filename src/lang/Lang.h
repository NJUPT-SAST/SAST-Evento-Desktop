#ifndef LANG_H
#define LANG_H

#include <QLocale>
#include <QtQml>

class Lang : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(Lang)
    QML_SINGLETON
private:
    QTranslator* translator = nullptr;

public:
    Lang() {
        QLocale::setDefault(QLocale::Chinese);
    }
    ~Lang() {
        if (translator)
            translator->deleteLater();
    }

public:
    enum LanguageMode {
        System,
        Chinese,
        English,
    };
    Q_ENUM(LanguageMode)
public:
    Q_INVOKABLE void changeLangMode(LanguageMode mode) {
        QLocale next;
        switch (mode) {
        case System:
            next = QLocale::system();
            break;
        case Chinese:
            next = QLocale::Chinese;
            break;
        case English:
            next = QLocale::English;
            break;
        }
        if (next.language() == QLocale())
            return;
        switch (next.language()) {
        case QLocale::Chinese:
            QCoreApplication::removeTranslator(translator);
            break;
        case QLocale::English:
            if (!translator) {
                translator = new QTranslator();
                translator->load("SAST_Evento_en.qm", ":/translations");
            }
            QCoreApplication::installTranslator(translator);
            break;
        }
        QLocale::setDefault(next);
    }
};

#endif // LANG_H
