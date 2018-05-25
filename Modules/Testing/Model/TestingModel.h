#pragma once

#include "BaseModel/BaseModel.h"
#include "Entities/Answer/Answer.h"
#include "Entities/ScaleResult/ScaleResult.h"

class TestingModel : public BaseModel {
Q_OBJECT
public:
	TestingModel(QObject *parent = nullptr);

	void countResults(int userId, int testId,
					  const Answers &answers) const;

signals:
	void resultsCounted(const ScaleResults &results);

private slots:
	void jsonResultsGot(const QJsonArray &jsonResults);
};
