import QtQuick 2.12
import PassengerFlowCount 1.0

Item{
    id: sankeyId
    property var lineInterval: 13 // 柱体间的 纵向间隔
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

    function createSankeyLine(xPos, linewidth, linecolor, leftStartY, rightEndY){
        if (isNaN(linewidth) || linewidth === 0 || isNaN(leftStartY) || isNaN(rightEndY)){
            print("linewidth is 0")
            return null
        }

        var component = Qt.createComponent("qrc:/SingleSankeyLine.qml")
        if (component.status === Component.Ready){
            var obj = component.createObject(sankeyId, {x: xPos, y: 0, width: sankeyId.width/2, height: sankeyId.height,
                                                                    lineWidth: linewidth,
                                                                    lineColor: linecolor
                                                                })
            obj.startPoint = Qt.point(0, leftStartY)
            obj.endPoint = Qt.point(obj.width, rightEndY)
            return obj
        }
        else if (component.status === Component.Error){
            print(paintedHour,"create 0-20 male Component error:", component.errorString())
        }
        return null
    }

    function paintSankey(){

        paintCoor.reset()
        // 每个人在性别一列所表示的柱体高度(曲线宽度)
        var oneHeight_sex = 0
        if (passengerFlowObj.femaleCt===0 || passengerFlowObj.maleCt===0)
            oneHeight_sex = sankeyId.height/(passengerFlowObj.femaleCt + passengerFlowObj.maleCt)
        else
            oneHeight_sex = (sankeyId.height-sankeyId.lineInterval) /(passengerFlowObj.femaleCt + passengerFlowObj.maleCt)

        paintCoor.femaleNextItemY = passengerFlowObj.maleCt === 0 ? 0 : passengerFlowObj.maleCt * oneHeight_sex + lineInterval


        var singleTimeLineEndY = 0 // 性别到时间柱体

        var ageHeight = (height-lineInterval*(Object.keys(passengerFlowObj.ageCountMap).length-1))/(passengerFlowObj.femaleCt + passengerFlowObj.maleCt)
        print("ageHeight:", ageHeight)
        var ageEndYList = []
        ageEndYList.push(0)
        if (passengerFlowObj.ageCountMap.hasOwnProperty("20")){
            ageEndYList.push(ageEndYList[ageEndYList.length-1] + passengerFlowObj.ageCountMap["20"]*ageHeight + sankeyId.lineInterval)
        }
        else{
            ageEndYList.push(ageEndYList[ageEndYList.length-1])
        }

        if (passengerFlowObj.ageCountMap.hasOwnProperty("40")){
            ageEndYList.push(ageEndYList[ageEndYList.length-1] + passengerFlowObj.ageCountMap["40"]*ageHeight + sankeyId.lineInterval)
        }
        else{
            ageEndYList.push(ageEndYList[ageEndYList.length-1])
        }

        if (passengerFlowObj.ageCountMap.hasOwnProperty("60")){
            ageEndYList.push(ageEndYList[ageEndYList.length-1] + passengerFlowObj.ageCountMap["60"]*ageHeight + sankeyId.lineInterval)
        }
        else{
            ageEndYList.push(ageEndYList[ageEndYList.length-1])
        }

        // 时间范围 // Object.keys(passengerFlowObj.ageMap).length
        for (var hourIndex=10; hourIndex < 22 ; ++hourIndex){
            var timeEndY = singleTimeLineEndY // 时间到年龄柱体
            var oneHeight_time = 0

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

            print(paintedHour,"hour sex:", theHourFemale, theHourMale)
            // 男->时间线 "#01A9DB"
            var maleToTimeLineObj = createSankeyLine(0, theHourMale*oneHeight_sex, "#16CEB9", paintCoor.maleNextItemY,
                                                     singleTimeLineEndY)
            if (maleToTimeLineObj !== null){
                maleToTimeLineObj.fresh()
                singleTimeLineEndY += maleToTimeLineObj.lineWidth
                oneHeight_time = (singleTimeLineEndY-timeEndY)/(theHourFemale + theHourMale)
                paintCoor.maleNextItemY += maleToTimeLineObj.lineWidth
                paintCoor.leftLines.push(maleToTimeLineObj)
            }

            // 女-> 时间线
            var femaleToTimeLineObj = createSankeyLine(0, theHourFemale*oneHeight_sex, "#F7517F", paintCoor.femaleNextItemY,
                                                       singleTimeLineEndY)
            if (femaleToTimeLineObj !== null){
                femaleToTimeLineObj.fresh()
                singleTimeLineEndY += femaleToTimeLineObj.lineWidth
                oneHeight_time = (singleTimeLineEndY-timeEndY)/(theHourFemale + theHourMale)

                singleTimeLineEndY += lineInterval
                paintCoor.femaleNextItemY += femaleToTimeLineObj.lineWidth
                paintCoor.leftLines.push(femaleToTimeLineObj)
            }

            // {年龄
            var ageArray=["20", "40", "60", "100"]
            var ageColor=["#0080FF","#FFE96C", "#58FA58", "#FF9105"]

            for (var ageIndex = 0; ageIndex < ageArray.length; ++ageIndex){

                var lineWidth = passengerFlowObj.ageMap[paintedHour][ageArray[ageIndex]]*oneHeight_time

                var ageObj = createSankeyLine(sankeyId.width/2, lineWidth,
                                                   ageColor[ageIndex], timeEndY, ageEndYList[ageIndex])

                print(ageArray[ageIndex] ,oneHeight_time, lineWidth, isNaN(lineWidth), timeEndY, ageEndYList[ageIndex])
                if (ageObj !== null){
                    print(ageArray[ageIndex],"fresh")
                    ageObj.fresh()
                    timeEndY += lineWidth
                    ageEndYList[ageIndex] += lineWidth
                    paintCoor.rightLines.push(ageObj)
                }
            }
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
