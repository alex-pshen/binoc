#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QImage>

class QLabel;
class QPushButton;
class QSpinBox;
class QDoubleSpinBox;

class Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = nullptr);

signals:

public slots:
    void redraw();

private:

    static const int w {800}, h{400};

    QImage mesh;
    QSpinBox *ifSpinBox, *aSpinBox;
    QDoubleSpinBox *wSpinBox;
    QPushButton* startButton;
    QLabel* lbl;
};

#endif // PANEL_H
