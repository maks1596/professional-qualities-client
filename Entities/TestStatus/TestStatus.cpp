#include "TestStatus.h"

#include <QString>

//  :: Constants ::

const QString PASSED_TEST_STATUS_JSON_STRING = "Passed";
const QString NOT_PASSED_TEST_STATUS_JSON_STRING = "NotPassed";

const QString PASSED_TEST_STATUS_STRING = "Пройден";
const QString NOT_PASSED_TEST_STATUS_STRING = "Не пройден";

//  :: Public functions ::

QString stringWithTestStatus(TestStatus status) {
	switch (status) {
	case TestStatus::Passed:
		return PASSED_TEST_STATUS_STRING;
	case TestStatus::NotPassed:
		return NOT_PASSED_TEST_STATUS_STRING;
	}
	return NOT_PASSED_TEST_STATUS_STRING;
}

//  :: Serialization functions ::

QString testStatusToJson(TestStatus status) {
	switch (status) {
	case TestStatus::Passed:
		return PASSED_TEST_STATUS_JSON_STRING;
	case TestStatus::NotPassed:
		return NOT_PASSED_TEST_STATUS_JSON_STRING;
	}
	return NOT_PASSED_TEST_STATUS_JSON_STRING;
}

TestStatus testStatusFromJson(const QString &string) {
	if (string == PASSED_TEST_STATUS_JSON_STRING) {
		return TestStatus::Passed;
	} else {
		return TestStatus::NotPassed;
	}
}
