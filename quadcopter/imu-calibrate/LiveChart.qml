import QtQuick 2.11
import QtCharts 2.2

ChartView {

    anchors.fill: parent
    antialiasing: true

    property int counter : 0

    Connections {

        target: chartData
        onChartDataChanged: {
            console.log("data received");
        }

        /*
        target: calibration
        onMinMaxAxisValuesChanged: {
            if (calibration.getMinMaxAxisValues() !== null) {
                axisY.min = calibration.getMinMaxAxisValues().getMinX() - 1;
                axisY.max = calibration.getMinMaxAxisValues().getMaxX() + 1;
                xSeries.append(counter, calibration.getMinMaxAxisValues().getX());

                counter++;
                if (counter > 500) {
                    xSeries.remove(0);
                    axisX.min = counter - 500;
                    axisX.max = counter;
                }
            }
        }*/
    }

    ValueAxis {
       id: axisX
       min: 0
       max: 500
    }

    ValueAxis {
        id: axisY
        min: -16384
        max: 16384
        gridVisible: false
        color: "#000000"
        labelsColor: "#000000"
        labelFormat: "%.0f"
    }

    LineSeries {
        id: xSeries
        color: "red"
        axisX: axisX
        axisY: axisY
        useOpenGL: true
    }
}
