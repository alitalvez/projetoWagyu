#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QCheckBox>
#include <QSpinBox>
#include <QEventLoop>
#include <QMenu>
#include <cmath>
#include "guimatrizcoo.h"
#include "guiimageloader.h"
#include "guiresults.h"
#include "imgloader.h"
#include "haralick.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GUIImageLoader *openFile = NULL;
    GUIResults *results = NULL;
    GUIMatrizCoo *matriz = NULL;
    ImgLoader *loader;
    double * matrizCoN_CPU;
    double * atributosSelecionados = new double[14];

    bool * boxCheckeds = new bool[14];
    bool isNovaImg = false;

    // GUI
        // MenuBar
        void createActions();
        void createMenu();
        QMenu *fileMenu;
        QMenu *resultsMenu;
        QAction *openAct;
        QAction *resultAct;
        QAction *matrizAct;
        Haralick *ath;

        // GuiPrincipal
        void createConnections();
        void createGUI();
        void createPreview();
        void createATH();
        void createDMCO();
        void createNT();
        QFrame *framePreview;
        QFrame *frameATH;
        QFrame *frameDMCO;
        QFrame *frameNT;
        QLabel *labelPreview;
        QLabel *labelATH;
        QLabel *labelDMCO;
        QLabel *labelNT;
        QScrollArea *areaPreview;
        QSpinBox *caixaDMCO;
        QSpinBox *caixaNT;
        //CheckBox
        QString nomesATH[14] = {"Selecionar Todos", "Energia",
                               "Contraste", "Correlação",
                               "Variancia", "MDI",
                               "Media Soma", "Variancia Soma",
                               "Entropia Soma", "Entropia",
                               "Variancia Diferença", "Entropia Diferença",
                               "Medidas Correlação 1", "Medidas Correlação 2"};
        QCheckBox **caixasDeSelecao = new QCheckBox*[14];
        void createBoxes();

private slots:
    void slotOpen();
    void slotResult();
    void slotMatriz();
    void slotExtracao();

    //Slots CheckBox
    void slotSelectAll();
    void slotATHs();

};

#endif // MAINWINDOW_H
