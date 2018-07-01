#include "QuestionsForm.h"
#include "ui_QuestionsForm.h"

#include "../Model/QuestionsModel.h"
#include "ElidedText/ElidedText.h"
#include "ItemDelegate/QuestionsItemDelegate.h"

//  :: Lifecycle ::

QuestionsForm::QuestionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionsForm)
{
    ui->setupUi(this);

    auto itemDelegate = new QuestionsItemDelegate(ui->questionsListView);
    ui->questionsListView->setItemDelegate(itemDelegate);

    connect(ui->cancelButton, &QPushButton::clicked,
            this, &QuestionsForm::cancelButtonClicked);
}

QuestionsForm::~QuestionsForm() {
    delete ui;
}

//  :: Public accessors ::

QuestionsModel *QuestionsForm::getModel() const {
    return m_model;
}
void QuestionsForm::setModel(QuestionsModel *model) {
    m_model = model;
    ui->questionsListView->setModel(model);
}

//  :: Protected methods ::

void QuestionsForm::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    setTestName(getModel()->getTestName());
}

//  :: Private methods ::

void QuestionsForm::setTestName(const QString &testName) {
    auto elidedTestName = elidedText(ui->testNameLabel, testName);
    ui->testNameLabel->setText(elidedTestName);
}

