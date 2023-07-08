pragma Singleton

import QtQuick
import FluentUI

FluObject{

    property var navigationView

    FluPaneItem{
        id:item_home
        count: 9
        title:lang.home
        infoBadge:FluBadge{
            count: item_home.count
        }
        icon:FluentIcons.Home
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_home.count = 0
            }
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Home.qml")
        }
    }

    FluPaneItem{
        id:item_timeTable
        count: 9
        title:lang.timeTable
        infoBadge:FluBadge{
            count: item_timeTable.count
        }
        icon:FluentIcons.Calendar
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_home.count = 0
            }
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Home.qml")
        }
    }

    FluPaneItem{
        id:item_history
        count: 0
        title:lang.history
        infoBadge:FluBadge{
            count: item_history.count
        }
        icon:FluentIcons.Replay
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_home.count = 0
            }
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Home.qml")
        }
    }

    FluPaneItem{
        id:item_souvenirCard
        count: 0
        title:lang.souvenirCard
        infoBadge:FluBadge{
            count: item_souvenirCard.count
        }
        icon:FluentIcons.Smartcard
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_home.count = 0
            }
            navigationView.push("qrc:/SAST_Evento/qml/page/T_SouvenirCard.qml")
        }
    }

    FluPaneItemExpander{
        title:lang.organize
        icon:FluentIcons.AllApps
        FluPaneItem{
            title:"TextBox"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_TextBox.qml")
            }
        }
        FluPaneItem{
            title:"TimePicker"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_TimePicker.qml")
            }
        }
        FluPaneItem{
            title:"DatePicker"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_DatePicker.qml")
            }
        }
        FluPaneItem{
            title:"CalendarPicker"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_CalendarPicker.qml")
            }
        }
        FluPaneItem{
            title:"ColorPicker"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_ColorPicker.qml")
            }
        }
    }

    FluPaneItemExpander{
        title:lang.manage
        icon:FluentIcons.ViewAll
        FluPaneItem{
            title:"InfoBar"
            image:"qrc:/SAST_Evento/res/image/control/InfoBar.png"
            recentlyUpdated:true
            desc:"An inline message to display app-wide statuschange information."
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_InfoBar.qml")
            }
        }
        FluPaneItem{
            title:"Progress"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Progress.qml")
            }
        }
        FluPaneItem{
            title:"RatingControl"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_RatingControl.qml")
            }
        }
        FluPaneItem{
            title:"Badge"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Badge.qml")
            }
        }
        FluPaneItem{
            title:"Rectangle"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Rectangle.qml")
            }
        }
        FluPaneItem{
            title:"StatusView"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_StatusView.qml")
            }
        }
        FluPaneItem{
            title:"Carousel"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Carousel.qml")
            }
        }
        FluPaneItem{
            title:"Expander"
            onTap:{
                navigationView.push("qrc:/SAST_Evento/qml/page/T_Expander.qml")
            }
        }
    }

    FluPaneItem{
        id:item_theming
        title:lang.theming
        infoBadge:FluBadge{
            count: 0
        }
        icon:FluentIcons.Brightness
        onTap:{
            navigationView.push("qrc:/SAST_Evento/qml/page/T_Theme.qml")
        }
    }

    function getRecentlyAddedData(){
        var arr = []
        for(var i=0;i<children.length;i++){
            var item = children[i]
            if(item instanceof FluPaneItem && item.recentlyAdded){
                arr.push(item)
            }
            if(item instanceof FluPaneItemExpander){
                for(var j=0;j<item.children.length;j++){
                    var itemChild = item.children[j]
                    if(itemChild instanceof FluPaneItem && itemChild.recentlyAdded){
                        arr.push(itemChild)
                    }
                }
            }
        }
        arr.sort(function(o1,o2){ return o2.order-o1.order })
        return arr
    }

    function getRecentlyUpdatedData(){
        var arr = []
        var items = navigationView.getItems();
        for(var i=0;i<items.length;i++){
            var item = items[i]
            if(item instanceof FluPaneItem && item.recentlyUpdated){
                arr.push(item)
            }
        }
        return arr
    }

    function getSearchData(){
        var arr = []
        var items = navigationView.getItems();
        for(var i=0;i<items.length;i++){
            var item = items[i]
            if(item instanceof FluPaneItem){
                arr.push({title:item.title,key:item.key})
            }
        }
        return arr
    }

    function startPageByItem(data){
        navigationView.startPageByItem(data)
    }

}
