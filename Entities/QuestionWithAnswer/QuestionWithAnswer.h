#pragma once

#include "../Question/Question.h"

/**
 * @brief Класс представляет собой сущность вопроса с вариантами ответов и
 *        данным на вопрос ответом
 */
class QuestionWithAnswer : public Question {
public:

    //  :: Lifecycle ::
    //  :: Constructors ::
    QuestionWithAnswer() = default;
    QuestionWithAnswer(const Question &question);
    QuestionWithAnswer(const Question &question,
                       const AnswerOptions &answerOptions);

    //  :: Accessors ::
    int getAnswerIndex() const;
    void setAnswerIndex(int answerIndex);

    /**
     * @brief Метод возвращает данный на вопрос ответ
     * @return сущность ответа
     */
    const AnswerOption &getAnswer() const;

private:
    int m_answerIndex = -1;
};
