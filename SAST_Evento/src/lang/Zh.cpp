#include "Zh.h"

Zh::Zh(QObject *parent)
    : Lang{parent}
{
    setObjectName("Zh");
    home("首页");
    timesheet("活动时间表");
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

    createEvent("创建活动");
    eventInfo("活动信息");
    addTypes("添加活动类型");
    addGroup("添加部门/组别");
    statistics("统计报表");
    uploadSouvenirCard("上传纪念卡");
    exportTimesheetPictures("导出时间表图片");

    zh("中文");
    en("英文");

    followSystem("跟随系统");
    light("浅色");
    dark("深色");
    openSideBar("开启");
    compactSideBar("紧凑");
    minimalSideBar("最小化");
    automatical("自动");
}
