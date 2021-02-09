import QtQuick 2.6
import Sailfish.Silica 1.0

ApplicationWindow {
    cover: Qt.resolvedUrl("cover.qml")

    initialPage: Page {
        allowedOrientations: Orientation.LandscapeMask

        Label {
            anchors.centerIn: parent
            text: "Hello, Aurora!"
        }

    }

}
