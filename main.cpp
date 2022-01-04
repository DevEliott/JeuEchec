#include "./vue/MainWindow.hpp"

#include <QApplication>


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	vue::MainWindow w;
	w.show();
	return a.exec();
}
