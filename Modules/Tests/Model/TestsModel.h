#pragma once

#include <QAbstractTableModel>
#include <QList>

#include "Entities/TestWithStatus/TestWithStatus.h"

class QTimer;
class Test;
class TestsService;

class TestsModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit TestsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //  :: Accessors ::
    TestsService *getService() const;
    void setService(TestsService *service);

    const QList<TestWithStatus> &getTests() const;
    void setTests(const QList<TestWithStatus> &tests);

public slots:
    void startUpdating();
    void stopUpdating();

    void update() const;

    void getTestAsync(const QModelIndex &idx) const;

signals:
    void testGot(const Test &test);

private:
    void initTimer();

    void resetModel(const QList<TestWithStatus> &newTests);
    void updateModel(const QList<TestWithStatus> &tests);

    void checkRowsCountChanged(const QList<TestWithStatus> &newTests);
    void emitAllDataChanged();

    QTimer *m_timer = nullptr;
    TestsService *m_service = nullptr;
    QList<TestWithStatus> m_tests;
};
