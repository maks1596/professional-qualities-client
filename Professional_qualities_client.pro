#-------------------------------------------------
#
# Project created by QtCreator 2017-07-16T20:51:56
#
#-------------------------------------------------

QT       += core gui
QT	 += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Professional_qualities_client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        Modules/Tests/View/MainWindow.cpp \
    Configurator/Configurator.cpp \
    Entities/Test/Test.cpp \
    Entities/AnswerOption/AnswerOption.cpp \
    Entities/Question/Question.cpp \
    Modules/Testing/View/TestForm.cpp \
    Forms/QuestionForm/QuestionForm.cpp \
    Forms/ResultForm/ResultForm.cpp \
    BaseModel/BaseModel.cpp \
    Requester/Requester.cpp \
    Serializable/Array/SerializableArray.cpp \
    Serializable/Object/SerializableObject.cpp \
    Entities/Answer/Answer.cpp \
    Entities/ScaleResult/ScaleResult.cpp \
    Modules/Autorization/Model/AutorizationModel.cpp \
    Entities/AutorizationData/AutorizationData.cpp \
    Modules/Autorization/View/LoginForm.cpp \
    Modules/Tests/Model/TestsModel.cpp \
    Entities/TestWithStatus/TestWithStatus.cpp \
    Entities/TestStatus/TestStatus.cpp \
    SharedStorage/SharedStorage.cpp \
    Modules/Testing/Model/TestingModel.cpp \
    Entities/BindedAnswers/BindedAnswers.cpp \
    Modules/Registration/View/RegistrationForm.cpp \
    Modules/Registration/Model/RegistrationModel.cpp \
    Entities/RegistrationData/RegistrationData.cpp

HEADERS  += Modules/Tests/View/MainWindow.h \
    Configurator/Configurator.h \
    Entities/Test/Test.h \
    Entities/AnswerOption/AnswerOption.h \
    Entities/Question/Question.h \
    Exception.h \
    Modules/Testing/View/TestForm.h \
    Forms/QuestionForm/QuestionForm.h \
    Entities/Answer/Answer.h \
    Forms/ResultForm/ResultForm.h \
    BaseModel/BaseModel.h \
    Requester/Requester.h \
    Requester/RequestType.h \
    Serializable/Array/SerializableArray.h \
    Serializable/Object/SerializableObject.h \
    Entities/AnswerOption/Type/AnswerOptionsType.h \
    Entities/ScaleResult/ScaleResult.h \
    Modules/Autorization/Model/AutorizationModel.h \
    Entities/AutorizationData/AutorizationData.h \
    Modules/Autorization/View/LoginForm.h \
    Modules/Tests/Model/TestsModel.h \
    Entities/TestWithStatus/TestWithStatus.h \
    Entities/TestStatus/TestStatus.h \
    SharedStorage/SharedStorage.h \
    Modules/Testing/Model/TestingModel.h \
    Entities/BindedAnswers/BindedAnswers.h \
    Modules/Registration/View/RegistrationForm.h \
    Modules/Registration/Model/RegistrationModel.h \
    Entities/RegistrationData/RegistrationData.h

FORMS    += Modules/Tests/View/MainWindow.ui \
    Modules/Testing/View/TestForm.ui \
    Forms/QuestionForm/QuestionForm.ui \
    Forms/ResultForm/ResultForm.ui \
    Modules/Autorization/View/LoginForm.ui \
    Modules/Registration/View/RegistrationForm.ui

# Для статической сборки
QMAKE_LFLAGS_RELEASE += -static -static-libgcc
