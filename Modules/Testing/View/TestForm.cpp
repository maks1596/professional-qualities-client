#include "TestForm.h"

#include <QVBoxLayout>

#include "../TestWelcomeForm/TestWelcomeForm.h"

#include "Forms/InstructionLabel/InstructionLabel.h"
#include "Forms/ResultsForm/ResultsForm.h"

#include "Modules/Questions/Assembler/QuestionsAssembler.h"
#include "Modules/Questions/IQuestionsOutput.h"

//  :: Constants ::

const int BASE_WIDTH = 400;
const int BASE_HEIGHT = 300;

const QString WINDOW_TITLE = "Прохождение теста";

//  :: Lifecycle ::

TestForm::TestForm(const Test &test, QWidget *parent) :
	QWidget(parent),
    m_test(test)
{
    setLayout(new QVBoxLayout(this));
    layout()->setMargin(0);
    resize(BASE_WIDTH, BASE_HEIGHT);
    setWindowTitle(WINDOW_TITLE);

    auto welcomeForm = createTestWelcomeForm(test);
    replaceCurrentWidget(welcomeForm);
}

TestForm::~TestForm() {}

//  :: Private slots ::

void TestForm::showQuestions() {
    auto questionsForm = createQuestionsForm(m_test);
    replaceCurrentWidget(questionsForm);
}

void TestForm::showInstruction() {
    QLabel *instructionLabel = new InstructionLabel(m_test.getInstruction());
	connect(this, &TestForm::destroyed,
            instructionLabel, &QLabel::deleteLater);
    instructionLabel->show();
}

void TestForm::showResults(const QList<ScaleResult> &results) {
    replaceCurrentWidget(createResultsForm(results));
}

//  :: Private methods ::

QWidget *TestForm::createTestWelcomeForm(const Test &test) {
    auto welcomeForm = new TestWelcomeForm(test.getName(),
                                           test.getInstruction(),
                                           this);

    connect(welcomeForm, &TestWelcomeForm::cancelButtonClicked,
            this, &TestForm::canceled);
    connect(welcomeForm, &TestWelcomeForm::startTestButtonClicked,
            this, &TestForm::showQuestions);

    return welcomeForm;
}

QWidget *TestForm::createQuestionsForm(const Test &test) {
    QWidget *view;
    IQuestionsOutput *output;
    std::tie(view, output) = QuestionsAssembler::assembly(test, this);

    connect(output, &IQuestionsOutput::cancelButtonClicked,
            this, &TestForm::canceled);
    connect(output, &IQuestionsOutput::instructionButtonClicked,
            this, &TestForm::showInstruction);
    connect(output, &IQuestionsOutput::resultsCounted,
            this, &TestForm::showResults);

    return view;
}

QWidget *TestForm::createResultsForm(const QList<ScaleResult> &results) {
    auto resultsForm = new ResultsForm(m_test.getName(),
                                       results,
                                       this);
    connect(resultsForm, &ResultsForm::finishTestButtonClicked,
            this, &TestForm::canceled);
    return resultsForm;
}

void TestForm::replaceCurrentWidget(QWidget *widget) {
    auto widgetsCount = layout()->count();
    if (widgetsCount > 0) {
        layout()->takeAt(0)->widget()->deleteLater();
    }
    layout()->addWidget(widget);
    widget->show();
}
