#pragma once

#include <QWidget>

class QPushButton;

namespace Ui {
class QuestionsForm;
}

class Answer;
class QuestionsModel;
class ScaleResult;

class QuestionsForm : public QWidget {
    Q_OBJECT

public:
    explicit QuestionsForm(QWidget *parent = nullptr);
    ~QuestionsForm();

    QuestionsModel *getModel() const;
    void setModel(QuestionsModel *model);

public slots:
    void showNotAllQuestionsHaveAnswersMessage();
    void showMessage(const QString &message);

signals:
    void finishTestButtonClicked();
    void resultsCounted(const QList<ScaleResult> &scaleResults);
    void cancelButtonClicked();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void setTestName(const QString &testName);

    QuestionsModel *m_model;
#ifdef QT_DEBUG
    QPushButton *m_randomAnswersButton;
#endif
    Ui::QuestionsForm *ui;
};
