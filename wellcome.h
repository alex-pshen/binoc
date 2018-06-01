#ifndef WELLCOME_H
#define WELLCOME_H

#include <QWidget>
#include <QPixmap>

class Wellcome : public QWidget {
	Q_OBJECT
public:
	explicit Wellcome(QWidget *parent = nullptr);

signals:
	void NewTest();
	void ShowResults();

private:
	QPixmap pixmap;
};

#endif  // WELLCOME_H
