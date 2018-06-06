#include "LoginForm.h"
#include "ui_LoginForm.h"

#include "../Model/AutorizationModel.h"
#include "Entities/AutorizationData/AutorizationData.h"
#include "Modules/Registration/View/RegistrationForm.h"
#include "SharedStorage/SharedStorage.h"

//  :: Lifecycle ::
//  :: Constructors ::
LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    ui->errorMessage->setStyleSheet("QLabel {color : red; }");
    ui->errorMessage->hide();

    connect(ui->login, &QLineEdit::returnPressed,
            [&] { ui->password->setFocus(); });
    connect(ui->password, &QLineEdit::returnPressed,
            ui->loginBtn, &QPushButton::click);

    connect(ui->login, &QLineEdit::textEdited,
            ui->errorMessage, &QLabel::hide);
    connect(ui->password, &QLineEdit::textEdited,
            ui->errorMessage, &QLabel::hide);

    connect(ui->loginBtn, &QPushButton::clicked,
			this, &LoginForm::onLoginBtnClicked);

#ifdef QT_DEBUG
    ui->login->setText("user");
    ui->password->setText("password");
#endif

	initModel();
}

//  :: Destructor ::
LoginForm::~LoginForm() {
    delete ui;
}

//  :: Private slots ::

void LoginForm::onLoginBtnClicked() {
	m_model->autorize({ui->login->text(),
					   ui->password->text()});
}

void LoginForm::onLoginSuccess(int userId) {
	SharedStorage::setUserId(userId);
	emit loginSuccessed();
}

void LoginForm::showErrorMessage() {
	ui->errorMessage->show();
	QApplication::alert(this);
}

void LoginForm::on_registrationButton_clicked() {
	auto registrationView = new RegistrationForm();
	hide();
	registrationView->show();

	connect(registrationView, &RegistrationForm::registrationSuccessed,
			this, &LoginForm::onLoginSuccess);
	connect(registrationView, &RegistrationForm::registrationCanceled,
			this, &LoginForm::show);

	connect(registrationView, &RegistrationForm::registrationSuccessed,
			registrationView, &RegistrationForm::deleteLater);
	connect(registrationView, &RegistrationForm::registrationCanceled,
			registrationView, &RegistrationForm::deleteLater);
}

//  :: Private methods ::

void LoginForm::initModel() {
	m_model = new AutorizationModel(this);
	connect(m_model, &AutorizationModel::autorizationSuccess,
			this, &LoginForm::onLoginSuccess);
	connect(m_model, &AutorizationModel::autorizationFailed,
			this, &LoginForm::showErrorMessage);
}
