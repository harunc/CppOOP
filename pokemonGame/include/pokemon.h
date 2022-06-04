//--- 2021-2022 Summer Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname: Harun Çifci
//---Student Number: 150180089
//--------------------------//

#ifndef _H
#define _H

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

//-------------Do Not Add Any New Class(es)-------------//

class pokemon
{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
private:
    string name;
    int hpValue;
    int atkValue;

public:
    pokemon() : name(""), hpValue(100), atkValue(10) {} // default constructor
    pokemon(string name, int atk)                       // constructor with name and atk
    {
        this->name = name;
        this->atkValue = atk;
        hpValue = 100;
    }
    pokemon(const pokemon &toBeCopied) // copy constructor
    {
        this->name = toBeCopied.name;
        this->atkValue = toBeCopied.atkValue;
        this->hpValue = toBeCopied.hpValue;
    }
    string getName() // getters
    {
        return this->name;
    }
    const int gethpValue()
    {
        return hpValue;
    }
    const int getatkValue()
    {
        return this->atkValue;
    }
    void getDamage(int atkOfEnemy) // Take damage
    {
        this->hpValue = hpValue - atkOfEnemy;
    }
};

class pokedex
{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
private:
    pokemon pokedexArray[100];
    int value;

public:
    pokedex() : value(0) {}                 // constructor
    void updatePokedex(pokemon &newPokemon) // update pokedex, add directly if value is 0 else check if it exists on pokedex
    {
        if (value == 0)
        {
            pokedexArray[0] = newPokemon;
            value++;
        }
        else
        {
            for (int i = 0; i <= this->value; i++)
            {
                if (pokedexArray[i].getName() == newPokemon.getName())
                {
                    break;
                }
                else
                {
                    pokedexArray[value] = newPokemon;
                    value++;
                    break;
                }
            }
        }
    }
    void printPokedex() // print pokedex
    {
        for (int i = 0; i < this->value; i++)
        {
            cout << pokedexArray[i].getName() << '\n';
        }
    }
    const int getValue() // get values of pokemons in pokedex
    {
        return this->value;
    }
};

class player
{
private:
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    string name;
    int pokemonNumber;
    int pokeballNumber;
    int badgeNumber;
    pokemon playerPokemon;

public:
    pokedex playerPokedex;
    player() : name("Ash"), pokemonNumber(0), pokeballNumber(10), badgeNumber(0), playerPokemon(pokemon("Charmander", 20)) {} // default constructor
    player(string newName, pokemon &pokemon)                                                                                  // constructor with name and poke
    {
        this->name = newName;
        this->playerPokemon = pokemon;
        this->pokeballNumber = 10;
        this->pokemonNumber = 0;
        this->badgeNumber = 0;
    }
    const int showPokemonNumber()
    {
        return pokemonNumber;
    }
    const int showPokeballNumber()
    {
        return pokeballNumber;
    }
    const int showBadgeNumber()
    {
        return badgeNumber;
    }
    pokemon *getPokemon()
    {
        return &playerPokemon;
    }
    const void battleWon() // battle Won effects
    {
        badgeNumber++;
        pokeballNumber = pokeballNumber + 3;
    }
    const void catchPokemon(pokemon &pokemon) // catch pokeeffects
    {
        pokemonNumber++;
        pokeballNumber--;
    }
};

class enemy
{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
private:
    string name;
    pokemon enemyPokemon;

public:
    enemy() : name("Misty"), enemyPokemon(pokemon("Alakazam", 10)) {} // default constructor
    enemy(string newName, pokemon &pokemon)                           // constructor with name and poke
    {
        this->name = newName;
        this->enemyPokemon = pokemon;
    }
    pokemon *getPokemon()
    {
        return &enemyPokemon;
    }
    const string getName()
    {
        return name;
    }
};

#endif