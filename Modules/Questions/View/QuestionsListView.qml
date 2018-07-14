import QtQuick 2.0

ListView {
    spacing: 10
    bottomMargin: 10

    model: questionsModel // This is available in all editors.
    delegate: Column {
        id: contentColumn

        width: parent.width
        height: questionFormulationText.height + answerOptionsFlow.height
        spacing: 10

        Text {
            id: questionFormulationText

            width: parent.width
            font.pointSize: 10
            renderType: Text.NativeRendering
            wrapMode: Text.WordWrap

            text: model.questionFormulation
        }

        Flow {
            id: answerOptionsFlow

            spacing: 10
            property var answersModel: model.answers

            Repeater {
                model: answerOptionsFlow.answersModel
                delegate: Text {
                    renderType: Text.NativeRendering
                    text: model.display
                    wrapMode: Text.WordWrap

                    MouseArea {
                        anchors.fill: parent
                        onClicked: model.answerIndex = model.index;
                    }
                }
            }
        }
    }
}
