#pragma once

#include <QWidget>

#include "Entities/ScaleResult/ScaleResult.h"

namespace Ui {
class ResultForm;
}

class ResultForm : public QWidget {
Q_OBJECT

public:
	explicit ResultForm(const ScaleResult &result, QWidget *parent = 0);
	~ResultForm();

private:
	Ui::ResultForm *ui;
};
