import QtQuick 2.12

Item{
    id: mainShowArea
    readonly property int circleSize: 10
    readonly property int fillRectWidth: 90
    Rectangle{
        id: leftPosition
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: circleSize
        radius: width/2
        color: "#BDBDBD"
        Rectangle{
            id: leftSlider
            x: 0
            y: (parent.height-height)/2
            width: circleSize
            height: circleSize
            radius: width/2
            color: "#0489B1"
        }
        MouseArea{
            anchors.fill: parent
            onPositionChanged: {
                leftSlider.y = mouseY-leftSlider.height/2
                //bezierLine.requestPaint()
                sankeyId.requestPaint()
            }
        }
    }
    Rectangle{
        id: rightPosition
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: circleSize
        radius: width/2
        color: "#BDBDBD"
        Rectangle{
            id: rightSlider
            x: 0
            y: (parent.height-height)/2
            width: circleSize
            height: circleSize
            radius: width/2
            color: "#0489B1"
        }
        MouseArea{
            anchors.fill: parent
            onPositionChanged: {
                rightSlider.y = mouseY-rightSlider.height/2
                //bezierLine.requestPaint()
                sankeyId.requestPaint()
            }
        }
    }
    Rectangle{
        id: center
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: leftPosition.right
        anchors.right: rightPosition.left
        //Component.onCompleted: print("center:",x,y,width,height)
        Rectangle{
            id: topControlPoint
            x: (parent.width-width)/2
            y: 0
            z: 1
            width: circleSize
            height: circleSize
            radius: circleSize/2
            color: "#FFBF00"
        }

        Rectangle{
            id: bottomControlPoint
            x: (parent.width-width)/2
            y: parent.height-height
            z: 1
            height: circleSize
            width: circleSize
            radius: circleSize/2
            color: "#01A9DB"
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                if (mouseY <= leftSlider.y+leftSlider.height/2){
                    topControlPoint.x=mouseX-topControlPoint.width/2
                    topControlPoint.y=mouseY-topControlPoint.width/2
                }
                else{
                    bottomControlPoint.x=mouseX-bottomControlPoint.width/2
                    bottomControlPoint.y=mouseY-bottomControlPoint.width/2
                }
                bezierLine.requestPaint()
            }
        }
        SingleSankeyLine{
            id: sankeyId
            anchors.fill: parent
            lineWidth: 80
            endPoint: Qt.point(width, rightSlider.y+rightSlider.height/2)
            startPoint: Qt.point(0, leftSlider.y+leftSlider.height/2)
            painting: true
        }
    }
}

