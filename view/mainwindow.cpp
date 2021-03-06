#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), mainLayout(new QVBoxLayout(this)), gridLayout(new QGridLayout()),
      turno(new QLabel()), menuPartita(nullptr), save(nullptr), save_name(nullptr)
{
    setWindowIcon(QIcon(":/resources/logo.jpg"));
    addMenu();   
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(gridLayout);
    turno->setObjectName("turno");
    turno->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(turno);
    setStyle();
    setLayout(mainLayout);

    resize(400,400);
}

void MainWindow::addMenu()
{
    QMenuBar* menubar = new QMenuBar(this);
    //MENU FILE
    QMenu* file = new QMenu("File",menubar);
    save = new QAction("Salva",file);
    save_name = new QAction("Salva con Nome",file);
    QAction *load = new QAction("Carica",file),
            *nuova= new QAction("Nuova Partita",file);
    file->addAction(nuova);
    file->addAction(load);
    file->addAction(save);
    file->addAction(save_name);
    save->setEnabled(false);
    save_name->setEnabled(false);
    save->setShortcut(QKeySequence("Ctrl+S"));
    save_name->setShortcut(QKeySequence("Ctrl+Shift+S"));
    load->setShortcut(QKeySequence("Ctrl+O"));
    nuova->setShortcut(QKeySequence("Ctrl+N"));
    
    connect(save_name, SIGNAL(triggered()), this, SLOT(selezionaFileSalvataggio()));
    connect(save, SIGNAL(triggered()), this, SIGNAL(salva()));
    connect(load, SIGNAL(triggered()), this, SLOT(selezionaFileCaricamento()));

    //alla pressione del tasto "Nuova partita", esso viene raccolto
    //dallo slot "Nuova partita" di mainwindow.
    connect(nuova, SIGNAL(triggered()), this, SLOT(nuovaPartita()));
    //MENU PARTITA
    menuPartita = new QMenu("Partita", menubar);

    QAction *reset = new QAction("Reset", menuPartita),
            *resa = new QAction("Dichiara Resa", menuPartita),
            *pareggio = new QAction("Dichiara Pareggio", menuPartita);
    connect(reset, SIGNAL(triggered()), this, SIGNAL(resetFinestra()));
    connect(resa, SIGNAL(triggered()), this, SIGNAL(resa()));
    connect(pareggio, SIGNAL(triggered()), this, SLOT(mostraPareggio()));
    menuPartita->addAction(reset);
    menuPartita->addAction(resa);
    menuPartita->addAction(pareggio);
    menuPartita->setEnabled(false);
    //aggiungo i menu alla menubar
    menubar->addMenu(file);
    menubar->addMenu(menuPartita);

    // Aggiungo la menubar al layout
    mainLayout->addWidget(menubar);
}

void MainWindow::addChessboard(int width, int height) 
{
    QSize tmp = size();
    pulisciFinestra();
    boardWidth = width;
    boardHeight = height;
    bool j = false;
    for(int i=0; i<width*height; ++i)
    {
        if(i % width)
            j = !j;
        ChessButton *button = new ChessButton(Posizione(i%width,i/width), this);
        button->setMinimumHeight(button->width());
        connect(button, SIGNAL(clicked(Posizione)), this, SIGNAL(casellaSelezionata(Posizione)));
        if(j)
            button->setObjectName("black");
        else
            button->setObjectName("white");
        gridLayout->addWidget(button, i/width, i%width);
    }
    resize(tmp);
    menuPartita->setEnabled(true);
    save->setEnabled(true);
    save_name->setEnabled(true);
    setEnabled(true);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    event->accept();
    setMaximumHeight(width());
    for(int i=0; i < gridLayout->count(); i++)
    {
        ChessButton* button = static_cast<ChessButton*>(gridLayout->itemAt(i)->widget());
        button->setMinimumHeight(button->width());
        button->setIconSize(button->size()*0.8);
    }   
}

void MainWindow::setStyle()
{ 
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    int dim = height > width ? width:height;
    dim *= 0.95;
    setMaximumSize(dim,dim); 
    gridLayout->setSpacing(0);
    QFile file(":/resources/chess/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);
}
void MainWindow::pulisciFinestra()
{
    for(int i=gridLayout->count()-1; i >= 0; i--)
        delete gridLayout->itemAt(i)->widget();
    turno->setText("");
    menuPartita->setEnabled(false);
    save->setEnabled(false);
    save_name->setEnabled(false);
}

void MainWindow::nuovaPartita()
{
    SelettoreGioco* sel = new SelettoreGioco();
    setEnabled(false);
    connect(sel, SIGNAL(finestraChiusa()), this, SLOT(abilitaFinestra()));
    connect(sel, SIGNAL(creaScacchi()), this, SIGNAL(nuovaPartitaScacchi()));
}

void MainWindow::mossaNonValida()
{
    QDialog *err = new QDialog(this);
    QVBoxLayout *layout_errore = new QVBoxLayout(err);
    layout_errore->addWidget(new QLabel(QString("Mossa non valida, reinserire posizione!"),err));
    err->show();
}

void MainWindow::aggiungiPedina(const Posizione& pos, const ID& pedina, const TipoGioco& tipoGioco)
{
    QString pathIcon(QString::fromStdString(":/resources/"+tipoGiocoToString(tipoGioco)+"/icons/"));
    if(tipoGioco == chess)
    {
        switch(pedina.getTipo())
        {
            case 'B': 
                pathIcon += "bishop";  
                break;
            case 'N': 
                pathIcon += "knight";
                break;
            case 'K':
                pathIcon += "king";
                break;
            case 'P':
                pathIcon += "pawn";
                break;
            case 'Q':
                pathIcon += "queen";
                break;
            case 'R': 
                pathIcon += "rook";
                break;
            default:
                pathIcon = "";
                break;
        }
    }
    pathIcon += "_"; 
    switch(pedina.getColore())
    {
        case bianco:
            pathIcon += "white";
            break;
        case nero:
            pathIcon += "black";
            break;
        default:
            pathIcon = "";
            break;
    }
    pathIcon += ".png";
    ChessButton* button = static_cast<ChessButton*>(gridLayout->itemAt(pos.x+pos.y*boardWidth)->widget());
    button->setIcon(QIcon(pathIcon));
    button->setIconSize(button->size()*0.8);
}

void MainWindow::pulisciCella(const Posizione& pos)
{
    ChessButton* button = static_cast<ChessButton*>(gridLayout->itemAt(pos.x+pos.y*boardWidth)->widget());
    button->setIcon(QIcon());
}

void MainWindow::selezionaPromozioneScacchi()
{
    SelettorePromozioneScacchi *sel = new SelettorePromozioneScacchi();
    setEnabled(false);
    connect(sel, SIGNAL(pedinaSelezionata(char)), this, SIGNAL(promozioneScacchi(char)));
}

void MainWindow::dialogAvviso(const QString& text, bool disableView)
{
    QDialog *avviso= new QDialog(this);
    QVBoxLayout *avviso_layout= new QVBoxLayout(avviso);
    avviso_layout->addWidget(new QLabel(text));
    setEnabled(!disableView);
    connect(avviso, SIGNAL(finished(int)), this, SIGNAL(terminaPartita()));
    avviso->show();
}

void MainWindow::mostraVincitore(const Colore& vincitore)
{
    dialogAvviso(QString::fromStdString("Ha vinto il giocatore " + coloreToString(vincitore)));
}

void MainWindow::mostraVincitoreResa(const Colore& vincitore)
{
    dialogAvviso(QString::fromStdString("Il giocatore avversario si è arreso.\nHa vinto il giocatore " + coloreToString(vincitore)));
}

void MainWindow::mostraPareggio()
{
    dialogAvviso("La partita è terminata in pareggio.");
}

void MainWindow::setLabelTurno(const Colore& s)
{
    turno->setText(QString::fromStdString("Turno del giocatore " + coloreToString(s)));
}

void MainWindow::selezionaFileSalvataggio()
{
    QString filename = QFileDialog::getSaveFileName(this, "Seleziona file", "", "*.json");
    if(filename != "")
    {
	QFileInfo fileinfo(filename);
        emit salvaConNome(fileinfo.absoluteDir().filePath(fileinfo.completeBaseName() + ".json"));
    }
}

void MainWindow::selezionaFileCaricamento()
{
    QString filename = QFileDialog::getOpenFileName(this, "Seleziona file", "", "*.json");
    if(filename != "")
        emit carica(filename);
}

void MainWindow::erroreFile()
{
    dialogAvviso("Errore nel caricamento del file", false);
}

void MainWindow::abilitaFinestra()
{
   setEnabled(true);
}
