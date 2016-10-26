#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <math.h>

using namespace std;

/**********************
*                     *
*    AKB zadanie 4    *
* generator instancji *
*                     *
*      vers. 0.8      *
*                     *
***********************/

//cos nie pyka do konca

//SORTOWANIE===================================================================
void Sortowanie( int *tab, int left, int right )
{
    int i = left;
    int j = right;
    int x = tab[(left + right)/2];
    do
    {
        while(tab[i] < x)
            i++;

        while(tab[j] > x)
            j--;

        if(i <= j)
        {
            swap(tab[i], tab[j]);

            i++;
            j--;
        }
    }
    while(i <= j);

    if(left<j) Sortowanie(tab, left, j);

    if(right>i) Sortowanie(tab, i, right);

}

//MAIN=========================================================================

int main()
{
    //DEFINICJE ZMIENNYCH======================================================

    int *multizbior;//tabela na elementy multizbioru
    int *result;//tabela wynikowa
    int check = 0;//zmienna od sprawdzania czy check pasuje do zbioru
    int cut = 0;//liczba ciec
    int lresult = 0;//liczba elementow zbioru wynikowego
    int wybor=0;

    //WCZYTYWANIE Z PLIKU=============================================================

    cout<<"AKwB - Zadanie 4 - Jakub Wajs 2015 - GENERATOR INSTANCJI"<<endl<<endl;

    string name;
    cout<<"Podaj nazwe pliku, ktory chcesz otworzyc: "<<endl;
    cin>>name;

    cout<<endl<<"Podaj liczbe ciec w badanej sekwencji: "<<endl;
    cin>>cut;

    cout<<endl<<"Wybierz rodzaj sortowania (1-rosnace, 2-malejace, 3-losowe): "<<endl;
    cin>>wybor;

    check = (cut+1)*(cut+2);//sprawdzanie dopasowania do wzoru
    check = check/2;

    lresult = cut+1;

    multizbior = new int [check];
    result = new int [lresult];

    string fileName = name + ".txt";
    fstream file;
    file.open(fileName.c_str(), ios::in);
    if(!file.good())
    {
        cout<<endl<<endl<<"BLAD!!! Nie wczytano pliku.";
        return 0;
    }
    int n=0;

    while(!file.eof())
    {
        file>>result[n];
        n++;
    }
    file.close();

    //DODAWANIE WARTOSCI==========================================================

    int c=0;
    int temp;
    for(int a=0; a<lresult-1; a++)
    {
        temp=result[a];
        multizbior[c]=temp;
        c++;
        for(int b=a+1; b<lresult; b++)
        {
            temp = temp+result[b];
            multizbior[c] = temp;
            c++;
        }
    }

    if(wybor==1)
    {
        Sortowanie(multizbior, 0, check);

        cout<<endl<<"Utworzono multizbior: "<<endl;
        for(int i=1; i<=check; i++)
            cout<<multizbior[i]<<" ";

        fileName = name + "-ins-ros.txt";     //zapis do pliku wynikowego
        fstream file2;
        file2.open(fileName.c_str(), ios::out);
        for(int j=1; j<=check; j++)                   //przepisanie informacji o lukach z macierzy do pliku
        {
            file2<<multizbior[j]<<" ";
        }
        file2.close();
    }

    if(wybor==2)
    {
        Sortowanie(multizbior, 0, check);

        cout<<endl<<"Utworzono multizbior: "<<endl;
        for(int i=check; i>0; i--)
            cout<<multizbior[i]<<" ";

        fileName = name + "-ins-mal.txt";     //zapis do pliku wynikowego
        fstream file2;
        file2.open(fileName.c_str(), ios::out);
        for(int j=check; j>0; j--)                   //przepisanie informacji o lukach z macierzy do pliku
        {
            file2<<multizbior[j]<<" ";
        }
        file2.close();
    }

    if(wybor==3)
    {
        cout<<endl<<"Utworzono multizbior: "<<endl;
        for(int i=0; i<check; i++)
            cout<<multizbior[i]<<" ";

        fileName = name + "-ins-los.txt";     //zapis do pliku wynikowego
        fstream file2;
        file2.open(fileName.c_str(), ios::out);
        for(int j=0; j<check; j++)                   //przepisanie informacji o lukach z macierzy do pliku
        {
            file2<<multizbior[j]<<" ";
        }
        file2.close();
    }

    delete [] multizbior;
    delete [] result;

    return 0;
}
