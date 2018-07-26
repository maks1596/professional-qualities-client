#pragma once

#include "BaseModel/BaseModel.h"

class Answer;
class ScaleResult;

class QuestionsService : public BaseService {
    Q_OBJECT
public:
    explicit QuestionsService(QObject *parent = nullptr);

    void countResults(int userId, int testId,
                      const QList<Answer> &answers) const;

signals:
    void resultsCounted(const QList<ScaleResult> &results);

private slots:
    void jsonResultsGot(const QJsonArray &jsonResults);
};
