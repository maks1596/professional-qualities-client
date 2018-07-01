#include "QuestionsModel.h"

#include "Entities/Test/Test.h"

Q_DECLARE_METATYPE(QuestionWithAnswer)

//  :: Private functions headers ::

template <typename... Args>
QList<QuestionWithAnswer> makeQuestionsWithAnswer(const Questions &questions,
                                                  Args... args);

//  :: Lifecycle ::

QuestionsModel::QuestionsModel(const Test &test, QObject *parent)
    : QAbstractListModel(parent),
      m_instruction(test.getInstruction())
{
    if (test.getAnswerOptionsType() == GENERAL) {
        setQuestionsWithAnswers(test.getQuestions(),
                                test.getGeneralAnswerOptions());
    } else {
        setQuestionsWithAnswers(test.getQuestions());
    }
}

//  :: QAbstractListModel ::

int QuestionsModel::rowCount(const QModelIndex &) const {
    return getQuestionsWithAnswers().size();
}

QVariant QuestionsModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        int row = index.row();
        const auto &data = getQuestionsWithAnswers().at(row);
        return QVariant::fromValue(data);
    }
    return QVariant();
}

//  :: Public accessors ::

const QList<QuestionWithAnswer> &QuestionsModel::getQuestionsWithAnswers() const {
    return m_questionsWithAnswers;
}
void QuestionsModel::setQuestionsWithAnswers(const QList<QuestionWithAnswer> &questionsWithAnswers) {
    m_questionsWithAnswers = questionsWithAnswers;
}

void QuestionsModel::setQuestionsWithAnswers(const Questions &questions) {
    auto questionsWithAnswer = makeQuestionsWithAnswer(questions);
    setQuestionsWithAnswers(questionsWithAnswer);
}

void QuestionsModel::setQuestionsWithAnswers(const Questions &questions,
                                             const AnswerOptions &generalAnswerOptions) {
    auto questionsWithAnswer = makeQuestionsWithAnswer(questions,
                                                       generalAnswerOptions);
    setQuestionsWithAnswers(questionsWithAnswer);
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
