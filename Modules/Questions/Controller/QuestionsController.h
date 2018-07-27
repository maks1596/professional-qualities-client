#pragma once

#include <QObject>
#include "../IQuestionsOutput.h"

class QuestionsForm;
class QuestionsModel;
class QuestionsService;

class ScaleResult;

class QuestionsController : public IQuestionsOutput {
    Q_OBJECT

public:
    explicit QuestionsController(QObject *parent = nullptr);

    //  :: Accessors ::
    QuestionsForm *getView() const;
    void setView(QuestionsForm *view);

    QuestionsModel *getModel() const;
    void setModel(QuestionsModel *model);

    QuestionsService *getService() const;
    void setService(QuestionsService *service);

public slots:
    void countResultsAsync() const;

private:
    QuestionsForm *m_view;
    QuestionsModel *m_model;
    QuestionsService *m_service;
};
