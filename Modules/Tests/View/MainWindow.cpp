#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>

#include "../Model/TestsColumnIndex.h"
#include "../Model/TestsModel.h"
#include "Entities/TestWithStatus/TestWithStatus.h"
#include "Modules/Testing/View/TestForm.h"

//  :: Lifecycle ::

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    ui->testsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow() {
    delete ui;
}

//  :: Public accessors ::

TestsModel *MainWindow::getModel() const {
    return m_model;
}
void MainWindow::setModel(TestsModel *model) {
    m_model = model;
    ui->testsTableView->setModel(m_model);
    connect(ui->testsTableView, &QTableView::doubleClicked,
            m_model, &TestsModel::getTestAsync);
    connect(m_model, &TestsModel::testGot,
            this, &MainWindow::onTestGot);

    ui->testsTableView->horizontalHeader()
            ->setSectionResizeMode(TESTS_NAME_COLUMN_INDEX,
                                   QHeaderView::Stretch);
    ui->testsTableView->horizontalHeader()
            ->setSectionResizeMode(TESTS_STATUS_COLUMN_INDEX,
                                   QHeaderView::ResizeToContents);
}

//  :: Public slots ::

void MainWindow::startUpdating() {
    m_model->startUpdating();
}
void MainWindow::stopUpdating() {
    m_model->stopUpdating();
}

//  :: Private slots ::

void MainWindow::onTestGot(const Test &test) {
	TestForm *testForm = new TestForm(test);

	connect(testForm, &TestForm::canceled,
			testForm, &TestForm::deleteLater);
	connect(testForm, &TestForm::canceled,
			this, &MainWindow::startUpdating);
	connect(testForm, &TestForm::destroyed,
			this, &MainWindow::show);
	connect(this, &MainWindow::destroyed,
			testForm, &TestForm::deleteLater);
	connect(testForm, &TestForm::error,
			this, &MainWindow::showErrorMessage);

	hide();
	stopUpdating();
	testForm->show();
}

void MainWindow::showErrorMessage(const QString &message) {
	QMessageBox::critical(this, "Ошибка", message);
}

void MainWindow::showStatusMessage(const QString &message) {
	ui->statusBar->showMessage(message);
}
