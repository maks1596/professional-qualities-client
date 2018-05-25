#pragma once

#include <QScopedPointer>

#include "Entities/Answer/Answer.h"
#include "Serializable/Object/SerializableObject.h"

class BindedAnswers : public SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	BindedAnswers();
	BindedAnswers(int userId, int testId, const Answers &answers);

	//  :: Copy ::
	BindedAnswers(const BindedAnswers &other);
	BindedAnswers &operator=(const BindedAnswers &other);

	//  :: Move ::
	BindedAnswers(BindedAnswers &&other);
	BindedAnswers &operator=(BindedAnswers &&other);

	//  :: Destructor ::
	virtual ~BindedAnswers() noexcept override;

	//  :: Accessors ::

	int getUserId() const;
	void setUserId(int userId);

	int getTestId() const;
	void setTestId(int testId);

	Answers getAnswers() const;
	void setAnswers(const Answers &answers);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
