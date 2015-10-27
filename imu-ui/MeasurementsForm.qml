import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    property int textLength: 100
    height: 75

    Grid {
        columns: 3
        rows: 1
        anchors.fill: parent

        MinMaxOutput {
            zegmaar: qsTr("jop")
        }

        MinMaxOutput {
            zegmaar: qsTr("jop")
        }

        MinMaxOutput {
            zegmaar: qsTr("jop")
        }
    }
}
