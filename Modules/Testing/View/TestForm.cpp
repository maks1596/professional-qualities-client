#include "TestForm.h"
#include "ui_TestForm.h"

#include <QLabel>
#include <QMessageBox>

#ifdef QT_DEBUG
#include <QTime>
#endif

#include "../Model/TestingModel.h"
#include "../TestWelcomeForm/TestWelcomeForm.h"

#include "Forms/ResultForm/ResultForm.h"

#include "Modules/Questions/Assembler/QuestionsAssembler.h"
#include "Modules/Questions/View/QuestionsForm.h"

#include "SharedStorage/SharedStorage.h"

//  :: Constants ::

const int INSTRUCTION_HELP_LABEL_MARGIN = 10;

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


	connect(ui->helpBtn, &QPushButton::clicked,
			this, &TestForm::onHelpBtnClicked);
	connect(ui->finishBtn, &QPushButton::clicked,
			this, &TestForm::onFinishTestBtnClicked);

	initModel();

#ifdef QT_DEBUG
    auto randomAnswersButton = new QPushButton("Radom", this);
    connect(randomAnswersButton, &QPushButton::clicked,
            [this]() {
        Answers answers;
        auto answerOptions = m_test.getGeneralAnswerOptions();
        int answerOptionsCount = answerOptions.size();
        qsrand(QTime::currentTime().msecsSinceStartOfDay());

        for (const auto &question : m_test.getQuestions()) {
            if (m_test.getAnswerOptionsType() == AnswerOptionsType::UNIQUE) {
                answerOptions = question.getAnswerOptions();
                answerOptionsCount = answerOptions.size();
            }

            int answerIndex = qrand() % answerOptionsCount;
            auto answerOption = answerOptions[answerIndex];
            answers.append(Answer(question.getId(), answerOption.getId()));
        }
        sendAnswers(answers);
    });
    ui->buttonsHorizontalLayout->addWidget(randomAnswersButton);
#endif
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

void TestForm::onHelpBtnClicked() {
	QLabel *help = new QLabel();
	help->setWindowTitle("Инструкция");
	help->setText(m_test.getInstruction());
	help->setWordWrap(true);
    help->setMargin(INSTRUCTION_HELP_LABEL_MARGIN);

	connect(this, &TestForm::destroyed,
			help, &QLabel::deleteLater);
	help->show();
}

void TestForm::onFinishTestBtnClicked() {

}

void TestForm::showResults(const ScaleResults &results) {
	initResults(results);
    ui->stackedWidget->setCurrentIndex(RESULTS_PAGE);
    updateResultsTestNameLabel();
}

//  :: Private methods ::

TestWelcomeForm *TestForm::createTestWelcomeForm(const Test &test) {
    auto welcomeForm = new TestWelcomeForm(test.getName(),
                                           test.getInstruction(),
                                           this);
    connect(welcomeForm, &TestWelcomeForm::cancelButtonClicked,
            this, &TestForm::canceled);
    connect(welcomeForm, &TestWelcomeForm::startTestButtonClicked,
            this, &TestForm::showQuestions);

    return welcomeForm;
}

QuestionsForm *TestForm::createQuestionsForm(const Test &test) {
    auto questionsForm = QuestionsAssembler::assembly(test, this);

    connect(questionsForm, &QuestionsForm::cancelButtonClicked,
            this, &TestForm::canceled);

    return questionsForm;
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
    setElidedText(ui->questionsTestNameLabel, testName);
}
void TestForm::setResultsTestNameLabelText(const QString &testName) {
    setElidedText(ui->resultsTestNameLabel, testName);
}

void TestForm::setElidedText(QLabel *label, const QString &text) {
    label->setText(elidedText(label, text));
}
QString TestForm::elidedText(const QLabel *label, const QString &text) const {
    auto font = label->font();
    auto width = label->width();
    QFontMetrics fontMetrics(font);
    return fontMetrics.elidedText(text, Qt::ElideRight, width);
}

void TestForm::initModel() {
	m_model = new TestingModel(this);
	connect(m_model, &TestingModel::resultsCounted,
			this, &TestForm::showResults);
	connect(m_model, &TestingModel::error,
			this, &TestForm::error);
}

void TestForm::initQuestions() {

}

void TestForm::sendAnswers(const Answers &answers) {
	m_model->countResults(SharedStorage::getUserId(),
						  m_test.getId(),
						  answers);
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
