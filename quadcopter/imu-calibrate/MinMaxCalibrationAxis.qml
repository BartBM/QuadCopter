import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {

    width: 180
    height: 100

    property string minText: "min x"
    property string axisText: "x"
    property string maxText: "max x"
    property real minValue: 1
    property real axisValue: 100.2
    property real maxValue: 21.33

    GridLayout {
        rows: 3
        columns: 2
        anchors.fill: parent
        clip: true

        Label {
            text: minText
        }
        Rectangle {
            color: "#d2d2d2"
            Label {
                text: minValue
                color: 'red'
                width:parent.parent.width/2
                horizontalAlignment: Text.AlignHCenter
            }
            height: childrenRect.height
            width: childrenRect.width
        }
        Label {
            text: axisText
        }
        Rectangle {
            color: "#d2d2d2"
            Label {
                text: axisValue
                color: 'blue'
                width:parent.parent.width/2
                horizontalAlignment: Text.AlignHCenter
            }
            height: childrenRect.height
            width: childrenRect.width
        }
        Label {
            text: maxText
        }
        Rectangle {
            color: "#d2d2d2"
            Label {
                text: maxValue
                color: 'green'
                width:parent.parent.width/2
                horizontalAlignment: Text.AlignHCenter
            }
            height: childrenRect.height
            width: childrenRect.width
        }
    }
}
