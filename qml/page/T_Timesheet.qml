import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import FluentUI

FluScrollablePage {
    launchMode: FluPageType.SingleTask
    title: lang.lang_timesheet
    Layout.fillWidth: true

    FluCalendarPicker {
        id: calendar
    }
}
