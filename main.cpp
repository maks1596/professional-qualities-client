#include <QApplication>

#include "Configurator/Configurator.h"

#include "Entities/Answer/Answer.h"
#include "Entities/ScaleResult/ScaleResult.h"
#include "Entities/Test/Test.h"

#include "Modules/Autorization/View/LoginForm.h"

#include "Modules/Tests/Assembler/TestsAssembler.h"
#include "Modules/Tests/View/MainWindow.h"


int main(int argc, char *argv[]) {
	QStringList paths = QCoreApplication::libraryPaths();
	paths.append(".");
	paths.append("imageformats");
	paths.append("platforms");
	QCoreApplication::setLibraryPaths(paths);

	QApplication a(argc, argv);
	Configurator::readConfigurations();

    auto mainWindow = TestsAssembler::assembly();
	LoginForm loginForm;

	QObject::connect(&loginForm, &LoginForm::loginSuccessed,
                     mainWindow, &MainWindow::show);
	QObject::connect(&loginForm, &LoginForm::loginSuccessed,
					 &loginForm, &LoginForm::hide);
	QObject::connect(&loginForm, &LoginForm::loginSuccessed,
                     mainWindow, &MainWindow::startUpdating);

	loginForm.show();

	return a.exec();
}
