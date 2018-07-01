#pragma once

#include <QWidget>

namespace Ui {
class TestWelcomeForm;
}

class TestWelcomeForm : public QWidget {
    Q_OBJECT

public:
    //  :: Lifecycle ::
    explicit TestWelcomeForm(const QString &testName,
                             const QString &instruction,
                             QWidget *parent = nullptr);
    ~TestWelcomeForm();

    //  :: Accessors ::

    QString getTestName() const;
    void setTestName(const QString &testName);

    QString getInstruction() const;
    void setInstruction(const QString &instruction);

signals:
    void cancelButtonClicked();
    void startTestButtonClicked();

private:
    Ui::TestWelcomeForm *ui;
};
