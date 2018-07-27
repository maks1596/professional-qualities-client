#pragma once

#include <utility>

class QWidget;
class Test;
class IQuestionsOutput;

namespace QuestionsAssembler {
    std::tuple<QWidget *, IQuestionsOutput *> assembly(const Test &test,
                                                       QWidget *parent = nullptr);
}
