//--- 2021-2022 Summer Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname: Harun Çifci
//---Student Number: 150180089
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "pokemon.h"

using namespace std;

//-------------Do Not Change These Global Variables-------------//
int NAME_COUNTER = 0;           // Use this to keep track of the enemy names
int POK_COUNTER = 0;            // Use this to keep track of the pokemon names
int PLAYER_POKEMON_ATTACK = 20; // You don't have to use this variable but its here if you need it
int ENEMY_POKEMON_ATTACK = 10;  // You don't have to use this variable but its here if you need it
//--------------------------------------------------------------//

//---If Necessary Add Your Global Variables Here---//
//
int ENEMY_POKEMON_COUNT = 0;
int ENEMY_COUNT = 0;
//
//
//-------------------------------------------------//

//-------------Do Not Change These Function Definitions-------------//
string *readEnemyNames(const char *);
string *readPokemonNames(const char *);
player characterCreate(string, int);
void mainMenu();
void fightEnemy(player *, string *, string *);
void catchPokemon(player *, string *);
//------------------------------------------------------------------//

//---If Necessary Add Your Function Definitions Here---//
//
//
//
//-----------------------------------------------------//

//-------------Do Not Change This Function-------------//
int main(int argc, char *argv[])
{
    system("clear");
    //---Creating Enemy and Pokemon Name Arrays---//
    string *enemyNames = readEnemyNames(argv[1]);
    string *pokemonNames = readPokemonNames(argv[2]);

    string playerName;
    int pokemonChoice;

    cout << "Welcome to the Pokemon Game! \n"
         << endl;
    cout << "Please enter your name: ";
    cin >> playerName;
    cout << "Please choose one of these pokemons as your pokemon: \n1- Bulbasaur \n2- Charmender \n3- Squirtle \nChoice: ";
    cin >> pokemonChoice;

    //---Character Creation--//
    player newPlayer = characterCreate(playerName, pokemonChoice);

    int menuChoice;

    while (true)
    {
        mainMenu();
        cin >> menuChoice;

        switch (menuChoice)
        {
        case 1:
            fightEnemy(&newPlayer, enemyNames, pokemonNames);
            break;
        case 2:
            catchPokemon(&newPlayer, pokemonNames);
            break;
        case 3:
            cout << newPlayer.showPokemonNumber() << endl;
            break;
        case 4:
            cout << newPlayer.showPokeballNumber() << endl;
            break;
        case 5:
            cout << newPlayer.showBadgeNumber() << endl;
            break;
        case 6:
            cout << endl;
            cout << "------- Pokedex -------" << endl;
            newPlayer.playerPokedex.printPokedex();
            break;
        case 7:
            //---Deletes Dynamic Arrays From Memory and Exits---//
            delete[] enemyNames;
            delete[] pokemonNames;
            return EXIT_SUCCESS;
            break;

        default:
            cout << "Please enter a valid number!!!" << endl;
            break;
        }
    }
    return EXIT_FAILURE;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
string *readEnemyNames(const char *argv) // I read it, making a dynamic array by looking to the first line of file.//
{
    string *temp = new string;
    ifstream myfile(argv);
    getline(myfile, *temp);
    string b = *temp;
    int c = stoi(b);
    string *line = new string[c];
    if (myfile.is_open())
    {
        int i = 0;
        while (getline(myfile, *temp))
        {
            line[i] = *temp; // get line and add it to the dynamic array we initialized.
            i++;
            ENEMY_COUNT++;
        }
        myfile.close();
    }

    else
    {
        cout << "Unable to open file";
    }
    free(temp);
    return line;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
string *readPokemonNames(const char *argv) // I read it, making a dynamic array by looking to the first line of file.//
{
    ifstream myfile(argv);
    string *temp = new string;
    getline(myfile, *temp);
    string b = *temp;
    int c = stoi(b);
    string *a = new string[c];
    if (myfile.is_open())
    {
        int si = 0;
        while (getline(myfile, *temp)) // get line and add it to the dynamic array we initialized.
        {
            a[si] = *temp;
            ENEMY_POKEMON_COUNT++;
            si++;
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    free(temp);
    return a;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
player characterCreate(string playerName, int pokemonChoice)
{

    if (pokemonChoice == 1) // Pokemon Choice and character initialization at beginning//
    {
        pokemon newPokemon("Bulbasaur", PLAYER_POKEMON_ATTACK);
        return player(playerName, newPokemon);
    }
    else if (pokemonChoice == 2)
    {
        pokemon newPokemon("Charmender", PLAYER_POKEMON_ATTACK);
        return player(playerName, newPokemon);
    }
    else
    {
        pokemon newPokemon("Squirtle", PLAYER_POKEMON_ATTACK);
        return player(playerName, newPokemon);
    }
};
//--------------------------------------------//

//-------------Do Not Change This Function-------------//
void mainMenu()
{
    cout << endl;
    cout << "-------- Menu --------" << endl;
    cout << "1. Fight for a badge" << endl;
    cout << "2. Catch a Pokemon" << endl;
    cout << "3. Number of Pokemons" << endl;
    cout << "4. Number of Pokeballs " << endl;
    cout << "5. Number of Badges" << endl;
    cout << "6. Pokedex" << endl;
    cout << "7. Exit" << endl;
    cout << endl;
    cout << "Choice: ";
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
void fightEnemy(player *newPlayer, string *enemyNames, string *pokemonNames)
{
    pokemon pokemon1(pokemonNames[POK_COUNTER], ENEMY_POKEMON_ATTACK); // Inıtıalize enemy and pokemon//
    newPlayer->playerPokedex.updatePokedex(pokemon1);                  // Update Pokedex
    enemy enemy(enemyNames[NAME_COUNTER], pokemon1);
    NAME_COUNTER++; // change counter in order to match with different enemies next time
    POK_COUNTER++;

    if (NAME_COUNTER == ENEMY_COUNT)
    {

        NAME_COUNTER = 0;
    }
    if (POK_COUNTER == ENEMY_POKEMON_COUNT)
    {
        POK_COUNTER = 0;
    }
    string enemyPokeName = pokemon1.getName();
    string enemyName = enemy.getName();
    int a = 0;
    cout
        << "You encounter with " << enemyName << " and his/hers pokemon " << enemyPokeName << endl;
    cout << enemyPokeName << " Health: 100 Attack: 10" << endl;
    cout << "1- Fight"
         << '\n'
         << "2- Runaway"
         << '\n'
         << "Choice: ";
    cin >> a;

    while (enemy.getPokemon()->gethpValue() > 0) // While enemy poke is alive
    {
        if (a == 1) // if chosen to fight.
        {
            newPlayer->getPokemon()->getDamage(ENEMY_POKEMON_ATTACK); // Pokemon receives damage.
            enemy.getPokemon()->getDamage(PLAYER_POKEMON_ATTACK);     // Pokemon receives damage.
            cout << "Your Pokemons Health: " << newPlayer->getPokemon()->gethpValue() << endl;
            ;
            cout << enemy.getName() << " Pokemons Health: " << enemy.getPokemon()->gethpValue() << endl;
            if (enemy.getPokemon()->gethpValue() == 0) // If you won
            {
                cout << "You Won!" << endl;
                newPlayer->getPokemon()->getDamage(-50); // Heal your poke.
                newPlayer->battleWon();                  // add badge
                break;
            }
        }
        else if (a == 2)
        {
            cout << "Run";
            system("clear");
            break;
        }
        else
        {
            cout << "Run";
            break;
        }
        cout << "1- Fight"
             << '\n'
             << "2- Runaway"
             << '\n'
             << "Choice: ";
        cin >> a;
    }
};
//--------------------------------------------//

//-------------Code This Function-------------//
void catchPokemon(player *newPlayer, string *pokemonNames)
{
    pokemon pokemon(pokemonNames[POK_COUNTER], ENEMY_POKEMON_ATTACK); // create poke
    POK_COUNTER++;                                                    // update poke counter in order to face with different enemies nex time
    if (POK_COUNTER == ENEMY_POKEMON_COUNT)
    {
        POK_COUNTER = 0;
    }
    newPlayer->playerPokedex.updatePokedex(pokemon);
    int a = 0;
    cout << "You encounter with " << pokemon.getName() << " Health: 100 Attack: 10" << endl;
    cout << "1- Catch" << endl;
    cout << "2- Runaway" << endl;
    cout << "Choice: ";
    cin >> a;
    if (a == 1)
    {
        cout << "You catch " << pokemon.getName() << endl;
        newPlayer->catchPokemon(pokemon);
    }
    else
    {
    }
    //---Code Here---//
    //
    //
    //
    //---------------//
};
//--------------------------------------------//
