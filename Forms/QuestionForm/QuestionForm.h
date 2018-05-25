#ifndef QUESTIONFORM_H
#define QUESTIONFORM_H

#include <QWidget>

#include "Entities/Question/Question.h"

namespace Ui {
class QuestionForm;
}

class QuestionForm : public QWidget {
Q_OBJECT

public:
	explicit QuestionForm(const Question &question,
						  QWidget *parent = 0);

	explicit QuestionForm(const Question &question,
						  const AnswerOptions &answerOptions,
						  QWidget *parent = 0);

	~QuestionForm();

	void setNumber(uint number);
	int getAnswerID() const;
	int getQuestionID() const;

private:
	void initAnswerOptions();

	Question m_question;
	AnswerOptions m_answerOptions;
	int m_answerID;
	Ui::QuestionForm *ui;
};

#endif // QUESTIONFORM_H
