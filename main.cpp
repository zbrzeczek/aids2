#include <iostream>
#include <string>

#include "Stale.h"

using namespace std;

int main() {
    char ch;
    bool nastepnaLinia = false;
    bool inputPlansza = true;
    bool inputPolecenia = false;
    bool koniecRzedow = false;
    string polecenie;
    int iloscB = 0, iloscR = 0;

    int iloscIinii = 0;
    int kolumna = 0;
    int zmiennaLinii = 0;
    int zmiennaKresek = 0;

    char hexWTablicy[MAXSIZE][MAXSIZE];

    //wypelnienie tablicy pustymi polami
    for (int i = 0; i < MAXSIZE; i++){
        for (int j = 0; j < MAXSIZE; j++){
            hexWTablicy[j][i] = ' ';
        }
    }

    //wypelnianie planszy na tablice 2d

    while (cin >> ch) {

        if (ch <= 'Z' && ch >= 'A' && inputPlansza) {
            inputPlansza = false;
            inputPolecenia = true;
            polecenie = "";
        }

        if (ch == '-' && inputPolecenia) {
            inputPolecenia = false;
            inputPlansza = true;
            iloscIinii = 0;
            kolumna = 0;
            zmiennaLinii = 0;
            iloscB = 0;
            iloscR = 0;
            nastepnaLinia = false;
            zmiennaKresek = 0;
            koniecRzedow = false;
        }

        //input plansyz i danych
        if (inputPlansza) {
            if (ch == '-') {
                zmiennaKresek++;
            }
            else if (ch == '<') {
                if (zmiennaKresek > 1) kolumna = 1;
                else kolumna++;

                if ((zmiennaKresek == 2 || zmiennaKresek == 3) && !koniecRzedow) {
                    zmiennaLinii++;
                    iloscIinii = zmiennaLinii;
                    koniecRzedow = true;
                }
                else if (zmiennaKresek > 3) {
                    zmiennaLinii++;
                }
                zmiennaKresek = 0;
            }
            else if (ch == 'b') {
                iloscB++;
                hexWTablicy[kolumna - 1][zmiennaLinii] = 'b';
            }
            else if (ch == 'r') {
                iloscR++;
                hexWTablicy[kolumna - 1][zmiennaLinii] = 'r';
            }
            else if (ch == '>') {
                if (hexWTablicy[kolumna - 1][zmiennaLinii] != 'r' && hexWTablicy[kolumna - 1][zmiennaLinii] != 'b') {
                    hexWTablicy[kolumna - 1][zmiennaLinii] = 'n';
                }
            }
        }
        //cout << ch;
        //input polecen
        if (inputPolecenia) {
            polecenie += ch;

            if (polecenie == sizeString){
                cout << iloscIinii << endl << endl;
                polecenie = "";
            }
            else if (polecenie == pNumString){
                cout << iloscB + iloscR << std::endl << std::endl;
                polecenie = "";
            }
            else {

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

