#pragma once

/**
 * @brief Класс обеспечивает доступ к общим данным из разных модулей приложения
 */
class SharedStorage {
public:
	//  :: Accessors ::
	static int getUserId();
	static void setUserId(int userId);

private:
	static int m_userId;
};
