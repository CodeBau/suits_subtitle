#include <iostream>                        //input/output library
#include <fstream>                         //ofstream and ifstream/ create files, write to files, and read from files.
#include <cstdlib>                         //to use exit 
#include <string>                          //strings library
#include <vector>                          //vectors library
#include <time.h>                          //header defines four variable types, two macro and various functions for manipulating date and time.

//abbreviation (shorts) occurring - OCCURS, quantity - QTY

using namespace std;

vector <string> wordlist;                  //list with unique words
vector <int> words_quantity;               //number of occurrences of a given word in the text
int verses_quantity_2_check;               //number of verses to check entered by the user
int word_not_occur = 0;                    //auxiliary(helper) variable to check the prevalence of the word list
string text_line_from_file[999999];        //tooked line of text from the file/ max 999999
string text_line;                          //currently checking text line
string word;                               //single word selected from the text line
char letter;                               //single letter from the selected line of text
char preceding_letters[3];                 //letters preceding the selected letter
int number_lines_in_file;                  //number of text lines present in the file
string auxiliary_how_much;                 //helper variable for calculating the text line in a text file 
clock_t start, stop;                       //variables needed to measure the time it takes to perform a function
double time_to_do_wordlist;                //how much time is needed to create a word list
int all_words_quantity;                    //how many words are in the text, from the verses selected by the user
int unique_words_quantity;                 //how many UNIQUE words are in the text, from the verses selected by the user
int once_occurring_word_quantity;          //how many words occur only once in the text, from the verses selected by the user


//void adding another letter at the end of a string word
void adding_letters()
{
    word += letter;  
}


//void showing wordlist, from verses selected by the user
void show_wordlist()                                                                            
{
    cout << "======================WORDLIST======================" << endl;
    for (unsigned int i = 0; i < wordlist.size(); i++)
    {
        cout << "/" << wordlist[i] << "/-/" << words_quantity[i] << "/";
        cout << endl;
    }
    cout << "================END OD THE WORDLIST=================" << endl;
}


//void adds new, previously not occurring, word.
void adding_word()
{
    wordlist.push_back(word);
    words_quantity.push_back(1);
    word.clear();
    unique_words_quantity++;
    once_occurring_word_quantity++;
}


//void checking if the word did not appear earlier or not already on the list.
void check_occurrence()                                                                      
{
    //sprawdzam czy slowo nie jest spacja
    if (word == "")
    {
    }

    //jesli slowo jest rozne od spacji 
    else
    {
        all_words_quantity++;

       //sprawdzam czy jest jakies(chociaz 1) slowo na liscie
        if (wordlist.size() == 0)
        {
            adding_word();

        }
        else
        {
            //jesli jest jakies(chociaz jedno) slowo na liscie to sprawdzam czy wystepuje takie samo jak chcemy dodac
            for (unsigned int j = 0; j < wordlist.size(); j++)
            {
                word_not_occur = 0;

                //jesli trafie na takie slowo
                if (wordlist[j] == word)
                {
                    word.clear();
                    
                    //sprawdzam czy na liscie jest wiecej slow niz jedno zebym musial pozycjonowac
                    if (wordlist.size() > 1)
                    {

                        //sprawdzam czy wczesniej wystapilo tylko raz, jesli tak to zamieniam ostatnia pojedyncza pozycje
                        if (words_quantity[j] == 1)
                        {
                            words_quantity[j]++;
                            string tempslowo = wordlist[j];
                            int tempile_slow = words_quantity[j];
                            wordlist[j] = wordlist[wordlist.size() - once_occurring_word_quantity];
                            words_quantity[j] = words_quantity[wordlist.size() - once_occurring_word_quantity];
                            wordlist[wordlist.size() - once_occurring_word_quantity] = tempslowo;
                            words_quantity[wordlist.size() - once_occurring_word_quantity] = tempile_slow;
                            once_occurring_word_quantity--;
                        }

                        //sprawdzam czy slowo jest najczesciej wystepujacym
                        else if (words_quantity[j] == words_quantity[0] && words_quantity[0] != words_quantity[1])
                        {
                            words_quantity[j]++;
                        }
                        //po odrzuceniu skrajnych warunkow na wystapienie tylko raz oraz na najczesciej wystepujace slowo sprawdzam pozycje
                        else
                        {
                            word_not_occur = 0;
                            words_quantity[j]++;
                            int ile_w_gore = 0;

                            for (int e = j - 1; e >= 0; e--)
                            {
                                //jesli pozycja wyzej wystepuje mniej razy niz dodawane slowo to dodaje przesuniecie o jedna poyzcje w gore
                                if (words_quantity[j] > words_quantity[e])
                                {
                                    ile_w_gore++;
                                }

                                //inaczej przestaje sprawdzac przesuniecie bo wszystkie pozycje wyzej na liscie wystepuja wiecej razy
                                else
                                {
                                    break;
                                }
                            }

                            //sprawdzam czy nastepuje przesuniecie w gore, jesli tak to przesuwam o tyle pozycji ile
                            if (ile_w_gore > 0)
                            {
                                string tempslowo = wordlist[j];
                                int tempile_slow = words_quantity[j];
                                wordlist[j] = wordlist[j - ile_w_gore];
                                words_quantity[j] = words_quantity[j - ile_w_gore];
                                wordlist[j - ile_w_gore] = tempslowo;
                                words_quantity[j - ile_w_gore] = tempile_slow;
                            }
                        }
                    }

                    //na liscie jest tylko jedno slowo nie ma potrzeby pozycjonowania 
                    else
                    {
                    }

                    break;
                }

                //nie ma takiego slowa na lisicie, wywolujemy if dodoawania slowa na liste
                else
                {
                    word_not_occur = 1;
                }
            }

            //sprawdzamy warunek niewystopienia slowa na liscie
            if (word_not_occur == 1)
            {
                adding_word();

            }
        }
    }
}


//void checking how many lines of text per text file
void check_how_many_lines()                                                       
{

    fstream  plik;
    plik.open("subtitles.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "Brak pliku";
        exit(0);
    }
    while (!plik.eof())
    {
        while (getline(plik, auxiliary_how_much)) ++number_lines_in_file;

    }

    plik.close();

}


//main function of the program
int main()
{
    start = clock();
    check_how_many_lines();
    cout << "Plik z napisami zawiera:" << number_lines_in_file << " wersow, ile chcesz wyswietlic?:" << endl;
    cin >> verses_quantity_2_check;

    fstream  plik;

    plik.open("subtitles.txt", ios::in);

    for (int i = 0; i <= verses_quantity_2_check - 1; i++)
    {
        word = "";
        getline(plik, text_line_from_file[i]);
        text_line = text_line_from_file[i];

        for (int unsigned j = 0; j <= text_line.length(); j++)
        {
            if (text_line.length() == 0)
            {
            }
            else
            {

                letter = text_line[j];
                preceding_letters[0] = text_line[j];

                if (preceding_letters[0] == 0)
                {

                    preceding_letters[1] = 0;
                }
                else
                {
                    preceding_letters[1] = text_line[j + 1];

                }
                if (preceding_letters[1] == 0)
                {

                    preceding_letters[2] = 0;
                }
                else
                {
                    preceding_letters[2] = text_line[j + 2];
                }

                if (preceding_letters[1] == -124 && preceding_letters[0] == -60 || preceding_letters[1] == -123 && preceding_letters[0] == -60)                                                                       //¹ 124,123
                {
                    letter = static_cast <char>(165);
                    adding_letters();
                }
                else if (preceding_letters[1] == -122 && preceding_letters[0] == -60 || preceding_letters[1] == -121 && preceding_letters[0] == -60)                                                                  //æ 122,121 60
                {
                    letter = static_cast <char>(134);
                    adding_letters();
                }
                else if (preceding_letters[1] == -104 && preceding_letters[0] == -60 || preceding_letters[1] == -103 && preceding_letters[0] == -60)                                                                   //ê 104,103 60
                {
                    letter = static_cast <char>(169);
                    adding_letters();
                }
                else if (preceding_letters[1] == -127 && preceding_letters[0] == -59 || preceding_letters[1] == -126 && preceding_letters[0] == -59)                                                                    //³ 127,126 59
                {
                    letter = static_cast <char>(136);
                    adding_letters();
                }
                else if (preceding_letters[1] == -125 && preceding_letters[0] == -59 || preceding_letters[1] == -124 && preceding_letters[0] == -59)                                                                   //ñ 125, 124 59
                {
                    letter = static_cast <char>(228);
                    adding_letters();
                }
                else if (preceding_letters[1] == -109 && preceding_letters[0] == -61 || preceding_letters[1] == -77 && preceding_letters[0] == -61)                                                                   //ó 109, 77 61
                {
                    letter = static_cast <char>(162);
                    adding_letters();
                }
                else if (preceding_letters[1] == -102 && preceding_letters[0] == -59 || preceding_letters[1] == -101 && preceding_letters[0] == -59)                                                                   //œ 101, 102 59
                {
                    letter = static_cast <char>(152);
                    adding_letters();
                }
                else if (preceding_letters[1] == -71 && preceding_letters[0] == -59 || preceding_letters[1] == -70 && preceding_letters[0] == -59)                                                                   //Ÿ 71, 70 59
                {
                    letter = static_cast <char>(171);
                    adding_letters();
                }
                else if (preceding_letters[1] == -69 && preceding_letters[0] == -59 || preceding_letters[1] == -68 && preceding_letters[0] == -59)                                                                   //¿ 68, 69 59
                {
                    letter = static_cast <char>(190);
                    adding_letters();
                }
                else if (preceding_letters[0] >= 65 && preceding_letters[0] <= 90)                                                                                                            //zamieniamy wielkie litery na ma³e
                {
                    letter += 32;
                    adding_letters();
                }
                else if (preceding_letters[0] >= 97 && preceding_letters[0] <= 122)                                                                                                            //sprawdzenie malej litery
                {
                    adding_letters();
                }
                else if (preceding_letters[0] == 32)                                                                                                                               //spacja nowe slowo
                {
                    check_occurrence();
                }

                else if (preceding_letters[0] == 0)
                {
                    check_occurrence();
                }
            }
        }
    }

    plik.close();

    show_wordlist();

    cout << endl;
    cout << "Wszystkich slow:/" << all_words_quantity << "/" << endl;
    cout << "Uniklanych slow:/" << unique_words_quantity << "/" << endl;
    cout << "Slow wystepujacych tylko raz:/" << once_occurring_word_quantity << "/" << endl;

    stop = clock();
    time_to_do_wordlist = (stop - start) / CLOCKS_PER_SEC;
    cout << "Potrzebny czas: " << time_to_do_wordlist << " sekund";

    int liczba_wystapien_do_zapisu_poczatek;
    int liczba_wystapien_do_zapisu_koniec;
    char czy_uzyc_zbednych;

    cout << endl;
    cout << "Od jakiej liczby wystapien slowa zapisac na liste: (W przedzial od " << words_quantity[0] << " - " << words_quantity[words_quantity.size() - 1] << ")";
    cin >> liczba_wystapien_do_zapisu_poczatek;
    if (liczba_wystapien_do_zapisu_poczatek)
        while (liczba_wystapien_do_zapisu_poczatek > words_quantity[0] || liczba_wystapien_do_zapisu_poczatek < words_quantity[words_quantity.size() - 1])
        {

            cout << "Podano bledna wartosc" << endl;
            cout << "Od jakiej liczby wystapien slowa zapisac na liste: (Przedzial od " << words_quantity[0] << " - " << words_quantity[words_quantity.size() - 1] << ")";
            cin >> liczba_wystapien_do_zapisu_poczatek;
        }

    cout << "Do jakiej liczby wystapien slowa zapisac na liste: ";
    cin >> liczba_wystapien_do_zapisu_koniec;
    cout << "Czy przefiltrowac przez liste znanych slowek Tak/Nie";
    cin >> czy_uzyc_zbednych;

    return 0;
}

