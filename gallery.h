#ifndef GALLERY_H
#define GALLERY_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class gallery;
}

class gallery : public QDialog
{
    Q_OBJECT

public:
    explicit gallery(QWidget *parent = nullptr);
    ~gallery();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::gallery *ui;
};

#endif // GALLERY_H
