#include <QtWidgets>
#include <QTimer>

#include "testpage.h"

TestPage::TestPage(QWidget *parent)
    : QWidget(parent)
    , params(0,0,0,0,0, Color::RED, Color::BLUE)
    , mesh(image_width, image_height, QImage::Format_RGB32)
    , meshL(new QLabel)
    , forwardPB(new QPushButton(tr("Увеличение частоты")))
    , backwardPB(new QPushButton(tr("Уменьшение частоты")))
    , pausePB(new QPushButton(tr("Пауза")))
    , stopPB(new QPushButton(tr("Сброс частоты")))
    , savePB(new QPushButton(tr("Сохранить")))
    , backPB(new QPushButton(tr("Назад")))
    , resultPB(new QPushButton(tr("Результат")))
{
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
    setLayout(mainLO);

    meshL->setPixmap(QPixmap::fromImage(mesh));

    connect(backPB, SIGNAL(clicked(bool)), this, SIGNAL(Prev()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect(backwardPB, SIGNAL(clicked(bool)), this, SLOT(Backward()));
    connect(forwardPB, SIGNAL(clicked(bool)), this, SLOT(Forward()));
    connect(pausePB, SIGNAL(clicked(bool)), &timer, SLOT(stop()));
    connect(stopPB, SIGNAL(clicked(bool)), this, SLOT(Reset()));

    savePB->setDisabled(true);
    resultPB->setDisabled(true);
}

void TestPage::Show(const Params &params_)
{
    timer.setInterval(params_.dt);
    params = params_;
    W1 = params_.w / 100.;
    Redraw();
    show();
}

void TestPage::Redraw()
{
    int I = params.IF;
    int A = params.A;
    double W = params.w / 100.;
    int bkr = (params.baseColor == Color::RED   ? 1 : 0);
    int bkg = (params.baseColor == Color::GREEN ? 1 : 0);
    int bkb = (params.baseColor == Color::BLUE  ? 1 : 0);
    int tkr = (params.testColor == Color::RED   ? 1 : 0);
    int tkg = (params.testColor == Color::GREEN ? 1 : 0);
    int tkb = (params.testColor == Color::BLUE  ? 1 : 0);

    for (int i = 0; i < image_width; ++i) {
        double x = i * 100. / image_width;
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
    W1 += dW/100.;
    Redraw();
}

void TestPage::Reset()
{
    W1 = params.w / 100.;
    Redraw();
}
