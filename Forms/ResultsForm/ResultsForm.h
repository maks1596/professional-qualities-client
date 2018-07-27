#pragma once

#include <QWidget>

namespace Ui {
class ResultsForm;
}

class ScaleResult;

class ResultsForm : public QWidget {
    Q_OBJECT

public:
    explicit ResultsForm(const QString &testName,
                         const QList<ScaleResult> &results,
                         QWidget *parent = nullptr);
    ~ResultsForm();

    QString getTestName() const;
    void setTestName(const QString &testName);

signals:
    void finishTestButtonClicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void setResults(const QList<ScaleResult> &results);

    QString m_testName;
    Ui::ResultsForm *ui;
};
