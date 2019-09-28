import QtQuick 2.12
import PassengerFlowCount 1.0

Item{
    id: sankeyId
    property var lineInterval: 3 // 柱体间的 纵向间隔
    QtObject{
        id: paintCoor
        property var maleNextItemY: 0 // 下一条曲线的y轴坐标
        property var femaleNextItemY: 0 // 下一条曲线的y轴坐标
        property var timeNextItemY: 0
        property var ageNextItemY: 0
        property var leftLines: []
        property var rightLines: []
        function reset(){
            maleNextItemY = 0 // 下一条曲线的y轴坐标
            femaleNextItemY = 0 // 下一条曲线的y轴坐标
            timeNextItemY = 0
            ageNextItemY = 0
            for (var leftLine in paintCoor.leftLines){
                paintCoor.leftLines[leftLine].visible = false
                paintCoor.leftLines[leftLine].destroy()
            }

            for (var rightLine in paintCoor.rightLines){
                paintCoor.rightLines[rightLine].visible = false
                paintCoor.rightLines[rightLine].destroy()
            }

            paintCoor.leftLines.splice(0, paintCoor.leftLines.length)
            paintCoor.rightLines.splice(0, paintCoor.rightLines.length)

        }
    }

    function paintSankey(){

        paintCoor.reset()

        // 每个人所表示的柱体高度(曲线宽度)
        var oneHeight = (height-lineInterval)/(passengerFlowObj.femaleCt + passengerFlowObj.maleCt)
        paintCoor.femaleNextItemY = passengerFlowObj.maleCt * oneHeight + lineInterval
        print("oneHeight:", height, oneHeight, Object.keys(passengerFlowObj.ageMap).length)

        var singleTimeLineEndY = 0
        // 时间范围 // Object.keys(passengerFlowObj.ageMap).length
        for (var hourIndex=10; hourIndex<=22 ; ++hourIndex){

            var paintedHour = (hourIndex).toString() // 当前正在绘制的时间点
            var theHourMale = 0
            var theHourFemale = 0

            if (!passengerFlowObj.sexMap.hasOwnProperty(paintedHour)){
                continue
            }

            if (passengerFlowObj.sexMap[paintedHour].hasOwnProperty("male")){
                theHourMale = passengerFlowObj.sexMap[paintedHour]["male"]
            }

            if (passengerFlowObj.sexMap[paintedHour].hasOwnProperty("female")){
                theHourFemale = passengerFlowObj.sexMap[paintedHour]["female"]
            }

            print(paintedHour," hour sex:", theHourFemale, theHourMale)
            // 男->时间线
            var maleComponent = Qt.createComponent("qrc:/SingleSankeyLine.qml")
            if (maleComponent.status === Component.Ready){
                var maleSankeyLine = maleComponent.createObject(sankeyId, {x: 0, y: 0, width: sankeyId.width/2,
                                                                    height: sankeyId.height,
                                                                    lineWidth: theHourMale*oneHeight,
                                                                    lineColor: "#81DAF5",
                                                                    hightLightColor: "#01A9DB"
                                                                })
                maleSankeyLine.startPoint = Qt.point(0, paintCoor.maleNextItemY)
                maleSankeyLine.endPoint = Qt.point(maleSankeyLine.width, singleTimeLineEndY)

                singleTimeLineEndY += maleSankeyLine.lineWidth
                paintCoor.maleNextItemY += maleSankeyLine.lineWidth

                maleSankeyLine.fresh()
                paintCoor.leftLines.push(maleSankeyLine)
            }
            else if (maleComponent.status === Component.Error){
                print("hour:", paintedHour," create male component error:", maleComponent.errorString())
            }

            // 女-> 时间线
            var femaleComponent = Qt.createComponent("qrc:/SingleSankeyLine.qml")
            if (femaleComponent.status === Component.Ready){
                var femaleSankeyLine = femaleComponent.createObject(sankeyId, {x: 0, y: 0,
                                                                        width: sankeyId.width/2, height: sankeyId.height,
                                                                        lineWidth: theHourFemale*oneHeight,
                                                                        lineColor: "#F7819F",
                                                                        hightLightColor: "#FE2E64",
                                                                    })
                print(paintCoor.femaleNextItemY)
                femaleSankeyLine.startPoint = Qt.point(0,  paintCoor.femaleNextItemY)
                femaleSankeyLine.endPoint = Qt.point(sankeyId.width/2, singleTimeLineEndY)
                femaleSankeyLine.fresh()
                paintCoor.femaleNextItemY += femaleSankeyLine.lineWidth
                singleTimeLineEndY += femaleSankeyLine.lineWidth + lineInterval
                paintCoor.leftLines.push(femaleSankeyLine)
            }
            else if (femaleComponent.status === Component.Error){
                print("hour:", paintedHour," create female component error:", femaleComponent.errorString())
            }

            // {年龄
            // 男 0-20

        }
    }

    PassengerFlowCount{
        id: passengerFlowObj
        onDataChanged: {
            paintSankey()
        }
    }

    Component.onCompleted: {
        visible = passengerFlowObj.initEnvironment()
    }
}

