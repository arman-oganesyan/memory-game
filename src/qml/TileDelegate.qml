import QtQuick 2.0

Item {
    id: root

    property bool showCard: false
    property bool matchedCard: false
    property color color: "#ffddd3"
    property color hoverColor: "#f3bfb3"
    property bool cardHovered: mouseArea.containsMouse && !matchedCard && !showCard

    height: grid.cellHeight
    width: grid.cellWidth

    onShowCardChanged: animation.start()

    state: matchedCard ? "matched" : "not_matched"
    states: [
        State {
            name: "matched"
            PropertyChanges { target: card; opacity: 0.2 }
        }
    ]


    Rectangle {
        id: card
        anchors.fill: parent
        anchors.margins: 5
        color: cardHovered ? root.hoverColor : root.color
        radius: 8

        Behavior on opacity {
            NumberAnimation { duration: 1500 }
        }

        Image {
            id: img
            source: "qrc:///img/" + id + "-unicorn.png"
            anchors.fill: parent
            opacity: 0
            fillMode: Image.PreserveAspectFit
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
                property: "opacity"
                value: root.showCard ? 0 : 1
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
            id: mouseArea
            anchors.fill: parent
            anchors.margins: 5
            hoverEnabled: true
            onClicked: {
                gameModel.processClicked(index)
            }
        }
    }
}
