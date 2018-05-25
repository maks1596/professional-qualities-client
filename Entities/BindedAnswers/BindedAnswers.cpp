#include "BindedAnswers.h"

#include <QJsonArray>
#include <QString>

//  :: Constants ::

const QString USER_ID_JSON_KEY = "userId";
const QString TEST_ID_JSON_KEY = "testId";
const QString ANSWERS_JSON_KEY = "answers";

//  :: Private function headers ::

Answers answersFromJsonArray(const QJsonArray &jsonArray);

//  :: Implementation ::

struct BindedAnswers::Implementation {
	int userId = 0;
	int testId = 0;
	Answers answers;
};

//  :: Lifecycle ::
//  :: Constructors ::
BindedAnswers::BindedAnswers()
	: pimpl(new Implementation())
{ }

BindedAnswers::BindedAnswers(int userId, int testId,
							 const Answers &answers)
	: BindedAnswers()
{
	setUserId(userId);
	setTestId(testId);
	setAnswers(answers);
}

//  :: Copy ::
BindedAnswers::BindedAnswers(const BindedAnswers &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
BindedAnswers &BindedAnswers::operator=(const BindedAnswers &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
BindedAnswers::BindedAnswers(BindedAnswers &&other)
	: pimpl(other.pimpl.take())
{ }
BindedAnswers &BindedAnswers::operator=(BindedAnswers &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
BindedAnswers::~BindedAnswers() {}

//  :: Accessors ::
//  :: User ID ::
int BindedAnswers::getUserId() const {
	return pimpl->userId;
}
void BindedAnswers::setUserId(int userId) {
	pimpl->userId = userId;
}

//  :: Test ID ::
int BindedAnswers::getTestId() const {
	return pimpl->testId;
}
void BindedAnswers::setTestId(int testId) {
	pimpl->testId = testId;
}

//  :: Answers ::
Answers BindedAnswers::getAnswers() const {
	return pimpl->answers;
}
void BindedAnswers::setAnswers(const Answers &answers) {
	pimpl->answers = answers;
}

//  :: Serializable ::

QJsonObject BindedAnswers::toJson() const {
	QJsonObject json;
	json[USER_ID_JSON_KEY] = getUserId();
	json[TEST_ID_JSON_KEY] = getTestId();

	QJsonArray jsonAnswers;
	for (const auto &answer : getAnswers()) {
		jsonAnswers.append(answer.toJson());
	}
	json[ANSWERS_JSON_KEY] = jsonAnswers;

	return json;
}

void BindedAnswers::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(USER_ID_JSON_KEY) && json[USER_ID_JSON_KEY].isDouble()) {
		setUserId(json[USER_ID_JSON_KEY].toInt());
	}
	if (json.contains(TEST_ID_JSON_KEY) && json[TEST_ID_JSON_KEY].isDouble()) {
		setTestId(json[TEST_ID_JSON_KEY].toInt());
	}

	if (json.contains(ANSWERS_JSON_KEY) && json[ANSWERS_JSON_KEY].isArray()) {
		auto jsonArray = json[ANSWERS_JSON_KEY].toArray();
		setAnswers(answersFromJsonArray(jsonArray));
	}
}

//  :: Private functions ::

Answers answersFromJsonArray(const QJsonArray &jsonArray) {
	Answers answers;
	Answer answer;

	for (const auto &jsonAnswer : jsonArray) {
		if (jsonAnswer.isObject()) {
			auto jsonObject = jsonAnswer.toObject();
			answer.initWithJsonObject(jsonObject);
			answers.append(answer);
		}
	}

	return answers;
}
