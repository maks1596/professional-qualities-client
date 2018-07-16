#include "QuestionWithAnswer.h"

//  :: Constatns ::

const int DEFAULT_ANSWER_INDEX = -1;

//  :: Lifecycle ::

QuestionWithAnswer::QuestionWithAnswer()
    : m_answerIndex(DEFAULT_ANSWER_INDEX){

}

QuestionWithAnswer::QuestionWithAnswer(const Question &question)
    : Question(question),
      m_answerIndex(DEFAULT_ANSWER_INDEX)
{ }

QuestionWithAnswer::QuestionWithAnswer(const Question &question,
                                       const AnswerOptions &answerOptions)
    : QuestionWithAnswer(question)
{
    setAnswerOptions(answerOptions);
}

//  :: Public accessors ::
//  :: Answer index ::
int QuestionWithAnswer::getAnswerIndex() const {
    return m_answerIndex;
}
void QuestionWithAnswer::setAnswerIndex(int answerIndex) {
    m_answerIndex = answerIndex;
}

//  :: Public methods ::

bool QuestionWithAnswer::hasAnswer() const {
    return m_answerIndex != DEFAULT_ANSWER_INDEX;
}

const AnswerOption &QuestionWithAnswer::getAnswer() const {
    return getAnswerOptions().at(getAnswerIndex());
}
