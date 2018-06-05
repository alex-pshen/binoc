#include <QApplication>

#include "wellcome.h"
#include "parameters.h"
#include "testpage.h"
#include "result.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Wellcome wellcome;
	Parameters parameters;
	TestPage testpage;
	Result result;

	QObject::connect(&wellcome, SIGNAL(NewTest()), &parameters, SLOT(show()));
	QObject::connect(&wellcome, SIGNAL(NewTest()), &wellcome, SLOT(hide()));

	QObject::connect(&parameters, SIGNAL(Finish(Params)), &testpage, SLOT(Show(Params)));
	QObject::connect(&parameters, SIGNAL(Finish(Params)), &parameters, SLOT(hide()));

	QObject::connect(&testpage, SIGNAL(Prev()), &parameters, SLOT(show()));
	QObject::connect(&testpage, SIGNAL(Prev()), &testpage, SLOT(hide()));
	QObject::connect(&testpage, SIGNAL(Next(Params)), &result, SLOT(Show(Params)));

	QObject::connect(&result, SIGNAL(Prev()), &result, SLOT(hide()));
	QObject::connect(&result, SIGNAL(Prev()), &testpage, SLOT(show()));

	wellcome.show();
	return app.exec();
}
