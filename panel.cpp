#include "panel.h"

#include <QtWidgets>
#include <QtMath>
QDialog
Panel::Panel(QWidget *parent) : QWidget(parent), mesh(w, h, QImage::Format_RGB32)
{
	int width = 150;
	setMinimumSize(100,100);
	ifSpinBox = new QSpinBox;
	ifSpinBox->setRange(0, 255);
	ifSpinBox->setSingleStep(1);
	ifSpinBox->setValue(127);
	ifSpinBox->setFixedWidth(width);

	aSpinBox = new QSpinBox;
	aSpinBox->setRange(0, 255);
	aSpinBox->setSingleStep(1);
	aSpinBox->setValue(127);
	aSpinBox->setFixedWidth(width);

	wSpinBox = new QDoubleSpinBox;
	wSpinBox->setRange(0, 1);
	wSpinBox->setSingleStep(0.01);
	wSpinBox->setValue(0.1);
	wSpinBox->setFixedWidth(width);

	startButton = new QPushButton(tr("Перерисовать"));
	startButton->setFixedWidth(width);

	QHBoxLayout* lo = new QHBoxLayout;
	QVBoxLayout* vlo = new QVBoxLayout;

	vlo->addWidget(ifSpinBox);
	vlo->addWidget(aSpinBox);
	vlo->addWidget(wSpinBox);
	vlo->addStretch();
	vlo->addWidget(startButton);

	lo->addLayout(vlo);
	lbl = new QLabel(this);
	lbl->setFixedSize(w, h);
	lbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    lbl->adjustSize();

	lo->addWidget(lbl);
	setLayout(lo);

	redraw();

	connect(startButton, SIGNAL(clicked(bool)), this, SLOT(redraw()));
}

void Panel::redraw()
{
	int I = ifSpinBox->value();
	int A = aSpinBox->value();
	double W = wSpinBox->value();

	for (int i = 0; i < w; ++i) {
		int c = I + A * qSin(W * i);
		c = qMin(255,c);
		c = qMax(0, c);
		for (int j = 0; j < h; ++j) {
			mesh.setPixel(i,j, qRgb(c,c,c));
		}
	}
	lbl->setPixmap(QPixmap::fromImage(mesh));
}
