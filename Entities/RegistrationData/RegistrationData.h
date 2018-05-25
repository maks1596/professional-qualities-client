#pragma once

#include "Serializable/Object/SerializableObject.h"

class RegistrationData : SerializableObject {
public:
	//  :: Lifecycle ::
	RegistrationData() = default;
	RegistrationData(const QString &login,
					 const QString &password,
					 const QString &name,
					 bool isProgrammer);

	//  :: Accessors ::
	QString getLogin() const;
	void setLogin(const QString &login);

	QString getPassword() const;
	void setPassword(const QString &password);

	QString getName() const;
	void setName(const QString &name);

	bool isProgrammer() const;
	void setIsProgrammer(bool isProgrammer);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	QString m_login;
	QString m_password;
	QString m_name;
	bool m_isProgrammer;
};
