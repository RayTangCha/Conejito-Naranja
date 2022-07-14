#include "naranja.h"

#include <QApplication>
#include <QSplashScreen>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Naranja w;
    std::ifstream ifs;
    ifs.open("C:\\Users\\Public\\Documents\\NaranjaSettings.dat");
    int settings=1;
    if(ifs.is_open())ifs>>settings;
    ifs.close();
    if(settings%10){
        QPixmap pix(":/new/prefix1/ganapathy-kumar-L75D18aVal8-unsplash.jpg");
        QSplashScreen splash(pix);
        splash.show();
        a.processEvents();
        Sleep(1000);
        w.show();
        splash.finish(&w);
    }
    else w.show();
    return a.exec();
}
