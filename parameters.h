#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QWidget>
#include <QComboBox>

#include "params.h"

class QSpinBox;
class QDoubleSpinBox;
class QPushButton;
class QLabel;

class Parameters : public QWidget
{
    Q_OBJECT
public:
    explicit Parameters(QWidget *parent = nullptr);

signals:
    void Back();
    void Finish(const Params&);

public slots:
    void Redraw();
    void onFinish();

private:
    static constexpr auto image_width {600}, image_height{100};
    QSpinBox *ifSB, *aSB, *wSB, *dwSB, *dtSB;
    QComboBox *baseColorCB, *testColorCB;
    QPushButton *nextPB, *prevPB;
    QLabel *meshL;
    QImage mesh;
};

#endif  // PARAMETERS_H
