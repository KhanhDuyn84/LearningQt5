import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    id: root
    visible: true
    width: (400)
    height: (400)
    title: qsTr("Hello World")
    onWidthChanged: {
        if(root.width === Screen.width || root.width === Screen.height)
        {
            console.info("===========ORIENTATION CHANGED===========");
            console.info("Screem DPI:", screenDpi);
            console.info("Screen Width:", Screen.width);
            console.info("Screen Height:", Screen.height);
            console.info("Width:", root.width);
            console.info("Height:", root.height);
            console.info("=========================================");
        }
    }

    property real contentScaleFactor: screenDpi / 160
    property real textScale: 1.0
    function dp(value) {
        return value * contentScaleFactor;
    }

    function sp(value) {
        return value * contentScaleFactor * textScale;
    }

    Component.onCompleted: {
        console.info("Screem DPI:", screenDpi);
        console.info("Screen Width:", Screen.width);
        console.info("Screen Height:", Screen.height);
        console.info("Width:", root.width);
        console.info("Height:", root.height);
    }

    Image {
        anchors.centerIn: parent
        source: resourceManager.getImagePath("Cat");
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            notificationClient.notification = "Hello, I'm a rectangle"
        }
        onPressed: parent.scale = 0.9
        onReleased: parent.scale = 1.0
    }

}
