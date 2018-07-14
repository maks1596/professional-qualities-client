#include "Question.h"

#include <QJsonArray>

#include "Entities/AnswerOption/AnswerOption.h"

//  :: Constants ::

const QString ID_JSON_KEY = "id";
const QString FORMULATION_JSON_KEY = "formulation";
const QString ANSWER_OPTIONS_JSON_KEY = "answerOptions";

//  :: Private function headers ::

QJsonArray toJsonArray(const AnswerOptions &answerOptions);
AnswerOptions fromJsonArray(const QJsonArray &jsonArray);

//  :: Implementation ::

struct Question::Implementation {
	int id;
	QString formulation;
	AnswerOptions answerOptions;
};

//  :: Lifecycle ::
//  :: Constructors ::
Question::Question(const int &id/*= 0*/) :
	pimpl(new Implementation())
{
	setId(id);
}

Question::Question(const QString &formulation,
				   const AnswerOptions &answerOptions) :
	Question()
{
	setFormulation(formulation);
	setAnswerOptions(answerOptions);
}

Question::Question(const int &id,
				   QString &formulation,
				   const AnswerOptions &answerOptions) :
	Question(formulation, answerOptions)
{
	setId(id);
}

//  :: Copy ::
Question::Question(const Question &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
Question &Question::operator=(const Question &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
Question::Question(Question &&other) : pimpl(other.pimpl.take()) {}
Question &Question::operator=(Question &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
Question::~Question() {}

//  :: Accessors ::
//  :: ID ::
int Question::getId() const {
	return pimpl->id;
}
void Question::setId(int id) {
	pimpl->id = id;
}

//  :: Formulation ::
QString Question::getFormulation() const {
	return pimpl->formulation;
}
void Question::setFormulation(const QString &formulation) {
	pimpl->formulation = formulation;
}

//  :: Answer options ::
const AnswerOptions &Question::getAnswerOptions() const {
    return pimpl->answerOptions;
}
QStringList Question::getAnswerOptionsFormulations() const {
    QStringList formulations;
    for (const auto &answerOption : getAnswerOptions()) {
        formulations << answerOption.getFormulation();
    }
    return formulations;
}
void Question::setAnswerOptions(const AnswerOptions &answerOptions) {
	pimpl->answerOptions = answerOptions;
}

//  :: Serializable ::

QJsonObject Question::toJson() const {
	QJsonObject json;
	json[ID_JSON_KEY] = getId();
	json[FORMULATION_JSON_KEY] = getFormulation();
	json[ANSWER_OPTIONS_JSON_KEY] = toJsonArray(getAnswerOptions());
	return json;
}

void Question::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
		setId(json[ID_JSON_KEY].toInt());
	}
	if (json.contains(FORMULATION_JSON_KEY) &&
			json[FORMULATION_JSON_KEY].isString()) {
		setFormulation(json[FORMULATION_JSON_KEY].toString());
	}
	if (json.contains(ANSWER_OPTIONS_JSON_KEY) &&
			json[ANSWER_OPTIONS_JSON_KEY].isArray()) {
		auto jsonAnswerOptions = json[ANSWER_OPTIONS_JSON_KEY].toArray();
		setAnswerOptions(fromJsonArray(jsonAnswerOptions));
	}
}

//  :: Private functions ::

QJsonArray toJsonArray(const AnswerOptions &answerOptions) {
	QJsonArray jsonArray;
	for (const auto &answerOption : answerOptions) {
		jsonArray.append(answerOption.toJson());
	}
	return jsonArray;
}

AnswerOptions fromJsonArray(const QJsonArray &jsonArray) {
	AnswerOptions answerOptions;
	for (const auto &jsonValue : jsonArray) {
		if (jsonValue.isObject()) {
			QJsonObject jsonObject = jsonValue.toObject();
			AnswerOption answerOption;
			answerOption.initWithJsonObject(jsonObject);
			answerOptions.append(answerOption);
		}
	}
	return answerOptions;
}
