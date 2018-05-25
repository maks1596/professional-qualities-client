#pragma once

#include <QList>
#include <QScopedPointer>

#include "Entities/AnswerOption/AnswerOption.h"
#include "Serializable/Object/SerializableObject.h"

class Question;
typedef QList<Question> Questions;

class Question : public SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	Question(const int &id = 0);
	Question(const QString &formulation,
			 const AnswerOptions &answerOptions = AnswerOptions());
	Question(const int &id,
			 QString &formulation,
			 const AnswerOptions &answerOptions = AnswerOptions());

	//  :: Copy ::
	Question(const Question &other);
	Question &operator=(const Question &other);

	//  :: Move ::
	Question(Question &&other);
	Question &operator=(Question &&other);

	//  :: Destructor ::
	~Question();

	//  :: Accessors ::
	int getId() const;
	void setId(int id);

	QString getFormulation() const;
	void setFormulation(const QString &formulation);

	AnswerOptions getAnswerOptions() const;
	void setAnswerOptions(const AnswerOptions &answerOptions);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
