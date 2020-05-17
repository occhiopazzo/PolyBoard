#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include "view/mainwindow.h"
#include "view/selettore_gioco.h"
#include "gioco/gioco.h"
#include "gioco/scacchi.h"
#include "posizione.h"
#include "tipogioco.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    mainWindow *view;
    Gioco *model;
    Posizione *posIniziale, *posFinale;
    void inizializzaPedine(const TipoGioco&);
    void mossaScacchi();
    // per ogni gioco implementato è necessario aggiungere un metodo mossa (ad esempio mossaDama)
public:
    explicit Controller(QObject *parent = nullptr);
private slots:
    void creaScacchi();
    void raccogliPosizione(Posizione);
    void promozioneScacchi(char);
};

#endif // CONTROLLER_H
