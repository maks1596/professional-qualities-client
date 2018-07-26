#pragma once

#include <QObject>

class QuestionsForm;
class QuestionsModel;
class QuestionsService;

class ScaleResult;

class QuestionsController : public QObject {
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

signals:
    void resultsCounted(const QList<ScaleResult> &results);

private:
    QuestionsForm *m_view;
    QuestionsModel *m_model;
    QuestionsService *m_service;
};
