/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

// Include protection
#ifndef PSYCHIC_POKEMON_H
#define PSYCHIC_POKEMON_H

#include "pokemon.h"

class PsychicPokemon : public Pokemon
{
public:
    // Its way of dealing damage is different than the base Pokemon, if its in Terrain it deals double amount of damage
    int dealDamage() const;

    // Psychic Pokemons can check whether they are on their terrain and modify their status accordingly
    void checkTerrain(const string &);

    // Copy constructor and default constructor are deleted
    PsychicPokemon() = delete;
    PsychicPokemon(const PsychicPokemon &) = delete;

    // It has a new constructor taking parameters from arena's addPokemon function
    PsychicPokemon(const string &, int, int);
};

#endif