// Fatih Baskın
// 150210710

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// Verbose is a global variable
bool verbose = false;

class City
{
public:
    // City name data
    std::string mCity;
    // City population data
    int mPopulation;

    /** Constructor of the City class, by providing the values directly.
     * @param city
     * Name of the city.
     * @param population
     * Population of the city.
     */
    City(const std::string &city, int population) : mCity{city}, mPopulation{population} {}

    /** Constructor of the City class, by providing the csv line.
     * @param line
     * CSV line input of the City class.
     */
    City(const std::string &);

    /** Copy Constructor of the City class.
     * @param source
     * Constant reference to a City object.
     */
    City(const City &source) : mCity{source.mCity}, mPopulation{source.mPopulation} {}

    /** Operator overload for printing the data as csv format "mCity;mPopulation"
     * Doesn't have line break at the end.
     */
    friend std::ostream &operator<<(std::ostream &, const City &);
};

// Enum class for enumerating the pivoting strategy.
enum class PivotStrategy
{
    Right,
    Random,
    Median
};

class QuickSort
{
private:
    // Pivoting strategy
    PivotStrategy mStrategy{PivotStrategy::Right};
    // Threshold for the insertionSort
    int mThreshold{1};

    /** Finds the partition index for the quicksort. Pivot element is the rightmost object.
     * Static because it can work without the initialization of the quickSort.
     * @param vect
     * Reference to a City pointer vector.
     * @param left_idx
     * Left index of the (sub)array.
     * @param right_idx
     * Right index of the (sub)array.
     * @return Index of the pivot
     */
    static int basicPartition(std::vector<City *> &, int, int);

    /** Select a random index between the range [left_idx, right_idx]
     * Static since it can work without the declaration of the class.
     * @param left_idx
     * Left index of the (sub)array.
     * @param right_idx
     * Right index of the (sub)array.
     * @return
     * A value in between left_idx and right_idx (inclusive).
     */
    static int selectRandomPivot(int, int);

    /** Selects three random elements inside the (sub)array and selects the median of those 3 as pivot.
     * @param vect
     * Constant reference to the City pointer vector where pivot will be selected.
     * @param left_idx
     * Left index of the (sub)array.
     * @param right_idx
     * Right index of the (sub)array.
     * @return
     * Selected pivot element's index for the partition function.
     */
    int selectMedianPivot(const std::vector<City *> &, int, int) const;

    /** Finds the partition index for the quicksort. Uses the strategy defined in the class while pivoting.
     * @param vect
     * Reference to a City pointer vector.
     * @param left_idx
     * Left index of the (sub)array.
     * @param right_idx
     * Right index of the (sub)array.
     * @return Index of the pivot
     */
    int strategyPartition(std::vector<City *> &, int, int);

public:
    /** Default constructor of the QuickSortPart1_3 class.
     * Strategy is right pivoting by default.
     * Insertion sort threshold is 1 by default.
     */
    QuickSort() : mStrategy{PivotStrategy::Right}, mThreshold{1} {}

    /** Custom constructior of the QuickSort class.
     * @param strategy
     * Pivoting strategy which is going to be set during the initialization.
     * @param k
     * Threshold for the insertion sort.
     */
    QuickSort(PivotStrategy strategy, int k) : mStrategy{strategy}, mThreshold{k} {}

    /** Setter for the strategy of the QuickSort.
     * @param strategy
     * Pivoting strategy to be set.
     */
    void setStrategy(PivotStrategy);

    /** Getter for the strategy of the QuickSort, returns as a string.
     * @return
     * Pivoting strategy as an enum.
     */
    PivotStrategy getStrategy() const;

    /** Getter for the strategy of the QuickSort, returns as a string.
     * @return
     * Pivoting strategy as a string.
     */
    std::string getStrategyString() const;

    /** Setter for the insertion sort threshold.
     * @param k
     * The threshold value (>1) for the insertion sort.
     */
    void setThreshold(int);

    /** Getter for the insertion sort threshold
     * @return
     * The hreshold value for the insertion sort.
     */
    int getThreshold() const;

    /** Sorts the elements of an City pointer vector in ascending order by their populations.
     * There is no optimization or anything. As in the Part 1.1. Therefore it can be static.
     * It doesn't require any QuickSort variables to be defined.
     * @param vect
     * Reference to an City pointer vector to be sorted.
     * @param left_idx
     * Leftmost index of the (sub)array.
     * @param right_idx
     * Rightmost index of the (sub)array.
     */
    static void basicQuickSort(std::vector<City *> &, int, int);

    /** Sorts the elements of an City pointer vector in ascending order by their populations.
     * Uses pivoting strategy of the object.
     * Pivoting options are right, median and random.
     * @param vect
     * Reference to City pointer vector to be sorted.
     * @param left_idx
     * Leftmost index of the (sub)array.
     * @param right_idx
     * Rightmost index of the (sub)array.
     */
    void strategyQuickSort(std::vector<City *> &, int, int);

    /** This insertion sort algorithm sorts City pointer vector by their populations in quadratic time.
     * @param vect
     * Reference to an City pointer vector to be sorted.
     * @param left_idx
     * Leftmost index of the (sub)array.
     * @param right_idx
     * Rightmost index of the (sub)array.
     */
    void insertionSort(std::vector<City *> &, int, int);

    /** Sorts the elements of an City pointer vector in ascending order, according to their populations.
     * Uses pivoting strategy and insertion sort threshold of the object.
     * Pivoting options are right, median and random.
     * Insertion sort threshold is a positive integer where below this threshold, quickSort switches to insertion sort for optimization.
     * @param vect
     * Reference to an City vector to be sorted.
     * @param left_idx
     * Leftmost index of the (sub)array.
     * @param right_idx
     * Rightmost index of the (sub)array.
     */
    void quickSort(std::vector<City *> &, int, int);
};

/** Operator overload for printing City objects as csv format "mCity;mPopulation".
 * Doesn't have line break at the end.
 */
std::ostream &
operator<<(std::ostream &os, const City &city)
{
    os << city.mCity << ";" << city.mPopulation;
    return os;
}

int main(int argc, char **argv)
{
    // Randomizer seed.
    srand(time(NULL));

    // Getting the arguments
    if (argc < 5)
    {
        std::cout << "Not enouth arguments\n";
        return 0;
    }
    char *inFileName = argv[1];
    char *mode = argv[2];
    char *k = argv[3];
    char *outFileName = argv[4];

    // Turning provided value for threshold into integer.
    std::stringstream ss;
    int threshold;
    ss << k;
    ss >> threshold;
    if (threshold < 1)
    {
        // Threshold values cannot be smaller than 1.
        std::cout << "Threshold values can never be smaller than 1. Setting it to 1.\n";
        threshold = 1;
    }

    // Parsing the mode into strategy.
    PivotStrategy strategy;
    switch (mode[0])
    {
    case 'l':
        strategy = PivotStrategy::Right;
        break;
    case 'r':
        strategy = PivotStrategy::Random;
        break;
    case 'm':
        strategy = PivotStrategy::Median;
        break;
    default:
        // If the provided letter is wrong, set it to default case, Right pivoting
        std::cout << "Wrong character for a strategy is provided. Default strategy is set (Right)\n";
        strategy = PivotStrategy::Right;
        break;
    }

    // If verbose input is provided.
    if (argc > 5)
        if (argv[5][0] == 'v')
            verbose = true;

    // Creating the cities vector by reading the input.
    // Using pointers to minimize performance losses while swapping city objects.
    // Swapping strings have some overload.
    std::vector<City *> cities;
    std::fstream inFile(inFileName, std::ios::in);

    // Assertion for the inFile.
    assert(inFile.is_open());

    // Read CSV line by line and use the constructor
    std::string line;
    if (inFile.is_open())
    {
        // While reading from the input, pushing back pointers of new city objects into vector.
        while (getline(inFile, line))
        {
            // Due to input sometimes being UTF-8 there is some problem while reading input.
            // There will be unknown characters in the output, due to output being in ASCII.
            while (line[0] == '\357' || line[0] == '\273' || line[0] == '\277')
                line.erase(line.begin());
            cities.push_back(new City{line});
        }
    }
    inFile.close();

    // Intitalizing the sorter.
    QuickSort sorter(strategy, threshold);

    // Start chronometer.
    const auto beginChrono{std::chrono::steady_clock::now()};

    // Calling the quickSort.
    sorter.quickSort(cities, 0, cities.size() - 1);

    // End the chronometer.
    const auto endChrono{std::chrono::steady_clock::now()};
    const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};

    // Print the chronometer result.
    std::cout << "Tame taken by QuicSort with pivot strategy '" << sorter.getStrategyString()
              << "' and threshold " << sorter.getThreshold() << ": [" << timeTaken.count() << "] ns.\n";

    // Writing the output:
    std::fstream outFile(outFileName, std::ios::out);
    // Assertion for the outFile.
    assert(outFile.is_open());

    // The << operator was overloaded to make code clearer.
    // Write sorted cities into the file.
    for (auto city : cities)
        outFile << *city << "\n";
    outFile.close();

    return 0;
}

// Method declarations of the City class.

City::City(const std::string &line)
{
    // The read line will be used for constructing this City object.
    // StringStream is used for parsing the csv line.
    std::stringstream stream(line);
    // With usig the getline,
    getline(stream, mCity, ';');
    // The last element without the seperator goes into the population.
    stream >> mPopulation;
}

// Medtod declarations of the QuickSort class.

PivotStrategy QuickSort::getStrategy() const { return mStrategy; }

std::string QuickSort::getStrategyString() const
{
    // Return the pivoting strategy as a string.
    switch (mStrategy)
    {
    case PivotStrategy::Median:
        return "median";
    case PivotStrategy::Random:
        return "random";
    case PivotStrategy::Right:
        return "right";
    }
    // Trivial case, for making compiler happy
    return "right";
}

int QuickSort::getThreshold() const { return mThreshold; }

void QuickSort::setThreshold(int k)
{
    // Threshold can at least be 1.
    if (k > 0)
        mThreshold = k;
    else
        mThreshold = 1;
}

void QuickSort::setStrategy(PivotStrategy strategy) { mStrategy = strategy; }

int QuickSort::basicPartition(std::vector<City *> &vect, int left_idx, int right_idx)
{
    // Pivot index, pivot initially starts from the left.
    int pivot_idx = left_idx;

    // Pivot element is the rightmost element by default.
    int pivot = vect[right_idx]->mPopulation;

    // Iteration starts from the leftmost index.
    int curr_idx = left_idx;
    while (curr_idx < right_idx)
    {
        // If the current element is larger than pivot then add it behind the pivot.
        if (vect[curr_idx]->mPopulation < pivot)
        {
            // Swapping the pointers of objects since it is faster than reassigning all the values of City.
            City *temp = vect[curr_idx];
            vect[curr_idx] = vect[pivot_idx];
            vect[pivot_idx] = temp;
            // Since a element was smaller than the pivot, pivot index is increased.
            pivot_idx++;
        }
        // Increment the current index after each iteration.
        curr_idx++;
    }

    // Finally, put the pivot into its place
    City *temp = vect[pivot_idx];
    vect[pivot_idx] = vect[right_idx];
    vect[right_idx] = temp;

    // Return the pivot index.
    return pivot_idx;
}

void QuickSort::basicQuickSort(std::vector<City *> &vect, int left_idx, int right_idx)
{
    // Base case, if the subarray is sized 1 or less, return.
    // Because an array with one element is already sorted.
    if (left_idx >= right_idx)
        return;

    // Find the pivot index using the partition function.
    // Selected rigtmost element for the pivoting strategt.
    int pivot_idx = basicPartition(vect, left_idx, right_idx);

    // Then call partition for left and right subarrays.
    // If check is done for not entering the recursive statement unnecessarily.
    if (left_idx < pivot_idx - 1)
        basicQuickSort(vect, left_idx, pivot_idx - 1);
    if (pivot_idx + 1 < right_idx)
        basicQuickSort(vect, pivot_idx + 1, right_idx);
}

int QuickSort::selectRandomPivot(int left_idx, int right_idx)
{
    // Select a random index between the range [left_idx, right_idx]
    // To include right_idx in the randomization, modulo is (right_idx - left_idx + 1).
    return left_idx + (rand() % (right_idx - left_idx + 1));
}

int QuickSort::selectMedianPivot(const std::vector<City *> &vect, int left_idx, int right_idx) const
{
    // If there is 1 or 2 elements in the subarray, return the right index.
    // It doesn't matter since there is not enough elements to pick median.
    if (right_idx - left_idx < 2)
        return right_idx;

    int select_idx1, select_idx2, select_idx3;

    if (right_idx - left_idx == 2)
    {
        // Random selection is trivial if the subarray size is 3. Select manually.
        select_idx1 = left_idx;
        select_idx2 = left_idx + 1;
        select_idx3 = right_idx;
    }
    else
    {
        // For 4 and more elements, random selection works fine.
        // Select a random index between the range [left_idx, right_idx]
        // To include right_idx in the randomization, modulo is (right_idx - left_idx + 1).
        // selectRandomPivot function can be used for that.
        select_idx1 = selectRandomPivot(left_idx, right_idx);
        select_idx2 = select_idx1;

        // Elements must be distinct.
        while (select_idx2 == select_idx1)
            select_idx2 = selectRandomPivot(left_idx, right_idx);

        select_idx3 = select_idx2;
        while (select_idx3 == select_idx1 || select_idx3 == select_idx2)
            select_idx3 = selectRandomPivot(left_idx, right_idx);
    }
    // Return the median.
    // Case if select1 is the median.
    if ((vect[select_idx1]->mPopulation <= vect[select_idx2]->mPopulation && vect[select_idx1]->mPopulation >= vect[select_idx3]->mPopulation) ||
        (vect[select_idx1]->mPopulation >= vect[select_idx2]->mPopulation && vect[select_idx1]->mPopulation <= vect[select_idx3]->mPopulation))
        return select_idx1;

    // Case if select2 is the median.
    if ((vect[select_idx2]->mPopulation >= vect[select_idx1]->mPopulation && vect[select_idx2]->mPopulation <= vect[select_idx3]->mPopulation) ||
        (vect[select_idx2]->mPopulation <= vect[select_idx1]->mPopulation && vect[select_idx2]->mPopulation >= vect[select_idx3]->mPopulation))
        return select_idx2;

    // Case if select3 is the median
    if ((vect[select_idx3]->mPopulation >= vect[select_idx1]->mPopulation && vect[select_idx3]->mPopulation <= vect[select_idx2]->mPopulation) ||
        (vect[select_idx3]->mPopulation <= vect[select_idx1]->mPopulation && vect[select_idx3]->mPopulation >= vect[select_idx2]->mPopulation))
        return select_idx3;

    // Trivial case, for making the compiler happy.
    return select_idx1;
}

int QuickSort::strategyPartition(std::vector<City *> &vect, int left_idx, int right_idx)
{

    // Select pivot according to the pivoting strategy.
    int select_pivot = right_idx;
    switch (mStrategy)
    {
    case PivotStrategy::Median:
        select_pivot = selectMedianPivot(vect, left_idx, right_idx);
        break;
    case PivotStrategy::Right:
        select_pivot = right_idx;
        break;
    case PivotStrategy::Random:
        select_pivot = selectRandomPivot(left_idx, right_idx);
        break;
    }
    // With the pivoting strategy, we select the which pivot to use, so swap the selected index with the last index.
    // This way, code in the Part 1.1 will be recycled.
    City *temp = vect[select_pivot];
    vect[select_pivot] = vect[right_idx];
    vect[right_idx] = temp;

    // Call the parent class partition to do the work for us.
    int partition_pivot = basicPartition(vect, left_idx, right_idx);

    if (verbose)
    {
        // If the current mode is verbose, write it into the log.
        std::fstream log("log.txt", std::ios::app);
        // Assertion check is necessary.
        assert(log.is_open());
        // Printing the pivot and array.
        log << "Pivot: " << vect[partition_pivot]->mPopulation << " Array: [";
        for (int i = left_idx; i < right_idx; i++)
            log << vect[i]->mPopulation << ", ";
        log << vect[right_idx] << "]\n";
        log.close();
    }

    return partition_pivot;
}

void QuickSort::strategyQuickSort(std::vector<City *> &vect, int left_idx, int right_idx)
{
    // Base case, if the subarray is sized 1 or less, return.
    // Because an array with one element is already sorted.
    if (left_idx >= right_idx)
        return;

    // Find the pivot index using the partition function.
    int pivot_idx = strategyPartition(vect, left_idx, right_idx);

    // Then call partition for left and right subarrays.
    // If check is done for not entering the recursive statement unnecessarily.
    if (left_idx < pivot_idx - 1)
        strategyQuickSort(vect, left_idx, pivot_idx - 1);
    if (pivot_idx + 1 < right_idx)
        strategyQuickSort(vect, pivot_idx + 1, right_idx);
}

void QuickSort::insertionSort(std::vector<City *> &vect, int left_idx, int right_idx)
{

    // In the range (left_idx, right_idx]
    for (int i = left_idx + 1; i <= right_idx; i++)
    {
        // key is the current element which is I am comparing to other elements.
        int key = vect[i]->mPopulation;
        // key_idx is the left index of the key.
        int key_idx = i - 1;
        // While inside the boundaries of the (sub)array and left element is bigger than key, swap and move left.
        while (key_idx >= left_idx && vect[key_idx]->mPopulation > key)
        {
            City *temp = vect[key_idx + 1];
            vect[key_idx + 1] = vect[key_idx];
            vect[key_idx] = temp;
            key_idx -= 1;
        }
    }
}

void QuickSort::quickSort(std::vector<City *> &vect, int left_idx, int right_idx)
{
    // Base case, if the subarray is sized 1 or less, return.
    // Because an array with one element is already sorted.
    if (left_idx >= right_idx)
        return;

    // If the current indexes are lower than the threshold, execute insertion sort only.
    if (right_idx - left_idx + 1 <= mThreshold)
    {
        insertionSort(vect, left_idx, right_idx);
        return;
    }

    // Find the pivot index using the partition function.
    int pivot_idx = strategyPartition(vect, left_idx, right_idx);

    // Then call partition for left and right subarrays.
    // If check is done for not entering the recursive statement unnecessarily.
    if (left_idx < pivot_idx - 1)
        quickSort(vect, left_idx, pivot_idx - 1);
    if (pivot_idx + 1 < right_idx)
        quickSort(vect, pivot_idx + 1, right_idx);
}
