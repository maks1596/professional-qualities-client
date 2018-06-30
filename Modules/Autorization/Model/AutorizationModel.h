#pragma once

#include "BaseModel/BaseModel.h"

class AutorizationData;

class AutorizationModel : public BaseService {
Q_OBJECT

public:
	//  :: Lifecycle ::
	AutorizationModel(QObject *parent = nullptr);

	/**
	 * @brief Метод производит авторизацию на основе переданных данных
	 * @param data - данные для авторизации
	 */
	void autorize(const AutorizationData &data) const;

signals:
	void autorizationSuccess(int userId);
	void autorizationFailed();

private slots:
	void jsonUserIdGot(const QJsonObject &jsonUserId);
};
