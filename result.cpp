#include <QtWidgets>

#include "result.h"

Result::Result(QWidget *parent)
    : QWidget(parent)
    , txt(new QLabel)
{
	setWindowTitle(tr("Результат"));
	QPushButton * backPB = new QPushButton(tr("Назад"));
	QPushButton * quitPB = new QPushButton(tr("Выход"));
	connect(backPB, SIGNAL(clicked(bool)), this, SIGNAL(Prev()));
	connect(quitPB, SIGNAL(clicked(bool)), QApplication::instance(), SLOT(quit()));

	QHBoxLayout * buttonsLO = new QHBoxLayout;
	buttonsLO->addWidget(backPB);
	buttonsLO->addWidget(quitPB);

	QVBoxLayout * mainLO = new QVBoxLayout;
	mainLO->addWidget(txt);
	mainLO->addLayout(buttonsLO);

	setLayout(mainLO);
}

void Result::Show(const Params &p)
{
	txt->setText(QString(
	             "Исходный глаз : %1\n"
	             "Интенсивность фона : %2 %\n"
	             "Амплитуда : %3 %\n"
	             "Базовая частота : %4\n"
	             "Минимальная частота : %5\n"
	             "Максимальная частота : %6\n"
	             ).arg(p.baseEye).arg(p.IF).arg(p.A).arg(p.w).arg(p.minW).arg(p.maxW));

	show();
}
