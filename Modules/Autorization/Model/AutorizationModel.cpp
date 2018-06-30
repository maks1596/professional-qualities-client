#include "AutorizationModel.h"

#include "Entities/AutorizationData/AutorizationData.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString AUTORIZE_API = "autorization";

const QString USER_ID_JSON_KEY = "userId";

//  :: Lifecycle ::

AutorizationModel::AutorizationModel(QObject *parent/*= nullptr*/)
	: BaseService(parent)
{ }

//  :: Public methods ::

void AutorizationModel::autorize(const AutorizationData &data) const {
	auto requester = makeRequester();

	disconnect(requester, &Requester::failure,
			   this, &BaseService::error);
	connect(requester, &Requester::failure,
			this, &AutorizationModel::autorizationFailed);
	connect(requester, SIGNAL(success(QJsonObject)),
			SLOT(jsonUserIdGot(QJsonObject)));

	requester->sendRequest(AUTORIZE_API,
						   RequestType::POST,
						   data.toJson());
}

//  :: Private slots ::

void AutorizationModel::jsonUserIdGot(const QJsonObject &jsonUserId) {
	int userId = 0;
	if (jsonUserId.contains(USER_ID_JSON_KEY) &&
			jsonUserId[USER_ID_JSON_KEY].isDouble()) {
		userId = jsonUserId[USER_ID_JSON_KEY].toInt();
	}
	emit autorizationSuccess(userId);
}
