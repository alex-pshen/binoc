#include <QApplication>

#include "wellcome.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Wellcome wellcome;
	wellcome.show();
	return app.exec();
}
