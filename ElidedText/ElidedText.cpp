#include "ElidedText.h"

#include <QLabel>

QString elidedText(const QLabel *label, const QString &text) {
    auto font = label->font();
    auto width = label->width();
    QFontMetrics fontMetrics(font);
    return fontMetrics.elidedText(text, Qt::ElideRight, width);
}
