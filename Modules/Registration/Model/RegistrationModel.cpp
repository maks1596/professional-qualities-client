#include "RegistrationModel.h"

#include "Entities/RegistrationData/RegistrationData.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString REGISTRATION_API = "registration";

const QString USER_ID_JSON_KEY = "userId";

//  :: Lifecycle ::

RegistrationModel::RegistrationModel(QObject *parent) :
	BaseModel(parent) { }

//  :: Public methods ::

void RegistrationModel::registration(const RegistrationData &data) {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonObject)),
			SLOT(jsonUserIdGot(QJsonObject)));
	requester->sendRequest(REGISTRATION_API,
						   RequestType::POST,
						   data.toJson());
}

//  :: Private slots ::

void RegistrationModel::jsonUserIdGot(const QJsonObject &jsonUserId) {
	int userId = 0;
	if (jsonUserId.contains(USER_ID_JSON_KEY) &&
			jsonUserId[USER_ID_JSON_KEY].isDouble()) {
		userId = jsonUserId[USER_ID_JSON_KEY].toInt();
	}
	emit registrationSuccessed(userId);
}
