#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QTimer;
class Test;
class TestsModel;
class TestWithStatus;

class MainWindow : public QMainWindow {
Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void startUpdating();
	void stopUpdating();

	//  :: Accessors ::
	QList<TestWithStatus> getTests() const;
	void setTests(const QList<TestWithStatus> &tests);

private slots:
    void onTestDoubleClicked(const QModelIndex &idx);

	void onTestsGot(const QList<TestWithStatus> &tests);
	void onTestGot(const Test &test);

	void showErrorMessage(const QString &message);
	void showStatusMessage(const QString &message);

private:
	void initTestsTable();
	void initModel();
	void initTimer();

	void updateTests() const;
	void updateTestsTable();

	void loadTest(int testId);
	int getTestId(const QModelIndex &idx) const;

private:
	QTimer *m_timer;
	TestsModel *m_model;
	QList<TestWithStatus> m_tests;

	Ui::MainWindow *ui;
};
