#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject* parent = nullptr);

    QString api(const QString& path){
        return "https://api.github.com" + path;
    }

    QString html(const QString& path){
        return "https://github.com" + path;
    }

    virtual QString accessToken(const QString &id,const QString &secret,const QString &code) = 0;
};

#endif  // REPOSITORY_H
