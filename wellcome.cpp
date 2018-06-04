#include <QtWidgets>

#include "wellcome.h"

Wellcome::Wellcome(QWidget *parent)
    : QWidget(parent)
    , pixmap(":/binocular-vision.jpg") {
	QLabel * txt = new QLabel("Бинокуля́рное зре́ние (от лат. bini — «два» и лат. oculus — «глаз»)—\n"
	                         "способность одновременно чётко видеть изображение предмета обоими\n"
	                         "глазами; в этом случае человек видит одно изображение предмета, на\n"
	                         "который смотрит, то есть это зрение двумя глазами,с подсознательным\n"
	                         "соединением в зрительном анализаторе (коре головного мозга)\n"
	                         "изображений, полученных каждым глазом в единый образ. Создаёт\n"
	                         "объёмность изображения. Бинокулярное зрение также называют\n"
	                         "стереоскопическим.\n");
	QHBoxLayout * txtLO = new QHBoxLayout;
	txtLO->addStretch();
	txtLO->addWidget(txt);
	txtLO->addStretch();

	QLabel * pic = new QLabel;
	pic->setPixmap(pixmap);
	QPushButton * newPB = new QPushButton(tr("Новый тест"));
	QPushButton * resPB = new QPushButton(tr("Результаты"));
	QPushButton * quitPB = new QPushButton(tr("Выход"));

	QHBoxLayout * hLO = new QHBoxLayout;
	hLO->addWidget(newPB);
	hLO->addWidget(resPB);
	hLO->addWidget(quitPB);

	QVBoxLayout * vLO = new QVBoxLayout;
	vLO->addWidget(pic, Qt::AlignCenter);
	vLO->addLayout(txtLO);
	vLO->addLayout(hLO);

	setLayout(vLO);
	adjustSize();
	setFixedSize(width(), height());
	setWindowTitle(tr("Тестирование бинокулярного зрения"));

	connect(quitPB, SIGNAL(clicked(bool)), QApplication::instance(), SLOT(quit()));
	connect(newPB, SIGNAL(clicked(bool)), this, SIGNAL(NewTest()));
	connect(resPB, SIGNAL(clicked(bool)), this, SIGNAL(ShowResults()));

	resPB->setDisabled(true);
}
