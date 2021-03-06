#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainWindow)
{
    caixasDeSelecao = new QCheckBox*[14];
    boxCheckeds = new bool[14];

    nomesATH[0] = "Selecionar Todos";
    nomesATH[1] = "Energia";
    nomesATH[2] = "Contraste";
    nomesATH[3] = "Correlação";
    nomesATH[4] = "Variancia";
    nomesATH[5] = "MDI";
    nomesATH[6] = "Media Soma";
    nomesATH[7] = "Variancia Soma";
    nomesATH[8] = "Entropia Soma";
    nomesATH[9] = "Entropia";
    nomesATH[10] = "Variancia Diferença";
    nomesATH[11] = "Entropia Diferença";
    nomesATH[12] = "Medidas Correlação 1";
    nomesATH[13] = "Medidas Correlação 2";


    ui->setupUi(this);
    createGUI();

    ui->extrairPb->setEnabled(false);
    frameATH->setEnabled(false);
    frameDMCO->setEnabled(false);
    frameNT->setEnabled(false);
    status = false;

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
// MENU BAR
    createActions();
    createMenu();
// Fim MENU BAR

    createConnections(); //Conecta a interface grafica
}

MainWindow::~MainWindow()
{
    delete [] loader;
    delete framePreview;
    delete frameATH;
    delete frameDMCO;
    delete labelATH;
    delete labelDMCO;
    delete caixaDMCO;
    delete caixasDeSelecao;
    delete fileMenu;
    delete ath;
    delete [] lbImg;
    delete openAct;
    delete matrizAct;
    delete [] boxCheckeds;
    delete ui;
}

/*
 *
 *
 *
 * METODOS
 *
 *
 *
 */

void MainWindow::createConnections()
{
    connect(caixasDeSelecao[0], SIGNAL(clicked()), this, SLOT(slotSelectAll()));
    for(int i = 1; i < 14; i++)
        connect(caixasDeSelecao[i], SIGNAL(clicked()), this, SLOT(slotATHs()));

    connect(ui->extrairPb, SIGNAL(released()), this, SLOT(slotExtracao()));

    matriz = new GUIMatrizCoo();
    connect(matriz->getBt(0), SIGNAL(released()), this, SLOT(slotMatrizesCoOc135()));
    connect(matriz->getBt(1), SIGNAL(released()), this, SLOT(slotMatrizesCoOc90()));
    connect(matriz->getBt(2), SIGNAL(released()), this, SLOT(slotMatrizesCoOc45()));
    connect(matriz->getBt(3), SIGNAL(released()), this, SLOT(slotMatrizesCoOc0()));
    connect(matriz->getBt(4), SIGNAL(released()), this, SLOT(slotMatrizesCoOc()));
    connect(matriz->getBt(5), SIGNAL(released()), this, SLOT(slotMatrizesCoOc0()));
    connect(matriz->getBt(6), SIGNAL(released()), this, SLOT(slotMatrizesCoOc45()));
    connect(matriz->getBt(7), SIGNAL(released()), this, SLOT(slotMatrizesCoOc90()));
    connect(matriz->getBt(8), SIGNAL(released()), this, SLOT(slotMatrizesCoOc135()));

}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Abrir"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Carregar uma nova imagem"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(slotOpen()));

    matrizAct = new QAction(tr("&Matriz"), this);
    matrizAct->setStatusTip(tr("Exibe as Matrizes de Co-ocorência"));
    matrizAct->setEnabled(false);
    connect(matrizAct, SIGNAL(triggered()), this, SLOT(slotMatriz()));


}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&Arquivo"));
    fileMenu->addAction(openAct);
}

void MainWindow::createGUI()
{
    createPreview();
    createATH();
    createDMCO();
    createNT();
}

void MainWindow::createPreview()
{
    framePreview = new QFrame(this->centralWidget());
    framePreview->setEnabled(true);
    framePreview->setGeometry(20,20,331,331);
    framePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    framePreview->setLineWidth(1);
    framePreview->setFrameShadow(QFrame::Raised);
    framePreview->setFrameShape(QFrame::StyledPanel);
    framePreview->setVisible(true);

    labelPreview = new QLabel(framePreview);
    labelPreview->setText("PREVIEW");
    labelPreview->setGeometry(140,0,71,16);
    labelPreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    labelPreview->setVisible(true);

}

void MainWindow::createATH()
{
    frameATH = new QFrame(this->centralWidget());
    frameATH->setEnabled(true);
    frameATH->setGeometry(400,20,231,331);
    frameATH->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    frameATH->setLineWidth(1);
    frameATH->setFrameShadow(QFrame::Raised);
    frameATH->setFrameShape(QFrame::StyledPanel);
    frameATH->setVisible(true);

    labelATH = new QLabel(frameATH);
    labelATH->setText("ATRIBUTOS DE TEXTURA");
    labelATH->setGeometry(40,0,171,16);
    labelATH->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    labelATH->setVisible(true);

    createBoxes();
}

void MainWindow::createBoxes()
{

    for(int i = 0, h = 30; i < 14; i++, h += 20)
    {
        caixasDeSelecao[i] = new QCheckBox(nomesATH[i], frameATH);
        caixasDeSelecao[i]->setVisible(true);
        caixasDeSelecao[i]->setGeometry(10,h,191,25);
        caixasDeSelecao[i]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
}

void MainWindow::createDMCO()
{
    frameDMCO = new QFrame(this->centralWidget());
    frameDMCO->setEnabled(true);
    frameDMCO->setGeometry(680,20, 241,71);
    frameDMCO->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    frameDMCO->setLineWidth(1);
    frameDMCO->setFrameShadow(QFrame::Raised);
    frameDMCO->setFrameShape(QFrame::StyledPanel);
    frameDMCO->setVisible(true);

    labelDMCO = new QLabel(frameDMCO);
    labelDMCO->setText("DISTANCIA MCO");
    labelDMCO->setGeometry(60,0,121,16);
    labelDMCO->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    labelDMCO->setToolTip("Distancia Matriz de Coocorrencia");
    labelDMCO->setVisible(true);

    caixaDMCO = new QSpinBox(frameDMCO);
    caixaDMCO->setEnabled(true);
    caixaDMCO->setGeometry(40,30,160,30);
    caixaDMCO->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    //caixaDMCO->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    caixaDMCO->setKeyboardTracking(true);
    caixaDMCO->setMinimum(1);
    caixaDMCO->setMaximum(99999);
    caixaDMCO->setVisible(true);
}

void MainWindow::createNT()
{
    frameNT = new QFrame(this->centralWidget());
    frameNT->setEnabled(true);
    frameNT->setGeometry(680,141, 241,71);
    frameNT->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    frameNT->setLineWidth(1);
    frameNT->setFrameShadow(QFrame::Raised);
    frameNT->setFrameShape(QFrame::StyledPanel);
    frameNT->setVisible(true);

    labelNT = new QLabel(frameNT);
    labelNT->setText("NUMERO DE THREADS");
    labelNT->setGeometry(50,0,161,16);
    labelNT->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    labelNT->setVisible(true);

    caixaNT = new QSpinBox(frameNT);
    caixaNT->setEnabled(true);
    caixaNT->setGeometry(40,30,160,30);
    caixaNT->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    //caixaNT->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    caixaNT->setKeyboardTracking(true);
    caixaNT->setMinimum(1);
    caixaNT->setMaximum(99999);
    caixaNT->setValue(4);
    caixaNT->setVisible(true);
}

/*
 *
 *
 *
 * SLOTS
 *
 *
 *
 */

void MainWindow::slotMatrizesCoOc()
{
    matriz->exibeResults(ath->getMatTot(), pow(2, 12), "Matriz Total");
}

void MainWindow::slotMatrizesCoOc0()
{
    matriz->exibeResults(ath->getMc0(), pow(2, 12), "Matriz 0º");
}

void MainWindow::slotMatrizesCoOc45()
{
    matriz->exibeResults(ath->getMc45(), pow(2, 12), "Matriz 45º");
}

void MainWindow::slotMatrizesCoOc90()
{
    matriz->exibeResults(ath->getMc90(), pow(2, 12), "Matriz 90º");
}

void MainWindow::slotMatrizesCoOc135()
{
    matriz->exibeResults(ath->getMc135(), pow(2, 12), "Matriz 135º");
}

void MainWindow::carregaCaminho()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Selecionar Pasta"), QDir::currentPath(), QFileDialog::ShowDirsOnly);

    QDirIterator itDir(dir, QDirIterator::Subdirectories);

    while(itDir.hasNext())
    {
        QString cam = itDir.next();

        int pos1 = cam.lastIndexOf(".");
        QString fim = cam;
        fim = fim.remove(0, pos1);
        if(fim == ".1")
            caminhoImg.append(cam);
    }
}

void MainWindow::slotOpen()
{
    int x = this->geometry().x() + this->centralWidget()->geometry().x() + 30;
    int y = this->geometry().y() + this->centralWidget()->geometry().y() + 40;

    this->carregaCaminho();

    lbImg = new QPushButton[caminhoImg.size()]();

    int xx = 10;
    int yy = 40;

    if(loader == NULL)
    {
        loader = new ImgLoader[caminhoImg.size()]();
        matrizCoN_CPU = new double * [caminhoImg.size()];
        atributosSelecionados = new double * [caminhoImg.size()];
        ath = new Haralick [caminhoImg.size()]();
    }
    QSignalMapper *signalMapper = new QSignalMapper(this);

    for(int i = 0; i < caminhoImg.size(); i++)
    {
        QString nome = caminhoImg.at(i);

        int pos = nome.lastIndexOf("/");

        nome = nome.remove(0, pos + 1);

        loader[i].setXY(x, y);
        loader[i].carregaCaminho(caminhoImg.at(i));

        lbImg[i].setParent(framePreview);
        lbImg[i].setText(nome);
        lbImg[i].show();
        lbImg[i].move(xx, yy);
        lbImg[i].setFlat(true);

        connect(&this->lbImg[i], SIGNAL(clicked()), signalMapper, SLOT(map()));

        signalMapper->setMapping(&this->lbImg[i], i);

        yy += 20;

        if(loader[i].getCaminho()!= NULL)
        {
            ui->extrairPb->setEnabled(true);
            frameATH->setEnabled(true);
            frameDMCO->setEnabled(true);
            frameNT->setEnabled(true);

            QPixmap pix("../projetoWagyu/Extras/gifinho.gif");
            if(pix.isNull())
            {
                pix = QPixmap(311, 301);
                QColor color(189,237,2,255);
                pix.fill(color);
            }

            QSplashScreen *spl = new QSplashScreen(pix);
            spl->showMessage("Calculando...", Qt::AlignCenter, Qt::black);
            spl->setGeometry(x, y, pix.width(), pix.height());
            qApp->processEvents(QEventLoop::AllEvents);

            spl->show();
            spl->raise();
            spl->activateWindow();

            QTime dieTime = QTime::currentTime().addMSecs(1000);
            while(QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            atributosSelecionados[i] = new double [14];
            for(int j = 1; j < 14; j++)
            {
                atributosSelecionados[i][j] = -2;
                boxCheckeds[j] = false;
                caixasDeSelecao[j]->setChecked(false);
                caixaDMCO->setValue(1);
                caixaNT->setValue(4);
            }

            int NG = pow(2, 12);
            matrizCoN_CPU[i] = new double[NG * NG];
            ath[i].HaralickInit(loader[i].getMatrizOrig(), loader[i].getLargura(), loader[i].getAltura(), NG, caixaNT->value());
            ath[i].calcularMatrizCoN(matrizCoN_CPU[i], caixaDMCO->value());
            ath[i].atCpu(matrizCoN_CPU[i], NG);
            matrizAct->setEnabled(true);
            spl->finish(this);
        }
    }
    status = true;
    connect(signalMapper, SIGNAL(mapped(const int &)), this, SLOT(slotPreview(const int &)));
}

void MainWindow::slotPreview(const int &i)
{
    QDesktopWidget t;
    QRect screenSize = t.availableGeometry(t.primaryScreen());
    QWidget* wgMat = new QWidget;
    wgMat->setWindowTitle(lbImg[i].text());

    wgMat->resize(380, 405);
    wgMat->move(screenSize.width()/2 - wgMat->size().width()/2, screenSize.height()/2 - wgMat->size().height()/2);
    wgMat->setMinimumSize(wgMat->size());
    wgMat->setMaximumSize(wgMat->size());


    QFrame *framePreview = new QFrame(wgMat);
    framePreview->setEnabled(true);
    framePreview->setGeometry(20,20,331,331);
    framePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    framePreview->setLineWidth(1);
    framePreview->setFrameShadow(QFrame::Raised);
    framePreview->setFrameShape(QFrame::StyledPanel);
    framePreview->setVisible(true);

    QLabel *labelPreview = new QLabel(framePreview);
    labelPreview->setText("PREVIEW");
    labelPreview->setGeometry(140,0,71,16);
    labelPreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    labelPreview->setVisible(true);

    QScrollArea *areaPreview = new QScrollArea(framePreview);
    areaPreview->setGeometry(10,20,311,301);
    areaPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    areaPreview->setFrameShadow(QFrame::Sunken);
    areaPreview->setFrameShape(QFrame::StyledPanel);
    areaPreview->setWidgetResizable(true);

    wgMat->show();
    loader[i].showImage();
    QLabel *imgPreview = loader[i].getImgPreview();

    areaPreview->setWidget(imgPreview);

}

void MainWindow::slotMatriz()
{
    matriz->exec();
}

void MainWindow::slotExtracao()
{
    for(int i = 1; i < 14; i++)
        boxCheckeds[i] = caixasDeSelecao[i]->isChecked();

    if(status)
    {
        QString dir = QFileDialog::getSaveFileName(this, "Salvar Arquivo", QDir::currentPath());
        QPixmap pix("../projetoWagyu/Extras/gifinho.gif");
        if(pix.isNull())
        {
            pix = QPixmap(300, 300);
            QColor color(189,237,2,255);
            pix.fill(color);
        }

        QSplashScreen *spl = new QSplashScreen(pix);
        spl->showMessage("Extraindo...", Qt::AlignCenter, Qt::black);
        spl->move(this->geometry().x() + (this->centralWidget()->width()/2) - 150, this->geometry().y() + (this->centralWidget()->height()/2) - 150);
        qApp->processEvents(QEventLoop::AllEvents);
        spl->show();
        spl->raise();
        spl->activateWindow();

        QTime dieTime = QTime::currentTime().addMSecs(500);
        while(QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        for(int i = 0; i < caminhoImg.size(); i++)
            ath[i].calcATH(atributosSelecionados[i], boxCheckeds);


        QByteArray ba = dir.toLatin1();
        const char *c_str = ba.data();


        std::ofstream arqSaida(c_str);

        for(int i = 1; i < 14; i++)
        {
            if(boxCheckeds[i])
            {
                arqSaida << nomesATH[i].toStdString() << ";";
                for(int j = 0; j < caminhoImg.size(); j++)
                    arqSaida << std::fixed << atributosSelecionados[j][i] << ";";
            }
            arqSaida << "\n";
        }
        arqSaida.close();

        spl->finish(this);
    }
}

void MainWindow::slotSelectAll()
{
    if(caixasDeSelecao[0]->isChecked())
        for(int i = 1; i < 14; i++)
            caixasDeSelecao[i]->setChecked(true);
    else
        for(int i = 1; i < 14; i++)
            caixasDeSelecao[i]->setChecked(false);
}

void MainWindow::slotATHs()
{
    if(caixasDeSelecao[0]->isChecked())
        caixasDeSelecao[0]->setChecked(false);
}
