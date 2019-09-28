import QtQuick 2.12

Canvas{
    property string lineColor: "#000000"
    property string hightLightColor: ""
    property var lineWidth: 1.0
    property var startPoint: Qt.point(0,0)
    property var endPoint: Qt.point(width, height)
    property var slope: 0.65
    property var painting: false
    opacity: 0.5
//    onHightLightColorChanged: {
//        requestPaint()
//    }

//    onSlopeChanged: {
//        requestPaint()
//    }
    function fresh(){
        painting = true
        requestPaint()
    }

    onPaint: {
        if (!painting){
            return
        }

        var ctx = getContext("2d")
        ctx.reset()
        if (hightLightColor.length>0){
            ctx.strokeStyle = hightLightColor
            ctx.fillStyle = hightLightColor
        }
        else{
            ctx.strokeStyle = lineColor
            ctx.fillStyle = lineColor
        }

        ctx.lineWidth=1
        ctx.beginPath()
        ctx.moveTo(startPoint.x, startPoint.y)
        ctx.quadraticCurveTo((endPoint.x-startPoint.x)*slope, startPoint.y, endPoint.x, endPoint.y)
        ctx.lineTo(endPoint.x, endPoint.y+lineWidth)
        ctx.quadraticCurveTo((endPoint.x-startPoint.x)*slope, startPoint.y+lineWidth, startPoint.x, startPoint.y+lineWidth)

        ctx.stroke()
        ctx.fill()
        ctx.closePath()


    }
}

