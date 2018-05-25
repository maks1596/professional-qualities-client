#pragma once

class QString;

enum class TestStatus {
	Passed,
	NotPassed
};

//  :: Public functions ::
QString stringWithTestStatus(TestStatus status);

//  :: Serialization functions ::
QString testStatusToJson(TestStatus status);
TestStatus testStatusFromJson(const QString &string);
