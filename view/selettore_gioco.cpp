#include "selettore_gioco.h"

SelettoreGioco::SelettoreGioco(QWidget *parent) : QWidget(parent), mainLayout(new QVBoxLayout(this)), gruppoGiochi(new QButtonGroup(this))
{
    setLayout(mainLayout);
    setMinimumWidth(300);
    QLabel* info = new QLabel("Seleziona gioco", this);
    info->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(info);
    QPushButton *pulsanteScacchi = new QPushButton(this);
    connect(gruppoGiochi, SIGNAL(buttonClicked(int)), this, SLOT(close()));  // chiudi finestra selettore quando viene selezionato un gioco
    pulsanteScacchi->setText("Scacchi");
    mainLayout->addWidget(pulsanteScacchi);
    gruppoGiochi->addButton(pulsanteScacchi);
    //il pulsante scacchi, se premuto
    //verrà raccolto da "creaScacchi"
    connect(pulsanteScacchi, SIGNAL(clicked()), this, SIGNAL(creaScacchi()));
    show();
}


//CreaScacchi, crea il nuovo tipo di gioco, in
//base al pulsante premuto, in questo caso solamente "Scacchi"
//ed emetterà il segnale "creaNuovoGioco", il quale passa
//il nuovo gioco alla MainWindow.

void SelettoreGioco::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    emit finestraChiusa();
}
