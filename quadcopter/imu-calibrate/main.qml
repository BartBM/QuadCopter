import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("IMU calibrate")

    function round(value, decimals) {
        if (decimals < 1) decimals = 1;
        return Math.round(value * Math.pow(10, decimals)) / Math.pow(10, decimals)
    }

    Connections {
        target: chartData
        onChartDataChanged: {
            console.log("data received");
        }

        /*
        target: calibration
        onMinMaxAxisValuesChanged: {
//            console.log("The application data changed!" +
//                                               calibration.getMinMaxAxisValues().getMinX() + "\n " +
//                                               calibration.getMinMaxAxisValues().getX() + "\n " +
//                                               calibration.getMinMaxAxisValues().getMaxX())
            if (calibration.getMinMaxAxisValues() !== null) {
                xAxisValues.minValue = round(calibration.getMinMaxAxisValues().getMinX(), 2)
                xAxisValues.axisValue = round(calibration.getMinMaxAxisValues().getX(), 2)
                xAxisValues.maxValue = round(calibration.getMinMaxAxisValues().getMaxX(), 2)
                liveChart.axisX.min = calibration.getMinMaxAxisValues().getMinX();


                yAxisValues.minValue = round(calibration.getMinMaxAxisValues().getMinY(), 2)
                yAxisValues.axisValue = round(calibration.getMinMaxAxisValues().getY(), 2)
                yAxisValues.maxValue = round(calibration.getMinMaxAxisValues().getMaxY(), 2)

                zAxisValues.minValue = round(calibration.getMinMaxAxisValues().getMinZ(), 2)
                zAxisValues.axisValue = round(calibration.getMinMaxAxisValues().getZ(), 2)
                zAxisValues.maxValue = round(calibration.getMinMaxAxisValues().getMaxZ(), 2)
            }
        }
        */
    }

    GridLayout {
        id: grid
        width: 160
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        layoutDirection: Qt.LeftToRight
        rows: 3
        columns: 1
        flow: GridLayout.TopToBottom

        MinMaxCalibrationAxis {
            id: xAxisValues
            Layout.fillHeight: false
            Layout.fillWidth: false
            minText: 'min x'
            axisText: 'x'
            maxText: 'max x'
        }

        MinMaxCalibrationAxis {
            id: yAxisValues
            minText: 'min y'
            axisText: 'y'
            maxText: 'max y'
        }

        MinMaxCalibrationAxis {
            id: zAxisValues
            minText: 'min z'
            axisText: 'z'
            maxText: 'max z'
        }
    }

    LiveChart {
        id: liveChart
        anchors.rightMargin: 15
        anchors.bottomMargin: 15
        anchors.topMargin: 15
        anchors.left: grid.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.leftMargin: 180
        clip: false
    }
}
