#include "QuestionsItemDelegate.h"

#include <QDebug>
#include <QPainter>

#include "Entities/QuestionWithAnswer/QuestionWithAnswer.h"

//  :: Lifecycle ::

QuestionsItemDelegate::QuestionsItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{ }

//  :: Public methods ::

QSize QuestionsItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const {
    auto size = QStyledItemDelegate::sizeHint(option, index);

    if (index.data().canConvert<QuestionWithAnswer>()) {
        QuestionWithAnswer questionWithAnswer = qvariant_cast<QuestionWithAnswer>(index.data());
        size.setHeight(size.height() * (1 + questionWithAnswer.getAnswerOptions().size()));
    }

    return size;
}

void QuestionsItemDelegate::paint(QPainter *painter,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    if (index.data().canConvert<QuestionWithAnswer>()) {
        QuestionWithAnswer questionWithAnswer = qvariant_cast<QuestionWithAnswer>(index.data());

        auto rect = option.rect;
        qDebug() << index.row() << ": rect " << rect;

        painter->drawText(rect, questionWithAnswer.getFormulation());
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
