/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

#include "psychicPokemon.h"

// Psychic pokemons can check their current terrain
void PsychicPokemon::checkTerrain(const string &terrain)
{
    if (terrain == "psychic")
        mIsTerrain = true;
    else
        mIsTerrain = false;
}

// Psychic pokemons can deal twice the amount of damage when they are in their own terrain
int PsychicPokemon::dealDamage() const
{
    // Psychic pokemons are immune to the psychic attacks so sending false to base method
    int base_damage = Pokemon::dealDamage(false);
    int modified_damage{base_damage};
    // If pokemon is in the terrain then it deals double amount of damage
    if (mIsTerrain)
        modified_damage *= 2;
    return modified_damage;
}

// Constructor with parameters, it uses base class constructor: name, hp, damage, power up chance, recharge
PsychicPokemon::PsychicPokemon(const string &name, int HP, int damage) : Pokemon{name, HP, damage, 0.3, 5}
{
    // It prints a message when it enters the arena.
    cout << "\n\n";
    cout << "Psychic Pokemon " << mName << " has entered the arena.\n"
         << "        Class : Psychic\n"
         << "        Name : " << mName << "\n"
         << "        HP : " << mHP << "\n"
         << "        Damage : " << mDamage << "\n";
}
