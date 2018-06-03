#ifndef TESTPAGE_H
#define TESTPAGE_H

#include <QWidget>
#include <QImage>
#include <QTimer>

#include "params.h"

class QPushButton;
class QLabel;

class TestPage : public QWidget
{
    Q_OBJECT
    static constexpr auto image_width{1200}, image_height{600};
public:
    explicit TestPage(QWidget *parent = nullptr);

signals:
    void Next();
    void Prev();

public slots:
    void Show(const Params& params_);
    void Redraw();
    void Forward();
    void Backward();
    void onTimeout();
    void Reset();

private:
    Params params;

    QImage mesh;
    QLabel * meshL;
    QPushButton *forwardPB, *backwardPB, *pausePB, *stopPB, *savePB, *backPB, *resultPB;

    double W1, dW;

    QTimer timer;
};

#endif // TESTPAGE_H
