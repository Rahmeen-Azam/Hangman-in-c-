#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

bool contains(char letter, string word) {
    return (word.find(letter) != string::npos);
}

string valid_word()
{
    ifstream infile("words.txt");
    string word;
    int count = 0;

    while (infile >> word) {
        if (word.find('-') != string::npos || word.find(' ') != string::npos) {
            continue;
        }
        count++;
    }

    srand(time(0));
    int random_number = rand() % count + 1; 

    infile.clear();
    infile.seekg(0, ios::beg);

    int current_word = 0;

    while (infile >> word) {
        if (word.find('-') != string::npos || word.find(' ') != string::npos) {
            continue;
        }
        current_word++;
        if (current_word == random_number) {
            break;
        }
    }

    for (int i = 0; i < word.length(); i++) {
        word[i] = toupper(word[i]);
    }

    return word;
}

int main()
{
    string word;
    int num;
    word = valid_word();
    num = word.length();
    vector<char> word_letter;

    for (int i = 0; i < num; i++) {
        word_letter.push_back(word[i]);
    }


    int lives = 6;
    vector<char> used_letters;
    vector<char> word_list(num, '_');

    while (word_letter.size() > 0 && lives > 0 && find(word_list.begin(), word_list.end(), '_') != word_list.end()) {
        cout << "You have " << lives << " lives left. You have used these letters: ";
        for (int i = 0; i < used_letters.size(); i++) {
            cout << used_letters[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < word_list.size(); i++) {      // Print the word list
            cout << word_list[i] << " ";
        }
        cout << endl;

        cout << "Enter a letter: ";    // Ask the user to input a letter
        char letter;
        cin >> letter;
        letter = toupper(letter);

		
		
        if (find(used_letters.begin(), used_letters.end(), letter) != used_letters.end()) {         // Check if the letter has been used before
  	        cout << endl <<"You have already used that letter. Try again." << endl;
    	    continue;
	    }
		
        used_letters.push_back(letter);      // Add the letter to the used letters vector

        bool found_letter = false;
         if (contains(letter, word)) {
            for (int i = 0; i < word.length(); i++) {
                if (word[i] == letter) {
                    word_list[i] = letter;
                    found_letter = true;
                    
                    
                    
                }
            }
        }

        if (!found_letter) {       // Update the lives count
            lives--;
            cout << "Sorry, that letter is not in the word." << endl;
        }
    }

    if (word_letter == word_list) {
        cout << "Congratulations, you guessed the word! The word was " << word << "." << endl;
    } else {
        cout << "Sorry, you ran out of lives. The word was " << word << "." << endl;
    
	}
	return 0;
}
