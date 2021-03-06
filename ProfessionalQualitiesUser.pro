#-------------------------------------------------
#
# Project created by QtCreator 2017-07-16T20:51:56
#
#-------------------------------------------------

QT += core gui
QT += quick qml quickwidgets
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProfessionalQualitiesUser
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
    Entities/TestWithStatus/TestWithStatus.cpp \
    Entities/TestStatus/TestStatus.cpp \
    SharedStorage/SharedStorage.cpp \
    Entities/BindedAnswers/BindedAnswers.cpp \
    Modules/Registration/View/RegistrationForm.cpp \
    Modules/Registration/Model/RegistrationModel.cpp \
    Entities/RegistrationData/RegistrationData.cpp \
    Modules/Tests/Service/TestsService.cpp \
    Modules/Tests/Model/TestsModel.cpp \
    Modules/Tests/Assembler/TestsAssembler.cpp \
    Modules/Testing/TestWelcomeForm/TestWelcomeForm.cpp \
    Modules/Questions/View/QuestionsForm.cpp \
    Modules/Questions/Model/QuestionsModel.cpp \
    Entities/QuestionWithAnswer/QuestionWithAnswer.cpp \
    Modules/Questions/Assembler/QuestionsAssembler.cpp \
    ElidedText/ElidedText.cpp \
    Modules/Questions/Controller/QuestionsController.cpp \
    Modules/Questions/Service/QuestionsService.cpp \
    Forms/InstructionLabel/InstructionLabel.cpp \
    Forms/ResultsForm/ResultsForm.cpp

HEADERS  += Modules/Tests/View/MainWindow.h \
    Configurator/Configurator.h \
    Entities/Test/Test.h \
    Entities/AnswerOption/AnswerOption.h \
    Entities/Question/Question.h \
    Exception.h \
    Modules/Testing/View/TestForm.h \
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
    Entities/TestWithStatus/TestWithStatus.h \
    Entities/TestStatus/TestStatus.h \
    SharedStorage/SharedStorage.h \
    Entities/BindedAnswers/BindedAnswers.h \
    Modules/Registration/View/RegistrationForm.h \
    Modules/Registration/Model/RegistrationModel.h \
    Entities/RegistrationData/RegistrationData.h \
    Modules/Tests/Service/TestsService.h \
    Modules/Tests/Model/TestsModel.h \
    Modules/Tests/Model/TestsColumnIndex.h \
    Modules/Tests/Assembler/TestsAssembler.h \
    Modules/Testing/TestWelcomeForm/TestWelcomeForm.h \
    Modules/Questions/View/QuestionsForm.h \
    Modules/Questions/Model/QuestionsModel.h \
    Entities/QuestionWithAnswer/QuestionWithAnswer.h \
    Modules/Questions/Assembler/QuestionsAssembler.h \
    ElidedText/ElidedText.h \
    Modules/Questions/Controller/QuestionsController.h \
    Modules/Questions/Service/QuestionsService.h \
    Modules/Questions/IQuestionsOutput.h \
    Forms/InstructionLabel/InstructionLabel.h \
    Forms/ResultsForm/ResultsForm.h

FORMS    += Modules/Tests/View/MainWindow.ui \
    Forms/ResultForm/ResultForm.ui \
    Modules/Autorization/View/LoginForm.ui \
    Modules/Registration/View/RegistrationForm.ui \
    Modules/Testing/TestWelcomeForm/TestWelcomeForm.ui \
    Modules/Questions/View/QuestionsForm.ui \
    Forms/ResultsForm/ResultsForm.ui

DISTFILES += \
    Modules/Questions/View/QuestionsListView.qml \
    Forms/AnswerOptionRadioButton.qml \
    Forms/AnswerOptionsButtonGroup.qml \
    Forms/QuestionView.qml
