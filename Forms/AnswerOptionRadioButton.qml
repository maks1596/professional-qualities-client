import QtQuick 2.6
import QtQuick.Controls 2.0

RadioButton {
    property string name: "AnswerOptionRadioButton"

    SystemPalette { id: palette; colorGroup: SystemPalette.Active }
    property color downColor: palette.buttonText
    property color defaultColor: palette.text

    id: control
    text: "Answer option"

    indicator: Rectangle {
        implicitWidth: control.font.pointSize << 1
        implicitHeight: implicitWidth

        smooth: true

        x: control.leftPadding
        y: (parent.height - height) >> 1

        radius: implicitWidth >> 1
        border.color: control.down ? control.downColor : control.defaultColor

        Rectangle {
            width: 12
            height: 12
            anchors.centerIn: parent
            radius: 6
            color: answerOptionRadioButton.down ? answerOptionRadioButton.downColor : answerOptionRadioButton.defaultColor
            visible: answerOptionRadioButton.checked
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        renderType: Text.NativeRendering

        color: control.down ? control.downColor : control.defaultColor

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        leftPadding: control.indicator.width + control.spacing
    }
}
