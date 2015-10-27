import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Column {
    property string zegmaar: "ah"
    //width: parent.width / 3
    //height: parent.height

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            width: 50
            text: "Min X"
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: minX
            width: textLength
            anchors.left: parent.Center
        }
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        Label {
            text: qsTr("Max X")
            width: 50
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: maxX
            width: textLength
        }
    }
}

