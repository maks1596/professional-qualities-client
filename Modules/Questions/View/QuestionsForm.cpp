#include "QuestionsForm.h"
#include "ui_QuestionsForm.h"

#include "../Model/QuestionsModel.h"

//  :: Lifecycle ::

QuestionsForm::QuestionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionsForm)
{
    ui->setupUi(this);
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
}
