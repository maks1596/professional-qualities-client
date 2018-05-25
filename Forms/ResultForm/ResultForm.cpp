#include "ResultForm.h"
#include "ui_ResultForm.h"

ResultForm::ResultForm(const ScaleResult &result, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ResultForm)
{
	ui->setupUi(this);
	ui->scaleLbl->setText(result.getScaleName());
	ui->resultLbl->setText(result.getResult());
}

ResultForm::~ResultForm() {
	delete ui;
}
