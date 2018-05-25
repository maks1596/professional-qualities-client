#pragma once

#include <QList>
#include <QScopedPointer>

#include "Serializable/Object/SerializableObject.h"

class QString;

class ScaleResult;
typedef QList<ScaleResult> ScaleResults;

class ScaleResult : public SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	ScaleResult();
	ScaleResult(const QString &scaleName, const QString &result);

	//  :: Copy ::
	ScaleResult(const ScaleResult &other);
	ScaleResult &operator=(const ScaleResult &other);

	//  :: Move ::
	ScaleResult(ScaleResult &&other);
	ScaleResult &operator=(ScaleResult &&other);

	//  :: Destructor ::
	~ScaleResult();

	//  :: Accessors ::

	QString getScaleName() const;
	void setScaleName(const QString &scaleName);

	QString getResult() const;
	void setResult(const QString &result);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
