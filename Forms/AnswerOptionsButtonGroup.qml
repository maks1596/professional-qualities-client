import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    property string name: "AnswerOptionsButtonGroup"
    property var questionModel
    property int answerIndex

    height: answerOptionsFlow.height

    Flow {
        id: answerOptionsFlow

        width: parent.width

        Repeater {
            model: questionModel.answers
            delegate: AnswerOptionRadioButton {
                id: answerOptionRadioButton

                text: model.display
                font.pointSize: 10

                checked: answerIndex === model.index
                onClicked: questionModel.answerIndex = model.index
            }
        }
    }

    ButtonGroup {
        buttons: answerOptionsFlow.children
    }
}
