#pragma once

#include <QScopedPointer>

#include "Entities/AnswerOption/Type/AnswerOptionsType.h"
#include "Entities/Question/Question.h"
#include "Serializable/Object/SerializableObject.h"

class Test : public SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	Test(int id = 0);

	//  :: Copy ::
	Test(const Test &other);
	Test &operator=(const Test &other);

	//  :: Move ::
	Test(Test &&other);
	Test &operator=(Test &&other);

	//  :: Destructor ::
    ~Test() override;

	//  :: Accessors ::

	int getId() const;
	void setId(int id);

	QString getName() const;
	void setName(const QString &name);

	QString getInstruction() const;
	void setInstruction(const QString &instruction);

	AnswerOptionsType getAnswerOptionsType() const;
	void setAnswerOptionsType(const AnswerOptionsType &type);

	AnswerOptions getGeneralAnswerOptions() const;
	void setGeneralAnswerOptions(const AnswerOptions &answerOptions);

	Questions getQuestions() const;
	void setQuestions(const Questions &questions);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
