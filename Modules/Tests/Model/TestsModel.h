#pragma once

#include <QList>

#include "BaseModel/BaseModel.h"

class Test;
class TestWithStatus;

class TestsModel : public BaseModel {
Q_OBJECT
public:
	TestsModel(QObject *parent = nullptr);

	void getTests(int userId) const;
	void getTest(int testId) const;

signals:
	void testsGot(const QList<TestWithStatus> &tests);
	void testGot(const Test &test);

private slots:
	void jsonTestsGot(const QJsonArray &jsonTests);
	void jsonTestGot(const QJsonObject &jsonTest);
};
