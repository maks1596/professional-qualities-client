#include "QuestionsAssembler.h"

#include "../Controller/QuestionsController.h"
#include "../Model/QuestionsModel.h"
#include "../Service/QuestionsService.h"
#include "../View/QuestionsForm.h"

QuestionsForm *QuestionsAssembler::assembly(const Test &test,
                                            QWidget *parent)
{
    auto view = new QuestionsForm(parent);
    auto model = new QuestionsModel(test, view);
    auto controller = new QuestionsController(view);
    auto service = new QuestionsService(view);

    view->setModel(model);

    controller->setView(view);
    controller->setModel(model);
    controller->setService(service);

    return view;
}
