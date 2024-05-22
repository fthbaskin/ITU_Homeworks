/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

#include <pokemon.h>

// Getters
string Pokemon::getName() const { return mName; }
int Pokemon::getHP() const { return mHP; }
int Pokemon::getPowerUpCounter() const { return mPowerUpCounter; }
bool Pokemon::getIsTerrain() const { return mIsTerrain; }
bool Pokemon::getIsPowerUp() const { return mIsPowerUp; }
bool Pokemon::getIsFainted() const { return mIsFainted; }
double const Pokemon::getPowerUpChance() const { return mPowerUpChance; };
int const Pokemon::getRecharge() const { return mRecharge; }

// Setters
void Pokemon::setName(const string &name) { mName = name; }
void Pokemon::setHP(int HP) { mHP = HP; }
void Pokemon::setPowerUpCounter(int counter) { mPowerUpCounter = counter; }
void Pokemon::setIsTerrain(bool flag) { mIsTerrain = flag; }
void Pokemon::setIsPowerUp(bool flag) { mIsPowerUp = flag; }
void Pokemon::setIsFainted(bool flag) { mIsFainted = flag; }

// Take damage, reduce HP by dmg if HP goes to 0 or negative, set fainted
void Pokemon::takeDamage(int dmg)
{
    // Deduce taken damage from HP, then do checks to see whether fainted or not
    mHP -= dmg;
    if (mHP <= 0)
    {
        mIsFainted = true;
        mHP = 0;
    }
}

// Pokemons try power up
void Pokemon::tryPowerUp()
{
    // Counter for power up counts backwards, if it is greater than zero, counter is decremented and IsPowerUp is false
    if (mPowerUpCounter > 0)
    {
        mPowerUpCounter -= 1;
        mIsPowerUp = false;
    }
    else
    {
        // First generating a double value between 0 and 1
        double random = (double)rand() / RAND_MAX;
        // Then comparing it with PowerUpChance to get that percentage of chance to enter if statement body
        if (random < mPowerUpChance)
        {
            // Set it as in the power up stage
            mIsPowerUp = true;
            // Set the counter when it gets into power up stage, also include current round to the counter
            mPowerUpCounter = mRecharge;
        }
        else
        {
            // If it has a higher value than mPowerUpChance, then it missed the power up try
            mIsPowerUp = false;
        }
    }
}

// Deal damage function, all pokemons except one type is prone to being confused
int Pokemon::dealDamage(bool confused) const
{
    if (!confused)
        return mDamage;
    else
        return 0;
}

// Print function
void Pokemon::print() const
{
    // Printing the name and HP
    cout << mName << " HP: " << mHP << "\n";
}

// Initializer list for the Pokemon class,
Pokemon::Pokemon(const string &name, int HP, int damage, double chance, int recharge) : mName{name}, mHP{HP}, mDamage{damage}, mPowerUpChance{chance}, mRecharge{recharge} {}