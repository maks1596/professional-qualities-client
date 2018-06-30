#pragma once

#include <BaseModel/BaseModel.h>

class RegistrationData;

class RegistrationModel : public BaseService {
	Q_OBJECT

public:
	RegistrationModel(QObject *parent = nullptr);

	void registration(const RegistrationData &data);

signals:
	void registrationSuccessed(int userId);

private slots:
	void jsonUserIdGot(const QJsonObject &jsonUserId);
};
