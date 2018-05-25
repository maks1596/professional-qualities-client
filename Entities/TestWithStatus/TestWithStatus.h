#pragma once

#include <QScopedPointer>

#include "Entities/TestStatus/TestStatus.h"
#include "Serializable/Object/SerializableObject.h"

class TestWithStatus : public SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	TestWithStatus();

	//  :: Copy ::
	TestWithStatus(const TestWithStatus &other);
	TestWithStatus &operator=(const TestWithStatus &other);

	//  :: Move ::
	TestWithStatus(TestWithStatus &&other);
	TestWithStatus &operator=(TestWithStatus &&other);

	//  :: Destructor ::
	~TestWithStatus();

	//  :: Accessors ::

	int getId() const;
	void setId(int id);

	QString getName() const;
	void setName(const QString &name);

	TestStatus getStatus() const;
	void setStatus(TestStatus status);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
