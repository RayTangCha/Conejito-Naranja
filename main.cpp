#include "naranja.h"

#include <QApplication>
#include <QSplashScreen>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pix(":/new/prefix1/D13ACE72-BE79-42FF-9CAE-A9EAEB8487E6.jpg");
    QSplashScreen splash(pix);
    splash.show();
    a.processEvents();
    Naranja w;
    Sleep(1000);
    w.show();
    splash.finish(&w);
    return a.exec();
}
