import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Rectangle{
        anchors.fill: parent

        Test_Sankey2Pt{
            id: testSankeyId
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width/3
        }
        Rectangle{
            anchors.left: testSankeyId.right
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: parent.height/2
            //color: "#F5D0A9"
            PassengerFlowCount{
                anchors.fill: parent
            }
        }
    }
}
