#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Test;
class TestsModel;

class MainWindow : public QMainWindow {
Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

    //  :: Lifecycle ::

    TestsModel *getModel() const;
    void setModel(TestsModel *model);

public slots:
    void startUpdating();
    void stopUpdating();

private slots:
	void onTestGot(const Test &test);

	void showErrorMessage(const QString &message);
	void showStatusMessage(const QString &message);

private:
    TestsModel *m_model;
	Ui::MainWindow *ui;
};
