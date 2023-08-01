#include "Zh.h"

Zh::Zh(QObject *parent)
    : Lang{parent}
{
    setObjectName("Zh");
    home("活动广场");
    schedule("活动日程");
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
    personalData("个人资料");
    sign_in("签到");

    createEvent("创建活动");
    eventInfo("活动信息");
    usermanage("用户管理");
    timesheet("活动时间");
    feedback("用户反馈");
    uploadSouvenirCard("上传纪念卡");
    ppt("幻灯片");

    zh("中文");
    en("英文");

    welcome("欢迎回来，");

    followSystem("跟随系统");
    light("浅色");
    dark("深色");
    openSideBar("开启");
    compactSideBar("紧凑");
    minimalSideBar("最小化");
    automatical("自动");
}
