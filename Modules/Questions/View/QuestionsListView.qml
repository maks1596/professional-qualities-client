import QtQuick 2.6
import QtQuick.Controls 2.0

import "../../../Forms"

Rectangle {
    id: backgroundRectangle

    SystemPalette { id: palette; colorGroup: SystemPalette.Active }
    color: palette.window

    ListView {
        spacing: 20

        anchors.fill: parent

        model: questionsModel // This is available in all editors.
        delegate: QuestionView {
            text: model.questionFormulation
            width: parent.width
        }

        ScrollBar.vertical: ScrollBar{}
    }
}
