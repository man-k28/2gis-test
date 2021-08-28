import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQml 2.15
import QtCharts 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("2Gis-test")

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            _2Gis_ModelsFacade.reload(fileDialog.fileUrl, maxWords.value)
        }
    }

    Column {
        width: parent.width
        height: parent.height
        Row {
            width: parent.width
            id: panel
            spacing: 10
            ProgressBar {
                id: progressBar
                width: parent.width - tbLoad.width - maxWords.width - elapsedTime.width - parent.spacing * 3
                to: 100
                from: 0
                anchors.verticalCenter: panel.verticalCenter

            }
            Label {
                id: elapsedTime
                anchors.verticalCenter: panel.verticalCenter
            }

            SpinBox {
                id: maxWords
                to: 100
                value: 15
                from: 1
                editable: true
            }

            ToolButton {
                id: tbLoad
                text: qsTr("Load")
                onClicked: {
                    fileDialog.visible = true
                    enabled = false
                }
            }
        }


        ChartView {
            id: chart
            title: qsTr("Top-%1 useful words").arg(maxWords.value)
            width: parent.width
            height: parent.height - panel.height
            legend.visible: false
            antialiasing: true
            Connections{
                target: _2Gis_ModelsFacade.primaryModel
                function onReady(millisecs)
                {
                    elapsedTime.text = qsTr("%1 мс").arg(millisecs)
                    series.clear()
                    var data = _2Gis_ModelsFacade.getData();
                    for(var i = 0; i < data.length; ++i) {
                        var element = data[i]
                        var slice = series.append(element.word, element.count)
                        slice.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
                        slice.label = qsTr("%1 (%2)").arg(element.word).arg(element.count)
                        slice.labelVisible = true
                    }
                    tbLoad.enabled = true
                }

                function onProgress(value) {
                    progressBar.value = value
                }
            }
            PieSeries {
                id: series
            }
        }



//        ListView {
//            id: listView
//            width: parent.width
//            height: parent.height - panel.height
//            clip: true
//            model: _2Gis_ModelsFacade.proxyModel
//            headerPositioning: ListView.OverlayHeader
//            boundsBehavior: Flickable.StopAtBounds
//            flickableDirection: Flickable.HorizontalAndVerticalFlick
//            cacheBuffer: 50
//            spacing: 10

//            delegate: Item {
//                id: rowDelegate
//                width: listView.width
//                height: 20

//                readonly property var rowEntry: model
//                readonly property int rowIndex: index
//                Row {
//                    width: parent.width
//                    height: parent.height
//                    spacing: 30
//                    Label {
//                        text: rowEntry.word
//                    }
//                    Label {
//                        text: rowEntry.count
//                    }
//                }
//            }
//        }
    }

}
