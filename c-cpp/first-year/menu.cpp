
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>

using namespace std;

int user_id = 0;
string users[10][6];

void registration() {
	ofstream fout("characters.txt");
	
    cout << "   Registration    " << endl;
    cout << "   Create a username:  ";
    cin >> users[user_id][0];
    cout << endl << "   Enter a race: ";
    cin >> users[user_id][1];
    cout << endl << "   Enter class:    ";
    cin >> users[user_id][2];
    cout << endl << "   Enter ATK:    ";
    cin >> users[user_id][3];
    cout << endl << "   Enter DEF:    ";
    cin >> users[user_id][4];
    cout << endl << "   Enter INT:    ";
    cin >> users[user_id][5];
    cout << endl << "		Your user id:	" << user_id << endl;
	fout << user_id << " " <<  users[user_id][0] << " " << users[user_id][1] << " " << users[user_id][2] << " " << users[user_id][3] << " " << users[user_id][4] << " " << users[user_id][5];
    cout << "   New character was successfully registered" << endl << endl << endl;
    user_id = user_id + 1;
    

}

void show() {
	
	cout << "	enter user id: 	";
	cin >> user_id;
	cout << endl;
    cout << "   username:  " << endl;
    cout << users[user_id][0] << endl;
    cout << "   race: " << endl;
    cout << users[user_id][1] << endl; 
    cout << "   class:    " << endl;
    cout << users[user_id][2] << endl;;
    cout << "   ATK:    " << endl;
    cout << users[user_id][3] << endl;
    cout << "   DEF:    " << endl;
    cout << users[user_id][4] << endl;
    cout << "   INT:    " << endl;
    cout << users[user_id][5] << endl;
    

}

void rewrite(){
	ofstream fout("characters.txt");
    cout << "   Please enter which user id you want to rewrite:    " << endl;
    cin >> user_id;
    cout << "   Create a username:  ";
    cin >> users[user_id][0];
    cout << endl << "   Enter a race: ";
    cin >> users[user_id][1];
    cout << endl << "   Enter class: ";
    cin >> users[user_id][2];
    cout << endl << "   Enter ATK: ";
    cin >> users[user_id][3];
    cout << endl << "   Enter DEF: ";
    cin >> users[user_id][4];
    cout << endl << "   Enter INT: ";
    cin >> users[user_id][5];
    cout << endl << "		Your user id:	" << user_id << endl;
	fout << user_id << " " <<  users[user_id][0] << " " << users[user_id][1] << " " << users[user_id][2] << " " << users[user_id][3] << " " << users[user_id][4] << " " << users[user_id][5];
    cout << "   New character was successfully rewrited" << endl << endl << endl;

	
}

int main()
{

	
    cout << " Welcome to Vmeste " << endl << endl;

    int counter = 1, chosen_option = counter;

    vector<string> options;

    options.push_back("Registration");
    options.push_back("Show character");
    options.push_back("Rewrite character");
    options.push_back("Exit");


    while (chosen_option != 4)
    {
        system("cls");

        for (size_t i = 0; i < options.size(); ++i)
        {
            if ((i + 1) == counter) cout << "> " << options[i] << endl;
            else					cout << options[i] << endl;
        }



        char pressed = getch();

        if (pressed == 119 && counter != 1) counter--;
        if (pressed == 115 && counter != options.size()) counter++;

        if (pressed == '\r' || pressed == '\n') {
            chosen_option = counter;
            system("cls");

            switch (chosen_option)
            {
            case 1: registration(); break;
            case 2: show(); break;
            case 3: rewrite(); break;
            case 4: return 0;

            }

            getch();
        }


    }

    getch();




    

    return 0;

}