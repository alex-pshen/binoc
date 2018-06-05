#include <QtWidgets>
#include <QTimer>

#include "testpage.h"

TestPage::TestPage(QWidget *parent)
    : QWidget(parent)
    , params(0,0,0,0,0, Color::RED, Color::BLUE, QString())
    , mesh(image_width, image_height, QImage::Format_RGB32)
    , meshL(new QLabel)
    , forwardPB(new QPushButton(tr("Увеличение частоты")))
    , backwardPB(new QPushButton(tr("Уменьшение частоты")))
    , pausePB(new QPushButton(tr("Пауза")))
    , stopPB(new QPushButton(tr("Сброс частоты")))
    , savePB(new QPushButton(tr("Сохранить")))
    , backPB(new QPushButton(tr("Назад")))
    , resultPB(new QPushButton(tr("Результат")))
    , statusBar(new QStatusBar)
{
	setWindowTitle(tr("Тестирование бинокулярного зрения"));
	QHBoxLayout * controlLO = new QHBoxLayout;
	controlLO->addStretch();
	controlLO->addWidget(backwardPB);
	controlLO->addWidget(pausePB);
	controlLO->addWidget(forwardPB);
	controlLO->addWidget(stopPB);
	controlLO->addWidget(savePB);
	controlLO->addStretch();

	QHBoxLayout * bottomLO = new QHBoxLayout;
	bottomLO->addWidget(backPB);
	bottomLO->addStretch();
	bottomLO->addWidget(resultPB);

	QVBoxLayout * mainLO = new QVBoxLayout;
	mainLO->addWidget(meshL);
	mainLO->addLayout(controlLO);
	mainLO->addLayout(bottomLO);
	mainLO->addWidget(statusBar);
	setLayout(mainLO);

	meshL->setPixmap(QPixmap::fromImage(mesh));

	connect(backPB, SIGNAL(clicked(bool)), this, SIGNAL(Prev()));
	connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
	connect(backwardPB, SIGNAL(clicked(bool)), this, SLOT(Backward()));
	connect(forwardPB, SIGNAL(clicked(bool)), this, SLOT(Forward()));
	connect(pausePB, SIGNAL(clicked(bool)), &timer, SLOT(stop()));
	connect(stopPB, SIGNAL(clicked(bool)), this, SLOT(Reset()));
	connect(savePB, SIGNAL(clicked(bool)), this, SLOT(Save()));
	connect(resultPB, SIGNAL(clicked(bool)), this, SLOT(Result()));
	connect(resultPB, SIGNAL(clicked(bool)), this, SLOT(hide()));

//	savePB->setDisabled(true);
//	resultPB->setDisabled(true);
}

void TestPage::Show(const Params &params_)
{
	timer.setInterval(params_.dt);
	params = params_;
	W1 = params.w;
	Redraw();
	show();
}

void TestPage::Redraw()
{
	int I = params.IF * 255. / 100.;
	int A = params.A * 255. / 100.;
	double W = params.w;
	int bkr = (params.baseColor == Color::RED   ? 1 : 0);
	int bkg = (params.baseColor == Color::GREEN ? 1 : 0);
	int bkb = (params.baseColor == Color::BLUE  ? 1 : 0);
	int tkr = (params.testColor == Color::RED   ? 1 : 0);
	int tkg = (params.testColor == Color::GREEN ? 1 : 0);
	int tkb = (params.testColor == Color::BLUE  ? 1 : 0);

	for (int i = 0; i < image_width; ++i) {
		double x = (i * 2 * 3.14159) / image_width - 3.14159;
		int c1 = (I + A * qSin(W * x)) / 2;
		int c2 = (I + A * qSin(W1 * x)) / 2;
		c1 = qMin(255,c1);
		c1 = qMax(0, c1);
		c2 = qMin(255,c2);
		c2 = qMax(0, c2);
		int cr = bkr * c1 + tkr * c2;
		int cg = bkg * c1 + tkg * c2;
		int cb = bkb * c1 + tkb * c2;
		for (int j = 0; j < image_height; ++j)
			mesh.setPixel(i,j, qRgb(cr, cg, cb));
	}
	meshL->setPixmap(QPixmap::fromImage(mesh));
	statusBar->showMessage(QString(tr("Базовая частота: %1. Тестовая частота: %2. "
	                                  "Верхняя частота: %3. Нижняя частота: %4")
	                               .arg(W).arg(W1).arg(params.maxW).arg(params.minW)));
}

void TestPage::Forward()
{
	dW = params.dw;
	timer.start(params.dt);
}

void TestPage::Backward()
{
	dW = -params.dw;
	timer.start(params.dt);
}

void TestPage::onTimeout()
{
	W1 += dW;
	Redraw();
}

void TestPage::Reset()
{
	timer.stop();
	W1 = params.w;
	Redraw();
}

void TestPage::Save()
{
	if (W1 > params.w)
		params.maxW = W1;
	if (W1 < params.w)
		params.minW = W1;
	Redraw();
}

void TestPage::Result()
{
	emit Next(params);
}
