#include "naranja.h"
#include "ui_naranja.h"
QImage image;
QString OpenFile;
QColor color=qRgb(95,75,139);
bool m_bPressed=false;
QPoint m_point;

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
    setWindowFlag(Qt::FramelessWindowHint);
    std::ifstream ifs;
    ifs.open("C:\\Users\\Public\\Documents\\NaranjaSettings.dat");
    int settings;
    ifs>>settings;
    if(ifs.is_open()){
        ui->checkBox_2->setCheckState(settings/1000?Qt::Checked:Qt::Unchecked);
        ui->checkBox_3->setCheckState(settings%1000-settings%100?Qt::Checked:Qt::Unchecked);
        ui->checkBox_4->setCheckState(settings%100-settings%10?Qt::Checked:Qt::Unchecked);
        ui->checkBox_5->setCheckState(settings%10?Qt::Checked:Qt::Unchecked);
    }
    ifs.close();
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
    if(ui->checkBox_4->isChecked()){
        OpenFile="C:\\Users\\Public\\Documents\\NaranjaPhotoTemp.png";
        if (OpenFile != "")
               if (image.load(OpenFile))
                   ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
    }
    ui->lineEdit_2->setPlaceholderText(" Watermark Text");
    ui->tabWidget->setTabShape(QTabWidget::Rounded);
}

Naranja::~Naranja()
{
    delete ui;
}


void Naranja::on_pushButton_clicked()
{
    if(ui->checkBox_2->isChecked())
        QMessageBox::warning(this,"Warning","You are leaving this application.");
    if(ui->checkBox_3->isChecked())
        image.save("C:\\Users\\Public\\Documents\\NaranjaPhotoTemp.png");
    std::ofstream ofs;
    ofs.open("C:\\Users\\Public\\Documents\\NaranjaSettings.dat",std::ios::trunc);
    ofs<<ui->checkBox_2->isChecked()<<ui->checkBox_3->isChecked()<<ui->checkBox_4->isChecked()<<ui->checkBox_5->isChecked();
    ofs.close();
    QApplication::exit();
}


void Naranja::on_pushButton_2_clicked()
{
    OpenFile = QFileDialog::getOpenFileName(this,
           "Please Choose An Image File",
           "",
           "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    if (OpenFile != "")
           if (image.load(OpenFile))
               ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
    std::string::size_type iPos = OpenFile.toStdString().find_last_of('/') + 1;
    std::string filename = OpenFile.toStdString().substr(iPos,OpenFile.toStdString().length() - iPos);
    ui->label_3->setText(QString::fromStdString(filename.size()<30?filename:filename.substr(0,30)+"..."));
}


void Naranja::on_pushButton_3_clicked()
{
    ui->label_2->clear();
    ui->label_3->setText("Please Open File");
}


void Naranja::on_pushButton_4_clicked()
{
    QClipboard *clip=QApplication::clipboard();
    clip->setPixmap(QPixmap::fromImage(image));
}


void Naranja::on_pushButton_5_clicked()
{
    QClipboard *clip=QApplication::clipboard();
    image=clip->image();
    ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
    ui->label_3->setText("From Clipboard");
    image.save("C:\\Users\\Public\\Documents\\NaranjaPhotoTemp.png");
    OpenFile="C:\\Users\\Public\\Documents\\NaranjaPhotoTemp.png";
}


void Naranja::on_pushButton_6_clicked()
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


void Naranja::on_pushButton_7_clicked()
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


void Naranja::on_pushButton_8_clicked()
{
    if (OpenFile != "")
           if (image.load(OpenFile))
               ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(OpenFile);
    std::string::size_type iPos = OpenFile.toStdString().find_last_of('/') + 1;
    std::string filename = OpenFile.toStdString().substr(iPos,OpenFile.toStdString().length() - iPos);
    ui->label_3->setText(QString::fromStdString(filename.size()<30?filename:filename.substr(0,30)+"..."));
}


void Naranja::on_pushButton_9_clicked()
{
    image.save(OpenFile);
}


void Naranja::on_pushButton_10_clicked()
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


void Naranja::on_pushButton_11_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    int cri=ui->lineEdit->text().toInt();
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


void Naranja::on_pushButton_12_clicked()
{
    color = QColorDialog::getColor(color);
    ui->label_5->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_13_clicked()
{
    QPainter painter(&image);
    int fontSize = 25, spacing = 10;
    QFont font("Lucida Calligraphy", fontSize, QFont::Thin);
    font.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    painter.setFont(font);
    if(ui->checkBox->isChecked()) painter.setPen(color);
    else painter.setPen(QColor(150, 150, 150));
    painter.translate(image.width() / 2, -image.width() / 2);
    painter.rotate(45);
    int squareEdgeSize = image.width() * sin(45.0) + image.height() * sin(45.0);
    int hCount = squareEdgeSize / ((fontSize + spacing) * (ui->lineEdit_2->text().size() + 1)) + 1;
    int x = squareEdgeSize / hCount + (fontSize + spacing) * 3;
    int y = x / 2;
    for (int i = 0; i < hCount; i++)
        for (int j = 0; j < hCount * 2; j++)
                painter.drawText(x * i, y * j,ui->lineEdit_2->text());
    ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
}


void Naranja::on_pushButton_14_clicked()
{
    if(ui->comboBox->currentText()=="Vertical"){
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


void Naranja::on_pushButton_15_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*(color.red()/255.),average*(color.green()/255.),average*(color.blue()/255.)));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_16_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    if(ui->comboBox->currentText()=="Vertical"){
        for(int x = 0; x<newImage->width(); x++){
            for(int y = 0; y<newImage->height(); y++){
                oldColor = QColor(image.pixel(x,y));
                int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
                newImage->setPixel(x,y,qRgb(average*(color.red()/255.)*((x+image.width()/ui->spinBox->value())/(image.width()/ui->spinBox->value()))
                                            ,average*(color.green()/255.)*((x+image.width()/ui->spinBox->value())/(image.width()/ui->spinBox->value()))
                                            ,average*(color.blue()/255.)*((x+image.width()/ui->spinBox->value())/(image.width()/ui->spinBox->value()))));
            }
        }
    }
    else{
        for(int x = 0; x<newImage->width(); x++){
            for(int y = 0; y<newImage->height(); y++){
                oldColor = QColor(image.pixel(x,y));
                int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
                newImage->setPixel(x,y,qRgb(average*(color.red()/255.)*((y+image.height()/ui->spinBox->value())/(image.height()/ui->spinBox->value()))<255
                                            ,average*(color.green()/255.)*((y+image.height()/ui->spinBox->value())/(image.height()/ui->spinBox->value()))
                                            ,average*(color.blue()/255.)*((y+image.height()/ui->spinBox->value())/(image.height()/ui->spinBox->value()))));
            }
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
            newImage->setPixel(x,y,qRgb(average*(color.red()/255.)*((x+image.width()/ui->spinBox_2->value())/(image.width()/ui->spinBox_2->value()))
                                        ,average*(color.green()/255.)*((x+image.width()/ui->spinBox_2->value())/(image.width()/ui->spinBox_2->value()))
                                        ,average*(color.blue()/255.)*((x+image.width()/ui->spinBox_2->value())/(image.width()/ui->spinBox_2->value()))));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
    newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average*(color.red()/255.)*((y+image.height()/ui->spinBox_3->value())/(image.height()/ui->spinBox_3->value()))
                                        ,average*(color.green()/255.)*((y+image.height()/ui->spinBox_3->value())/(image.height()/ui->spinBox_3->value()))
                                        ,average*(color.blue()/255.)*((y+image.height()/ui->spinBox_3->value())/(image.height()/ui->spinBox_3->value()))));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_18_clicked()
{
    color = qRgb(255-color.red(),255-color.green(),255-color.blue());
    ui->label_5->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_20_clicked()
{
    OpenFile = QFileDialog::getOpenFileName(this,
           "Please choose an image file",
           "",
           "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    image.save(OpenFile);
}


void Naranja::on_commandLinkButton_3_clicked()
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


void Naranja::on_commandLinkButton_4_clicked()
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


void Naranja::on_pushButton_19_clicked()
{
    color = qRgb(186,110,64);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_21_clicked()
{
    color = qRgb(154,146,101);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_22_clicked()
{
    color = qRgb(220,223,227);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_23_clicked()
{
    color = qRgb(255,180,66);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_commandLinkButton_2_clicked()
{
    OpenFile="C:\\Users\\Public\\Documents\\NaranjaPhotoTemp.png";
    if (OpenFile != "")
           if (image.load(OpenFile))
               ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
}


void Naranja::on_pushButton_24_clicked()
{
    color = qRgb(87,33,77);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_25_clicked()
{
    color = qRgb(237,116,100);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_27_clicked()
{
    color = qRgb(224, 69, 123);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_26_clicked()
{
    color = qRgb(159, 144, 193);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_28_clicked()
{
    color = qRgb(145, 168, 208);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_29_clicked()
{
    color = qRgb(102, 103, 171);
    ui->label_11->setText("RGB("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
    QImage *newImage = new QImage(ui->label_6->width(),ui->label_6->height(), QImage::Format_ARGB32);
    for(int x = 0; x<newImage->width(); x++)
        for(int y = 0; y<newImage->height(); y++)
            newImage->setPixel(x,y,qRgb(color.red(),color.green(),color.blue()));
    ui->label_6->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_6->size()));
}


void Naranja::on_pushButton_30_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    double ramp=ui->lineEdit_3->text().toDouble();
    double gamp=ui->lineEdit_4->text().toDouble();
    double bamp=ui->lineEdit_5->text().toDouble();
    double radd=ui->lineEdit_6->text().toDouble();
    double gadd=ui->lineEdit_7->text().toDouble();
    double badd=ui->lineEdit_8->text().toDouble();
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            newImage->setPixel(x,y,qRgb(oldColor.red()*ramp+radd,oldColor.green()*gamp+gadd,oldColor.blue()*bamp+badd));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
    image=*newImage;
}


void Naranja::on_pushButton_31_clicked()
{
    QImage *newImage = new QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    double ramp=ui->lineEdit_3->text().toDouble();
    double gamp=ui->lineEdit_4->text().toDouble();
    double bamp=ui->lineEdit_5->text().toDouble();
    double radd=ui->lineEdit_6->text().toDouble();
    double gadd=ui->lineEdit_7->text().toDouble();
    double badd=ui->lineEdit_8->text().toDouble();
    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(image.pixel(x,y));
            newImage->setPixel(x,y,qRgb(oldColor.red()*ramp+radd,oldColor.green()*gamp+gadd,oldColor.blue()*bamp+badd));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(*newImage).scaled(ui->label_2->size()));
}


void Naranja::on_pushButton_32_clicked()
{
    ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
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
    image=imgCopy;
}


void Naranja::on_pushButton_34_clicked()
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


void Naranja::on_pushButton_35_clicked()
{
    ui->label_2->setPixmap(QPixmap::fromImage(image).scaled(ui->label_2->size()));
}


void Naranja::on_pushButton_36_clicked()
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


void Naranja::on_pushButton_37_clicked()
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


void Naranja::on_pushButton_38_clicked()
{
    if(ui->comboBox_3->currentText()=="Horizontal"){
        QImage imgCopy;
        int width = image.width();
        int height = image.height();
        int window[3][3]={{3, 3, 3}, {-3, -3, -3}, {0, 0, 0}};
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
    else{
        QImage imgCopy;
        int width = image.width();
        int height = image.height();
        int window[3][3]={{3, -3, 0}, {3, -3, 0}, {3, -3, 0}};
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
}


void Naranja::on_pushButton_39_clicked()
{
    on_pushButton_15_clicked();
    on_pushButton_36_clicked();
}


void Naranja::on_pushButton_40_clicked()
{
    on_pushButton_15_clicked();
    on_pushButton_15_clicked();
    on_pushButton_36_clicked();
}


void Naranja::on_pushButton_41_clicked()
{
    on_pushButton_6_clicked();
    on_pushButton_18_clicked();
    on_pushButton_15_clicked();
    on_pushButton_6_clicked();
    on_pushButton_18_clicked();
}


void Naranja::on_pushButton_42_clicked()
{
    on_pushButton_15_clicked();
    on_pushButton_15_clicked();
    on_pushButton_7_clicked();
    on_pushButton_10_clicked();
    on_pushButton_36_clicked();
}


void Naranja::on_label_2_linkActivated(const QString &link)
{
    ui->pushButton_2->click();
}

