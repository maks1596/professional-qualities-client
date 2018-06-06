#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QTimer>

#include "Entities/TestWithStatus/TestWithStatus.h"
#include "Modules/Testing/View/TestForm.h"
#include "../Model/TestsModel.h"
#include "SharedStorage/SharedStorage.h"

//  :: Constants ::

const uint UPDATE_INTERVAL = 1000;

enum ColumnIndexes {
	NAME,
	STATUS,
	COLUMNS_AMOUNT
};

//  :: Lifecycle ::
//  :: Constructors ::
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    connect(ui->testsTableWidget, &QTableWidget::doubleClicked,
            this, &MainWindow::onTestDoubleClicked);

	initTestsTable();
	initModel();
	initTimer();
}

//  :: Destructor ::
MainWindow::~MainWindow() {
	delete ui;
}

//  :: Public methods ::

void MainWindow::startUpdating() {
	updateTests();
	m_timer->start();
}
void MainWindow::stopUpdating() {
	m_timer->stop();
}

//  :: Public accessors ::

QList<TestWithStatus> MainWindow::getTests() const {
	return m_tests;
}
void MainWindow::setTests(const QList<TestWithStatus> &tests) {
	m_tests = tests;
	updateTestsTable();
}

//  :: Private slots ::

void MainWindow::onTestDoubleClicked(const QModelIndex &idx) {
	if(idx.isValid()) {
		loadTest(getTestId(idx));
	}
}

void MainWindow::onTestsGot(const QList<TestWithStatus> &tests) {
	showStatusMessage("");
	setTests(tests);
}

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

//  :: Private methods ::
//  :: Initialization ::
void MainWindow::initTestsTable() {
	ui->testsTableWidget->setColumnCount(COLUMNS_AMOUNT);
	ui->testsTableWidget->setHorizontalHeaderLabels({"Название теста",
													 "Статус",
													 "Удаление"});
	ui->testsTableWidget->horizontalHeader()
			->setSectionResizeMode(NAME, QHeaderView::Stretch);
}

void MainWindow::initModel() {
	m_model = new TestsModel(this);
	connect(m_model, &TestsModel::testsGot,
			this, &MainWindow::onTestsGot);
	connect(m_model, &TestsModel::testGot,
			this, &MainWindow::onTestGot);
	connect(m_model, &TestsModel::error,
			this, &MainWindow::showStatusMessage);
}

void MainWindow::initTimer() {
	m_timer = new QTimer(this);
	m_timer->setInterval(UPDATE_INTERVAL);
	connect(m_timer, &QTimer::timeout,
			this, &MainWindow::updateTests);
}

//  :: Update ::

void MainWindow::updateTests() const {
	m_model->getTests(SharedStorage::getUserId());
}

void MainWindow::updateTestsTable() {
	ui->testsTableWidget->setRowCount(m_tests.size());

	for (int row = 0; row < m_tests.size(); ++row) {
		auto test = m_tests.at(row);
		ui->testsTableWidget->setItem(row, NAME,
									  new QTableWidgetItem(test.getName()));

		auto testStatus = test.getStatus();
		auto statusString = stringWithTestStatus(testStatus);
		ui->testsTableWidget->setItem(row, STATUS,
									  new QTableWidgetItem(statusString));
	}

	ui->testsTableWidget->resizeColumnsToContents();
	ui->testsTableWidget->horizontalHeader()
			->setSectionResizeMode(NAME, QHeaderView::Stretch);
}

//  :: Helpers ::
inline
int MainWindow::getTestId(const QModelIndex &idx) const {
	if(idx.isValid()) {
		return m_tests.at(idx.row()).getId();
	} else {
		return 0;
	}
}

void MainWindow::loadTest(int testId) {
	m_model->getTest(testId);
}
