#include "AppInfo.h"

#include <QQmlContext>
#include <QDebug>
#include "En.h"
#include "Zh.h"

#include <QtGlobal>

AppInfo::AppInfo(QObject *parent)
    : QObject{parent}
{
    version("0.1");
    lang(new Zh());
}

void AppInfo::init(QQmlApplicationEngine *engine){
    QQmlContext * context = engine->rootContext();
    Lang* lang = this->lang();
    context->setContextProperty("lang",lang);
    QObject::connect(this,&AppInfo::langChanged,this,[=]{
        context->setContextProperty("lang",this->lang());
    });
    context->setContextProperty("appInfo",this);
}

void AppInfo::changeLang(const QString& locale){
    if(_lang){
        _lang->deleteLater();
    }
    if(locale=="Zh"){
        lang(new Zh());
    }else if(locale=="En"){
        lang(new En());
    }else {
        lang(new En());
    }
}