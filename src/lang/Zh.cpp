#include "Zh.h"

Zh::Zh(QObject* parent) : Lang{parent} {
    setObjectName("Zh");

    // MainWindow
    lang_hint("提示");
    lang_hint_info("SAST Evento已隐藏至托盘，点击托盘可再次激活窗口");
    lang_plaza("活动广场");
    lang_schedule("活动日程");
    lang_department_evento("部门活动");
    lang_calendar("日历");
    lang_manage("活动管理");
    lang_my("我的");
    lang_user_feedback("用户反馈");
    lang_theming("主题");
    lang_dark_mode("夜间模式");

    // Login
    lang_login("登录");
    lang_use_link("       使用 Link 登入");
    lang_login_failed("登录失败");
    lang_by_cpp("SAST-C++组开发\n");
    lang_visitor_login("访客登录");

    // Plaza
    lang_undertaking_evento("正在进行的活动");
    lang_latest_evento("最新的活动");

    // schedule
    lang_registered_evento("已报名的活动");
    lang_subscribed_evento("已订阅的活动");
    lang_feedback("反馈");
    lang_modify_feedback("修改反馈");
    lang_check_message("使用小程序扫描二维码或输入密钥");
    lang_check_hint("密钥请向讲师获取哦");

    // event info
    lang_undertaking("进行中");
    lang_not_started("未开始");
    lang_over("已结束");
    lang_cancelled("已取消");
    lang_checked_in("已签到");
    lang_check_in("签到");
    lang_subscribe("+订阅");
    lang_unsubscribe("取消订阅");
    lang_feedback_text("为本次活动打个分吧，你的反馈会被匿名上传哦");
    lang_feedback_hint("输入你的留言（选填，Ctrl+Enter换行）");
    lang_modify_and_submit("修改并提交");
    lang_submit("提交");
    lang_submit_success("提交成功");
    lang_register("报名");
    lang_cancellation("取消报名");
    lang_register_success("报名成功");
    lang_subscribe_hint("订阅后小程序将在活动开始前通知您");

    // my page
    lang_history("历史活动");
    lang_welcome("欢迎回来，");
    lang_souvenir_card("纪念卡");
    lang_profile("个人资料");

    // setting
    lang_settings("设置");
    lang_navigation_view_display_mode("导航视图显示模式");
    lang_followSystem("跟随系统");
    lang_light("浅色");
    lang_dark("深色");
    lang_locale("语言环境");
    lang_zh("中文");
    lang_en("英文");
    lang_openSideBar("开启");
    lang_compactSideBar("紧凑");
    lang_minimalSideBar("最小化");
    lang_automatical("自动");
    lang_check_update("检查更新");
    lang_native_text_rendering("Native文本渲染");
    lang_animation_effect("动画效果");

    // evento block
    lang_copy("复制");
    lang_get_qrcode("获取签到二维码");
    lang_edit_event("编辑活动");
    lang_cancel_event("取消活动");
    lang_delete_event("删除活动");
    lang_confirm_cancel("确认取消？该操作不可恢复！");
    lang_confirm_delete("确认删除？该操作不可恢复！");

    // other
    lang_cancel("取消");
    lang_exit("退出");
    lang_determine_exit("确定退出程序？");
    lang_ok("确定");
    lang_check_success("签到成功");
    lang_subscribe_success("订阅成功");
    lang_error("错误：");
    lang_input_is_empty("输入为空");
    lang_check_up_failure("检查更新错误: ");
    lang_reload("重新加载");
    lang_is_currently_latest_version("当前已是最新版本");
    lang_stay_tuned("敬请期待");
    lang_copy_success("已复制到剪切板");
    lang_move_up("上移一层");
    lang_move_down("下移一层");
    lang_loading("正在加载中...");
    lang_calendar_hint("右键活动卡片可调整层级");
}
