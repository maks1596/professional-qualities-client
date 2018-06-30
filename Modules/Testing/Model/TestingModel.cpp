#include "TestingModel.h"

#include <QJsonArray>
#include <QJsonValue>
#include <QString>

#include "Entities/BindedAnswers/BindedAnswers.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString COUNT_RESULTS_API = "tests/count-results";

//  :: Lifecycle ::

TestingModel::TestingModel(QObject *parent/*= nullptr*/)
	: BaseService(parent)
{ }

//  :: Public methods ::

void TestingModel::countResults(int userId, int testId,
								const Answers &answers) const {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonArray)),
			SLOT(jsonResultsGot(QJsonArray)));
	BindedAnswers bindedAnswers(userId, testId, answers);
	requester->sendRequest(COUNT_RESULTS_API,
						   RequestType::POST,
						   bindedAnswers.toJson());
}

//  :: Private slots ::

void TestingModel::jsonResultsGot(const QJsonArray &jsonResults) {
	ScaleResults results;

	for (const auto &jsonResult : jsonResults) {
		if (jsonResult.isObject()) {
			auto jsonObject = jsonResult.toObject();
			ScaleResult result;
			result.initWithJsonObject(jsonObject);
			results += result;
		}
	}

	emit resultsCounted(results);
}
