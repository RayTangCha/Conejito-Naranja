#include "gallery.h"
#include "ui_gallery.h"
#include <fstream>
QString curitem;
bool openpic=0;

gallery::gallery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gallery)
{
    ui->setupUi(this);
    ui->label_6->setVisible(0);
    setWindowFlag(Qt::FramelessWindowHint);
    std::string str=" ";
    std::ifstream ifs;
    int total=0;
    ifs.open("C:\\Users\\Public\\Documents\\NaranjaPhotoHistory.dat");
    ui->listWidget_2->setIconSize(QSize(100, 100));
    ui->listWidget_2->setSpacing(10);
    for(;getline(ifs,str);)
        if(str!=""){
            QListWidgetItem *imageItem = new QListWidgetItem;
            imageItem->setIcon(QIcon(QString::fromStdString(str)));
            imageItem->setSizeHint(QSize(200, 160));
            imageItem->setText(QString::fromStdString(str));
            ui->listWidget_2->addItem(imageItem);
            total++;
        }
    ui->lcdNumber->display(total);
}

gallery::~gallery()
{
    delete ui;
}

void gallery::on_pushButton_clicked()
{
    this->close();
}


void gallery::on_pushButton_2_clicked()
{
    std::string str=" ";
    std::ifstream ifs;
    ifs.open("C:\\Users\\Public\\Documents\\NaranjaPhotoHistory.dat");
    ui->listWidget_2->clear();
    for(;getline(ifs,str);)
        if(str!=""&&QString::fromStdString(str).contains(ui->lineEdit->text(),Qt::CaseInsensitive)){
            QListWidgetItem *imageItem = new QListWidgetItem;
            imageItem->setIcon(QIcon(QString::fromStdString(str)));
            imageItem->setSizeHint(QSize(200, 160));
            imageItem->setText(QString::fromStdString(str));
            ui->listWidget_2->addItem(imageItem);
        }
}


void gallery::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    QImage image;
    if (image.load(item->text()))
        ui->label_4->setPixmap(QPixmap::fromImage(image).scaled(ui->label_4->size()));
    std::string::size_type iPos = item->text().toStdString().find_last_of('/') + 1;
    std::string filename = item->text().toStdString().substr(iPos, item->text().toStdString().length() - iPos);
    ui->label_5->setText(QString::fromStdString(filename));
    curitem=item->text();
}


void gallery::on_pushButton_3_clicked()
{
    std::ofstream ofs;
    ofs.open("C:\\Users\\Public\\Documents\\NaranjaPhotoHistory.dat",std::ios::trunc);
    ofs<<"";
    ofs.close();
    this->close();
}


void gallery::on_pushButton_4_clicked()
{
    if(openpic){
        openpic=0;
        ui->pushButton_4->setText("Open");
        ui->label_6->setVisible(0);
    }
    else{
        ui->label_6->setVisible(1);
        ui->pushButton_4->setText("Close");
        QImage image;
        if (image.load(curitem))
            ui->label_6->setPixmap(QPixmap::fromImage(image).scaled(ui->label_6->size()));
        openpic=1;
    }
}

