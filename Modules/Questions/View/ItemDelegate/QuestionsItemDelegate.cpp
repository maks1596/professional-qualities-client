#include "QuestionsItemDelegate.h"

#include <QPainter>

#include "Entities/QuestionWithAnswer/QuestionWithAnswer.h"
#include "Forms/QuestionForm/QuestionForm.h"


#include <QApplication>


QuestionsItemDelegate::QuestionsItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{ }

void QuestionsItemDelegate::paint(QPainter *painter,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    if (index.data().canConvert<QuestionWithAnswer>()) {
        QuestionWithAnswer questionWithAnswer = qvariant_cast<QuestionWithAnswer>(index.data());

        auto rect = option.rect;
        painter->drawText(rect, questionWithAnswer.getFormulation());
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
