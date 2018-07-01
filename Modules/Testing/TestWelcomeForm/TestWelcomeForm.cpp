#include "TestWelcomeForm.h"
#include "ui_TestWelcomeForm.h"

//  :: Lifecycle ::

TestWelcomeForm::TestWelcomeForm(const QString &testName,
                                 const QString &instruction,
                                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWelcomeForm)
{
    ui->setupUi(this);

    setTestName(testName);
    setInstruction(instruction);

    connect(ui->cancelButton, &QPushButton::clicked,
            this, &TestWelcomeForm::cancelButtonClicked);
    connect(ui->startTestButton, &QPushButton::clicked,
            this, &TestWelcomeForm::startTestButtonClicked);
}

TestWelcomeForm::~TestWelcomeForm() {
    delete ui;
}

//  :: Public accessors ::
//  :: Test name ::
QString TestWelcomeForm::getTestName() const {
    return ui->testNameLabel->text();
}
void TestWelcomeForm::setTestName(const QString &testName) {
    ui->testNameLabel->setText(testName);
}

//  :: Instruction ::
QString TestWelcomeForm::getInstruction() const {
    return ui->instructionLabel->text();
}
void TestWelcomeForm::setInstruction(const QString &instruction) {
    ui->instructionLabel->setText(instruction);
}
