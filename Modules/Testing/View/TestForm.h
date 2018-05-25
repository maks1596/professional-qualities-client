#pragma once

#include <QWidget>
#include <QList>

#include "Entities/Test/Test.h"
#include "Entities/Answer/Answer.h"
#include "Entities/ScaleResult/ScaleResult.h"

namespace Ui {
class TestForm;
}

class TestingModel;

class TestForm : public QWidget {
Q_OBJECT

public:
	//  :: Lifecycle ::
	explicit TestForm(const Test &test, QWidget *parent = nullptr);
	~TestForm();

signals:
	void canceled();
	void error(const QString &error);

private slots:
	void onHelpBtnClicked();
	void showQuestions();
	void onFinishTestBtnClicked();
	void showResults(const ScaleResults &results);

private:
	void initModel();
	void initQuestions();
	void sendAnswers(const Answers &answers);
	void initResults(const ScaleResults &results);

	Test m_test;
	TestingModel *m_model;
	Ui::TestForm *ui;
};
