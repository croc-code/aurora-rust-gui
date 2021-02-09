import QtQuick 2.6
import Sailfish.Silica 1.0

CoverBackground {
    Rectangle {
        id: background

        anchors.fill: parent
        color: "blue"

        Label {
            id: label

            anchors.centerIn: parent
            text: "Rust GUI"
            color: "white"
        }

    }

    CoverActionList {
        id: coverAction

        CoverAction {
            iconSource: "image://theme/icon-cover-cancel"
            onTriggered: Qt.quit()
        }

    }

}
