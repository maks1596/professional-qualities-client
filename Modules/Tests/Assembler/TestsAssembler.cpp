#include "TestsAssembler.h"

#include "Modules/Tests/View/MainWindow.h"
#include "Modules/Tests/Model/TestsModel.h"
#include "Modules/Tests/Service/TestsService.h"

MainWindow *TestsAssembler::assembly(QWidget *parent/*= nullptr*/) {
    auto view = new MainWindow(parent);
    auto model = new TestsModel(view);
    auto service = new TestsService(model);

    model->setService(service);
    view->setModel(model);

    return view;
}
