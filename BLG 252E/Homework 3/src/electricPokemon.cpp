/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

#include "electricPokemon.h"

// Additional getters
bool ElectricPokemon::getIsConfused() const { return mIsConfused; }
int ElectricPokemon::getConfusedTimer() const { return mConfusedTimer; }
const int ElectricPokemon::getConfusedTimerLimit() const { return mConfusedTimerLimit; }

// Additional setters
void setIsConfused(bool);
void setConfusedTimer(int);

// ElectricPokemon's damage dealing mechanism differs from the base one, it checks whether being confused and powerup mechanisms also modify the values
int ElectricPokemon::dealDamage(bool psychicAttack)
{
    // First, whether being confused must be checked
    checkConfused(psychicAttack);
    // Then base damage must be calculated
    int base_damage{Pokemon::dealDamage(mIsConfused)};
    // From the base damage, modified damage must be calculated
    int modified_damage{base_damage};
    // If Electric Pokemon is in the PowerUp stage, then its damage must be modified by multiplying it with 3
    if (mIsPowerUp)
        modified_damage *= 3;
    // Then finally return damage
    return modified_damage;
}

// Electric Pokemons can check their current terrain
void ElectricPokemon::checkTerrain(const string &terrain)
{
    if (terrain == "electric")
        mIsTerrain = true;
    else
        mIsTerrain = false;
}

// Electric Pokemons can check their current confusion status,
void ElectricPokemon::checkConfused(bool confusionAttack)
{
    if (mIsTerrain)
    {
        // If current terrain is electric terrain, to ignore comming attacks and set current status to not confused
        mIsConfused = false;
        mConfusedTimer = 0;
    }
    else
    {
        // If pokemon is not on its own terrain, then update confusion status accordingly
        if (confusionAttack)
        {
            // If there is a confusion attack, set confused and confused timer
            mIsConfused = true;
            mConfusedTimer = mConfusedTimerLimit;
        }
        else
        {
            // Otherwise, update current status accordingly
            if (mConfusedTimer > 0)
            {
                // If timer value is bigger than zero, decrement timer and set confused status true
                mIsConfused = true;
                mConfusedTimer -= 1;
            }
            if (mConfusedTimer == 0)
            {
                // If timer reaches zero, set status false
                mIsConfused = false;
            }
        }
    }
}

// Constructor with parameters, it uses base class constructor: name, hp, damage, power up chance, recharge
ElectricPokemon::ElectricPokemon(const string &name, int HP, int damage) : Pokemon{name, HP, damage, 0.2, 3}
{
    // It prints a message when it enters the arena.
    cout << "\n\n";
    cout << "Electric Pokemon " << mName << " has entered the arena.\n"
         << "        Class : Electric\n"
         << "        Name : " << mName << "\n"
         << "        HP : " << mHP << "\n"
         << "        Damage : " << mDamage << "\n";
}