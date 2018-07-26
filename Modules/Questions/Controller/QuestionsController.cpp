#include "QuestionsController.h"

#include "../Model/QuestionsModel.h"
#include "../Service/QuestionsService.h"
#include "../View/QuestionsForm.h"
#include "Entities/Answer/Answer.h"
#include "SharedStorage/SharedStorage.h"

//  :: Lifecycle ::

QuestionsController::QuestionsController(QObject *parent)
    : QObject(parent) { }

//  :: Public accessors ::
//  :: View ::
QuestionsForm *QuestionsController::getView() const {
    return m_view;
}
void QuestionsController::setView(QuestionsForm *view) {
    m_view = view;

    connect(m_view, &QuestionsForm::finishTestButtonClicked,
            this, &QuestionsController::countResultsAsync);
    connect(this, &QuestionsController::resultsCounted,
            m_view, &QuestionsForm::resultsCounted);
}

//  :: Model ::
QuestionsModel *QuestionsController::getModel() const {
    return m_model;
}
void QuestionsController::setModel(QuestionsModel *model) {
    m_model = model;
}

//  :: Service ::
QuestionsService *QuestionsController::getService() const {
    return m_service;
}
void QuestionsController::setService(QuestionsService *service) {
    m_service = service;

    connect(m_service, &QuestionsService::resultsCounted,
            this, &QuestionsController::resultsCounted);
}

//  :: Public slots ::

void QuestionsController::countResultsAsync() const {
    if (getModel()->areAllQuestionsHaveAnswers()) {
        getService()->countResults(SharedStorage::getUserId(),
                                   getModel()->getTestId(),
                                   getModel()->getAnswers());
    } else {
        getView()->showNotAllQuestionsHaveAnswersMessage();
    }
}

