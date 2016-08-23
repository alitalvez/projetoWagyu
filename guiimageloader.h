#ifndef GUIIMAGELOADER_H
#define GUIIMAGELOADER_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QScrollArea>
#include <QLabel>
#include "imgloader.h"

namespace Ui {
class GUIImageLoader;
}

class GUIImageLoader : public QDialog
{
    Q_OBJECT

public:
    explicit GUIImageLoader(QWidget *parent = 0);
    ~GUIImageLoader();
    ImgLoader* getLoader();
    int getLargura();
    int getAltura();
    int getNc();

private:
    Ui::GUIImageLoader *ui;
    ImgLoader *loader = NULL;

    int largura;
    int altura;
    int nc;

private slots:
    void slotGetCaminho();

};

#endif // GUILoadImage_H