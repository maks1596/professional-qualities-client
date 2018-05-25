#include "AnswerOption.h"

#include <QString>

//  :: Constants ::

const QString ID_JSON_KEY = "id";
const QString FORMULATION_JSON_KEY = "formulation";

//  :: Implementation ::

struct AnswerOption::Implementation {
	int id = 0;
	QString formulation = "";
};

//  :: Lifecycle ::
//  :: Constructors ::
AnswerOption::AnswerOption(int id/*= 0*/)
	: pimpl(new Implementation())
{
	setId(id);
}

AnswerOption::AnswerOption(const QString &formulation) :
	AnswerOption()
{
	setFormulation(formulation);
}

AnswerOption::AnswerOption(const int &id,
						   const QString &formulation) :
	AnswerOption(id)
{
	setFormulation(formulation);
}

//  :: Copy ::
AnswerOption::AnswerOption(const AnswerOption &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
AnswerOption &AnswerOption::operator=(const AnswerOption &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
AnswerOption::AnswerOption(AnswerOption &&other) : pimpl(other.pimpl.take()) {}
AnswerOption &AnswerOption::operator=(AnswerOption &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
AnswerOption::~AnswerOption() {}

//  :: Accessors ::
//  :: ID ::
int AnswerOption::getId() const {
	return pimpl->id;
}
void AnswerOption::setId(int id) {
	pimpl->id = id;
}

//   :: Formulation ::
QString AnswerOption::getFormulation() const {
	return pimpl->formulation;
}
void AnswerOption::setFormulation(const QString &formulation) {
	pimpl->formulation = formulation;
}

//  :: Serializable ::

QJsonObject AnswerOption::toJson() const {
	QJsonObject json;
	json[ID_JSON_KEY] = getId();
	json[FORMULATION_JSON_KEY] = getFormulation();
	return json;
}

void AnswerOption::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
		setId(json[ID_JSON_KEY].toInt());
	}
	if (json.contains(FORMULATION_JSON_KEY) &&
			json[FORMULATION_JSON_KEY].isString()) {
		setFormulation(json[FORMULATION_JSON_KEY].toString());
	}
}
