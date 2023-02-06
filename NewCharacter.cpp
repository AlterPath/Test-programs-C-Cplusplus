#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>

using namespace std;
int user_id = 0;

class Character{
	
public:
	string name[32];
	string race[32];
	string clas[32];
	int ATK[4];
	int DEF[4];
	int INT[4];
	int user_id[1];
	
};

int start(){
	int freeuser_id;
	ifstream fin("cppstudio.txt");
	fin >> freeuser_id;
	return freeuser_id;
}


void registration() {
	
	ofstream fout("0.txt");
	
//	switch(user_id){
		
//	case 0: ofstream fout("0.txt");
//	case 1: ofstream fout("1.txt");
//	case 2: ofstream fout("2.txt");
//	case 3: ofstream fout("3.txt");
//	case 4: ofstream fout("4.txt");
//	case 5: ofstream fout("5.txt");
//	}

	
	Character character;
	
    cout << "   Registration    " << endl;
    cout << "   Create a username:  ";
    cin >> character.name;
    cout << endl << "   Enter a race: ";
    cin >> character.race;
    cout << endl << "   Enter class:    ";
    cin >> character.clas;
    cout << endl << "   Enter ATK:    ";
    cin >> character.ATK;
    cout << endl << "   Enter DEF:    ";
    cin >> character.DEF;
    cout << endl << "   Enter INT:    ";
    cin >> character.INT;
    cout << endl << "		Your user id:	" << user_id << endl;
	fout << user_id << " " <<  character.name << " " << character.race << " " << character.clas << " " << character.ATK << " " << character.DEF << " " << character.INT;
    cout << "   New character was successfully registered" << endl << endl << endl;
    user_id = user_id + 1;
    

}

void show() {
	
	cout << "	enter user id: 	";
	cin >> user_id;
	cout << endl;
    cout << "   username:  " << endl;
    cout << character.name << endl;
    cout << "   race: " << endl;
    cout << character.race << endl; 
    cout << "   class:    " << endl;
    cout << ucharacter.clas << endl;;
    cout << "   ATK:    " << endl;
    cout << character.ATK << endl;
    cout << "   DEF:    " << endl;
    cout << character.DEF << endl;
    cout << "   INT:    " << endl;
    cout << character.INT << endl;
    

}

void rewrite(){
	cout << "   Please enter which user id you want to rewrite:    " << endl;
    cin >> user_id;
	
	switch(user_id)
	{
	case 0: ofstream fout("0.txt");
	case 1: ofstream fout("1.txt");
	case 2: ofstream fout("2.txt");
	case 3: ofstream fout("3.txt");
	case 4: ofstream fout("4.txt");
	case 5: ofstream fout("5.txt");
	}

    cout << "   Create a username:  ";
    cin >> character.name;
    cout << endl << "   Enter a race: ";
    cin >> character.race;
    cout << endl << "   Enter class: ";
    cin >> character.clas;
    cout << endl << "   Enter ATK: ";
    cin >> character.ATK;
    cout << endl << "   Enter DEF: ";
    cin >> character.DEF;
    cout << endl << "   Enter INT: ";
    cin >> character.INT;
    cout << endl << "		Your user id:	" << user_id << endl;
	fout << user_id << " " <<  character.name << " " << character.race << " " << character.clas << " " << character.ATK << " " << character.DEF << " " << character.INT;
    cout << "   Character was successfully rewrited" << endl << endl << endl;

	
}

int main()
{
	start();
	
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