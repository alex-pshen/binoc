#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QWidget>
#include <QComboBox>

#include "params.h"

class QSpinBox;
class QDoubleSpinBox;
class QPushButton;
class QLabel;
class QSLider;
class QRadioButton;

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
	void SetDwSB(int dw);
	void SetDwS(double dw);

private:
	static constexpr auto image_width {600}, image_height{100};
	static constexpr auto PI = 3.14159;
	QSpinBox *ifSB, *aSB, *wSB, *dtSB;
	QDoubleSpinBox *dwSB;
	QSlider *dwS;
	QComboBox *baseColorCB, *testColorCB;
	QPushButton *prevPB, *nextPB;
	QLabel *meshL;
	QImage mesh;
	QRadioButton *leftRB, *rightRB;
};

#endif  // PARAMETERS_H
