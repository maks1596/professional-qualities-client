import QtQuick 2.0

Rectangle {
    property string name: "QuestionView"
    property alias text: formulationText.text

    border.color: "lightgray"
    border.width: 2

    height: contentColumn.height

    Column {
        id: contentColumn

        width: parent.width

        Text {
            id: formulationText

            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 10
            anchors.margins: 20

            font.pointSize: 10
            renderType: Text.NativeRendering
            wrapMode: Text.WordWrap

            text: "Question view"
        }

        AnswerOptionsButtonGroup {
            questionModel: model
            answerIndex: model.answerIndex
            width: parent.width
        }
    }
}
