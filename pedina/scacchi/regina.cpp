#include "regina.h"

Regina::Regina(Colore _colore, short int _x, short int _y)
    : PedinaScacchi(_colore, _x, _y), Torre(_colore, _x, _y), Alfiere(_colore, _x, _y){}

bool Regina::controlloMossa(short int _x, short int _y) const{
    return Torre::controlloMossa(_x,_y) || Alfiere::controlloMossa(_x,_y);
}