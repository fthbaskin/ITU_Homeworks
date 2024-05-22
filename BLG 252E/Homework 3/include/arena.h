/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

// Include protection
#ifndef ARENA_H
#define ARENA_H

#include "pokemon.h"
#include "psychicPokemon.h"
#include "electricPokemon.h"

class Arena
{
public:
    // Getters
    ElectricPokemon *getElectricPokemon() const;
    PsychicPokemon *getPsychicPokemon() const;
    const string &getTerrain() const;
    int getTerrainCooldown() const;
    int const getTerrainCooldownLimit() const;
    double const getElectricChance() const;
    double const getPsychicChance() const;

    // Setters
    void setElectricPokemon(ElectricPokemon *);
    void setPsychicPokemon(PsychicPokemon *);
    void setTerrain(const string &);
    void setTerrainCooldown(int);

    // Constructor is default, it will not do not do anything special, all private members are initialized with initial values
    Arena() = default;
    // Copy constructor is deleted
    Arena(const Arena &) = delete;

    // Custom destructor is required since there are dynamically allocated elements
    ~Arena();

    // Adding pokemon to battle
    void addPokemon(char, string, int, int);

    // Simulating battle
    void simulateBattle();

    // Terrain generation
    void spawnTerrain();
    void restartTerrain();

    // These just print things, they are const
    void printRoundStats(int, int) const;
    void printMatchResults() const;

private:
    // Pokemons, they are dynamically allocated and initally pointers are bull
    ElectricPokemon *mElectricPokemon{nullptr};
    PsychicPokemon *mPsychicPokemon{nullptr};
    // Terrain name, cooldowns and spawn chances
    string mTerrain{"none"};
    int mTerrainCooldown{0};
    int const mTerrainCooldownLimit{5};
    double const mElectricChance{0.2};
    double const mPsychicChance{0.2};
    // This function is used to calculate new terrain
    void terrainCalc();
};

#endif