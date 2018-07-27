#pragma once

#include <QObject>

template <typename>
class QList;

class ScaleResult;

class IQuestionsOutput : public QObject {
    Q_OBJECT

protected:
    IQuestionsOutput(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void cancelButtonClicked();
    void instructionButtonClicked();
    void resultsCounted(const QList<ScaleResult> &results);
};
