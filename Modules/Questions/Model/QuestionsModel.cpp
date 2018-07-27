#include "QuestionsModel.h"

#include <QStringListModel>
#include <QTime>

#include "Entities/Answer/Answer.h"
#include "Entities/Test/Test.h"

//  :: Constants ::

enum QuestionsModelRoles {
    QuestionFormulationRole = Qt::UserRole + 1,
    AnswerIndexRole,
    AnswersRole
};

const QString QUESTION_FORMULATION_ROLE_NAME = "questionFormulation";
const QString ANSWER_INDEX_ROLE_NAME = "answerIndex";
const QString ANSWERS_ROLE_NAME = "answers";

//  :: Private functions headers ::

template <typename... Args>
QList<QuestionWithAnswer> makeQuestionsWithAnswer(const Questions &questions,
                                                  Args... args);

//  :: Lifecycle ::

QuestionsModel::QuestionsModel(const Test &test, QObject *parent)
    : QAbstractListModel(parent),
      m_testId(test.getId()),
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
    if (!index.isValid()) {
        return QVariant();
    }
    int row = index.row();

    switch (role) {
    case Qt::DisplayRole: {
        const auto &data = getQuestionsWithAnswer().at(row);
        return QVariant::fromValue(data);
    } break;

    case QuestionFormulationRole: {
        return getQuestionsWithAnswer().at(row).getFormulation();
    } break;

    case AnswerIndexRole: {
        return getQuestionsWithAnswer().at(row).getAnswerIndex();
    } break;

    case AnswersRole: {
        auto questionWithAnswers = getQuestionsWithAnswer().at(row);
        auto answerOptionsFormulations = questionWithAnswers.getAnswerOptionsFormulations();
        auto model = new QStringListModel(answerOptionsFormulations);
        return QVariant::fromValue(model);
    } break;
    }

    return QVariant();
}

QHash<int, QByteArray> QuestionsModel::roleNames() const {
    auto roles = QAbstractListModel::roleNames();

    roles[QuestionFormulationRole] = QUESTION_FORMULATION_ROLE_NAME.toLocal8Bit();
    roles[AnswerIndexRole] = ANSWER_INDEX_ROLE_NAME.toLocal8Bit();
    roles[AnswersRole] = ANSWERS_ROLE_NAME.toLocal8Bit();

    return roles;
}

Qt::ItemFlags QuestionsModel::flags(const QModelIndex &index) const {
    if  (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool QuestionsModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) {
        return false;
    }

    if (role == AnswerIndexRole) {
        m_questionsWithAnswer[index.row()].setAnswerIndex(value.toInt());
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

//  :: Public accessors ::
//  :: Test ID ::
int QuestionsModel::getTestId() const {
    return m_testId;
}
void QuestionsModel::setTestId(int testId) {
    m_testId = testId;
}

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
QList<QuestionWithAnswer> &QuestionsModel::getQuestionsWithAnswer() {
    return m_questionsWithAnswer;
}
void QuestionsModel::setQuestionsWithAnswer(const QList<QuestionWithAnswer> &questionsWithAnswer) {
    beginResetModel();
    m_questionsWithAnswer = questionsWithAnswer;
    endResetModel();
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

//  :: Public methods ::

bool QuestionsModel::areAllQuestionsHaveAnswers() const {
    for (const auto &questionWithAnswer : getQuestionsWithAnswer()) {
        if (!questionWithAnswer.hasAnswer()) {
            return false;
        }
    }
    return true;
}

QList<Answer> QuestionsModel::getAnswers() const {
    QList<Answer> answers;
    answers.reserve(rowCount());

    for (const auto &questionWithAnswer : getQuestionsWithAnswer()) {
        answers.append(Answer(questionWithAnswer.getId(),
                              questionWithAnswer.getAnswer().getId()));
    }

    return answers;
}

#ifdef QT_DEBUG
void QuestionsModel::setRandomAnswers() {
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    auto questionsCount = rowCount();

    for (int questionIndex = 0; questionIndex < questionsCount; ++questionIndex) {
        const auto &questionWithAnswer = getQuestionsWithAnswer().at(questionIndex);
        auto answerOptionsCount = questionWithAnswer.getAnswerOptions().size();
        auto answerIndex = qrand() % answerOptionsCount;
        setData(index(questionIndex), answerIndex, AnswerIndexRole);
    }
}
#endif

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
