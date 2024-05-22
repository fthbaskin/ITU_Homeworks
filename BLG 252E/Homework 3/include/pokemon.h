/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

// Include protection
#ifndef POKEMON_H
#define POKEMON_H

// Srtring library and iostream library is required to hold names and communicate
#include <string>
#include <iostream>

// stdlib is required for rand() function
#include <stdlib.h>

// For ease of coding, using scope resolution operator for string, cin, cout
using std::cin;
using std::cout;
using std::string;

class Pokemon
{
public:
    // Setters
    // To speed up copying a string, const reference is sent into the method
    void setName(const string &);
    void setHP(int);
    void setPowerUpCounter(int);
    void setIsTerrain(bool);
    void setIsPowerUp(bool);
    void setIsFainted(bool);

    // Getters, these are const functions, they only return a value
    string getName() const;
    int getHP() const;
    int getPowerUpCounter() const;
    bool getIsTerrain() const;
    bool getIsPowerUp() const;
    bool getIsFainted() const;
    double const getPowerUpChance() const;
    int const getRecharge() const;

    // Every pokemon can take damage
    void takeDamage(int);

    // Every pokemon has the powerUp method (it might differ, then the function will be overriden)
    void tryPowerUp();

    // Every pokemon can deal damage, it takes confusion as a parameter (it might differ, then the function will be overriden)
    int dealDamage(bool) const;

    // Default constructor and copy constructor are deleted
    Pokemon() = delete;
    Pokemon(const Pokemon &) = delete;

    // It has a print function to write its name and hp, it is const, it doesn't change anything
    void print() const;

    // Only the constructor with parameters do remain
    // It takes string as a const reference so it copies it directly whilce costructing
    Pokemon(const string &, int, int, double, int);

protected:
    // Those were given in the homework statement
    string mName;
    int mHP;
    int const mDamage;
    double const mPowerUpChance;
    int const mRecharge;

    // These are required for implementation
    int mPowerUpCounter{0};
    bool mIsTerrain{false};
    bool mIsPowerUp{false};
    bool mIsFainted{false};
};

#endif