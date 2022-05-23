/***************************************************************************
 *   Copyright (C) 2007 by Giulio Sorrentino                               *
 *   numerone@fastwebnet.it                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _CARTA_H_
#define _CARTA_H_

#include <stdexcept>
#include <fstream>
#include <wx/string.h>
using namespace std;

class carta {
    private:
        size_t seme;
        size_t valore;
        bool briscola;
        void setSeme(size_t seme) throw(invalid_argument*);
        void setValore(size_t valore) throw (invalid_argument*);
    public:
        carta(size_t seme, size_t valore, int cartaBriscola) throw(invalid_argument*);
        carta(size_t intero, int cartaBriscola) throw(invalid_argument*);
        size_t getPunteggio();
        size_t getSeme() {return seme;}
        wxString getSemeStr();
        size_t getValore() {return valore;}
        bool isBriscola();
        friend ostream& operator<<(ostream& o, carta& c);
        friend bool operator<(carta& c1, carta& c2);
};

#endif
