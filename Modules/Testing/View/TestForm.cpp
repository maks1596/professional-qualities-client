#include "TestForm.h"
#include "ui_TestForm.h"

#include <QLabel>
#include <QMessageBox>

#include "../Model/TestingModel.h"
#include "Forms/QuestionForm/QuestionForm.h"
#include "Forms/ResultForm/ResultForm.h"
#include "SharedStorage/SharedStorage.h"

//  :: Constants ::

const int INSTRUCTION_HELP_LABEL_MARGIN = 10;

enum PageIndexes {
	INSTRUCTION_PAGE,
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
	ui->stackedWidget->setCurrentIndex(INSTRUCTION_PAGE);

	ui->nameLbl->setText(m_test.getName());
	ui->instrucationLbl->setText(m_test.getInstruction());

	connect(ui->backBtn, &QPushButton::clicked,
			this, &TestForm::canceled);
	connect(ui->cancelBtn, &QPushButton::clicked,
			this, &TestForm::canceled);
	connect(ui->toTestsBtn, &QPushButton::clicked,
			this, &TestForm::canceled);

	connect(ui->startBtn, &QPushButton::clicked,
			this, &TestForm::showQuestions);
	connect(ui->helpBtn, &QPushButton::clicked,
			this, &TestForm::onHelpBtnClicked);
	connect(ui->finishBtn, &QPushButton::clicked,
			this, &TestForm::onFinishTestBtnClicked);

	initModel();
}

//  :: Destructor ::
TestForm::~TestForm() {
	delete ui;
}

//  :: Private slots ::

void TestForm::showQuestions() {
	initQuestions();
	ui->stackedWidget->setCurrentIndex(QUESTIONS_PAGE);
}

void TestForm::onHelpBtnClicked() {
	QLabel *help = new QLabel();
	help->setWindowTitle("Инструкция");
	help->setText(m_test.getInstruction());
	help->setWordWrap(true);
	help->setMargin(10);

	connect(this, &TestForm::destroyed,
			help, &QLabel::deleteLater);
	help->show();
}

void TestForm::onFinishTestBtnClicked() {
	auto questionsLayout = ui->questions->layout();
	Answers answers;
	for (int i = 0; i < questionsLayout->count(); i++) {
		QuestionForm *questionForm = (QuestionForm *)questionsLayout->itemAt(i)->widget();
		Answer answer{questionForm->getQuestionID(), questionForm->getAnswerID()};
		if (answer.getAnswerOptionId()) {
			answers.append(answer);
		} else {
			QMessageBox::information(this, "Не закончен",
									 "Вы ответили не на все вопросы\n" +
									 QString("(Вопрос №%1)").arg(i + 1));
			questionForm->setFocus();
			return;
		}
	}
	sendAnswers(answers);
}

void TestForm::showResults(const ScaleResults &results) {
	initResults(results);
	ui->stackedWidget->setCurrentIndex(RESULTS_PAGE);
}

//  :: Private methods ::

void TestForm::initModel() {
	m_model = new TestingModel(this);
	connect(m_model, &TestingModel::resultsCounted,
			this, &TestForm::showResults);
	connect(m_model, &TestingModel::error,
			this, &TestForm::error);
}

void TestForm::initQuestions() {
	uint counter = 1;
	for(const Question &question : m_test.getQuestions()) {
		QuestionForm *questionForm;
		if(m_test.getAnswerOptionsType() == UNIQUE) {
			questionForm = new QuestionForm(question, this);
		} else {
			questionForm = new QuestionForm(question, m_test.getGeneralAnswerOptions(), this);
		}
		questionForm->setNumber(counter++);
		ui->questions->layout()->addWidget(questionForm);
	}
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
