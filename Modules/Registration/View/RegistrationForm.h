#pragma once

#include <QWidget>

namespace Ui {
class RegistrationForm;
}

class RegistrationModel;

class RegistrationForm : public QWidget {
Q_OBJECT

public:
	explicit RegistrationForm(QWidget *parent = nullptr);
	~RegistrationForm();

signals:
	void registrationSuccessed(int userId);
	void registrationCanceled();

private slots:
	void on_okButton_clicked();
	void showErrorMessage(const QString &message);
	void checkAllFieldsFilledIn();

private:
	bool doPasswordsMatch() const;
	bool doAllFieldsFilledIn() const;
	void initModel();

	Ui::RegistrationForm *ui;
	RegistrationModel *m_model;
};
