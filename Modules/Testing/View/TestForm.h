#pragma once

#include <QWidget>

#include "Entities/Test/Test.h"
#include "Entities/Answer/Answer.h"
#include "Entities/ScaleResult/ScaleResult.h"

class QLabel;

namespace Ui {
class TestForm;
}

class TestingModel;
class TestWelcomeForm;
class QuestionsForm;

class TestForm : public QWidget {
Q_OBJECT

public:
	//  :: Lifecycle ::
	explicit TestForm(const Test &test, QWidget *parent = nullptr);
	~TestForm();

signals:
	void canceled();
	void error(const QString &error);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
	void onHelpBtnClicked();
	void showQuestions();
	void onFinishTestBtnClicked();
	void showResults(const ScaleResults &results);

private:
    TestWelcomeForm *createTestWelcomeForm(const Test &test);
    QuestionsForm *createQuestionsForm(const Test &test);

    void updateTestNameLabels();
    void updateQuestionsTestNameLabel();
    void updateResultsTestNameLabel();

    void setTestName(const QString &testName);
    void setQuestionsTestNameLabelText(const QString &testName);
    void setResultsTestNameLabelText(const QString &testName);

    void setElidedText(QLabel *label, const QString &text);
    QString elidedText(const QLabel *label, const QString &text) const;

	void initModel();
	void initQuestions();
	void sendAnswers(const Answers &answers);
	void initResults(const ScaleResults &results);

    void pushWidget(QWidget *widget);
    void popCurrentWidget();
    void replaceCurrentWidget(QWidget *widget);

	Test m_test;
	TestingModel *m_model;
	Ui::TestForm *ui;
};
