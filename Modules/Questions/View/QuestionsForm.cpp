#include "QuestionsForm.h"
#include "ui_QuestionsForm.h"

#include <QMessageBox>
#include <QtQml/QQmlContext>

#include "../Model/QuestionsModel.h"
#include "ElidedText/ElidedText.h"

//  :: Constants ::

const QString MODEL_PROPERTY_NAME = "questionsModel";
const QString MESSAGE_TITLE = "Информация";
const QString NOT_ALL_QUESTIONS_HAVE_ANSWERS_MESSAGE = "Не на все вопросы дан ответ";

//  :: Lifecycle ::

QuestionsForm::QuestionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionsForm)
{
    ui->setupUi(this);

    connect(ui->cancelButton, &QPushButton::clicked,
            this, &QuestionsForm::cancelButtonClicked);
    connect(ui->finishTestButton, &QPushButton::clicked,
            this, &QuestionsForm::finishTestButtonClicked);

#ifdef QT_DEBUG
    m_randomAnswersButton = new QPushButton("Radom", this);
    ui->buttonsHorizontalLayout->addWidget(m_randomAnswersButton);
#endif
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
    auto qmlContext = ui->questionsListQuickWidget->rootContext();
    qmlContext->setContextProperty(MODEL_PROPERTY_NAME, m_model);

#ifdef QT_DEBUG
    connect(m_randomAnswersButton, &QPushButton::clicked,
            getModel(), &QuestionsModel::setRandomAnswers);
#endif
}

//  :: Public slots ::

void QuestionsForm::showNotAllQuestionsHaveAnswersMessage() {
    showMessage(NOT_ALL_QUESTIONS_HAVE_ANSWERS_MESSAGE);
}

void QuestionsForm::showMessage(const QString &message) {
    QMessageBox::information(this, MESSAGE_TITLE, message);
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

