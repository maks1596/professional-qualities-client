#include "SharedStorage.h"

//  :: Private static members ::

int SharedStorage::m_userId = 0;

//  :: Accessors ::
//  :: User ID ::
int SharedStorage::getUserId() {
	return m_userId;
}
void SharedStorage::setUserId(int userId) {
	m_userId = userId;
}
