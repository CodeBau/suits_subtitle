#include <iostream>                        //input/output library
#include <fstream>                         //ofstream and ifstream/ create files, write to files, and read from files.
#include <cstdlib>                         //to use exit 
#include <string>                          //strings library
#include <vector>                          //vectors library
#include <time.h>                          //header defines four variable types, two macro and various functions for manipulating date and time.
#include <algorithm>					   //use to transform lowercase


//abbreviation (shorts) occurring - OCCURS, quantity - QTY

using namespace std;

vector <string> wordlist;                  //list with unique words
vector <int> word_quantity;               //number of occurrences of a given word in the text
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
int yes_or_no = 0;						   //auxiliary variable for yes / no mode


//checking yes or no 
void give_y_or_n()
{
	string user_known_words;                     //whether to use words saved in the file known_words.txt
	char first_letter_y_n;				         //first character from the entered string

	while (yes_or_no != 1)
	{
		cin >> user_known_words;
		transform(user_known_words.begin(), user_known_words.end(), user_known_words.begin(), ::tolower);

		if (user_known_words.length() > 1)
		{
			if (user_known_words == "tak")
			{
				user_known_words = "t";
			}
			else if (user_known_words == "nie")
			{
				user_known_words = "n";
			}
			else
				user_known_words = "a";
		}

		first_letter_y_n = user_known_words[0];
		switch (first_letter_y_n)
		{
		case 't':
		case 'n':
			yes_or_no = 1;
			break;
		default:
			cout << "Dokonaj wyboru Tak/Nie ";
			break;
		}
	}
}


//checking if the string entered is a number and belong to the numerical interval
int is_it_number(int max, int min)
{
	int its_number = 0;                                          //variable that determines whether string is a number
	int b;                                                       //temporary variable to save the string as int

	while (its_number != 1)
	{
		cout << "Podaj liczbe z przedzialu: (" << max << " - " << min << ") " << endl;
		string number;                                           //string entered by the user
		cin >> number;

		//checking if all characters from the string are numbers / if any character is not interrupted and ask for a new input
		for (unsigned int i = 0; i < number.length(); i++)
		{

			if (number[i] == '0' || number[i] == '1' || number[i] == '2' || number[i] == '3' || number[i] == '4' || number[i] == '5' || number[i] == '6' || number[i] == '7' || number[i] == '8' || number[i] == '9')
			{
				b = atoi(number.c_str());
				{
					if (b <= max && b >= min)
					{
						its_number = 1;
					}
					else
					{
						cout << "Podana liczba jest z poza mozliwego przedzialu" << endl;
						its_number = 0;
						break;
					}
				}
			}
			else
			{
				cout << "Podano bledna wartosc" << endl;
				its_number = 0;
				break;
			}
		}
	}
	return b;
}


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
		cout << "/" << wordlist[i] << "/-/" << word_quantity[i] << "/";
		cout << endl;
	}
	cout << "================END OD THE WORDLIST=================" << endl;
}


//void adds new, previously not occurring, word.
void adding_word()
{
	wordlist.push_back(word);
	word_quantity.push_back(1);
	word.clear();
	unique_words_quantity++;
	once_occurring_word_quantity++;
}


//void checking if the word did not appear earlier or not already on the list.
void check_occurrence()
{
	//if the word is a space, skip the next steps
	if (word == "")
	{
	}

	else
	{
		all_words_quantity++;

		//checking if there is at least one word on the worlist (any word)
		if (wordlist.size() == 0)
		{
			adding_word();
		}
		else
		{
			//if there is a word on the list, check if the same word occurs
			for (unsigned int j = 0; j < wordlist.size(); j++)
			{
				word_not_occur = 0;

				if (wordlist[j] == word)
				{
					word.clear();

					//checking if the wordlist has more than one word
					if (wordlist.size() > 1)
					{

						//eliminating extreme cases / the word occurring once / the word most often occurring
						//checking if a word has appeared only once before, if so then the exchange occurs with the first word on the list that occurs once
						if (word_quantity[j] == 1)
						{
							word_quantity[j]++;
							string tempword = wordlist[j];                                         //variable for temporarily storing a word
							int tempword_quantity = word_quantity[j];                              //variable for temporarily storing a word_quantity
							wordlist[j] = wordlist[wordlist.size() - once_occurring_word_quantity];
							word_quantity[j] = word_quantity[wordlist.size() - once_occurring_word_quantity];
							wordlist[wordlist.size() - once_occurring_word_quantity] = tempword;
							word_quantity[wordlist.size() - once_occurring_word_quantity] = tempword_quantity;
							once_occurring_word_quantity--;
						}

						//checking if the word is the most common word
						else if (word_quantity[j] == word_quantity[0] && word_quantity[0] != word_quantity[1])
						{
							word_quantity[j]++;
						}

						//after rejecting extreme cases, checking from the most common words that are more common than words checked
						else
						{
							word_not_occur = 0;
							word_quantity[j]++;
							int offset_value_up = 0;                                    //variable that specifies how many positions the word should be moved up

							for (int e = j - 1; e >= 0; e--)
							{
								//checking for subsequent words, if it comes across a less common word then increases the upward shift by one position. If it encounters a more frequent item, it will stop checking
								if (word_quantity[j] > word_quantity[e])
								{
									offset_value_up++;
								}
								else break;
							}

							//if the up offset value is greater than 0, it shifts positions as much as needed
							if (offset_value_up > 0)
							{
								string tempword = wordlist[j];                                         //variable for temporarily storing a word
								int tempword_quantity = word_quantity[j];                              //variable for temporarily storing a word_quantity
								wordlist[j] = wordlist[j - offset_value_up];
								word_quantity[j] = word_quantity[j - offset_value_up];
								wordlist[j - offset_value_up] = tempword;
								word_quantity[j - offset_value_up] = tempword_quantity;
							}
						}
					}

					//there is only one word on the list, there is no need for positioning
					break;
				}

				//there is no such word on the list we call "if" adding words to the offer
				else
				{
					word_not_occur = 1;
				}
			}

			//checking the condition of the word being on the list
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

	fstream  file;
	file.open("subtitles.txt", ios::in);
	if (file.good() == false)
	{
		cout << "Brak pliku";
		exit(0);
	}
	while (!file.eof())
	{
		while (getline(file, auxiliary_how_much)) ++number_lines_in_file;
	}
	file.close();
}

//main function of the program
int main()
{
#pragma region CreatingWordlist
	start = clock();
	check_how_many_lines();
	cout << "Plik z napisami zawiera:" << number_lines_in_file << " wersow, ile chcesz wyswietlic?: ";
	verses_quantity_2_check = is_it_number(number_lines_in_file, 1);

	fstream  file;

	file.open("subtitles.txt", ios::in);

	for (int i = 0; i <= verses_quantity_2_check - 1; i++)
	{
		word = "";                                               //to make sure the word "zeroed"                
		getline(file, text_line_from_file[i]);
		text_line = text_line_from_file[i];

		for (int unsigned j = 0; j <= text_line.length(); j++)
		{
			if (text_line.length() == 0)
			{
			}
			//checking subsequent letters / skipping special characters / converting to Polish characters/ lowercase characters
			else
			{
				//defining preceding characters before the checked letter / checking if there are any preceding characters
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

				//converting to Polish characters
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

				//lowercase characters
				else if (preceding_letters[0] >= 65 && preceding_letters[0] <= 90)                                                                                                            //zamieniamy wielkie litery na ma³e
				{
					letter += 32;
					adding_letters();
				}

				//standard letter
				else if (preceding_letters[0] >= 97 && preceding_letters[0] <= 122)                                                                                                            //sprawdzenie malej litery
				{
					adding_letters();
				}

				//after finding spaces, checks whether to add a word
				else if (preceding_letters[0] == 32)                                                                                                                               //spacja nowe slowo
				{
					check_occurrence();
				}

				//at the end of the line of text, checks whether to add a word
				else if (preceding_letters[0] == 0)
				{
					check_occurrence();
				}
			}
		}
	}

	file.close();

	show_wordlist();

	cout << endl;
	cout << "Wszystkich slow:/" << all_words_quantity << "/" << endl;
	cout << "Uniklanych slow:/" << unique_words_quantity << "/" << endl;
	cout << "Slow wystepujacych tylko raz:/" << once_occurring_word_quantity << "/" << endl;

	stop = clock();
	time_to_do_wordlist = (stop - start) / CLOCKS_PER_SEC;
	cout << "Potrzebny czas: " << time_to_do_wordlist << " sekund";

#pragma endregion


#pragma region CreatingUserWordlist

	vector <string> userwordlist;			     //vector with filtered words in terms of quantity (and if the user has chosen so with the file known_words.txt)
	int user_wordlist_quantity_start;            //up to what number of occurrences of words in the text should be accepted on the user's list
	int user_wordlist_quantity_end;              //from what number of occurrences of words in the text should be included in the user's list

	cout << endl;
	cout << "OD jakiej liczby wystapien slowa zapisac na liste, ";
	user_wordlist_quantity_start = is_it_number(word_quantity[0], word_quantity[word_quantity.size() - 1]);
	cout << "DO jakiej liczby wystapien slowa zapisac na liste, ";
	user_wordlist_quantity_end = is_it_number(user_wordlist_quantity_start, word_quantity[word_quantity.size() - 1]);
	cout << "Czy przefiltrowac przez liste znanych slowek Tak/Nie ";
	give_y_or_n();

#pragma region CreatingKnownWordlist
	/*
	trzeba wgrac plik known_wors.txt jesli give_y_or_n da t;
	jesli nie to pomijamy
	*/
#pragma endregion
	/*
	trzeba dac for po wordlist.size
	if (word_quantity<user_wordlist_quantity_start && word_quantity>user_wordlist_quantity_end)
	{
	biezemy slowo 
	jesli give_y_or_n jest t to sprawdzmy czy jest na liscie
	jesli nie dajemy slowo na userwordlist;
	}
	*/

#pragma endregion


	return 0;
}

