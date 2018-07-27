#include "TestForm.h"
#include "ui_TestForm.h"

#include <QLabel>
#include <QMessageBox>

#include "../TestWelcomeForm/TestWelcomeForm.h"

#include "ElidedText/ElidedText.h"

#include "Forms/InstructionLabel/InstructionLabel.h"
#include "Forms/ResultForm/ResultForm.h"

#include "Modules/Questions/Assembler/QuestionsAssembler.h"
#include "Modules/Questions/IQuestionsOutput.h"

#include "SharedStorage/SharedStorage.h"

//  :: Constants ::

enum PageIndexes {
    WELCOME_PAGE,
	QUESTIONS_PAGE,
	RESULTS_PAGE
};

//  :: Lifecycle ::
//  :: Constructor ::
TestForm::TestForm(const Test &test, QWidget *parent) :
	QWidget(parent),
	m_test(test),
	ui(new Ui::TestForm)
{
	ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(WELCOME_PAGE);

    auto welcomeForm = createTestWelcomeForm(test);
    pushWidget(welcomeForm);

	connect(ui->cancelBtn, &QPushButton::clicked,
			this, &TestForm::canceled);
	connect(ui->toTestsBtn, &QPushButton::clicked,
			this, &TestForm::canceled);
}

//  :: Destructor ::
TestForm::~TestForm() {
    delete ui;
}

//  :: Protected methods ::

void TestForm::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updateTestNameLabels();
}

//  :: Private slots ::

void TestForm::showQuestions() {
    auto questionsForm = createQuestionsForm(m_test);
    replaceCurrentWidget(questionsForm);
}

void TestForm::showInstruction() {
    QLabel *instructionLabel = new InstructionLabel(m_test.getInstruction());
	connect(this, &TestForm::destroyed,
            instructionLabel, &QLabel::deleteLater);
    instructionLabel->show();
}

void TestForm::showResults(const ScaleResults &results) {
	initResults(results);
    ui->stackedWidget->setCurrentIndex(RESULTS_PAGE);
    updateResultsTestNameLabel();
}

//  :: Private methods ::

QWidget *TestForm::createTestWelcomeForm(const Test &test) {
    auto welcomeForm = new TestWelcomeForm(test.getName(),
                                           test.getInstruction(),
                                           this);

    connect(welcomeForm, &TestWelcomeForm::cancelButtonClicked,
            this, &TestForm::canceled);
    connect(welcomeForm, &TestWelcomeForm::startTestButtonClicked,
            this, &TestForm::showQuestions);

    return welcomeForm;
}

QWidget *TestForm::createQuestionsForm(const Test &test) {
    QWidget *view;
    IQuestionsOutput *output;
    std::tie(view, output) = QuestionsAssembler::assembly(test, this);

    connect(output, &IQuestionsOutput::cancelButtonClicked,
            this, &TestForm::canceled);
    connect(output, &IQuestionsOutput::instructionButtonClicked,
            this, &TestForm::showInstruction);
    connect(output, &IQuestionsOutput::resultsCounted,
            this, &TestForm::showResults);

    return view;
}

//  :: Update test name labels ::
void TestForm::updateTestNameLabels() {
    switch (ui->stackedWidget->currentIndex()) {
    case QUESTIONS_PAGE:
        updateQuestionsTestNameLabel();
        break;

    case RESULTS_PAGE:
        updateResultsTestNameLabel();
        break;
    }
}
void TestForm::updateQuestionsTestNameLabel() {
    setQuestionsTestNameLabelText(m_test.getName());
}
void TestForm::updateResultsTestNameLabel() {
    setResultsTestNameLabelText(m_test.getName());
}

//  :: Set test name ::
void TestForm::setTestName(const QString &testName) {
    setQuestionsTestNameLabelText(testName);
    setResultsTestNameLabelText(testName);
}
void TestForm::setQuestionsTestNameLabelText(const QString &testName) {
    elidedText(ui->questionsTestNameLabel, testName);
}
void TestForm::setResultsTestNameLabelText(const QString &testName) {
    elidedText(ui->resultsTestNameLabel, testName);
}

void TestForm::initResults(const ScaleResults &results) {
	for(const auto &result : results) {
		ui->results->layout()->addWidget(new ResultForm(result, this));
    }
}

void TestForm::pushWidget(QWidget *widget) {
    ui->stackedWidget->addWidget(widget);
    ui->stackedWidget->setCurrentWidget(widget);
    widget->show();
}
void TestForm::popCurrentWidget() {
    auto widget = ui->stackedWidget->currentWidget();
    ui->stackedWidget->removeWidget(widget);
    widget->deleteLater();
}
void TestForm::replaceCurrentWidget(QWidget *widget) {
    popCurrentWidget();
    pushWidget(widget);
}
