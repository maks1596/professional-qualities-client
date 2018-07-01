#include "QuestionsAssembler.h"

#include "../View/QuestionsForm.h"
#include "../Model/QuestionsModel.h"

QuestionsForm *QuestionsAssembler::assembly(const Test &test,
                                            QWidget *parent)
{
    auto view = new QuestionsForm(parent);
    auto model = new QuestionsModel(test, view);

    view->setModel(model);

    return view;
}
