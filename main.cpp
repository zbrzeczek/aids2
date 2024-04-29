#include <iostream>
#include <string>
#include <stack>

#include "Stale.h"

using namespace std;

int isGameOverFunction(char tablicaKonc[MAXSIZE][MAXSIZE], int iloscLinii){
    char tablica[MAXSIZE][MAXSIZE];

    for (int i = 0; i<iloscLinii; i++){
        for (int j = 0; j<iloscLinii; j++){
            tablica[i][j] = tablicaKonc[i][j];
        }
    }

    if (iloscLinii == 1){
        if (tablica[0][0] == 'b') return BLUE;
        else if (tablica[0][0] == 'r') return RED;
        else return false;
    }


    stack<Point> stosPktRed, stosPktBlue;
    int zmiennaX, zmiennaY;
    char sprawdzanie;
    stack<Point>  *stosPkt;


    Point pozycjaRed;
    Point pozycjaBlue;
    Point pozycja;
    //najpeirw czerwone jest sprawdzane
    for (int i = 0; i < iloscLinii; i ++){

        //sprawdzenie dolnej krawedzi dla czerwonego
        if (tablica[iloscLinii-1][i] == 'r') {
            tablica[iloscLinii-1][i] = 'N';
            if (tablica[iloscLinii-2][i] == 'r'){
                pozycjaRed.x = i;
                pozycjaRed.y = iloscLinii-2;
                stosPktRed.push(pozycjaRed);
            }
            else if (i+1 < iloscLinii && tablica[iloscLinii-2][i+1] == 'r'){
                pozycjaRed.x = i+1;
                pozycjaRed.y = iloscLinii-2;
                stosPktRed.push(pozycjaRed);
            }
        }

        //sprawdzenie bocznej krawedzi dla niebieskiego
        if (tablica[i][0] == 'b') {
            tablica[i][0] = 'N';
            if (i-1 >= 0 && tablica[i-1][1] == 'b'){
                pozycjaBlue.x = 1;
                pozycjaBlue.y = i-1;
                stosPktBlue.push(pozycjaBlue);
            }
            else if (tablica[i][1] == 'b'){
                pozycjaBlue.x = 1;
                pozycjaBlue.y = i;
                stosPktBlue.push(pozycjaBlue);
            }
        }
    }

    while (!stosPktRed.empty() || !stosPktBlue.empty()){
        if(!stosPktRed.empty()) {
            pozycja = stosPktRed.top();
            if (pozycja.y == 0) {
                return RED;
            }
            stosPktRed.pop();
            tablica[pozycja.y][pozycja.x] = 'N';
            sprawdzanie = 'r';
            stosPkt = &stosPktRed;
            zmiennaY = 0;
            zmiennaX = 0;
        }
        else if (!stosPktBlue.empty()){
            pozycja = stosPktBlue.top();
            if (pozycja.x == iloscLinii-1) {
                return BLUE;
            }
            stosPktBlue.pop();
            tablica[pozycja.y][pozycja.x] = 'N';
            sprawdzanie = 'b';
            stosPkt = &stosPktBlue;
            zmiennaY = 1;
            zmiennaX = 1;
        }

        Point przetrzymujaca;

        //musisz dac jakas zmienna na y zeby nie zmieniac za kazdym raze
        // jezeli stos jest pusty a nie drugi koniec to falsz

        if (pozycja.x + zmiennaX < iloscLinii && pozycja.y - 1 + zmiennaY >= 0 && tablica[pozycja.y - 1 + zmiennaY][pozycja.x + zmiennaX] == sprawdzanie){
            przetrzymujaca.x = pozycja.x + zmiennaX;
            przetrzymujaca.y = pozycja.y - 1 + zmiennaY;
            stosPkt->push(przetrzymujaca);
        }
        if (pozycja.y - 1 >= 0 && pozycja.x + 1 < iloscLinii && tablica[pozycja.y - 1][pozycja.x + 1] == sprawdzanie){
            przetrzymujaca.x = pozycja.x + 1;
            przetrzymujaca.y = pozycja.y - 1;
            stosPkt->push(przetrzymujaca);
        }
        if (pozycja.x + 1 - zmiennaX < iloscLinii  && pozycja.y + zmiennaY  < iloscLinii &&  tablica[pozycja.y + zmiennaY][pozycja.x + 1 - zmiennaX] == sprawdzanie){
            przetrzymujaca.x = pozycja.x + 1 - zmiennaX;
            przetrzymujaca.y = pozycja.y + zmiennaY;
            stosPkt->push(przetrzymujaca);
        }
        if (pozycja.x - 1 + zmiennaX >= 0 && pozycja.y - zmiennaY >= 0 && tablica[pozycja.y - zmiennaY][pozycja.x - 1 + zmiennaX] == sprawdzanie){
            przetrzymujaca.x = pozycja.x - 1 + zmiennaX;
            przetrzymujaca.y = pozycja.y - zmiennaY;
            stosPkt->push(przetrzymujaca);
        }
        if (pozycja.y + 1 < iloscLinii && pozycja.x - zmiennaX >= 0 && tablica[pozycja.y + 1][pozycja.x - zmiennaX] == sprawdzanie){
            przetrzymujaca.x = pozycja.x - zmiennaX;
            przetrzymujaca.y = pozycja.y + 1;
            stosPkt->push(przetrzymujaca);
        }
        if (pozycja.x - 1 >= 0 && pozycja.y + 1 - zmiennaY <iloscLinii && tablica[pozycja.y + 1 - zmiennaY][pozycja.x - 1] == sprawdzanie){
            przetrzymujaca.x = pozycja.x - 1;
            przetrzymujaca.y = pozycja.y + 1 - zmiennaY;
            stosPkt->push(przetrzymujaca);
        }

    }

    return false;
}

int main() {
    char ch, zmienna;
    bool inputPlansza = true;
    bool inputPolecenia = false;
    bool koniecRzedow = false;
    bool isBoardCorrect = false;
    int isGameOver, iloscPionkowZmienna;
    string polecenie;
    int iloscB = 0, iloscR = 0, zmiennaIloscWygranychPossible = 0;

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
            if (iloscB == iloscR || iloscR == iloscB + 1) isBoardCorrect = true;

            //stworzenie koncowej tablicy
            for (int i = 0; i < 2 * MAXSIZE -1; i++){
                for (int j = 0; j < 2 * MAXSIZE -1; j++){
                    if (hexWTablicy[i][j] != ' ') {
                        if (i < iloscIinii && j < MAXSIZE) {
                            tablicaKonc[j][iloscIinii - 1 - i + j] = hexWTablicy[i][j];
                        } else if (j < MAXSIZE){
                            tablicaKonc[i - iloscIinii + 1 + j][j] = hexWTablicy[i][j];
                        }
                    }
                }
            }

            isGameOver = isGameOverFunction(tablicaKonc, iloscIinii);

        }

        if (ch == '-' && inputPolecenia) {
            inputPolecenia = false;
            inputPlansza = true;
            iloscIinii = 0;
            kolumna = 0;
            zmiennaLinii = 0;
            iloscB = 0;
            iloscR = 0;
            zmiennaKresek = 0;
            koniecRzedow = false;
            isBoardCorrect = false;
            zmiennaIloscWygranychPossible = 0;
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
                    if (!isGameOver) {
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
            else if (polecenie == bPossibleString){
                if (isBoardCorrect){
                    if (isGameOver > 0){
                        if ((isGameOver == BLUE && iloscB==iloscR) || (isGameOver== RED && iloscR-1 == iloscB)){
                            zmienna = (isGameOver == BLUE) ? 'b' : 'r';
                            iloscPionkowZmienna = (isGameOver == BLUE) ? iloscB : iloscR;
                            for (int i =0; i < iloscIinii; i++){
                                for (int j =0; j < iloscIinii; j++){
                                    if (tablicaKonc[i][j] == zmienna){
                                        tablicaKonc[i][j] = 'N';
                                        isGameOver = isGameOverFunction(tablicaKonc, iloscIinii);
                                        if (isGameOver > 0) zmiennaIloscWygranychPossible++;
                                        tablicaKonc[i][j] = zmienna;
                                    }
                                }
                            }
                            if (zmiennaIloscWygranychPossible == iloscPionkowZmienna) cout << "NO" << endl;
                            else cout << "YES" << endl;
                        }
                        else cout << "NO" << endl;
                    }
                    else cout << "YES" << endl;
                }
                else cout << "NO" << endl;
            }
        }
    }
    return 0;
}

