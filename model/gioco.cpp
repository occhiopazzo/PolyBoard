#include "gioco.h"

Gioco::Gioco(int _width, int _height, Colore giocatore_iniziale) : tavolo(_width, _height), giocatore_corrente(giocatore_iniziale){}

Colore Gioco::getGiocatoreCorrente() const{
    return giocatore_corrente;
}

ID* Gioco::getIdPedina(const Posizione& pos) const
{
    if(tavolo[pos])
        return new ID(tavolo[pos]->getId());
    else
        return nullptr;
}

int Gioco::getWidth() const
{
    return tavolo.getWidth();
}

int Gioco::getHeight() const
{
    return tavolo.getHeight();
}

bool Gioco::isEmpty(const Posizione& pos) const
{
    return tavolo[pos] == nullptr;
}

void Gioco::inserisciPedina(const Posizione& pos, const ID& id)
{
    Pedina *toInsert = idToPedina(id);
    if(toInsert)
        tavolo.insert(*toInsert, pos);
    delete toInsert;
}
