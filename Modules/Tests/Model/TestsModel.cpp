#include "TestsModel.h"

#include <QJsonArray>
#include <QJsonValue>
#include <QString>

#include "Entities/Test/Test.h"
#include "Entities/TestWithStatus/TestWithStatus.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString GET_TESTS_API = "tests/for-user/%1";
const QString GET_TEST_API = "tests/%1";

//  :: Lifecycle ::
TestsModel::TestsModel(QObject *parent/*= nullptr*/)
	: BaseModel(parent)
{ }

//  :: Public methods ::

void TestsModel::getTests(int userId) const {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonArray)),
			SLOT(jsonTestsGot(QJsonArray)));
	requester->sendRequest(GET_TESTS_API.arg(userId));
}

void TestsModel::getTest(int testId) const {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonObject)),
			SLOT(jsonTestGot(QJsonObject)));
	requester->sendRequest(GET_TEST_API.arg(testId));
}

//  :: Private slots ::

void TestsModel::jsonTestsGot(const QJsonArray &jsonTests) {
	QList<TestWithStatus> tests;

	for (const auto &jsonValue : jsonTests) {
		if (jsonValue.isObject()) {
			auto jsonObject = jsonValue.toObject();
			TestWithStatus test;
			test.initWithJsonObject(jsonObject);
			tests += test;
		}
	}

	emit testsGot(tests);
}

void TestsModel::jsonTestGot(const QJsonObject &jsonTest) {
	Test test;
	test.initWithJsonObject(jsonTest);
	emit testGot(test);
}
