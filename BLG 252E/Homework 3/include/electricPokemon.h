/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

// Include protection
#ifndef ELECTRIC_POKEMON_H
#define ELECTRIC_POKEMON_H

#include "pokemon.h"

class ElectricPokemon : public Pokemon
{
public:
    // Additional getters, these are constant but the useful ones will be callec "check" which modify the values with a logic
    bool getIsConfused() const;
    int getConfusedTimer() const;
    const int getConfusedTimerLimit() const;

    // Additional setters
    void setIsConfused(bool);
    void setConfusedTimer(int);

    // Its way of dealing damage is different than the base Pokemon, if its in PowerUp, if its in Terrain etc.
    int dealDamage(bool);

    // Electric Pokemons can check whether they are on their terrain and modify their status accordingly
    void checkTerrain(const string &);

    // Copy constructor and default constructor are deleted
    ElectricPokemon() = delete;
    ElectricPokemon(const ElectricPokemon &) = delete;

    // It has a new constructor taking parameters from arena's addPokemon function
    ElectricPokemon(const string &, int, int);

private:
    // In addition to the base Pokemon, it has confused state, by default it is false
    bool mIsConfused{false};
    // If a electric pokemon is being subject to confusion attack,
    int mConfusedTimer{0};
    const int mConfusedTimerLimit{3};

    // Electric pokemons are needed to be checked whether they are still confused
    // This method is used as a tool, to check whether ElectricPokemon is confused, it takes confusionAttack as input
    void checkConfused(bool);
};

#endif