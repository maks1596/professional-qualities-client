#include "QuestionsModel.h"

#include "Entities/Test/Test.h"

//  :: Private functions headers ::

template <typename... Args>
QList<QuestionWithAnswer> makeQuestionsWithAnswer(const Questions &questions,
                                                  Args... args);

//  :: Lifecycle ::

QuestionsModel::QuestionsModel(const Test &test, QObject *parent)
    : QAbstractListModel(parent),
      m_testName(test.getName()),
      m_instruction(test.getInstruction())
{
    if (test.getAnswerOptionsType() == GENERAL) {
        setQuestionsWithAnswer(test.getQuestions(),
                                test.getGeneralAnswerOptions());
    } else {
        setQuestionsWithAnswer(test.getQuestions());
    }
}

//  :: QAbstractListModel ::

int QuestionsModel::rowCount(const QModelIndex &) const {
    return getQuestionsWithAnswer().size();
}

QVariant QuestionsModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        int row = index.row();
        const auto &data = getQuestionsWithAnswer().at(row);
        return QVariant::fromValue(data);
    }
    return QVariant();
}

//  :: Public accessors ::
//  :: Test name ::
QString QuestionsModel::getTestName() const {
    return m_testName;
}
void QuestionsModel::setTestName(const QString &testName) {
    m_testName = testName;
}

//  :: Instruction ::
QString QuestionsModel::getInstruction() const {
    return m_instruction;
}
void QuestionsModel::setInstruction(const QString &instruction) {
    m_instruction = instruction;
}

//  :: Questions with answer ::
const QList<QuestionWithAnswer> &QuestionsModel::getQuestionsWithAnswer() const {
    return m_questionsWithAnswer;
}
void QuestionsModel::setQuestionsWithAnswer(const QList<QuestionWithAnswer> &questionsWithAnswer) {
    m_questionsWithAnswer = questionsWithAnswer;
}

void QuestionsModel::setQuestionsWithAnswer(const Questions &questions) {
    auto questionsWithAnswer = makeQuestionsWithAnswer(questions);
    setQuestionsWithAnswer(questionsWithAnswer);
}

void QuestionsModel::setQuestionsWithAnswer(const Questions &questions,
                                             const AnswerOptions &generalAnswerOptions) {
    auto questionsWithAnswer = makeQuestionsWithAnswer(questions,
                                                       generalAnswerOptions);
    setQuestionsWithAnswer(questionsWithAnswer);
}

//  :: Private functions ::

template <typename... Args>
QList<QuestionWithAnswer> makeQuestionsWithAnswer(const Questions &questions,
                                                  Args... args) {
    QList<QuestionWithAnswer> questionsWithAnswer;
    questionsWithAnswer.reserve(questions.size());

    for (const auto &question : questions) {
        QuestionWithAnswer questionWithAnswer(question, args...);
        questionsWithAnswer.append(questionWithAnswer);
    }

    return questionsWithAnswer;
}
