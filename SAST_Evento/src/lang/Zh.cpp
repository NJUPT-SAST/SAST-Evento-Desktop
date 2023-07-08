#include "Zh.h"

Zh::Zh(QObject *parent)
    : Lang{parent}
{
    setObjectName("Zh");
    home("首页");
    timeTable("活动时间表");
    history("历史活动");
    souvenirCard("纪念卡");
    organize("组织活动");
    manage("管理活动");
    theming("主题");
    dark_mode("夜间模式");
    sys_dark_mode("跟随系统");
    search("搜索");
    my("我的");
    settings("设置");
    locale("语言环境");
    navigation_view_display_mode("导航视图显示模式");
    zh("中文");
    en("英文");
}
