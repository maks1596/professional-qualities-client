#include "Test.h"

#include <QJsonArray>
#include <QString>

//  :: Constants ::

const QString ID_JSON_KEY = "id";
const QString NAME_JSON_KEY = "name";
const QString INSTRUCTION_JSON_KEY = "instruction";
const QString ANSWER_OPTIONS_TYPE_JSON_KEY = "answerOptionsType";
const QString GENERAL_ANSWER_OPTIONS_JSON_KEY = "generalAnswerOptions";
const QString QUESTIONS_JSON_KEY = "questions";

//  :: Private function headers ::

AnswerOptions answerOptionsFromJsonArray(const QJsonArray &jsonArray);
Questions questionsFromJsonArray(const QJsonArray &jsonArray);

//  :: Implementation ::

struct Test::Implementation {
	int id = 0;
	QString name = "";
	QString instruction = "";
    AnswerOptionsType type = GENERAL;
	AnswerOptions generalAnswerOptions;
	Questions questions;
};

//  :: Lifecycle ::
//  :: Constructors ::
Test::Test(int id/*= 0*/)
	: pimpl(new Implementation())
{
	setId(id);
}

//  :: Copy ::
Test::Test(const Test &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
Test &Test::operator=(const Test &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
Test::Test(Test &&other) : pimpl(other.pimpl.take()) {}
Test &Test::operator=(Test &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
Test::~Test() {}

//  :: Accessors ::
//  :: ID ::
int Test::getId() const {
	return pimpl->id;
}
void Test::setId(int id) {
	pimpl->id = id;
}

//  :: Name ::
QString Test::getName() const {
	return pimpl->name;
}
void Test::setName(const QString &name) {
	pimpl->name = name;
}

//  :: Instruction ::
QString Test::getInstruction() const {
	return pimpl->instruction;
}
void Test::setInstruction(const QString &instruction) {
	pimpl->instruction = instruction;
}

//  :: Answer options type ::
AnswerOptionsType Test::getAnswerOptionsType() const {
	return pimpl->type;
}
void Test::setAnswerOptionsType(const AnswerOptionsType &type) {
	pimpl->type = type;
}

//  :: General answer options ::
AnswerOptions Test::getGeneralAnswerOptions() const {
	return pimpl->generalAnswerOptions;
}
void Test::setGeneralAnswerOptions(const AnswerOptions &answerOptions) {
	pimpl->generalAnswerOptions = answerOptions;
}

//  :: Questions ::
Questions Test::getQuestions() const {
	return pimpl->questions;
}
void Test::setQuestions(const Questions &questions) {
	pimpl->questions = questions;
}

//  :: Serializable ::

QJsonObject Test::toJson() const {
	QJsonObject json;
	json[ID_JSON_KEY] = getId();
	json[NAME_JSON_KEY] = getName();
	json[INSTRUCTION_JSON_KEY] = getInstruction();

	QJsonArray jsonAnswerOptions;
	for (const auto &answerOption : getGeneralAnswerOptions()) {
		jsonAnswerOptions.append(answerOption.toJson());
	}
	json[GENERAL_ANSWER_OPTIONS_JSON_KEY] = jsonAnswerOptions;

	QJsonArray jsonQuestions;
	for (const auto &question : getQuestions()) {
		jsonQuestions.append(question.toJson());
	}
	json[QUESTIONS_JSON_KEY] = jsonQuestions;

	return json;
}

void Test::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
		setId(json[ID_JSON_KEY].toInt());
	}
	if (json.contains(NAME_JSON_KEY) &&
			json[NAME_JSON_KEY].isString()) {
		setName(json[NAME_JSON_KEY].toString());
	}
	if (json.contains(INSTRUCTION_JSON_KEY) &&
			json[INSTRUCTION_JSON_KEY].isString()) {
		setInstruction(json[INSTRUCTION_JSON_KEY].toString());
	}
	if (json.contains(GENERAL_ANSWER_OPTIONS_JSON_KEY) &&
			json[GENERAL_ANSWER_OPTIONS_JSON_KEY].isArray()) {
		auto jsonArray = json[GENERAL_ANSWER_OPTIONS_JSON_KEY].toArray();
		setGeneralAnswerOptions(answerOptionsFromJsonArray(jsonArray));
		setAnswerOptionsType(getGeneralAnswerOptions().isEmpty() ?
								 UNIQUE : GENERAL);
	}
	if (json.contains(QUESTIONS_JSON_KEY) && json[QUESTIONS_JSON_KEY].isArray()) {
		auto jsonArray = json[QUESTIONS_JSON_KEY].toArray();
		setQuestions(questionsFromJsonArray(jsonArray));
	}
}

//  :: Private functions ::

AnswerOptions answerOptionsFromJsonArray(const QJsonArray &jsonArray) {
	AnswerOptions answerOptions;
	AnswerOption answerOption;

	for (const auto &jsonAnswerOption : jsonArray) {
		if (jsonAnswerOption.isObject()) {
			auto jsonObject = jsonAnswerOption.toObject();
			answerOption.initWithJsonObject(jsonObject);
			answerOptions.append(answerOption);
		}
	}

	return answerOptions;
}

Questions questionsFromJsonArray(const QJsonArray &jsonArray) {
	Questions questions;
	Question question;

	for (const auto &jsonQuestion : jsonArray) {
		if (jsonQuestion.isObject()) {
			auto jsonObject = jsonQuestion.toObject();
			question.initWithJsonObject(jsonObject);
			questions.append(question);
		}
	}

	return questions;
}
