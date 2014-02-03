#ifndef CODESAMPLEWINDOW_H
#define CODESAMPLEWINDOW_H

#include <QMainWindow>
#include "wallmodel.h"

namespace Ui {
class CodeSampleWindow;
}

class CodeSampleWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit CodeSampleWindow(QWidget *parent = 0);
	~CodeSampleWindow();
	void animationDelay(int length);

public slots:
	void updateTreeStatus();
	void updateComparisonStatus();
	void updateResults();

private slots:
	void on_execButton_clicked();

private:
	Ui::CodeSampleWindow *ui;
	WallModel *model;
};

#endif // CODESAMPLEWINDOW_H
