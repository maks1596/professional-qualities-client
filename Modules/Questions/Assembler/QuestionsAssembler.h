#pragma once

#include <utility>

class QWidget;
class QuestionsForm;
class Test;
class IQuestionsOutput;

namespace QuestionsAssembler {
    std::tuple<QuestionsForm *, IQuestionsOutput *> assembly(const Test &test,
                                                             QWidget *parent = nullptr);
}
