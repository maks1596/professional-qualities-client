#pragma once

#include <QLabel>

class InstructionLabel : public QLabel {
public:
    explicit InstructionLabel(QWidget *parent = nullptr);

    explicit InstructionLabel(const QString &instruction,
                              QWidget *parent = nullptr);

    explicit InstructionLabel(const QString &testName,
                              const QString &instruction,
                              QWidget *parent = nullptr);
};
