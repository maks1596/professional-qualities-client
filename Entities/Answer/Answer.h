#pragma once

#include <QList>
#include <QScopedPointer>

#include "Serializable/Object/SerializableObject.h"

class Answer;
typedef QList<Answer> Answers;

class Answer : public SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	Answer();
	Answer(int questionId, int answerOptionId);

	//  :: Copy ::
	Answer(const Answer &other);
	Answer &operator=(const Answer &other);

	//  :: Move ::
	Answer(Answer &&other);
	Answer &operator=(Answer &&other);

	//  :: Destructor ::
	~Answer();

	//  :: Accessors ::

	int getAnswerOptionId() const;
	void setAnswerOptionId(int id);

	int getQuestionId() const;
	void setQuestionId(int id);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
