/* @Author
 * Student Name: Fatih Baskın
 * Student ID : 150210710
 */

#include "arena.h"

// Getters
ElectricPokemon *Arena::getElectricPokemon() const { return mElectricPokemon; }
PsychicPokemon *Arena::getPsychicPokemon() const { return mPsychicPokemon; }
const string &Arena::getTerrain() const { return mTerrain; }
int Arena::getTerrainCooldown() const { return mTerrainCooldown; }
int const Arena::getTerrainCooldownLimit() const { return mTerrainCooldownLimit; }
double const Arena::getElectricChance() const { return mElectricChance; }
double const Arena::getPsychicChance() const { return mPsychicChance; }

// Setters
void Arena::setElectricPokemon(ElectricPokemon *electric) { mElectricPokemon = electric; }
void Arena::setPsychicPokemon(PsychicPokemon *psychic) { mPsychicPokemon = psychic; }
void Arena::setTerrain(const string &terrain) { mTerrain = terrain; }
void Arena::setTerrainCooldown(int cooldown) { mTerrainCooldown = cooldown; }

// Since there are dynamically allocated elements on the arena, custom destructor is required
Arena::~Arena()
{
    if (mPsychicPokemon != nullptr)
        delete mPsychicPokemon;
    if (mElectricPokemon != nullptr)
        delete mElectricPokemon;
}

// This works to add a pokemon to the arena
void Arena::addPokemon(char type, string name, int hp, int damage)
{
    // There are two cases, electric or psychic
    if (type == 'e')
    {
        // If current electric pokemon is occupied, deallocate it to prevent memory leak
        if (mElectricPokemon != nullptr)
            delete mElectricPokemon;
        // Allocate it using custom constructor dynamically
        mElectricPokemon = new ElectricPokemon(name, hp, damage);
    }
    else if (type == 'p')
    {
        // If current psychic pokemon is occupied, deallocate it to prevent memory leak
        if (mPsychicPokemon != nullptr)
            delete mPsychicPokemon;
        // Allocate it using custom constructor dynamically
        mPsychicPokemon = new PsychicPokemon(name, hp, damage);
    }
}

// This works to simulate battle
void Arena::simulateBattle()
{
    // This check is very important to prevent a segmentation fault and other errors
    if (mElectricPokemon == nullptr || mPsychicPokemon == nullptr)
    {
        cout << "\n\n";
        cout << "Error, not enough players!\n";
        return;
    }

    // This is used for whether a psychic attack is encountered
    bool psychicToken{false};
    // Round number starts from 1, but while loop is constructed in a way that it requires to start from zero
    int roundNumber{0};
    // At the begining of the battle, terrain should be restarted
    restartTerrain();
    while (1)
    {
        roundNumber += 1;
        // spawnTerrain function makes the necessary checks and spawns a new terrain accordingly
        spawnTerrain();
        // This is the coin flip if coinflip is 0, electric starts, if coinflip is 1, psychic starts
        int coinFlip = rand() % 2;
        if (coinFlip == 1)
        {
            // If coinflip is 1, psychic starts and it tries power up, psycic token is set as psychic pokemon's current powerUp status
            mPsychicPokemon->tryPowerUp();
            psychicToken = mPsychicPokemon->getIsPowerUp();
            // Then it deals damage to electric pokemon
            mElectricPokemon->takeDamage(mPsychicPokemon->dealDamage());
            // If electric pokemon faints, break the loop, there is a possibility that powerup status from the last round can be inaccurate
            // because isPowerUp is updated when tryPowerUp is called
            if (mElectricPokemon->getIsFainted())
            {
                mElectricPokemon->setIsPowerUp(false);
                printRoundStats(roundNumber, coinFlip);
                break;
            }
            // If it didn't faint, then electric pokemon tries power up
            mElectricPokemon->tryPowerUp();
            // Then it deals damage to psychic pokemon, psychicToken is used to see whether psychic attack is active or not
            mPsychicPokemon->takeDamage(mElectricPokemon->dealDamage(psychicToken));
            // Electric Pokemon consumes the token by dealing attack,
            psychicToken = false;
            // Finally, if psychic pokemon faints, break the loop, there is no need to correct powerUp because it is updated in the round
            if (mPsychicPokemon->getIsFainted())
            {
                printRoundStats(roundNumber, coinFlip);
                break;
            }
        }
        else
        {
            // If coinflip is 0, electic starts and it tries power up
            mElectricPokemon->tryPowerUp();
            // Then it deals damage to psychic pokemon, psychicToken is used to see whether psychic attack is active or not
            mPsychicPokemon->takeDamage(mElectricPokemon->dealDamage(psychicToken));
            // Electric Pokemon consumes the token by dealing attack,
            psychicToken = false;
            // If psychic pokemon faints, break the loop, there is a possibility that powerup status from the last round can be inaccurate
            // because isPowerUp is updated when tryPowerUp is called
            if (mPsychicPokemon->getIsFainted())
            {
                mPsychicPokemon->setIsPowerUp(false);
                printRoundStats(roundNumber, coinFlip);
                break;
            }
            // If it didn't faint, then psychic pokemon tries power up, psycic token is set as psychic pokemon's current powerUp status
            mPsychicPokemon->tryPowerUp();
            psychicToken = mPsychicPokemon->getIsPowerUp();
            // Then it deals damage to electric pokemon
            mElectricPokemon->takeDamage(mPsychicPokemon->dealDamage());
            // Finally, if psychic pokemon faints, break the loop, there is no need to correct powerUp because it is updated in the round
            if (mElectricPokemon->getIsFainted())
            {
                printRoundStats(roundNumber, coinFlip);
                break;
            }
        }
        printRoundStats(roundNumber, coinFlip);
    }
    // Print match results
    printMatchResults();
    // At the end of the simulation, deallocate objects and set their pointers to null
    delete mElectricPokemon;
    delete mPsychicPokemon;
    mPsychicPokemon = nullptr;
    mElectricPokemon = nullptr;
}

// This function only prints something therefore it is const
void Arena::printRoundStats(int round, int tails) const
{
    cout << "\n\n";
    // These are the information of the current round
    cout << "Round: " << round << "\n"
         << "Current Terrain: " << mTerrain << "\n";
    // Depending on the head/tail, this message can change
    if (tails == 0)
    {
        // Tails = 0 means electric goes first
        cout << mElectricPokemon->getName() << " goes first.\n";
        // The power ups should be printed in order
        if (mElectricPokemon->getIsPowerUp())
            cout << mElectricPokemon->getName() << " has initiated a power up.\n";
        if (mPsychicPokemon->getIsPowerUp())
            cout << mPsychicPokemon->getName() << " has initiated a power up.\n";
    }
    if (tails == 1)
    {
        // Tails = 1 means psychic goes first
        cout << mPsychicPokemon->getName() << " goes first.\n";
        // The power ups should be printed in order
        if (mPsychicPokemon->getIsPowerUp())
            cout << mPsychicPokemon->getName() << " has initiated a power up.\n";
        if (mElectricPokemon->getIsPowerUp())
            cout << mElectricPokemon->getName() << " has initiated a power up.\n";
    }
    // Then print their status info
    mElectricPokemon->print();
    mPsychicPokemon->print();
    // Finally print who is leading
    if (mElectricPokemon->getHP() > mPsychicPokemon->getHP())
        cout << mElectricPokemon->getName() << " is in the lead!\n";
    else
        cout << mPsychicPokemon->getName() << " is in the lead!\n";
}
void Arena::printMatchResults() const
{
    cout << "\n\n";
    cout << "Match Results:\n";
    if (mPsychicPokemon->getIsFainted())
        cout << mElectricPokemon->getName() << " has won the match!\n";
    else if (mElectricPokemon->getIsFainted())
        cout << mPsychicPokemon->getName() << " has won the match!\n";
}

void Arena::spawnTerrain()
{
    // If terrain counter have reached zero, new terrain must be calculated and Pokemon's should be notified of the change
    if (mTerrainCooldown == 0)
    {
        // Calculate new terrain
        terrainCalc();
        // Then notify the Pokemons
        if (mPsychicPokemon != nullptr)
            mPsychicPokemon->checkTerrain(mTerrain);
        if (mElectricPokemon != nullptr)
            mElectricPokemon->checkTerrain(mTerrain);
    }
    if (mTerrainCooldown > 0)
        mTerrainCooldown -= 1;
}

// This is a private function that eases up the calculations
void Arena::terrainCalc()
{
    // This is used for calculating the new terrain
    double random = (double)rand() / RAND_MAX;
    if (random < mPsychicChance)
    {
        // If number is between 0 and psychic chance, it generates psychic terrain
        mTerrain = "psychic";
        // Sets up cooldown counter
        mTerrainCooldown = mTerrainCooldownLimit;
    }
    else if (random < mPsychicChance + mElectricChance)
    {
        // If number is between psychic chance and psychic chance + electric chance, terrain is electric
        mTerrain = "electric";
        // Sets up cooldown counter
        mTerrainCooldown = mTerrainCooldownLimit;
    }
    else
    {
        // If the number is beyond the limits listed above, terrain is none
        mTerrain = "none";
        mTerrainCooldown = 0;
    }
}

void Arena::restartTerrain()
{
    // First, terrain is calculated, it ignores current counters and terrain types
    terrainCalc();
    // Then terrain checks are done for every Pokemon
    if (mPsychicPokemon != nullptr)
        mPsychicPokemon->checkTerrain(mTerrain);
    if (mElectricPokemon != nullptr)
        mElectricPokemon->checkTerrain(mTerrain);
}