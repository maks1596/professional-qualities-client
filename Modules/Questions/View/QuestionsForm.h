#pragma once

#include <QWidget>

namespace Ui {
class QuestionsForm;
}

class Answer;
class QuestionsModel;
class ScaleResult;

class QuestionsForm : public QWidget {
    Q_OBJECT

public:
    explicit QuestionsForm(QWidget *parent = 0);
    ~QuestionsForm();

    QuestionsModel *getModel() const;
    void setModel(QuestionsModel *model);

signals:
    void testingFinished(const QList<Answer> &answers);
    void resultsCounted(const QList<ScaleResult> &scaleResults);
    void cancelButtonClicked();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void setTestName(const QString &testName);

    QuestionsModel *m_model;
    Ui::QuestionsForm *ui;
};
