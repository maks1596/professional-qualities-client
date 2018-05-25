#include "Answer.h"

#include <QString>

//  :: Constants ::

const QString ANSWER_OPTION_ID_JSON_KEY = "answerId";
const QString QUESTION_ID_JSON_KEY = "questionId";

//  :: Implementation ::

struct Answer::Implementation {
	int answerOptionId = 0;
	int questionId = 0;
};

//  :: Lifecycle ::
//  :: Constructors ::
Answer::Answer()
	: pimpl(new Implementation())
{ }

Answer::Answer(int questionId, int answerOptionId) :
	Answer()
{
	setQuestionId(questionId);
	setAnswerOptionId(answerOptionId);
}

//  :: Copy ::
Answer::Answer(const Answer &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
Answer &Answer::operator=(const Answer &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
Answer::Answer(Answer &&other) : pimpl(other.pimpl.take()) {}
Answer &Answer::operator=(Answer &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
Answer::~Answer() {}

//  :: Accessors ::
//  :: Answer option ID ::
int Answer::getAnswerOptionId() const {
	return pimpl->answerOptionId;
}
void Answer::setAnswerOptionId(int id) {
	pimpl->answerOptionId = id;
}

//  :: Question ID ::
int Answer::getQuestionId() const {
	return pimpl->questionId;
}
void Answer::setQuestionId(int id) {
	pimpl->questionId = id;
}

//  :: Serializable ::

QJsonObject Answer::toJson() const {
	QJsonObject json;
	json[QUESTION_ID_JSON_KEY] = getQuestionId();
	json[ANSWER_OPTION_ID_JSON_KEY] = getAnswerOptionId();
	return json;
}

void Answer::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(QUESTION_ID_JSON_KEY) &&
			json[QUESTION_ID_JSON_KEY].isDouble()) {
		setQuestionId(json[QUESTION_ID_JSON_KEY].toInt());
	}
	if (json.contains(ANSWER_OPTION_ID_JSON_KEY) &&
			json[ANSWER_OPTION_ID_JSON_KEY].isDouble()) {
		setAnswerOptionId(json[ANSWER_OPTION_ID_JSON_KEY].toInt());
	}
}
