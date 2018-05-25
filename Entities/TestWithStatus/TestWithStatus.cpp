#include "TestWithStatus.h"

//  :: Constants ::

const QString ID_JSON_KEY = "id";
const QString NAME_JSON_KEY = "name";
const QString STATUS_JSON_KEY = "status";

//  :: Implementation ::

struct TestWithStatus::Implementation {
	int id = 0;
	QString name = "";
	TestStatus status = TestStatus::NotPassed;
};

//  :: Lifecycle ::
//  :: Constructors ::
TestWithStatus::TestWithStatus()
	: pimpl(new Implementation())
{ }

//  :: Copy ::
TestWithStatus::TestWithStatus(const TestWithStatus &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
TestWithStatus &TestWithStatus::operator=(const TestWithStatus &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
TestWithStatus::TestWithStatus(TestWithStatus &&other)
	: pimpl(other.pimpl.take())
{ }
TestWithStatus &TestWithStatus::operator=(TestWithStatus &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
TestWithStatus::~TestWithStatus() {}

//  :: Accessors ::
//  :: ID ::
int TestWithStatus::getId() const {
	return pimpl->id;
}
void TestWithStatus::setId(int id) {
	pimpl->id = id;
}

//  :: Name ::
QString TestWithStatus::getName() const {
	return pimpl->name;
}
void TestWithStatus::setName(const QString &name) {
	pimpl->name = name;
}

//  :: Instruction ::
TestStatus TestWithStatus::getStatus() const {
	return pimpl->status;
}
void TestWithStatus::setStatus(TestStatus status) {
	pimpl->status = status;
}

//  :: Serializable ::

QJsonObject TestWithStatus::toJson() const {
	QJsonObject json;
	json[ID_JSON_KEY] = getId();
	json[NAME_JSON_KEY] = getName();
	json[STATUS_JSON_KEY] = testStatusToJson(getStatus());
	return json;
}

void TestWithStatus::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
		setId(json[ID_JSON_KEY].toInt());
	}
	if (json.contains(NAME_JSON_KEY) &&
			json[NAME_JSON_KEY].isString()) {
		setName(json[NAME_JSON_KEY].toString());
	}
	if (json.contains(STATUS_JSON_KEY) &&
			json[STATUS_JSON_KEY].isString()) {
		auto statusString = json[STATUS_JSON_KEY].toString();
		auto status = testStatusFromJson(statusString);
		setStatus(status);
	}
}

