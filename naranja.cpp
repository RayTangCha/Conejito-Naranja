#include "naranja.h"
#include "ui_naranja.h"
#include <QFileDialog>
#include <QString>
#include <QScreen>
#include <QPainter>
#include <QWindow>
#include <QMouseEvent>
#include <QGraphicsEffect>
#include <QColorDialog>
#include <string.h>
#include <fstream>
#include <QListWidget>
#include <QPainter>
#include <gallery.h>
#include <QSplashScreen>
QImage image;
QString OpenFile,OpenFilePath;
bool m_bPressed=false;
QPoint m_point;
QColor color=qRgb(95,75,139);

void Naranja::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_bPressed = true;
        m_point = event->pos();
    }
}

void Naranja::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void Naranja::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
    move(event->pos()-m_point+pos());
}

Naranja::Naranja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Naranja)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->listWidget->setVisible(0);
    ui->horizontalSlider->setRange(2,10);
    ui->horizontalSlider->setSliderPosition(5);
    ui->spinBox->setRange(4,10);
    ui->spinBox->setValue(6);
    ui->spinBox_2->setRange(4,10);
    ui->spinBox_2->setValue(6);
    ui->spinBox_3->setRange(4,10);
    ui->spinBox_3->setValue(4);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_12->width(),ui->label_12->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_12->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_12->size()));
    std::ifstream ifs;
    ifs.open("C:\\Users\\Public\\Documents\\NaranjaDefaultLense.dat");
    if(ifs.is_open()){
        std::string str;
        ifs>>str;
        ui->lineEdit->setText(QString::fromStdString(str));
        ifs>>str;
        ui->lineEdit_2->setText(QString::fromStdString(str));
        ifs>>str;
        ui->lineEdit_3->setText(QString::fromStdString(str));
        ifs>>str;
        ui->lineEdit_4->setText(QString::fromStdString(str));
        ifs>>str;
        ui->lineEdit_5->setText(QString::fromStdString(str));
        ifs>>str;
        ui->lineEdit_6->setText(QString::fromStdString(str));
    }
    std::ifstream reifs;
    reifs.open("C:\\Users\\Public\\Documents\\NaranjaDefaultPicture.dat");
    if(reifs.is_open()){
        std::string str;
        getline(reifs,str);
        reifs.close();
        OpenFile=QString::fromStdString(str);
        image.load(OpenFile);
        ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label_3->setText("File Path: "+OpenFile);
        std::ofstream ofs;
        ofs.open("C:\\Users\\Public\\Documents\\NaranjaPhotoHistory.dat",std::ios::app);
        ofs<<OpenFile.toStdString()<<"\n";
        ofs.close();
        ui->listWidget->setVisible(0);
    }
}

Naranja::~Naranja()
{
    delete ui;
}


void Naranja::on_commandLinkButton_clicked()
{
    OpenFile = QFileDialog::getOpenFileName(this,
           "Please choose an image file",
           "",
           "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    if (OpenFile != "")
           if (image.load(OpenFile))
               ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
    ui->label->setAlignment(Qt::AlignCenter);
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(OpenFile);
    OpenFilePath = OpenFileInfo.filePath();
    ui->label_3->setText("File Path: "+OpenFilePath);
    std::ofstream ofs;
    ofs.open("C:\\Users\\Public\\Documents\\NaranjaPhotoHistory.dat",std::ios::app);
    ofs<<OpenFilePath.toStdString()<<"\n";
    ofs.close();
    ui->listWidget->setVisible(0);
}


void Naranja::on_commandLinkButton_2_clicked()
{
    QApplication::exit();
}


void Naranja::on_commandLinkButton_3_clicked()
{
    ui->label_2->clear();
    ui->label_3->setText("Please Press [Open] to open picture files");
}


void Naranja::on_commandLinkButton_4_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            newImage->setPixel(x,y,qRgb(255-oldColor.red(),255-oldColor.green(),255-oldColor.blue()));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average,average,average));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_2_clicked()
{
    QString OpenFile, OpenFilePath;
    OpenFile = QFileDialog::getOpenFileName(this,
           "Please choose an image file",
           "",
           "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(OpenFile);
    OpenFilePath = OpenFileInfo.filePath();
    image.save(OpenFilePath);
}


void Naranja::on_pushButton_3_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            newImage->setPixel(x,y,qRgb(oldColor.red()*1.5,oldColor.green(),oldColor.blue()*0.5));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_4_clicked()
{
    image.save(OpenFilePath);
}


void Naranja::on_pushButton_5_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    double ramp=ui->lineEdit->text().toDouble();
    double gamp=ui->lineEdit_2->text().toDouble();
    double bamp=ui->lineEdit_3->text().toDouble();
    double radd=ui->lineEdit_4->text().toDouble();
    double gadd=ui->lineEdit_5->text().toDouble();
    double badd=ui->lineEdit_6->text().toDouble();
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            newImage->setPixel(x,y,qRgb(oldColor.red()*ramp+radd,oldColor.green()*gamp+gadd,oldColor.blue()*bamp+badd));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
    if(ui->checkBox->isChecked()){
        std::ofstream ofs;
        ofs.open("C:\\Users\\Public\\Documents\\NaranjaDefaultLense.dat",std::ios::trunc);
        ofs<<ramp<<" "<<gamp<<" "<<bamp<<" "<<radd<<" "<<gadd<<" "<<badd;
        ofs.close();
    }
}


void Naranja::on_pushButton_6_clicked()
{
    QGraphicsBlurEffect *blureffect = new QGraphicsBlurEffect;
    blureffect->setBlurRadius(ui->horizontalSlider->value());
    ui->label_2->setGraphicsEffect(blureffect);
}


void Naranja::on_pushButton_7_clicked()
{
    QGraphicsColorizeEffect *blueeffect= new QGraphicsColorizeEffect;
    blueeffect->setColor(Qt::blue);
    ui->label_2->setGraphicsEffect(blueeffect);
}


void Naranja::on_pushButton_8_clicked()
{
    QGraphicsColorizeEffect *redeffect= new QGraphicsColorizeEffect;
    redeffect->setColor(Qt::red);
    ui->label_2->setGraphicsEffect(redeffect);
}


void Naranja::on_pushButton_9_clicked()
{
    QGraphicsColorizeEffect *greeneffect= new QGraphicsColorizeEffect;
    greeneffect->setColor(Qt::green);
    ui->label_2->setGraphicsEffect(greeneffect);
}


void Naranja::on_pushButton_10_clicked()
{
    QGraphicsBlurEffect *blureffect = new QGraphicsBlurEffect;
    blureffect->setBlurRadius(2);
    ui->label_2->setGraphicsEffect(blureffect);
}


void Naranja::on_pushButton_11_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            newImage->setPixel(x,y,qRgb(oldColor.red()+30,oldColor.green()+20,oldColor.blue()-20));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_12_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            newImage->setPixel(x,y,qRgb(oldColor.red()+30,oldColor.green()-20,oldColor.blue()+20));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_13_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*1.5,average,average*0.5));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_14_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*1.8,average*1.7,average*1.5));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_15_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*1.5,average*1.5,average*1.5));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_16_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(0,average*1.5,average*0.4));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_17_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*0.7,average*0.4,average*0.6));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_18_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*1.6,average*1.6+4,average*1.6+10));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_19_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*1.4+20,average*1.4+30,average*1.4+40));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_20_clicked()
{
    color = QColorDialog::getColor(color);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_12->width(),ui->label_12->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_12->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_12->size()));
}


void Naranja::on_pushButton_21_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*(color.red()/255.)*1.5,average*(color.green()/255.)*1.5,average*(color.blue()/255.)*1.5));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_22_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    if(ui->comboBox->currentText()=="Vertical"){
        for(int x = 0; x<newImage->width(); x++){
            for(int y = 0; y<newImage->height(); y++){
                oldColor = QColor(image.pixel(x,y));
                int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
                newImage->setPixel(x,y,qRgb(average*(color.red()/255.)*1.5*((x+image.width()/ui->spinBox->value())/(image.width()/ui->spinBox->value()))
                                            ,average*(color.green()/255.)*1.5*((x+image.width()/ui->spinBox->value())/(image.width()/ui->spinBox->value()))
                                            ,average*(color.blue()/255.)*1.5*((x+image.width()/ui->spinBox->value())/(image.width()/ui->spinBox->value()))));
            }
        }
    }
    else{
        for(int x = 0; x<newImage->width(); x++){
            for(int y = 0; y<newImage->height(); y++){
                oldColor = QColor(image.pixel(x,y));
                int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
                newImage->setPixel(x,y,qRgb(average*(color.red()/255.)*1.5*((y+image.height()/ui->spinBox->value())/(image.height()/ui->spinBox->value()))
                                            ,average*(color.green()/255.)*1.5*((y+image.height()/ui->spinBox->value())/(image.height()/ui->spinBox->value()))
                                            ,average*(color.blue()/255.)*1.5*((y+image.height()/ui->spinBox->value())/(image.height()/ui->spinBox->value()))));
            }
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_commandLinkButton_5_clicked()
{
    if (OpenFile != "")
           if (image.load(OpenFile))
               ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
    ui->label->setAlignment(Qt::AlignCenter);
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(OpenFile);
    OpenFilePath = OpenFileInfo.filePath();
    ui->label_3->setText("File Path:"+OpenFilePath);
}


void Naranja::on_pushButton_23_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*(color.red()/255.)*1.5*((x+image.width()/ui->spinBox_2->value())/(image.width()/ui->spinBox_2->value()))
                                        ,average*(color.green()/255.)*1.5*((x+image.width()/ui->spinBox_2->value())/(image.width()/ui->spinBox_2->value()))
                                        ,average*(color.blue()/255.)*1.5*((x+image.width()/ui->spinBox_2->value())/(image.width()/ui->spinBox_2->value()))));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
    newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*(color.red()/255.)*1.5*((y+image.height()/ui->spinBox_3->value())/(image.height()/ui->spinBox_3->value()))
                                        ,average*(color.green()/255.)*1.5*((y+image.height()/ui->spinBox_3->value())/(image.height()/ui->spinBox_3->value()))
                                        ,average*(color.blue()/255.)*1.5*((y+image.height()/ui->spinBox_3->value())/(image.height()/ui->spinBox_3->value()))));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_commandLinkButton_6_clicked()
{
    ui->listWidget->setVisible(1);
    std::string str=" ";
    std::ifstream ifs;
    ifs.open("C:\\Users\\Public\\Documents\\NaranjaPhotoHistory.dat");
    for(;getline(ifs,str);)
        if(str!="")ui->listWidget->addItem(QString::fromStdString(str));
}


void Naranja::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->listWidget->setVisible(0);
    OpenFile=item->text();
    if (OpenFile != "")
           if (image.load(OpenFile))
               ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
    ui->label->setAlignment(Qt::AlignCenter);
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(OpenFile);
    OpenFilePath = OpenFileInfo.filePath();
    ui->label_3->setText("File Path: "+OpenFilePath);
}


void Naranja::on_pushButton_24_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    double ramp=ui->lineEdit->text().toDouble();
    double gamp=ui->lineEdit_2->text().toDouble();
    double bamp=ui->lineEdit_3->text().toDouble();
    double radd=ui->lineEdit_4->text().toDouble();
    double gadd=ui->lineEdit_5->text().toDouble();
    double badd=ui->lineEdit_6->text().toDouble();
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            newImage->setPixel(x,y,qRgb(oldColor.red()*ramp+radd,oldColor.green()*gamp+gadd,oldColor.blue()*bamp+badd));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
}


void Naranja::on_pushButton_25_clicked()
{
    ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
}


void Naranja::on_pushButton_28_clicked()
{
    std::ofstream ofs;
    ofs.open("C:\\Users\\Public\\Documents\\NaranjaDefaultPicture.dat",std::ios::trunc);
    ofs<<OpenFilePath.toStdString();
    ofs.close();
}


void Naranja::on_pushButton_27_clicked()
{
    std::ofstream ofs;
    ofs.open("C:\\Users\\Public\\Documents\\NaranjaDefaultPicture.dat",std::ios::trunc);
    ofs<<"";
    ofs.close();
    std::ofstream reofs;
    reofs.open("C:\\Users\\Public\\Documents\\NaranjaDefaultLense.dat",std::ios::trunc);
    reofs<<"";
    reofs.close();
}

void Naranja::on_pushButton_26_clicked()
{
    QPainter painter(&image);
    int fontSize = 25, spacing = 10;
    QFont font("Lucida Calligraphy", fontSize, QFont::Thin);
    font.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    painter.setFont(font);
    if(ui->checkBox_2->isChecked()) painter.setPen(color);
    else painter.setPen(QColor(150, 150, 150));
    painter.translate(image.width() / 2, -image.width() / 2);
    painter.rotate(45);
    int squareEdgeSize = image.width() * sin(45.0) + image.height() * sin(45.0);
    int hCount = squareEdgeSize / ((fontSize + spacing) * (ui->lineEdit_7->text().size() + 1)) + 1;
    int x = squareEdgeSize / hCount + (fontSize + spacing) * 3;
    int y = x / 2;
    for (int i = 0; i < hCount; i++)
        for (int j = 0; j < hCount * 2; j++)
                painter.drawText(x * i, y * j,ui->lineEdit_7->text());
    ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
}

void Naranja::on_pushButton_29_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    int cri=ui->lineEdit_8->text().toInt();
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            if(average>cri)newImage->setPixel(x,y,qRgb(255,255,255));
            else newImage->setPixel(x,y,qRgb(0,0,0));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_30_clicked()
{
    if(ui->comboBox_2->currentText()=="Vertical"){
        QImage newImage(QSize(image.width(),image.height()), QImage::Format_ARGB32);
        QColor tmpColor;
        int r, g, b;
        for (int x = 0; x < newImage.width(); x++) {
            for (int y = 0; y < newImage.height(); y++) {
                tmpColor = QColor(image.pixel(x, y));
                r = tmpColor.red();
                g = tmpColor.green();
                b = tmpColor.blue();
                newImage.setPixel(x, newImage.height() - y - 1, qRgb(r, g, b));
            }
        }
        ui->label_2->setPixmap(QPixmap::fromImage(newImage).scaled(ui->label_2->size()));
        image=newImage;
    }
    else{
        QImage newImage(QSize(image.width(),image.height()), QImage::Format_ARGB32);
        QColor tmpColor;
        int r, g, b;
        for (int x = 0; x < newImage.width(); x++) {
            for (int y = 0; y < newImage.height(); y++) {
                tmpColor = QColor(image.pixel(x, y));
                r = tmpColor.red();
                g = tmpColor.green();
                b = tmpColor.blue();
                newImage.setPixel(newImage.width() - x - 1, y, qRgb(r, g, b));
            }
        }
        ui->label_2->setPixmap(QPixmap::fromImage(newImage).scaled(ui->label_2->size()));
        image=newImage;
    }
}


void Naranja::on_pushButton_31_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
    image=imgCopy;
}


void Naranja::on_pushButton_32_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{ui->lineEdit_9->text().toInt()
                        ,ui->lineEdit_10->text().toInt()
                        ,ui->lineEdit_11->text().toInt()}, {
                        ui->lineEdit_12->text().toInt(),
                        ui->lineEdit_13->text().toInt(),
                        ui->lineEdit_14->text().toInt()}, {
                        ui->lineEdit_15->text().toInt(),
                        ui->lineEdit_16->text().toInt(),
                        ui->lineEdit_17->text().toInt()}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
    image=imgCopy;
}


void Naranja::on_pushButton_33_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{ui->lineEdit_9->text().toInt()
                        ,ui->lineEdit_10->text().toInt()
                        ,ui->lineEdit_11->text().toInt()}, {
                        ui->lineEdit_12->text().toInt(),
                        ui->lineEdit_13->text().toInt(),
                        ui->lineEdit_14->text().toInt()}, {
                        ui->lineEdit_15->text().toInt(),
                        ui->lineEdit_16->text().toInt(),
                        ui->lineEdit_17->text().toInt()}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
}


void Naranja::on_pushButton_34_clicked()
{
    ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
}


void Naranja::on_commandLinkButton_7_clicked()
{
    int width = image.width();
    int height = image.height();
    int pixel[8];
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            if(average>128)newImage->setPixel(x,y,qRgb(255,255,255));
            else newImage->setPixel(x,y,qRgb(0,0,0));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
    QImage newImg = QImage(width, height, QImage::Format_RGB888);
    newImg.fill(Qt::white);
    for (int y = 1; y < height; y++)
        for (int x = 1; x < width; x++) {
             memset(pixel, 0, 8);
             if (QColor(image.pixel(x, y)).red() == 0) {
                newImg.setPixel(x, y, qRgb(0, 0, 0));
                pixel[0] = QColor(image.pixel(x - 1, y - 1)).red();
                pixel[1] = QColor(image.pixel(x - 1, y)).red();
                pixel[2] = QColor(image.pixel(x - 1, y + 1)).red();
                pixel[3] = QColor(image.pixel(x, y - 1)).red();
                pixel[4] = QColor(image.pixel(x, y + 1)).red();
                pixel[5] = QColor(image.pixel(x + 1, y - 1)).red();
                pixel[6] = QColor(image.pixel(x + 1, y)).red();
                pixel[7] = QColor(image.pixel(x + 1, y + 1)).red();
                if (pixel[0] + pixel[1] + pixel[2] + pixel[3] + pixel[4] + pixel[5] + pixel[6] + pixel[7] == 0)
                     newImg.setPixel(x, y, qRgb(255, 255, 255));
             }
        }
    ui->label_2->setPixmap(QPixmap::fromImage(newImg).scaled(ui->label_2->size()));
    image=newImg;
}


void Naranja::on_commandLinkButton_8_clicked()
{
    int width = image.width();
    int height = image.height();
    int pixel[8];
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            if(average>128)newImage->setPixel(x,y,qRgb(255,255,255));
            else newImage->setPixel(x,y,qRgb(0,0,0));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
    QImage newImg = QImage(width, height, QImage::Format_RGB888);
    newImg.fill(Qt::white);
    for (int y = 1; y < height; y++)
        for (int x = 1; x < width; x++) {
             memset(pixel, 0, 8);
             if (QColor(image.pixel(x, y)).red() == 0) {
                newImg.setPixel(x, y, qRgb(0, 0, 0));
                pixel[0] = QColor(image.pixel(x - 1, y - 1)).red();
                pixel[1] = QColor(image.pixel(x - 1, y)).red();
                pixel[2] = QColor(image.pixel(x - 1, y + 1)).red();
                pixel[3] = QColor(image.pixel(x, y - 1)).red();
                pixel[4] = QColor(image.pixel(x, y + 1)).red();
                pixel[5] = QColor(image.pixel(x + 1, y - 1)).red();
                pixel[6] = QColor(image.pixel(x + 1, y)).red();
                pixel[7] = QColor(image.pixel(x + 1, y + 1)).red();
                if (pixel[0] + pixel[1] + pixel[2] + pixel[3] + pixel[4] + pixel[5] + pixel[6] + pixel[7] == 0)
                     newImg.setPixel(x, y, qRgb(color.red(),color.green(),color.blue()));
             }
        }
    ui->label_2->setPixmap(QPixmap::fromImage(newImg).scaled(ui->label_2->size()));
    image=newImg;
}


void Naranja::on_commandLinkButton_9_clicked()
{
    gallery gal;
    gal.show();
    gal.exec();
}


void Naranja::on_commandLinkButton_10_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{-1, 3, -1}, {3, -5, 3}, {-1, 3, -1}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
    image=imgCopy;
}


void Naranja::on_commandLinkButton_11_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{1, -3, 1}, {-3, 7, -3}, {1, -3, 1}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
    image=imgCopy;
}


void Naranja::on_commandLinkButton_12_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{3, 3, 3}, {-3, -3, -3}, {0, 0, 0}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
    image=imgCopy;
}


void Naranja::on_commandLinkButton_13_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{3, 0, -3}, {3, 5, -3}, {3, 0, -3}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
    image=imgCopy;
}


void Naranja::on_commandLinkButton_14_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{3, -1, 3}, {-1, -10, -1}, {3, -1, 3}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
    image=imgCopy;
}


void Naranja::on_commandLinkButton_15_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{4, -1, 1}, {-3, 3, 4}, {-1, -9, 1}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
    image=imgCopy;
}


void Naranja::on_commandLinkButton_16_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{-4, 3, 2}, {-3, 17, -3}, {2, -7, -4}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
    image=imgCopy;
}


void Naranja::on_commandLinkButton_17_clicked()
{
    QImage imgCopy;
    int width = image.width();
    int height = image.height();
    int window[3][3] = {{-5, 2, 1}, {-22, 22, 5}, {1, -6, 1}};
    if (image.format() != QImage::Format_RGB888)
        imgCopy = QImage(width, height, QImage::Format_RGB888);
    else
        imgCopy = QImage(image);
    QImage imgCopyrgbImg = QImage(image).convertToFormat(QImage::Format_RGB888);
    uint8_t *rgbImg = imgCopyrgbImg.bits();
    uint8_t *rgb = imgCopy.bits();
    int nRowBytes = (width * 24 + 31) / 32 * 4;
    int  lineNum_24 = 0;
    for (int x = 1; x < image.width(); x++) {
        for (int y = 1; y < image.height(); y++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int m = x - 1; m <= x + 1; m++)
                for (int n = y - 1; n <= y + 1; n++)
                    if (m >= 0 && m < width && n < height) {
                        lineNum_24 = n * nRowBytes;
                        sumR += rgbImg[lineNum_24 + m * 3] * window[n - y + 1][m - x + 1];
                        sumG += rgbImg[lineNum_24 + m * 3 + 1] * window[n - y + 1][m - x + 1];
                        sumB += rgbImg[lineNum_24 + m * 3 + 2] * window[n - y + 1][m - x + 1];
                    }
            int old_r = rgbImg[lineNum_24 + x * 3];
            sumR += old_r;
            sumR = qBound(0, sumR, 255);
            int old_g = rgbImg[lineNum_24 + x * 3 + 1];
            sumG += old_g;
            sumG = qBound(0, sumG, 255);
            int old_b = rgbImg[lineNum_24 + x * 3 + 2];
            sumB += old_b;
            sumB = qBound(0, sumB, 255);
            lineNum_24 = y * nRowBytes;
            rgb[lineNum_24 + x * 3] = sumR;
            rgb[lineNum_24 + x * 3 + 1] = sumG;
            rgb[lineNum_24 + x * 3 + 2] = sumB;
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(imgCopy).scaled(ui->label_2->size()));
    image=imgCopy;
}

