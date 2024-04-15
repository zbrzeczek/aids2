#include <iostream>

#include "Stale.h"

int main() {
    char ch;
    int nastepnaLinia = FALSE;
    int inputPlansza = TRUE;
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

    while (inputPlansza){
        ch = std::cin.get();

        if (ch == '-'){
            if (nastepnaLinia) nastepnaLinia = FALSE;
        }
        else if (ch == '<'){
            if (nastepnaLinia){
                iloscIinii = zmiennaLinii;
                nastepnaLinia = FALSE;
            }
            kolumna++;

        }
        else if (ch == 'b'){
            iloscB ++ ;
            hexWTablicy[kolumna-1][zmiennaLinii] = 'b';
        }
        else if (ch == 'r') {
            iloscR ++ ;
            hexWTablicy[kolumna-1][zmiennaLinii] = 'r';
        }
        else if (ch == '\n') {
            kolumna = 0;
            zmiennaLinii++;
            nastepnaLinia = TRUE;
        }
        else if (ch == '>'){
            if (hexWTablicy[kolumna-1][zmiennaLinii] != 'r' && hexWTablicy[kolumna-1][zmiennaLinii] != 'b') hexWTablicy[kolumna-1][zmiennaLinii] = 'n';
        }

        if (iloscIinii != 0 && iloscIinii*2+1 == zmiennaLinii) inputPlansza = FALSE;
    }

    std::cout << iloscIinii << std::endl << std::endl;
    std::cout << iloscB+iloscR << std::endl << std::endl;

    for (int i = 0; i < MAXSIZE; i++){
        for (int j = 0; j < MAXSIZE; j++){
            std::cout << hexWTablicy[j][i] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}

