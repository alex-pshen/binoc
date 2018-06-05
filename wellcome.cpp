#include <QtWidgets>

#include "wellcome.h"

Wellcome::Wellcome(QWidget *parent)
    : QWidget(parent)
    , pixmap(":/bolshie-golubye-glaza-rebenka.jpg") {
	QLabel * txt = new QLabel(
	               "Уважаемый, пользователь!\n"
	               "Приветствуем Вас, в программном комплексе бинокулярного восприятия.\n"
	               "Программа позволит вам проверить ваше бинокулярное зрение, способность\n"
	               "зрительного анализатора к восприятию глубинной протяженности и\n"
	               " удаленности объектов наблюдения.\n"
	               "Желаем, Вам, легкого тестирования, хороших результатов и крепкого здоровья.");
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
//	hLO->addWidget(resPB);
//	hLO->addStretch();
	hLO->addWidget(quitPB);

	QVBoxLayout * vLO = new QVBoxLayout;
	QHBoxLayout * picLO = new QHBoxLayout;
	picLO->addStretch();
	picLO->addWidget(pic, Qt::AlignCenter);
	picLO->addStretch();
	vLO->addWidget(pic, Qt::AlignCenter);
//	vLO->addLayout(picLO);
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
