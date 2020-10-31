import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Memory Game")

    GridView {
        id: grid
        anchors.fill: parent
        cellWidth: width / 10
        cellHeight: height / 10
        model: 100

        delegate: Item {
            height: grid.cellHeight
            width: grid.cellWidth


            Rectangle {
                id: card
                anchors.fill: parent
                anchors.margins: 5
                color: "#fae596"
                radius: 5

                Image {
                    id: img
                    visible: false
                    source: "https://icon-library.net/images/50x50-icon/50x50-icon-0.jpg";
                    anchors.fill: parent
                }

                transform: Rotation {
                    id: rotation
                    origin.x: (card.width / 2)
                    origin.y: (card.height / 2)
                    axis {
                        x: 0
                        y: 1
                        z: 0
                    }
                    angle: 0
                }

                SequentialAnimation {
                    id: animation

                    PropertyAnimation {
                        id: rotate_away
                        target: rotation
                        properties: "angle"
                        from: 0
                        to: 90
                        duration: 250
                    }

                    PropertyAction {
                        target: img
                        property: "visible"
                        value: !img.visible
                    }

                    PropertyAnimation {
                        id: rotate_new
                        target: rotation
                        properties: "angle"
                        from: -90
                        to: 0
                        duration: 250
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    anchors.margins: 5
                    onClicked: {
                        animation.start();
                    }
                }
            }
        }
    }

    //    Grid {
    //        width: parent.width
    //        height: parent.height

    //        rows: 10
    //        columns: 10
    //        rowSpacing: 2
    //        columnSpacing: 2

    //        Repeater {
    //            id: rowRepeater

    //            model: parent.rows * parent.columns

    //            delegate: Rectangle {

    //                width: parent.width / parent.rows
    //                height: parent.height / parent.columns
    //                color: "red"

    //                Text {
    //                    anchors.fill: parent
    //                    text: qsTr("text")
    //                }
    //            }
    //        }

    //    }


}
