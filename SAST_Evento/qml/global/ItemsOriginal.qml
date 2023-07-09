pragma Singleton

import QtQuick
import FluentUI

Loader {
    id: loader
    source: ""

    property int identity

    onIdentityChanged: {
        if (identity === 1) {
            // 管理员
            loader.source = "qrc:/SAST_Evento/qml/global/ItemsOriginal_manager.qml"
        } else {
            // 用户
            loader.source = "qrc:/SAST_Evento/qml/global/ItemsOriginal_usr.qml"
        }
    }

    function getRecentlyAddedData() {
        var arr = []
        for (var i = 0; i < loader.item.children.length; i++) {
            var item = children[i]
            if (item instanceof FluPaneItem && item.recentlyAdded) {
                arr.push(item)
            }
            if (item instanceof FluPaneItemExpander) {
                for (var j = 0; j < item.children.length; j++) {
                    var itemChild = item.children[j]
                    if (itemChild instanceof FluPaneItem
                            && itemChild.recentlyAdded) {
                        arr.push(itemChild)
                    }
                }
            }
        }
        arr.sort(function (o1, o2) {
            return o2.order - o1.order
        })
        return arr
    }

    function getRecentlyUpdatedData() {
        var arr = []
        var items = loader.item.navigationView.getItems()
        for (var i = 0; i < items.length; i++) {
            var item = items[i]
            if (item instanceof FluPaneItem && item.recentlyUpdated) {
                arr.push(item)
            }
        }
        return arr
    }

    function getSearchData() {
        var arr = []
        var items = loader.item.navigationView.getItems()
        for (var i = 0; i < items.length; i++) {
            var item = items[i]
            if (item instanceof FluPaneItem) {
                arr.push({
                             "title": item.title,
                             "key": item.key
                         })
            }
        }
        return arr
    }

    function startPageByItem(data) {
        loader.item.navigationView.startPageByItem(data)
    }
}
