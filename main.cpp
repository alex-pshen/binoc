#include <QApplication>

#include "wellcome.h"
#include "parameters.h"
#include "testpage.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    Wellcome wellcome;
    Parameters parameters;
    TestPage testpage;

    QObject::connect(&wellcome, SIGNAL(NewTest()), &parameters, SLOT(show()));
    QObject::connect(&wellcome, SIGNAL(NewTest()), &wellcome, SLOT(hide()));

    QObject::connect(&parameters, SIGNAL(Finish(Params)), &testpage, SLOT(Show(Params)));
    QObject::connect(&parameters, SIGNAL(Finish(Params)), &parameters, SLOT(hide()));

    QObject::connect(&testpage, SIGNAL(Prev()), &parameters, SLOT(show()));
    QObject::connect(&testpage, SIGNAL(Prev()), &testpage, SLOT(hide()));

    wellcome.show();
	return app.exec();
}
