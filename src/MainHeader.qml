import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    id: root

    signal resetClicked

    Text {
        id: textAttemptsTitle
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        horizontalAlignment: Qt.AlignLeft
        verticalAlignment: Qt.AlignVCenter
        font.pixelSize: 20
        width: contentWidth
        text: qsTr("Attempts:")
    }

    Text {
        id: textAttemptsNumber
        anchors.left: textAttemptsTitle.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        verticalAlignment: Qt.AlignVCenter
        horizontalAlignment: Qt.AlignRight
        font: textAttemptsTitle.font
        width: 40
        text: gameModel.attemptsNumber
    }

    Button {
        id: buttonStart
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height: 25
        font: textAttemptsTitle.font
        text: qsTr("Reset")
        onClicked: resetClicked()
    }
}
