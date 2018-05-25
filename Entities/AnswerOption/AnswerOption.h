#pragma once

#include <QList>
#include <QScopedPointer>

#include "Serializable/Object/SerializableObject.h"

class QString;

class AnswerOption;
typedef QList<AnswerOption> AnswerOptions;

class AnswerOption : public SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	AnswerOption(int id = 0);
	AnswerOption(const QString &formulation);
	AnswerOption(const int &id, const QString &formulation);

	//  :: Copy ::
	AnswerOption(const AnswerOption &other);
	AnswerOption &operator=(const AnswerOption &other);

	//  :: Move ::
	AnswerOption(AnswerOption &&other);
	AnswerOption &operator=(AnswerOption &&other);

	//  :: Destructor ::
	~AnswerOption();

	//  :: Accessors ::

	int getId() const;
	void setId(int id);

	QString getFormulation() const;
	void setFormulation(const QString &formulation);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
