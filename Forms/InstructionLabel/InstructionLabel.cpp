#include "InstructionLabel.h"


//  :: Constants ::

const QString DEFAULT_WINDOW_TITLE = "Инструкция";
const int INSTRUCTION_MARGIN = 10;

//  :: Lifecycle ::

InstructionLabel::InstructionLabel(QWidget *parent)
    : InstructionLabel(QString(), parent)
{ }

InstructionLabel::InstructionLabel(const QString &instruction,
                                   QWidget *parent)
    : InstructionLabel(DEFAULT_WINDOW_TITLE, instruction, parent)
{ }

InstructionLabel::InstructionLabel(const QString &testName,
                                   const QString &instruction,
                                   QWidget *parent)
    : QLabel(instruction, parent)
{
    setWindowTitle(testName);
    setWordWrap(true);
    setMargin(INSTRUCTION_MARGIN);
}
