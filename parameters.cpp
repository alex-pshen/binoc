#include <QtWidgets>

#include "parameters.h"

Parameters::Parameters(QWidget *parent)
    : QWidget(parent)
    , ifSB(new QSpinBox)
    , aSB(new QSpinBox)
    , wSB(new QSpinBox)
    , dtSB(new QSpinBox)
    , dwSB(new QDoubleSpinBox)
    , dwS(new QSlider(Qt::Horizontal))
    , baseColorCB(new QComboBox)
    , testColorCB(new QComboBox)
    , prevPB(new QPushButton(tr("Назад")))
    , nextPB(new QPushButton(tr("Далее")))
    , meshL(new QLabel)
    , mesh(image_width, image_height, QImage::Format_RGB32)
    , leftRB(new QRadioButton(tr("Левый")))
    , rightRB(new QRadioButton(tr("Правый")))
{
	setWindowTitle(tr("Тестирование бинокулярного зрения"));
	// =============Интенсивность фона===============
	constexpr auto ifMin = 0, ifMax = 100;
	QSlider * ifS = new QSlider(Qt::Horizontal);
	ifS->setRange(ifMin, ifMax);
	connect(ifS, SIGNAL(valueChanged(int)), ifSB, SLOT(setValue(int)));
	connect(ifSB, SIGNAL(valueChanged(int)), ifS, SLOT(setValue(int)));
	ifSB->setRange(ifMin, ifMax);
	ifSB->setValue((ifMin + ifMax)/2);
	QLabel * ifL = new QLabel(tr("Яркость фона, %:"));

	// ============== Амплитуда ===================
	constexpr auto aMin = 0, aMax = 100;
	QSlider * aS = new QSlider(Qt::Horizontal);
	aS->setRange(aMin, aMax);
	connect(aS, SIGNAL(valueChanged(int)), aSB, SLOT(setValue(int)));
	connect(aSB, SIGNAL(valueChanged(int)), aS, SLOT(setValue(int)));
	aSB->setRange(aMin, aMax);
	aSB->setValue((aMin + aMax)/2);
	QLabel * aL = new QLabel(tr("Амплитуда, %:"));

	// ====================== Частота ========================
	constexpr auto wMin = 1, wMax = 50;
	QSlider * wS = new QSlider(Qt::Horizontal);
	wS->setRange(wMin, wMax);
	connect(wS, SIGNAL(valueChanged(int)), wSB, SLOT(setValue(int)));
	connect(wSB, SIGNAL(valueChanged(int)), wS, SLOT(setValue(int)));
	wSB->setRange(wMin, wMax);
	wSB->setValue(5);
	QLabel * wL = new QLabel(tr("Базовая частота:"));

	// ==================== Шаг частоты =================
	constexpr auto dwMin = .1, dwMax = 2.;
	dwS->setRange(1, 20);
	connect(dwS, SIGNAL(valueChanged(int)), this, SLOT(SetDwSB(int)));
	connect(dwSB, SIGNAL(valueChanged(double)), this, SLOT(SetDwS(double)));
	dwSB->setRange(dwMin, dwMax);
	dwS->setValue(dwMin);
	QLabel * dwL = new QLabel(tr("Шаг частоты:"));

	// ================== Шаг времени ==================
	constexpr auto dtMin = 100, dtMax = 10000;
	QSlider * dtS = new QSlider(Qt::Horizontal);
	dtS->setRange(dtMin, dtMax);
	connect(dtS, SIGNAL(valueChanged(int)), dtSB, SLOT(setValue(int)));
	connect(dtSB, SIGNAL(valueChanged(int)), dtS, SLOT(setValue(int)));
	dtSB->setRange(dtMin, dtMax);
	dtSB->setValue(1000);
	QLabel * dtL = new QLabel(tr("Шаг времени, мс:"));

	// =============== Цвета ============================
	baseColorCB->addItems({"Красный", "Зеленый", "Синий"});
	testColorCB->addItems({"Красный", "Зеленый", "Синий"});
	testColorCB->setCurrentIndex(2);
	QHBoxLayout * colorLO = new QHBoxLayout;
	colorLO->addWidget(baseColorCB);
	colorLO->addStretch();
	colorLO->addWidget(new QLabel(tr("Исходный глаз:")));
	colorLO->addWidget(leftRB);
	colorLO->addWidget(rightRB);
	leftRB->setChecked(true);
	colorLO->addStretch();
	colorLO->addWidget(testColorCB);

	QHBoxLayout * buttonsLO = new QHBoxLayout;
//	buttonsLO->addWidget(prevPB);
	buttonsLO->addStretch();
	buttonsLO->addWidget(nextPB);

	QGridLayout * grid = new QGridLayout;
	grid->addWidget(ifL,  0, 0);
	grid->addWidget(ifSB, 0, 1);
	grid->addWidget(ifS,  0, 2);
	grid->addWidget(aL,   1, 0);
	grid->addWidget(aSB,  1, 1);
	grid->addWidget(aS,   1, 2);
	grid->addWidget(wL,   2, 0);
	grid->addWidget(wSB,  2, 1);
	grid->addWidget(wS,   2, 2);
	grid->addWidget(dwL,   3, 0);
	grid->addWidget(dwSB,  3, 1);
	grid->addWidget(dwS,   3, 2);
	grid->addWidget(dtL,   4, 0);
	grid->addWidget(dtSB,  4, 1);
	grid->addWidget(dtS,   4, 2);

	QVBoxLayout * mainLO = new QVBoxLayout;
	mainLO->addLayout(grid);
	mainLO->addLayout(colorLO);
	mainLO->addWidget(meshL);
	mainLO->addLayout(buttonsLO);
	setLayout(mainLO);

	connect(ifSB, SIGNAL(valueChanged(int)), this, SLOT(Redraw()));
	connect(aSB, SIGNAL(valueChanged(int)), this, SLOT(Redraw()));
	connect(wSB, SIGNAL(valueChanged(int)), this, SLOT(Redraw()));
	connect(baseColorCB, SIGNAL(currentIndexChanged(int)), this, SLOT(Redraw()));
	connect(testColorCB, SIGNAL(currentIndexChanged(int)), this, SLOT(Redraw()));

	connect(nextPB, SIGNAL(clicked(bool)), this, SLOT(onFinish()));

	prevPB->setDisabled(true);

	Redraw();
}

void Parameters::Redraw()
{
	int I = ifSB->value() * 255. /100.;
	int A = aSB->value() * 255. / 100.;
	double W = wSB->value();
	int kr = (baseColorCB->currentIndex() == 0 ? 1 : 0) | (testColorCB->currentIndex() == 0 ? 1 : 0);
	int kg = (baseColorCB->currentIndex() == 1 ? 1 : 0) | (testColorCB->currentIndex() == 1 ? 1 : 0);
	int kb = (baseColorCB->currentIndex() == 2 ? 1 : 0) | (testColorCB->currentIndex() == 2 ? 1 : 0);

	for (int i = 0; i < image_width; ++i) {
		double x = (i * 2 * PI) / image_width - PI;
		int c = I + A * qSin(W * x);
		c = qMin(255,c);
		c = qMax(0, c);
		for (int j = 0; j < image_height; ++j)
			mesh.setPixel(i,j, qRgb(kr * c, kg * c, kb * c));
	}
	meshL->setPixmap(QPixmap::fromImage(mesh));
}

void Parameters::onFinish()
{
	Color baseColor;
	switch (baseColorCB->currentIndex()) {
	case 0:
		baseColor = Color::RED;
		break;
	case 1:
		baseColor = Color::GREEN;
		break;
	case 2:
		baseColor = Color::BLUE;
		break;
	}

	Color testColor;
	switch (testColorCB->currentIndex()) {
	case 0:
		testColor = Color::RED;
		break;
	case 1:
		testColor = Color::GREEN;
		break;
	case 2:
		testColor = Color::BLUE;
		break;
	}

	QString baseEye = (leftRB->isChecked() ? tr("левый") : tr("правый"));

	Params params(ifSB->value(), aSB->value(), wSB->value(), dwSB->value(), dtSB->value(),
	              baseColor, testColor, baseEye);
	emit Finish(params);
}

void Parameters::SetDwSB(int dw)
{
	dwSB->setValue(dw / 10.);
}

void Parameters::SetDwS(double dw)
{
	dwS->setValue(dw * 10);
}
