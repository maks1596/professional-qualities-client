#include "TestsModel.h"

#include <QTimer>

#include "../Service/TestsService.h"
#include "SharedStorage/SharedStorage.h"
#include "TestsColumnIndex.h"

//  :: Constants ::

const QStringList kHorizontalHeaders = {
    "Название теста",
    "Статус"
};

const uint UPDATE_INTERVAL = 1000;

//  :: Lifecycle ::

TestsModel::TestsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    initTimer();
}

//  :: QAbstractTableModel ::

QVariant TestsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (section < kHorizontalHeaders.size()) {
                return kHorizontalHeaders[section];
            }
        } else {
            return section + 1;
        }
    }
    return QVariant();
}

int TestsModel::rowCount(const QModelIndex &) const {
    return m_tests.size();
}

int TestsModel::columnCount(const QModelIndex &) const {
    return TESTS_COLUMNS_AMOUNT;
}

QVariant TestsModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        auto row = index.row();
        const auto &test = m_tests[row];

        switch (index.column()) {
        case TESTS_NAME_COLUMN_INDEX: {
            return test.getName();
        } break;

        case TESTS_STATUS_COLUMN_INDEX: {
            auto status = test.getStatus();
            return stringWithTestStatus(status);
        } break;
        }
    }
    return QVariant();
}

//  :: Public accessors ::
//  :: Service ::
TestsService *TestsModel::getService() const {
    return m_service;
}
void TestsModel::setService(TestsService *service) {
    m_service = service;
    connect(m_service, &TestsService::testsGot,
            this, &TestsModel::setTests);
    connect(m_service, &TestsService::testGot,
            this, &TestsModel::testGot);
}

//  :: Tests ::
const QList<TestWithStatus> &TestsModel::getTests() const {
    return m_tests;
}
void TestsModel::setTests(const QList<TestWithStatus> &tests) {
    if (m_tests.isEmpty()) {
        resetModel(tests);
    } else {
        updateModel(tests);
    }
}

//  :: Public slots ::

void TestsModel::startUpdating() {
    update();
    m_timer->start();
}
void TestsModel::stopUpdating() {
    m_timer->stop();
}

void TestsModel::update() const {
    m_service->getTests(SharedStorage::getUserId());
}

void TestsModel::getTestAsync(const QModelIndex &idx) const {
    if (idx.isValid()) {
        auto testId = getTests().at(idx.row()).getId();
        m_service->getTest(testId);
    }
}

//  :: Private methods ::

inline
void TestsModel::initTimer() {
    m_timer = new QTimer(this);
    m_timer->setInterval(UPDATE_INTERVAL);
    connect(m_timer, &QTimer::timeout,
            this, &TestsModel::update);
}

inline
void TestsModel::resetModel(const QList<TestWithStatus> &newTests) {
    beginResetModel();
    m_tests = newTests;
    endResetModel();
}

inline
void TestsModel::updateModel(const QList<TestWithStatus> &tests) {
    checkRowsCountChanged(tests);
    m_tests = tests;
    emitAllDataChanged();
}

inline
void TestsModel::checkRowsCountChanged(const QList<TestWithStatus> &newTests) {
    int oldSize = m_tests.size(),
            newSize = newTests.size();
    if (oldSize < newSize) {
        beginInsertRows(QModelIndex(), oldSize, newSize - 1);
        endInsertRows();
    } else if (oldSize > newSize) {
        beginRemoveRows(QModelIndex(), newSize, oldSize - 1);
        endRemoveRows();
    }
}

inline
void TestsModel::emitAllDataChanged() {
    auto topLeft = index(0, 0);
    auto bottomRight = index(m_tests.size() - 1,
                             columnCount() - 1);
    emit dataChanged(topLeft, bottomRight);
}
