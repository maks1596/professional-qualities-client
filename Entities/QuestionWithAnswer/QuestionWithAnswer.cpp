#include "QuestionWithAnswer.h"

//  :: Lifecycle ::

QuestionWithAnswer::QuestionWithAnswer(const Question &question)
    : Question(question) { }

QuestionWithAnswer::QuestionWithAnswer(const Question &question,
                                       const AnswerOptions &answerOptions)
    : Question(question)
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

const AnswerOption &QuestionWithAnswer::getAnswer() const {
    return getAnswerOptions().at(getAnswerIndex());
}
