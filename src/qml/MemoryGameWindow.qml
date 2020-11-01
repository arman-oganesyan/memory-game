import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.3

Window {
    id: root
    visible: true
    width: 1280
    height: 720
    title: qsTr("Memory Game")

    MessageDialog {
        id: dialogReset
        title: qsTr("Confirm action")
        text: qsTr("Do you want to reset? You will lost all the progress")
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: gameModel.start()
    }

    MainHeader {
        id: mainHeader
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5
        height: 40

        onResetClicked: dialogReset.open()
    }

    GridView {
        id: grid
        anchors.top: mainHeader.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        cellWidth: width / gameModel.dimension
        cellHeight: height / gameModel.dimension
        model: gameModel

        delegate: TileDelegate {
            showCard: open
            matchedCard: matched
        }

        Text {
            anchors.fill: parent
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
            font.pixelSize: 50
            font.bold: true
            visible: gameModel.gameFinished
            text: qsTr('Finished!\nPress \'Reset\' to play again!')
        }
    }
}
