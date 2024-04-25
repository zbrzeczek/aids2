#include <iostream>
#include <string>

#include "Stale.h"

using namespace std;

int isGameOverFunction(char tablica[MAXSIZE][MAXSIZE], int iloscLinii){
    int isGameOver;

    //najpeirw czerwone jest sprawdzane
    for (int i  =0; i < iloscLinii; i ++){
        if (tablica[0][i] == 'r') {
            
        }
    }


    return isGameOver;
}

int main() {
    char ch;
    bool nastepnaLinia = false;
    bool inputPlansza = true;
    bool inputPolecenia = false;
    bool koniecRzedow = false;
    bool isBoardCorrect = false;
    int isGameOver;
    string polecenie;
    int iloscB = 0, iloscR = 0;

    int iloscIinii = 0;
    int kolumna = 0;
    int zmiennaLinii = 0;
    int zmiennaKresek = 0;

    char hexWTablicy[2 * MAXSIZE-1][2 * MAXSIZE -1];
    char tablicaKonc[MAXSIZE][MAXSIZE];

    //wypelnienie tablicy pustymi polami
    for (int i = 0; i < MAXSIZE * 2 - 1; i++){
        for (int j = 0; j < MAXSIZE * 2 - 1; j++){
            hexWTablicy[j][i] = ' ';
        }
    }
    for (int i = 0; i < MAXSIZE; i++){
        for (int j = 0; j < MAXSIZE; j++){
            tablicaKonc[j][i] = ' ';
        }
    }

    //wypelnianie planszy na tablice 2d

    while (cin >> ch) {

        if (ch <= 'Z' && ch >= 'A' && inputPlansza) {
            inputPlansza = false;
            inputPolecenia = true;
            polecenie = "";
            if (iloscB == iloscR || iloscR == iloscB +1) isBoardCorrect = true;

            //stworzenie koncowej tablicy
            for (int i = 0; i < 2 * MAXSIZE -1; i++){
                for (int j = 0; j < 2 * MAXSIZE -1; j++){
                    if (hexWTablicy[i][j] != ' ') {
                        if (i < iloscIinii) {
                            tablicaKonc[j][iloscIinii - 1 - i + j] = hexWTablicy[i][j];
                        } else {
                            tablicaKonc[i - iloscIinii + 1 + j][j] = hexWTablicy[i][j];
                        }
                    }
                }
            }

            isGameOver = isGameOverFunction(tablicaKonc, iloscIinii);
            /*for (int i = 0; i < MAXSIZE * 2 - 1; i++){
                for (int j = 0; j < MAXSIZE * 2 -1 ; j++){
                    cout << hexWTablicy[i][j] << ' ';
                }
                cout << endl;
            }
            for (int i = 0; i < iloscIinii; i++){
                for (int j = 0; j < iloscIinii; j++){
                    cout << tablicaKonc[i][j] << ' ';
                }
                cout << endl;
            }*/
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
                else if (zmiennaKresek > 3 || (zmiennaKresek == 2 && koniecRzedow)) {
                    zmiennaLinii++;
                }
                zmiennaKresek = 0;
            }
            else if (ch == 'b') {
                iloscB++;
                hexWTablicy[zmiennaLinii-1][kolumna-1] = 'b';
            }
            else if (ch == 'r') {
                iloscR++;
                hexWTablicy[zmiennaLinii-1][kolumna-1] = 'r';
            }
            else if (ch == '>') {
                if (hexWTablicy[zmiennaLinii -1][kolumna -1] != 'r' && hexWTablicy[zmiennaLinii-1][kolumna -1] != 'b') {
                    hexWTablicy[zmiennaLinii -1][kolumna -1] = 'n';
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
            else if (polecenie == bCorrectString){
                if (isBoardCorrect) {
                    cout << "YES"<<endl;
                }
                else cout << "NO" << endl;
            }
            else if (polecenie == gameOverString){
                if (isBoardCorrect){
                    if (isGameOver == false) {
                        cout << "NO" << endl;
                    }
                    else if (isGameOver == BLUE) {
                        cout << "YES BLUE" << endl;
                    }
                    else if (isGameOver == RED){
                        cout << "YES RED" << endl;
                    }
                }
                else {
                    cout << "NO" << endl;
                }
            }
        }

    }
    return 0;
}

