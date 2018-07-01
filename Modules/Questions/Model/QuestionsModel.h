#pragma once

#include <QAbstractListModel>

#include "Entities/QuestionWithAnswer/QuestionWithAnswer.h"

class Test;

class QuestionsModel : public QAbstractListModel {
    Q_OBJECT

public:
    //  :: Lifecycle ::
    explicit QuestionsModel(const Test &test, QObject *parent = nullptr);

    //  :: QAbstractListModel ::
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //  :: Accessors ::
    const QList<QuestionWithAnswer> &getQuestionsWithAnswers() const;
    void setQuestionsWithAnswers(const QList<QuestionWithAnswer> &questionsWithAnswers);

    void setQuestionsWithAnswers(const Questions &questions);
    void setQuestionsWithAnswers(const Questions &questions,
                                 const AnswerOptions &generalAnswerOptions);

private:
    QString m_instruction;
    QList<QuestionWithAnswer> m_questionsWithAnswers;
};
