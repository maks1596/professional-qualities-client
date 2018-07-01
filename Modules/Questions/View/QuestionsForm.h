#pragma once

#include <QWidget>

namespace Ui {
class QuestionsForm;
}

class QuestionsModel;

class QuestionsForm : public QWidget {
    Q_OBJECT

public:
    explicit QuestionsForm(QWidget *parent = 0);
    ~QuestionsForm();

    QuestionsModel *getModel() const;
    void setModel(QuestionsModel *model);

private:
    QuestionsModel *m_model;
    Ui::QuestionsForm *ui;
};
