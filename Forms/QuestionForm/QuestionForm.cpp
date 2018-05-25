#include "QuestionForm.h"
#include "ui_QuestionForm.h"

#include <QRadioButton>

QuestionForm::QuestionForm(const Question &question, QWidget *parent) :
	QuestionForm(question, question.getAnswerOptions(), parent) {}

QuestionForm::QuestionForm(const Question &question,
						   const AnswerOptions &answerOptions,
						   QWidget *parent) :
	QWidget(parent),
	m_question(question),
	m_answerOptions(answerOptions),
	m_answerID(),
	ui(new Ui::QuestionForm)
{
	ui->setupUi(this);

	ui->formulationLbl->setText(m_question.getFormulation());
	initAnswerOptions();
}

QuestionForm::~QuestionForm() {
	delete ui;
}

inline
void QuestionForm::initAnswerOptions() {
	for(const AnswerOption &answerOption : m_answerOptions) {
		QRadioButton *btn = new QRadioButton(answerOption.getFormulation(), this);
		connect(btn, &QRadioButton::clicked,
				[&]{ m_answerID = answerOption.getId(); });
		ui->answerOptionsGB->layout()->addWidget(btn);
	}
}

void QuestionForm::setNumber(uint number) {
	static const QString numberFormat = "%1)";
	ui->numberLbl->setText(numberFormat.arg(number));
}

int QuestionForm::getAnswerID() const {
	return m_answerID;
}

int QuestionForm::getQuestionID() const {
	return m_question.getId();
}


