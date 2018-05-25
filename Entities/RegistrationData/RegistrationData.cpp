#include "RegistrationData.h"

//  :: Constants ::

const QString LOGIN_JSON_KEY = "login";
const QString PASSWORD_JSON_KEY = "password";
const QString NAME_JSON_KEY = "name";
const QString IS_PROGRAMMER_JSON_KEY = "isProgrammer";

//  :: Lifecycle ::

RegistrationData::RegistrationData(const QString &login,
								   const QString &password,
								   const QString &name,
								   bool isProgrammer){
	setLogin(login);
	setPassword(password);
	setName(name);
	setIsProgrammer(isProgrammer);
}

//  :: Public Accessors ::
//  :: Login ::

QString RegistrationData::getLogin() const {
	return m_login;
}
void RegistrationData::setLogin(const QString &login) {
	m_login = login;
}

//  :: Password ::
QString RegistrationData::getPassword() const {
	return m_password;
}
void RegistrationData::setPassword(const QString &password) {
	m_password = password;
}

//  :: Name ::
QString RegistrationData::getName() const {
	return m_name;
}
void RegistrationData::setName(const QString &name) {
	m_name = name;
}

//  :: Is programmer ::
bool RegistrationData::isProgrammer() const {
	return m_isProgrammer;
}
void RegistrationData::setIsProgrammer(bool isProgrammer) {
	m_isProgrammer = isProgrammer;
}

//  :: Serializable ::

QJsonObject RegistrationData::toJson() const {
	QJsonObject json;
	json[LOGIN_JSON_KEY] = getLogin();
	json[PASSWORD_JSON_KEY] = getPassword();
	json[NAME_JSON_KEY] = getName();
	json[IS_PROGRAMMER_JSON_KEY] = isProgrammer();
	return json;
}
void RegistrationData::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(LOGIN_JSON_KEY) && json[LOGIN_JSON_KEY].isString()) {
		setLogin(json[LOGIN_JSON_KEY].toString());
	}
	if (json.contains(PASSWORD_JSON_KEY) && json[PASSWORD_JSON_KEY].isString()) {
		setPassword(json[PASSWORD_JSON_KEY].toString());
	}
	if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
		setName(json[NAME_JSON_KEY].toString());
	}
	if (json.contains(IS_PROGRAMMER_JSON_KEY) &&
			json[IS_PROGRAMMER_JSON_KEY].isBool()) {
		setIsProgrammer(json[IS_PROGRAMMER_JSON_KEY].toBool());
	}
}
