#include "RegistrationForm.h"
#include "ui_RegistrationForm.h"

#include <QMessageBox>

#include "../Model/RegistrationModel.h"
#include "Entities/RegistrationData/RegistrationData.h"

//  :: Lifecycle ::

RegistrationForm::RegistrationForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::RegistrationForm)
{
	ui->setupUi(this);

	connect(ui->cancelButton, &QPushButton::clicked,
			this, &RegistrationForm::registrationCanceled);

	connect(ui->loginLineEdit, &QLineEdit::textChanged,
			this, &RegistrationForm::checkAllFieldsFilledIn);
	connect(ui->passwordLineEdit, &QLineEdit::textChanged,
			this, &RegistrationForm::checkAllFieldsFilledIn);
	connect(ui->repeatPasswordLineEdit, &QLineEdit::textChanged,
			this, &RegistrationForm::checkAllFieldsFilledIn);
	connect(ui->nameLineEdit, &QLineEdit::textChanged,
			this, &RegistrationForm::checkAllFieldsFilledIn);
	checkAllFieldsFilledIn();

	initModel();
}

RegistrationForm::~RegistrationForm() {
	delete ui;
}

//  :: Private slots ::

void RegistrationForm::on_okButton_clicked() {
	if (!doPasswordsMatch()) {
		showErrorMessage("Пароли не совпадают");
		return;
	}
	m_model->registration(RegistrationData(
							  ui->loginLineEdit->text(),
							  ui->passwordLineEdit->text(),
							  ui->nameLineEdit->text(),
							  ui->programmerCheckBox->isChecked()
						  ));
}

void RegistrationForm::showErrorMessage(const QString &message) {
	QMessageBox::critical(this, "Ошибка", message);
}

void RegistrationForm::checkAllFieldsFilledIn() {
	ui->okButton->setEnabled(doAllFieldsFilledIn());
}

//  :: Private methods ::

bool RegistrationForm::doPasswordsMatch() const {
	return ui->passwordLineEdit->text() == ui->repeatPasswordLineEdit->text();
}

bool RegistrationForm::doAllFieldsFilledIn() const {
	return !(ui->loginLineEdit->text().isEmpty() ||
			 ui->passwordLineEdit->text().isEmpty() ||
			 ui->repeatPasswordLineEdit->text().isEmpty() ||
			 ui->nameLineEdit->text().isEmpty());
}

void RegistrationForm::initModel() {
	m_model = new RegistrationModel(this);

	connect(m_model, &RegistrationModel::registrationSuccessed,
			this, &RegistrationForm::registrationSuccessed);
	connect(m_model, &RegistrationModel::error,
			this, &RegistrationForm::showErrorMessage);
}


