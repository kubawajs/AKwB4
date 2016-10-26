#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <math.h>

using namespace std;

/*******************
*                  *
*  AKB zadanie 4   *
*                  *
*  vers. 08-01-16  *
*                  *
*******************/

//zmieniono podawanie danych - juz nie trzeba podawac liczby ciec

//DEFINICJE FUNKCJI============================================================

void szukaj(int licznosc, int badel, int *multizbior, int *result, int maxind, int ind, int *jest)
{
    int temp=0;//zmienna tymczasowa
    bool check=true;//sprawdza czy nie znaleziono liczby nie znajdujacej sie w multizbiorze, eliminujacej rozwiazanie
    bool *compare;//tablica do oznaczania elementow multizbioru, ktore juz wystapily
    compare = new bool [licznosc];

    for(int a=0; a<licznosc; a++)//falszowanie tablicy
    {
        compare[a]=false;
    }

    result[ind]=multizbior[badel];//przypisanie badanego elementu do miejsca w tablicy wynikowej

    for(int i=0; i<=ind; i++)//oznaczenie elementow zbioru wynikowego jako juz wystepujace
    {
        if(check)
        {
            for(int j=0; j<licznosc; j++)
            {
                if(result[i]==multizbior[j] && compare[j]==false)
                {
                    compare[j]=true;
                    break;
                }
                else if(j==licznosc-1)
                {
                    check=false;
                    break;
                }
            }
        }
    }
    for(int a=0; a<ind; a++)//sprawdzanie wszystkich kombinacji i oznaczanie jako wystepujacych w multizbiorze
    {
        temp=result[a];
        if(check)
        {
            for(int b=a+1; b<=ind; b++)
            {
                if(check)
                {
                    temp=temp+result[b];
                    for(int j=0; j<licznosc; j++)
                    {
                        if(temp==multizbior[j] && compare[j]==false)
                        {
                            compare[j]=true;
                            break;
                        }
                        if(j==licznosc-1)
                        {
                            check=false;
                            break;
                        }
                    }
                }
            }
        }
    }

    if(ind==maxind && check)//sprawdzanie czy licznosc zbioru wynikowego zgadza sie z przewidywana
    {
        cout<<"Odnaleziono rozwiazanie: "<<endl;
        for(int i=0; i<=maxind; i++)
        {
            cout<<result[i]<<" ";
        }
        cout<<endl;
        *jest=1;
    }
    else
    {
        for(int i=0; i<licznosc; i++)//uruchamianie funkcji rekurencyjnej dla wszystkich elementow jeszcze nie wykorzystanych
        {
            if(*jest==1) break;
            if(check && compare[i]==false)
            {
                szukaj(licznosc, i, multizbior, result, maxind, ind+1, jest);
            }
        }
    }
    delete [] compare;
}

//MAIN=========================================================================

int main()
{
    //DEFINICJE ZMIENNYCH======================================================

    int licznosc=0;//zmienna od licznosci multizbioru
    int jest=0;//wskaznik czy juz znaleziono rozwiazanie
    int *multizbior;//tabela na elementy multizbioru
    int *result;//tabela wynikowa
    float check = 0;//zmienna od sprawdzania czy licznosc pasuje do zbioru
    int cut = 0;//liczba ciec
    int lresult = 0;//liczba elementow zbioru wynikowego
    bool check2 = false;//zmienna od sprawdzenia czy licznosc odpowiednia

    //POMIAR CZASU=============================================================

    clock_t start, stop;
    double czas;

    //WCZYTYWANIE==============================================================

    cout<<"AKwB - Zadanie 4 - Jakub Wajs 2015"<<endl<<endl;
    string name;
    cout<<"Podaj nazwe pliku, ktory chcesz otworzyc: "<<endl;
    cin>>name;
    string fileName = name + ".txt";
    fstream file;
    file.open(fileName.c_str(), ios::in);
    if(!file.good())
    {
        cout<<endl<<endl<<"BLAD!!! Nie wczytano pliku.";
        return 0;
    }
    while(!file.eof())//wczytywanie z pliku dla policzenia elementow multizbioru
    {
        int test=0;
        file>>test;
        licznosc++;
    }
    file.close();

    //WERYFIKACJA LICZNOSCI MULTIZBIORU========================================

    //cout<<"Podaj liczbe ciec w badanej sekwencji: ";
    //cin>>cut;

    float delta, compare;
    compare=licznosc;
    delta = 4 * ((2*licznosc) - 2) + 9;
    cut = (-3 + sqrt(delta))/2;

    check = (cut+1)*(cut+2);//sprawdzanie dopasowania do wzoru
    check = check/2;

    if(check==licznosc)
    {
        cout<<endl<<"Podano prawidlowe dane. Licznosc multizbioru odpowiednia."<<endl<<endl;
        check2=true;
        lresult=cut+1;
    }
    else
    {
        cout<<endl<<"Podano bledne dane. Licznosc multizbioru nieodpowiednia."<<endl<<endl;
        check2=false;
    }

    //WCZYTYWANIE Z PLIKU=============================================================

    if(check2)
    {
        multizbior = new int [licznosc];

        int n=0;
        file.open(fileName.c_str(), ios::in);//wczytywanie danych do tablicy
        while(!file.eof())
        {
            file>>multizbior[n];
            n++;
        }
        file.close();

        //TWORZENIE TABEL=================================================================

        lresult = cut+1;
        result = new int [lresult];

        start = clock();//inicjowanie pomiaru czasu
        for(int i=0; i<licznosc; i++)
        {
            if(jest==0)//jesli jeszcze nie odnaleziono rozwiazania uruchamiaj dla kolejnych elementow multizbioru
            {
                for(int k=0; k<lresult; k++)//tabela na wynik wypelniona Nkami
                {
                    result[k]=0;
                }
                szukaj(licznosc, i, multizbior, result, lresult-1, 0, &jest);
            }
        }
        if(jest==0)//jesli nie znajdzie rozwiazania
        {
            cout<<"Brak rozwiazania."<<endl;
        }
        stop = clock();//koniec pomiaru czasu

        czas = (double)(stop-start)/CLOCKS_PER_SEC;//przeliczenie czasu na milisekundy

        int minuty = czas/60;
        double sekundy = czas - (minuty*60);

        if(czas>10.00)
            cout<<endl<<"Czas znalezienia rozwiazania: "<<minuty<<" min "<<setprecision(3)<<sekundy<<" s"<<endl;
        else if(czas>=1)
        {
            cout<<endl<<"Czas znalezienia rozwiazania: ";
            cout << setprecision(3) << czas << " s" <<endl;
        }
        else if(czas<1)
        {
            cout<<endl<<"Czas znalezienia rozwiazania: ";
            cout << setprecision(2) << czas << " s" <<endl;
        }
    }

    delete [] multizbior;
    delete [] result;

    return 0;
}
