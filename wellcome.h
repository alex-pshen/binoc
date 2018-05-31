#ifndef WELLCOME_H
#define WELLCOME_H

#include <QWidget>

class Wellcome : public QWidget
{
	Q_OBJECT
public:
	explicit Wellcome(QWidget *parent = nullptr);

signals:
	void NewTest();
	void ShowResults();

public slots:
};

#endif // WELLCOME_H
