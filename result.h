#ifndef RESULT_H
#define RESULT_H

#include <QWidget>

#include "params.h"

class QLabel;

class Result : public QWidget
{
	Q_OBJECT
public:
	explicit Result(QWidget *parent = nullptr);

signals:
	void Prev();

public slots:
	void Show(const Params& params_);

private:
	QLabel * txt;
};

#endif // RESULT_H
