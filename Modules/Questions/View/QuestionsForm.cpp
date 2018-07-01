#include "QuestionsForm.h"
#include "ui_QuestionsForm.h"

#include "../Model/QuestionsModel.h"
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
    ui->testNameLabel->setText(model->getTestName());
    ui->questionsListView->setModel(model);
}
