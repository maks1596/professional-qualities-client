#pragma once

class QWidget;
class QuestionsForm;
class Test;

namespace QuestionsAssembler {
    QuestionsForm *assembly(const Test &test,
                            QWidget *parent = nullptr);
}
