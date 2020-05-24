#include <iostream>           //input/output library
#include <fstream>            //ofstream and ifstream/ create files, write to files, and read from files.
#include <cstdlib>            //to use exit 
#include <string>             //strings library
#include <vector>             //vectors library
#include <time.h>             //header defines four variable types, two macro and various functions for manipulating date and time.
#include <cstdlib>             // czas


//trzeba dodac funkcje ktora podaje przedzial oraz sprawdza czy podany znak jest liczba i czy nalezy do danego przedzialu
/*
int l=0;
while ((l<1) || (l>20)) {
cout << "Podaj liczbê (1-20): ";
if (!(cin >> l)) {
cin.clear();
cin.ignore(1000, '\n');
}
}

cin.ignore(numeric_limits<int>::max(), '\n'); - pan powiedzial ze lepiej tak
*/

using namespace std;

vector <string> lista_slow;                                                                     //lista unikalnych s³ów
vector <int> ile_slow;                                                                          //liczba powtorzen lista_slow w tekscie                                                                                                   
int liczba_wersow;                                                                              //liczba wybranych wersow do sprawdzenia
int nie_ma = 0;                                                                                 //warunek pomocniczy 
string wiersz[999999];                                                                          //ilosc sprawdzanych wierszy
string wers;                                                                                    //linijka sprawdzanego testu
string slowo;                                                                                   //sprawdzane slowo
char litera;                                                                                    //litera wzieta w iteracji do rozpatrzenia
char litery[3];                                                                                 //tablica do sprawdzenia nastepnej litery
int w;
string ile;
clock_t start, stop;
double czas;
int liczba_wszystkich_slow;
int liczba_uniklanych_slow;
int liczba_slow_wystepujacyh_raz;


void dodawanie_litera()
{
    //cout << "To jest litera ktora bedzie dodana:/" <<litera<<"/"<< endl;
    slowo += litera;
    //cout << "To slowo:/" << slowo << "/" << endl;
}

void lista()                                                                            //wyswietla zawartosci listy, wszystkich slow z okreslonego zakresu
{
    cout << "===============LISTA S£ÓW===============" << endl;
    for (unsigned int i = 0; i < lista_slow.size(); i++)
    {
        cout << "/" << lista_slow[i] << "/-/" << ile_slow[i] << "/";
        cout << endl;
    }
    cout << endl;
    cout << "===============KONIEC LISTY=================" << endl;
}
void dodanie_slowa()
{
    lista_slow.push_back(slowo);
    ile_slow.push_back(1);
    slowo.clear();
    liczba_uniklanych_slow++;
    liczba_slow_wystepujacyh_raz++;
    //cout << "slowo PO USUNIECIU :/" << slowo <<"/"<< endl;
    //cout << "Uniklanych slow:/" << liczba_uniklanych_slow << "/" << endl;
    //cout << "Slow wystepujacych tylko raz: /" << liczba_slow_wystepujacyh_raz << "/" << endl;
}

void sprawdzenie()                                                                      //sprawdza czy slowo jest na liscie
{
    //lista();
    //cout << "SPRAWDZAM CZY DODAC NOWE SLOWO:/" << slowo << "/" << endl;


    //sprawdzam czy slowo nie jest spacja
    if (slowo == "")
    {
        //cout << "Nie dodaje spacji" << endl;
    }

    //jesli slowo jest rozne od spacji 
    else
    {
        liczba_wszystkich_slow++;
        //cout << "Wszystkich slow: /" << liczba_wszystkich_slow << "/" << endl;

        //sprawdzam czy jest jakies(chociaz 1) slowo na liscie
        if (lista_slow.size() == 0)
        {
            //cout << "Dodaje pierwsze slowo" << endl;
            dodanie_slowa();

        }
        else
        {
            //jesli jest jakies(chociaz jedno) slowo na liscie to sprawdzam czy wystepuje takie samo jak chcemy dodac
            for (unsigned int j = 0; j < lista_slow.size(); j++)
            {
                nie_ma = 0;

                //jesli trafie na takie slowo
                if (lista_slow[j] == slowo)
                {
                    slowo.clear();
                    //cout << "sprawdzam czy na liscie slow jest wiecej niz 1" << endl;
                    //cout << "ile_slow[j]:/" << ile_slow[j]<<"/"<<endl;
                    //cout << "ile_slow[0]:/" << ile_slow[0]<<"/"<<endl;


                    //sprawdzam czy na liscie jest wiecej slow niz jedno zebym musial pozycjonowac
                    if (lista_slow.size() > 1)
                    {
                        //cout << "Jest wiecej slow niz 1" << endl;

                        //sprawdzam czy wczesniej wystapilo tylko raz, jesli tak to zamieniam ostatnia pojedyncza pozycje
                        if (ile_slow[j] == 1)
                        {
                            //cout << "=====To slowo wystapilo wczesniej 1 raz" << endl;
                            //lista();

                            //cout << "j:/" << j << "/" << endl;
                            //cout << "liczba_slow_wystepujacyh_raz:/" << liczba_slow_wystepujacyh_raz << "/" << endl;
                            //cout << "lista_slow.size():/" << lista_slow.size() << "/" << endl;

                            ile_slow[j]++;
                            //cout << "Zwiekszamy ile_slow[j] na 2:/" << ile_slow[j] << "/" << endl;
                            string tempslowo = lista_slow[j];
                            int tempile_slow = ile_slow[j];
                            //cout << "tempslowo:" << tempslowo << "-" << tempile_slow << endl;
                            //cout << "lista_slow[lista_slow.size()-liczba_slow_wystepujacyh_raz]:" << lista_slow[lista_slow.size() - liczba_slow_wystepujacyh_raz] << "-" << ile_slow[lista_slow.size() - liczba_slow_wystepujacyh_raz] << endl;
                            lista_slow[j] = lista_slow[lista_slow.size() - liczba_slow_wystepujacyh_raz];
                            ile_slow[j] = ile_slow[lista_slow.size() - liczba_slow_wystepujacyh_raz];
                            //cout << "Po zamianie lista_slow[j]:" << lista_slow[j] << "-" << ile_slow[j] << endl;
                            //lista();
                            lista_slow[lista_slow.size() - liczba_slow_wystepujacyh_raz] = tempslowo;
                            ile_slow[lista_slow.size() - liczba_slow_wystepujacyh_raz] = tempile_slow;
                            //lista();

                            liczba_slow_wystepujacyh_raz--;
                            //cout << "Uniklanych slow:/" << liczba_slow_wystepujacyh_raz << "/" << endl;
                        }
                        //sprawdzam czy slowo jest najczesciej wystepujacym
                        else if (ile_slow[j] == ile_slow[0] && ile_slow[0] != ile_slow[1])
                        {
                            //cout << "Slowo najczesciej wystepujace" << endl;
                            ile_slow[j]++;
                        }
                        //po odrzuceniu skrajnych warunkow na wystapienie tylko raz oraz na najczesciej wystepujace slowo sprawdzam pozycje
                        else
                        {
                            nie_ma = 0;
                            ile_slow[j]++;
                            int ile_w_gore = 0;

                            for (int e = j - 1; e >= 0; e--)
                            {
                                //lista();
                                //cout << endl << "zaczynam petle j:/" << j << "/ oraz e:/" << e << "/" << endl;
                                //cout << "porownuje slowo:/" << lista_slow[j] << "/-/" << ile_slow[j] << "/ ze slowem:/" << lista_slow[e] << "/-/" << ile_slow[e] << "/" << endl;

                                //jesli pozycja wyzej wystepuje mniej razy niz dodawane slowo to dodaje przesuniecie o jedna poyzcje w gore
                                if (ile_slow[j] > ile_slow[e])
                                {
                                    // cout << "Warunek j>e jest spelniony, zwiekszam ile w gore" << endl;
                                    ile_w_gore++;
                                    //cout <<"Ile w gore:" << ile_w_gore << endl;
                                }
                                //inaczej przestaje sprawdzac przesuniecie bo wszystkie pozycje wyzej na liscie wystepuja wiecej razy
                                else
                                {
                                    //cout << "Warunek j>e NIE jest spelniony" << endl;
                                    break;
                                }
                            }
                            //sprawdzam czy nastepuje przesuniecie w gore, jesli tak to przesuwam o tyle pozycji ile
                            if (ile_w_gore > 0)
                            {
                                //cout << "Ile_w_gore wieksze od zera" << endl;
                                string tempslowo = lista_slow[j];
                                int tempile_slow = ile_slow[j];
                                //cout << "tempslowo:" << tempslowo << "-" << tempile_slow << endl;
                                //cout << "lista_slow[j-ile_w_gore]:" << lista_slow[j - ile_w_gore] << "-" << ile_slow[j - ile_w_gore] << endl;
                                lista_slow[j] = lista_slow[j - ile_w_gore];
                                ile_slow[j] = ile_slow[j - ile_w_gore];
                                //cout << "Po zamianie lista_slow[j]:" << lista_slow[j] << "-" << ile_slow[j] << endl;
                                //lista();
                                lista_slow[j - ile_w_gore] = tempslowo;
                                ile_slow[j - ile_w_gore] = tempile_slow;
                                //lista();
                            }
                        }
                    }

                    //na liscie jest tylko jedno slowo nie ma potrzeby pozycjonowania 
                    else
                    {
                        //cout<<"Nie ma wiecej niz 1 lista_slow w zbiorze"<<endl;
                    }

                    break;
                }
                //nie ma takiego slowa na lisicie, wywolujemy if dodoawania slowa na liste
                else
                {
                    nie_ma = 1;
                }
            }
            //sprawdzamy warunek niewystopienia slowa na liscie
            if (nie_ma == 1)
            {
                //cout << "Dodaje nowe slowo" << slowo <<"/"<< endl;
                dodanie_slowa();

            }
        }
    }
}

void ile_wersow()                                                       //sprawdza ile max wersów ma plik tekstowy
{

    fstream  plik;
    plik.open("napisy.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "Brak pliku";
        exit(0);
    }
    while (!plik.eof())
    {
        while (getline(plik, ile)) ++w;

    }

    plik.close();

}

int main()
{
    start = clock();
    ile_wersow();
    cout << "Plik z napisami zawiera:" << w << " wersow, ile chcesz wyswietlic?:" << endl;
    cin >> liczba_wersow;

    fstream  plik;

    plik.open("napisy.txt", ios::in);

    for (int i = 0; i <= liczba_wersow - 1; i++)
    {
        slowo = "";
        getline(plik, wiersz[i]);
        wers = wiersz[i];

        for (int unsigned j = 0; j <= wers.length(); j++)
        {
            if (wers.length() == 0)
            {
            }
            else
            {

                litera = wers[j];
                //cout << "Litera to:/" << litera << "/" << endl;
                litery[0] = wers[j];

                if (litery[0] == 0)
                {

                    litery[1] = 0;
                }
                else
                {
                    litery[1] = wers[j + 1];

                }
                if (litery[1] == 0)
                {

                    litery[2] = 0;
                }
                else
                {
                    litery[2] = wers[j + 2];
                }

                if (litery[1] == -124 && litery[0] == -60 || litery[1] == -123 && litery[0] == -60)                                                                       //¹ 124,123
                {
                    //cout << "tutaj jest a," << endl;
                    litera = static_cast <char>(165);
                    dodawanie_litera();
                }
                else if (litery[1] == -122 && litery[0] == -60 || litery[1] == -121 && litery[0] == -60)                                                                  //æ 122,121 60
                {
                    //cout << "tutaj jest c'" << endl;
                    litera = static_cast <char>(134);
                    dodawanie_litera();
                }
                else if (litery[1] == -104 && litery[0] == -60 || litery[1] == -103 && litery[0] == -60)                                                                   //ê 104,103 60
                {
                    //cout << "tutaj jest e," << endl;
                    litera = static_cast <char>(169);
                    dodawanie_litera();
                }
                else if (litery[1] == -127 && litery[0] == -59 || litery[1] == -126 && litery[0] == -59)                                                                    //³ 127,126 59
                {
                    //cout << "tutaj jest l/" << endl;
                    litera = static_cast <char>(136);
                    dodawanie_litera();
                }
                else if (litery[1] == -125 && litery[0] == -59 || litery[1] == -124 && litery[0] == -59)                                                                   //ñ 125, 124 59
                {
                    //cout << "tutaj jest n'" << endl;
                    litera = static_cast <char>(228);
                    dodawanie_litera();
                }
                else if (litery[1] == -109 && litery[0] == -61 || litery[1] == -77 && litery[0] == -61)                                                                   //ó 109, 77 61
                {
                    //cout << "tutaj jest o'" << endl;
                    litera = static_cast <char>(162);
                    dodawanie_litera();
                }
                else if (litery[1] == -102 && litery[0] == -59 || litery[1] == -101 && litery[0] == -59)                                                                   //œ 101, 102 59
                {
                    //cout << "tutaj jest s'" << endl;
                    litera = static_cast <char>(152);
                    dodawanie_litera();
                }
                else if (litery[1] == -71 && litery[0] == -59 || litery[1] == -70 && litery[0] == -59)                                                                   //Ÿ 71, 70 59
                {
                    //cout << "tutaj jest z'" << endl;
                    litera = static_cast <char>(171);
                    dodawanie_litera();
                }
                else if (litery[1] == -69 && litery[0] == -59 || litery[1] == -68 && litery[0] == -59)                                                                   //¿ 68, 69 59
                {
                    //cout << "tutaj jest z." << endl;
                    litera = static_cast <char>(190);
                    dodawanie_litera();
                }
                else if (litery[0] >= 65 && litery[0] <= 90)                                                                                                            //zamieniamy wielkie litery na ma³e
                {
                    //cout << "Zamieniamy wielka litere na mala" << endl;
                    litera += 32;
                    dodawanie_litera();
                }
                else if (litery[0] >= 97 && litery[0] <= 122)                                                                                                            //sprawdzenie malej litery
                {
                    //cout << "To jest mala litera" << endl;
                    dodawanie_litera();
                }
                else if (litery[0] == 32)                                                                                                                               //spacja nowe slowo
                {
                    //cout << "spacja dodaje slowo" << endl;
                    sprawdzenie();
                }

                else if (litery[0] == 0)
                {
                    //cout << "Jest koniec wersa dodaje slowo" << endl;
                    sprawdzenie();
                }


            }
        }
    }

    plik.close();

    lista();

    cout << endl;
    //cout << "koniec wszystkiego" << endl << endl;
    cout << "Wszystkich slow:/" << liczba_wszystkich_slow << "/" << endl;
    cout << "Uniklanych slow:/" << liczba_uniklanych_slow << "/" << endl;
    cout << "Slow wystepujacych tylko raz:/" << liczba_slow_wystepujacyh_raz << "/" << endl;

    stop = clock();
    czas = (stop - start) / CLOCKS_PER_SEC;
    cout << "Potrzebny czas: " << czas << " sekund";

    int liczba_wystapien_do_zapisu_poczatek;
    int liczba_wystapien_do_zapisu_koniec;
    char czy_uzyc_zbednych;

    cout << endl;
    cout << "Od jakiej liczby wystapien slowa zapisac na liste: (W przedzial od " << ile_slow[0] << " - " << ile_slow[ile_slow.size() - 1] << ")";
    cin >> liczba_wystapien_do_zapisu_poczatek;
    if (liczba_wystapien_do_zapisu_poczatek)
        while (liczba_wystapien_do_zapisu_poczatek > ile_slow[0] || liczba_wystapien_do_zapisu_poczatek < ile_slow[ile_slow.size() - 1])
        {

            cout << "Podano bledna wartosc" << endl;
            cout << "Od jakiej liczby wystapien slowa zapisac na liste: (Przedzial od " << ile_slow[0] << " - " << ile_slow[ile_slow.size() - 1] << ")";
            cin >> liczba_wystapien_do_zapisu_poczatek;
        }

    cout << "Do jakiej liczby wystapien slowa zapisac na liste: ";
    cin >> liczba_wystapien_do_zapisu_koniec;
    cout << "Czy przefiltrowac przez liste znanych slowek Tak/Nie";
    cin >> czy_uzyc_zbednych;

    return 0;
}

