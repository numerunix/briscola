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

#include <iostream>
#include "mazzo.h"
#include "giocatore.h"
#include "cpu.h"

#include <windows.h>
#include "internat.h"
using namespace std;

static internat* inter;

int main(int argc, char *argv[]) {
    inter = new internat(internat::LANGUAGES::INGLESE);
    carta::inter = inter;
    giocatore::inter = inter;
    cpu::inter = inter;
    if (argc != 3) {
        cout << inter->get_translated_string(internat::STRINGS::PARAMETERS_ERROR) << endl;
        return EXIT_FAILURE;
    }
    bool primaPartita = true;
    size_t puntiUtente = 0, puntiCpu = 0;
    int i = 0;
    mazzo* m = new mazzo();
    cpu *cp=new cpu(argv[2]);
    giocatore* primo=new giocatore(argv[1]),
              *secondo=cp,
              *g=primo,
              *temp;
    carta *c,
          *c1;
    try {
        m->mischia();
    } catch (overflow_error* e) {
        cerr<<e->what();
        return EXIT_FAILURE;
    } catch (invalid_argument* e) {
        cerr<<e->what();
        return EXIT_FAILURE;
    }
    for (i=0; i<3; i++) {
        try {
            primo->addCarta(m);
            secondo->addCarta(m);
        } catch (overflow_error* e) {
            cerr<<e->what();
            return EXIT_FAILURE;
        }
    }
    cout << "Briscola CUI 1.0 by numerone " << inter->get_translated_string(internat::STRINGS::TESTING_ARM64) << endl;
    do {
            cout<< inter->get_translated_string(internat::STRINGS:: IN_DECK)<< " "<<m->getNumeroCarte()<< inter->get_translated_string(internat::STRINGS::CARDS) << " " << endl;
            cout<<*cp;
            try {
                primo->gioca();
                c=primo->getCartaGiocata();
                cout<<endl<<inter->get_translated_string(internat::STRINGS::GAMED_CARD)<< ":" << *c << endl << endl;
                secondo->gioca(primo);
                c1=secondo->getCartaGiocata();
                cout<<inter->get_translated_string(internat::STRINGS::GAMED_CARD) << ":" <<*c1<<endl;
#ifdef WIN32
                system("pause");
                system("cls");
#else
		system("echo Premere un tasto per continuare...; read dummy");
		system("clear");
#endif
                if ((c->getSeme()==c1->getSeme() && *c<*c1) || (!c->isBriscola() && c1->isBriscola())) {
                    temp=primo;
                    primo=secondo;
                    secondo=temp;
                }
                primo->setPunteggio(secondo);
                try {
                    primo->addCarta(m);
                    secondo->addCarta(m);
                } catch (overflow_error *e) {
                    ;
                }
            } catch (underflow_error* e) {
                puntiUtente += g->getPunteggio();
                puntiCpu += cp->getPunteggio();
                cout<< inter->get_translated_string(internat::STRINGS::ENDED_GAME);
                if (puntiUtente == puntiCpu)
                    cout << inter->get_translated_string(internat::STRINGS::GAME_DROWN);
                else if (puntiUtente > puntiCpu)
                    cout << inter->get_translated_string(internat::STRINGS::YOU_WIN) << " "<<puntiUtente - puntiCpu << " " << inter->get_translated_string(internat::STRINGS::POINTS) << endl;
                else
                    cout << inter->get_translated_string(internat::STRINGS::YOU_LOOSE) << " "<< puntiCpu - puntiUtente << " " << inter->get_translated_string(internat::STRINGS::POINTS) << endl;
                if (primaPartita)
                    cout << inter->get_translated_string(internat::STRINGS::PLAY_SECOND_MATCH) << endl;
                else {
                    puntiUtente = puntiCpu = 0;
                    cout << inter->get_translated_string(internat::STRINGS::PLAY_NEW_MATCH) << endl;
                }
                cin >> i;
                if (i==1)
                {
                    primaPartita =! primaPartita;

                    delete m;
                    m = new mazzo();
                    delete cp;
                    cp = new cpu(argv[2]);
                    delete g;
                    g = new giocatore(argv[1]);
                    if (primaPartita) {
                        secondo = cp;
                        primo = g;
                    }
                    else {
                        primo = cp;
                        secondo = g;
                    }
                    try {
                        m->mischia();
                    }
                    catch (overflow_error* e) {
                        cerr << e->what();
                        return EXIT_FAILURE;
                    }
                    catch (invalid_argument* e) {
                        cerr << e->what();
                        return EXIT_FAILURE;
                    }
                    for (i = 0; i < 3; i++) {
                        try {
                            primo->addCarta(m);
                            secondo->addCarta(m);
                        }
                        catch (overflow_error* e) {
                            cerr << e->what();
                            return EXIT_FAILURE;
                        }
                    }
                } else
                    break;
            }
    } while (true);
    return EXIT_SUCCESS;
}
