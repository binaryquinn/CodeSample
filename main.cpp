#include "codesamplewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CodeSampleWindow w;
	w.show();
	
	return a.exec();
}
