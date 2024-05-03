#include <iostream>
#include <string>
#include <stack>

#include "Board.h"
#include "Stale.h"

using namespace std;

int isGameOverFunction(Board *plansza){
    char tablica[MAXSIZE][MAXSIZE];
    int linie = plansza->getLinie();

    for (int i = 0; i< linie; i++){
        for (int j = 0; j< linie; j++){
            tablica[i][j] = plansza->getPole(i, j);
        }
    }

    if (linie == 1){
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
    for (int i = 0; i < linie; i ++){

        //sprawdzenie dolnej krawedzi dla czerwonego
        if (tablica[linie-1][i] == 'r') {
            tablica[linie-1][i] = 'N';
            if (tablica[linie-2][i] == 'r'){
                pozycjaRed.x = i;
                pozycjaRed.y = linie-2;
                stosPktRed.push(pozycjaRed);
            }
            else if (i+1 < linie && tablica[linie-2][i+1] == 'r'){
                pozycjaRed.x = i+1;
                pozycjaRed.y = linie-2;
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
            if (pozycja.x == linie-1) {
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

        if (pozycja.x + zmiennaX < linie && pozycja.y - 1 + zmiennaY >= 0 && tablica[pozycja.y - 1 + zmiennaY][pozycja.x + zmiennaX] == sprawdzanie){
            przetrzymujaca.x = pozycja.x + zmiennaX;
            przetrzymujaca.y = pozycja.y - 1 + zmiennaY;
            stosPkt->push(przetrzymujaca);
        }
        if (pozycja.y - 1 >= 0 && pozycja.x + 1 < linie && tablica[pozycja.y - 1][pozycja.x + 1] == sprawdzanie){
            przetrzymujaca.x = pozycja.x + 1;
            przetrzymujaca.y = pozycja.y - 1;
            stosPkt->push(przetrzymujaca);
        }
        if (pozycja.x + 1 - zmiennaX < linie  && pozycja.y + zmiennaY  < linie &&  tablica[pozycja.y + zmiennaY][pozycja.x + 1 - zmiennaX] == sprawdzanie){
            przetrzymujaca.x = pozycja.x + 1 - zmiennaX;
            przetrzymujaca.y = pozycja.y + zmiennaY;
            stosPkt->push(przetrzymujaca);
        }
        if (pozycja.x - 1 + zmiennaX >= 0 && pozycja.y - zmiennaY >= 0 && tablica[pozycja.y - zmiennaY][pozycja.x - 1 + zmiennaX] == sprawdzanie){
            przetrzymujaca.x = pozycja.x - 1 + zmiennaX;
            przetrzymujaca.y = pozycja.y - zmiennaY;
            stosPkt->push(przetrzymujaca);
        }
        if (pozycja.y + 1 < linie && pozycja.x - zmiennaX >= 0 && tablica[pozycja.y + 1][pozycja.x - zmiennaX] == sprawdzanie){
            przetrzymujaca.x = pozycja.x - zmiennaX;
            przetrzymujaca.y = pozycja.y + 1;
            stosPkt->push(przetrzymujaca);
        }
        if (pozycja.x - 1 >= 0 && pozycja.y + 1 - zmiennaY < linie && tablica[pozycja.y + 1 - zmiennaY][pozycja.x - 1] == sprawdzanie){
            przetrzymujaca.x = pozycja.x - 1;
            przetrzymujaca.y = pozycja.y + 1 - zmiennaY;
            stosPkt->push(przetrzymujaca);
        }

    }

    return false;
}

bool isBoardPossible(Board *plansza) {
    char zmienna;
    int zmiennaGO = 0;
    char tablica[MAXSIZE][MAXSIZE];
    int iloscPionkowZmienna, zmiennaIloscWygranychPossible = 0;

    for (int i = 0; i< plansza->getLinie(); i++){
        for (int j = 0; j< plansza->getLinie(); j++){
            tablica[i][j] = plansza->getPole(i, j);
        }
    }

    if (plansza->getCorrect()){
        if (plansza->getGameOver() > 0){
            if ((plansza->getGameOver() == BLUE && plansza->getB()==plansza->getR()) || (plansza->getGameOver()== RED && plansza->getB()==plansza->getR()-1)){
                zmienna = (plansza->getGameOver() == BLUE) ? 'b' : 'r';
                iloscPionkowZmienna = (plansza->getGameOver() == BLUE) ? plansza->getB() : plansza->getR();
                for (int i =0; i < plansza->getLinie(); i++){
                    for (int j =0; j < plansza->getLinie(); j++){
                        if (plansza->getPole(i, j) == zmienna){
                            plansza->setPole('N', i, j);
                            zmiennaGO = isGameOverFunction(plansza);
                            if (zmiennaGO > 0) zmiennaIloscWygranychPossible++;
                            plansza->setPole(zmienna, i, j);
                        }
                    }
                }
                if (zmiennaIloscWygranychPossible == iloscPionkowZmienna) return false;
                else return true;
            }
            else return false;
        }
        else return true;
    }
    else return false;
}

bool naive(Board *plansza, int depth, int player){
    char pionek = (player==RED) ? 'r' : 'b';
    int winner = isGameOverFunction(plansza);

    if (depth == 0){
        return (winner == player);
    }
    if (winner == player){
        return false;
    }

    for (int i = 0; i < plansza->getLinie(); i++){
        for (int j = 0; j < plansza->getLinie(); j++) {

            if (plansza->getPole(i, j) != 'N') {
                continue;
            }
            plansza->setPole(pionek, i, j);

            if ((naive(plansza, depth-1, player))) {
                plansza->setPole('N', i, j);
                return true;
            }
            plansza->setPole('N', i, j);
        }
    }
    return false;
}

int main() {
    char ch;
    bool inputPlansza = true;
    bool inputPolecenia = false;
    bool koniecRzedow = false;
    int depth, kolej, iloscruchow;
    int kolumna = 0;
    string polecenie;

    int zmiennaLinii = 0;
    int zmiennaKresek = 0;

    char hexWTablicy[2 * MAXSIZE-1][2 * MAXSIZE -1];

    //wypelnienie tablicy pustymi polami
    for (int i = 0; i < MAXSIZE * 2 - 1; i++){
        for (int j = 0; j < MAXSIZE * 2 - 1; j++){
            hexWTablicy[j][i] = ' ';
        }
    }

    Board nowaPlansza;

    //wypelnianie planszy na tablice 2d

    while (cin >> ch) {

        if (ch <= 'Z' && ch >= 'A' && inputPlansza) {
            inputPlansza = false;
            inputPolecenia = true;
            polecenie = "";
            if (nowaPlansza.getB() == nowaPlansza.getR() || nowaPlansza.getB() + 1 == nowaPlansza.getR()) nowaPlansza.setCorrect(true);

            //stworzenie koncowej tablicy
            for (int i = 0; i < 2 * MAXSIZE -1; i++){
                for (int j = 0; j < 2 * MAXSIZE -1; j++){
                    if (hexWTablicy[i][j] != ' ') {
                        if (i < nowaPlansza.getLinie() && j < MAXSIZE) {
                            nowaPlansza.setPole(hexWTablicy[i][j], j, nowaPlansza.getLinie() - 1 - i + j);
                        } else if (j < MAXSIZE){
                            nowaPlansza.setPole(hexWTablicy[i][j], i - nowaPlansza.getLinie() + 1 + j, j);
                        }
                    }
                }
            }

            nowaPlansza.setGameOver(isGameOverFunction(&nowaPlansza));
            nowaPlansza.setPossible(isBoardPossible(&nowaPlansza));
        }

        if (ch == '-' && inputPolecenia) {
            nowaPlansza.wyczyscPlansze();
            inputPolecenia = false;
            inputPlansza = true;
            zmiennaLinii = 0;
            zmiennaKresek = 0;
            kolumna = 0;
            koniecRzedow = false;
            depth = 0;
            kolej = 0;
            iloscruchow = 0;

            for (int i = 0; i < MAXSIZE * 2 - 1; i++){
                for (int j = 0; j < MAXSIZE * 2 - 1; j++){
                    hexWTablicy[j][i] = ' ';
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
                    nowaPlansza.setLinie(zmiennaLinii);
                    koniecRzedow = true;
                }
                else if (zmiennaKresek > 3 || (zmiennaKresek == 2 && koniecRzedow)) {
                    zmiennaLinii++;
                }
                zmiennaKresek = 0;
            }
            else if (ch == 'b') {
                nowaPlansza.setB(nowaPlansza.getB()+1);
                hexWTablicy[zmiennaLinii-1][kolumna-1] = 'b';
            }
            else if (ch == 'r') {
                nowaPlansza.setR(nowaPlansza.getR()+1);
                hexWTablicy[zmiennaLinii-1][kolumna-1] = 'r';
            }
            else if (ch == '>') {
                if (hexWTablicy[zmiennaLinii -1][kolumna -1] != 'r' && hexWTablicy[zmiennaLinii-1][kolumna -1] != 'b') {
                    hexWTablicy[zmiennaLinii -1][kolumna -1] = 'N';
                }
            }
        }
        //cout << ch;
        //input polecen
        if (inputPolecenia) {
            polecenie += ch;

            if (polecenie == sizeString){
                cout << nowaPlansza.getLinie() << endl << endl;
                polecenie = "";
            }
            else if (polecenie == pNumString){
                cout << nowaPlansza.getR()+nowaPlansza.getB() << std::endl << std::endl;
                polecenie = "";
            }
            else if (polecenie == bCorrectString){
                if (nowaPlansza.getCorrect()) {
                    cout << "YES"<<endl;
                }
                else cout << "NO" << endl;
                polecenie = "";
            }
            else if (polecenie == gameOverString){
                if (nowaPlansza.getCorrect()){
                    if (!nowaPlansza.getGameOver()) {
                        cout << "NO" << endl;
                    }
                    else if (nowaPlansza.getGameOver() == BLUE) {
                        cout << "YES BLUE" << endl;
                    }
                    else if (nowaPlansza.getGameOver() == RED){
                        cout << "YES RED" << endl;
                    }
                }
                else {
                    cout << "NO" << endl;
                }
                polecenie = "";
            }
            else if (polecenie == bPossibleString){
                if (nowaPlansza.getPossible()) cout << "YES" << endl;
                else cout << "NO" << endl;
                polecenie = "";
            }
            else if (polecenie == red1NaiveString || polecenie == blue1NaiveString || polecenie == red2NaiveString || polecenie == blue2NaiveString){
                if (nowaPlansza.getPossible() && nowaPlansza.getGameOver() == 0) {
                    kolej = (nowaPlansza.getR() == nowaPlansza.getB()) ? RED : BLUE;
                    int player;
                    if (polecenie == blue1NaiveString || polecenie == red1NaiveString) {
                        depth = 1;
                        if (polecenie == blue1NaiveString){
                            iloscruchow = (kolej == RED) ? 2 : 1;
                            player = BLUE;
                        }
                        else {
                            iloscruchow = (kolej == RED) ? 1 : 2;
                            player = RED;
                        }
                    }
                    else {
                        depth = 2;
                        if (polecenie == blue2NaiveString){
                            iloscruchow = (kolej == RED) ? 4 : 3;
                            player = BLUE;
                        }
                        else {
                            iloscruchow = (kolej == RED) ? 3 : 4;
                            player = RED;
                        }
                    }

                    if (iloscruchow <= nowaPlansza.getLinie() * nowaPlansza.getLinie() - nowaPlansza.getB() - nowaPlansza.getR()) {
                        if(naive(&nowaPlansza, depth, player)) cout << "YES" << endl;
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                else cout << "NO" << endl;
                polecenie = "";
            }
        }
    }
    return 0;
}

