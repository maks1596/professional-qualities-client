#pragma once

#include <QWidget>

namespace Ui {
class LoginForm;
}

class AutorizationModel;

class LoginForm : public QWidget {
Q_OBJECT
public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

signals:
    void loginSuccessed();
	void registrationButtonClicked();

private slots:
    void onLoginBtnClicked();
	void onLoginSuccess(int userId);
	void showErrorMessage();

	void on_registrationButton_clicked();

private:
	void initModel();

    Ui::LoginForm *ui;
	AutorizationModel *m_model;
};
