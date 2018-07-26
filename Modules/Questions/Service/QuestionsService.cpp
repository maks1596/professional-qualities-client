#include "QuestionsService.h"

#include <QJsonArray>
#include <QJsonValue>
#include <QString>

#include "Entities/Answer/Answer.h"
#include "Entities/BindedAnswers/BindedAnswers.h"
#include "Entities/ScaleResult/ScaleResult.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString COUNT_RESULTS_API = "tests/count-results";

//  :: Lifecycle ::

QuestionsService::QuestionsService(QObject *parent/*= nullptr*/)
    : BaseService(parent)
{ }

//  :: Public methods ::

void QuestionsService::countResults(int userId, int testId,
                                    const QList<Answer> &answers) const {
    auto requester = makeRequester();
    connect(requester, SIGNAL(success(QJsonArray)),
            SLOT(jsonResultsGot(QJsonArray)));
    BindedAnswers bindedAnswers(userId, testId, answers);
    requester->sendRequest(COUNT_RESULTS_API,
                           RequestType::POST,
                           bindedAnswers.toJson());
}

//  :: Private slots ::

void QuestionsService::jsonResultsGot(const QJsonArray &jsonResults) {
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

