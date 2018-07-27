#pragma once

#include <QWidget>

#include "Entities/Test/Test.h"

class ScaleResult;

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
	void showInstruction();
    void showQuestions();
    void showResults(const QList<ScaleResult> &results);

private:
    QWidget *createTestWelcomeForm(const Test &test);
    QWidget *createQuestionsForm(const Test &test);
    QWidget *createResultsForm(const QList<ScaleResult> &results);

    void replaceCurrentWidget(QWidget *widget);

    Test m_test;
};
