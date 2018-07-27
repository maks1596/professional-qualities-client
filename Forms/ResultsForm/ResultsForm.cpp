#include "ResultsForm.h"
#include "ui_ResultsForm.h"

#include "ElidedText/ElidedText.h"
#include "Forms/ResultForm/ResultForm.h"

//  :: Lifecycle ::

ResultsForm::ResultsForm(const QString &testName,
                         const QList<ScaleResult> &results,
                         QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultsForm)
{
    ui->setupUi(this);

    setTestName(testName);
    setResults(results);

    connect(ui->finishButton, &QPushButton::clicked,
            this, &ResultsForm::finishTestButtonClicked);
}

ResultsForm::~ResultsForm() {
    delete ui;
}
void ResultsForm::setTestName(const QString &testName) {
    m_testName = testName;
    auto elidedTestName = elidedText(ui->testNameLabel, m_testName);
    ui->testNameLabel->setText(elidedTestName);
}

//  :: Public accessors ::

QString ResultsForm::getTestName() const {
    return m_testName;
}

//  :: Protected methods ::

void ResultsForm::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    setTestName(getTestName());
}

//  :: Private methods ::

void ResultsForm::setResults(const QList<ScaleResult> &results) {
    for(const auto &result : results) {
        ui->resultsWidget->layout()->addWidget(new ResultForm(result, this));
    }
}
