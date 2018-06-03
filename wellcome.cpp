#include <QtWidgets>

#include "wellcome.h"

Wellcome::Wellcome(QWidget *parent)
    : QWidget(parent)
    , pixmap(":/wellcome") {
	QLabel * txt = new QLabel("Бинокуля́рное зре́ние (от лат. bini — «два» и лат. oculus — «глаз»)—\n"
	                         "способность одновременно чётко видеть изображение предмета обоими\n"
	                         "глазами; в этом случае человек видит одно изображение предмета, на\n"
	                         "который смотрит, то есть это зрение двумя глазами,с подсознательным\n"
	                         "соединением в зрительном анализаторе (коре головного мозга)\n"
	                         "изображений, полученных каждым глазом в единый образ. Создаёт\n"
	                         "объёмность изображения. Бинокулярное зрение также называют\n"
	                         "стереоскопическим.\n"
	                         "Если бинокулярное зрение не развивается,\n"
	                         "возможно зрение только правым или левым глазом. Такое зрение\n"
	                         "называется монокулярным.\n"
	                         "Возможно попеременное зрение: то правым,\n"
	                         "то левым глазом — монокулярное альтернирующее. Иногда встречается\n"
	                         "зрение двумя глазами, но без слияния в один зрительный образ\n"
	                         "— одновременное.\n"
	                         "Отсутствие бинокулярного зрения при двух открытых глазах внешне\n"
	                         "проявляется в виде постепенно развивающегося косоглазия.");
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
	setWindowTitle(tr("Превед!!!"));

	connect(quitPB, SIGNAL(clicked(bool)), QApplication::instance(), SLOT(quit()));
    connect(newPB, SIGNAL(clicked(bool)), this, SIGNAL(NewTest()));
    connect(resPB, SIGNAL(clicked(bool)), this, SIGNAL(ShowResults()));

    resPB->setDisabled(true);
}
