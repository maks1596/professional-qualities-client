#pragma once

#include <QStyledItemDelegate>

class QuestionsItemDelegate : public QStyledItemDelegate {
public:
    QuestionsItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};
