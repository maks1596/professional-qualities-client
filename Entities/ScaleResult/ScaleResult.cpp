#include "ScaleResult.h"

#include <QString>

//  :: Constants ::

const QString SCALE_NAME_JSON_KEY = "scaleName";
const QString RESULT_JSON_KEY = "result";

//  :: Implementation ::

struct ScaleResult::Implementation {
	QString scaleName = "";
	QString result = "";
};

//  :: Lifecycle ::
//  :: Constructors ::
ScaleResult::ScaleResult()
	: pimpl(new Implementation())
{ }

ScaleResult::ScaleResult(const QString &scaleName, const QString &result) :
	ScaleResult()
{
	setScaleName(scaleName);
	setResult(result);
}

//  :: Copy ::
ScaleResult::ScaleResult(const ScaleResult &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
ScaleResult &ScaleResult::operator=(const ScaleResult &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
ScaleResult::ScaleResult(ScaleResult &&other) : pimpl(other.pimpl.take()) {}
ScaleResult &ScaleResult::operator=(ScaleResult &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
ScaleResult::~ScaleResult() {}

//  :: Accessors ::
//  :: Scale name ::
QString ScaleResult::getScaleName() const {
	return pimpl->scaleName;
}
void ScaleResult::setScaleName(const QString &scaleName) {
	pimpl->scaleName = scaleName;
}

//  :: Result ::
QString ScaleResult::getResult() const {
	return pimpl->result;
}
void ScaleResult::setResult(const QString &result) {
	pimpl->result = result;
}

//  :: Serializable ::

QJsonObject ScaleResult::toJson() const {
	QJsonObject json;
	json[SCALE_NAME_JSON_KEY] = getScaleName();
	json[RESULT_JSON_KEY] = getResult();
	return json;
}

void ScaleResult::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(SCALE_NAME_JSON_KEY) &&
			json[SCALE_NAME_JSON_KEY].isString()) {
		setScaleName(json[SCALE_NAME_JSON_KEY].toString());
	}
	if (json.contains(RESULT_JSON_KEY) &&
			json[RESULT_JSON_KEY].isString()) {
		setResult(json[RESULT_JSON_KEY].toString());
	}
}
