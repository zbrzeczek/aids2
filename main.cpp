#include <iostream>
#include <string>

#include "Stale.h"

using namespace std;

int main() {
    char ch;
    int nastepnaLinia = FALSE;
    int input = TRUE;
    int inputPlansza = TRUE;
    int inputPolecenia = FALSE;
    string polecenie;
    int iloscB = 0, iloscR = 0;

    int iloscIinii = 0;
    int kolumna = 0;
    int zmiennaLinii = 0;

    char hexWTablicy[MAXSIZE][MAXSIZE];

    //wypelnienie tablicy pustymi polami
    for (int i = 0; i < MAXSIZE; i++){
        for (int j = 0; j < MAXSIZE; j++){
            hexWTablicy[j][i] = ' ';
        }
    }

    //wypelnianie planszy na tablice 2d

    while (input) {
        if (inputPlansza) {
            if (ch = cin.get()) {

                if (ch == '-') {
                    if (nastepnaLinia) nastepnaLinia = FALSE;
                } else if (ch == '<') {
                    if (nastepnaLinia) {
                        iloscIinii = zmiennaLinii;
                        nastepnaLinia = FALSE;
                    }
                    kolumna++;

                } else if (ch == 'b') {
                    iloscB++;
                    hexWTablicy[kolumna - 1][zmiennaLinii] = 'b';
                } else if (ch == 'r') {
                    iloscR++;
                    hexWTablicy[kolumna - 1][zmiennaLinii] = 'r';
                } else if (ch == '\n') {
                    kolumna = 0;
                    zmiennaLinii++;
                    nastepnaLinia = TRUE;
                } else if (ch == '>') {
                    if (hexWTablicy[kolumna - 1][zmiennaLinii] != 'r' &&
                        hexWTablicy[kolumna - 1][zmiennaLinii] != 'b')
                        hexWTablicy[kolumna - 1][zmiennaLinii] = 'n';
                }

                if (iloscIinii != 0 && iloscIinii * 2 + 1 == zmiennaLinii) {
                    inputPlansza = FALSE;
                    inputPolecenia = TRUE;
                }
            }
            else break;
        }

        if (inputPolecenia) {
            getline (cin,polecenie);
            if(cin.eof()) break;

            if (polecenie == sizeString){
                cout << iloscIinii << endl << endl;
            }
            else if (polecenie == pNumString){
                cout << iloscB + iloscR << std::endl << std::endl;
            }
            else if (polecenie == bCorrectString){

            }
            else {
                inputPolecenia = FALSE;
                inputPlansza = TRUE;
                iloscIinii = 0;
                kolumna = 0;
                zmiennaLinii = 0;
                iloscB = 0;
                iloscR = 0;
                nastepnaLinia = FALSE;
            }
        }

        /*for (int i = 0; i < MAXSIZE; i++) {
            for (int j = 0; j < MAXSIZE; j++) {
                std::cout << hexWTablicy[j][i] << ' ';
            }
            std::cout << std::endl;
        }*/
    }
    return 0;
}

