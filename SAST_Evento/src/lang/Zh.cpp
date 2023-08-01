#include "Zh.h"

Zh::Zh(QObject *parent)
    : Lang{parent}
{
    setObjectName("Zh");
    lang_home("活动广场");
    lang_schedule("活动日程");
    lang_history("历史活动");
    lang_souvenirCard("纪念卡");
    lang_organize("组织活动");
    lang_manage("管理活动");
    lang_theming("主题");
    lang_dark_mode("夜间模式");
    lang_sys_dark_mode("跟随系统");
    lang_search("搜索");
    lang_my("我的");
    lang_settings("设置");
    lang_locale("语言环境");
    lang_navigation_view_display_mode("导航视图显示模式");
    lang_personalData("个人资料");
    lang_sign_in("签到");

    lang_createEvent("创建活动");
    lang_eventInfo("活动信息");
    lang_usermanage("用户管理");
    lang_timesheet("活动时间");
    lang_feedback("用户反馈");
    lang_uploadSouvenirCard("上传纪念卡");
    lang_ppt("幻灯片");

    lang_zh("中文");
    lang_en("英文");

    lang_welcome("欢迎回来，");
    lang_login("登录");
    lang_comment("评论");
    lang_publish("发表");
    lang_subscribe("+订阅");
    lang_unsubscribe("取消订阅");
    lang_signed_in("已签到");
    lang_in_progress("进行中");
    lang_not_started("未开始");
    lang_over("已结束");
    lang_ongoing_events("正在进行的活动");
    lang_latest_events("最新的活动");
    lang_username("账号");
    lang_password("密码");
    lang_participate_in("参加活动");
    lang_exit("退出");
    lang_cancel("取消");
    lang_determine_exit("确定退出程序？");

    lang_followSystem("跟随系统");
    lang_light("浅色");
    lang_dark("深色");
    lang_openSideBar("开启");
    lang_compactSideBar("紧凑");
    lang_minimalSideBar("最小化");
    lang_automatical("自动");
}
