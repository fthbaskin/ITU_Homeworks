// Fatih Baskın
// 150210710

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <assert.h>
#include <chrono>

// City class
class City
{
public:
    // City name data
    std::string mCity{""};
    // City population data
    int mPopulation{0};

    City() : mCity(""), mPopulation(0){};

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

/** Operator overload for printing City objects as csv format "mCity;mPopulation".
 * Doesn't have line break at the end.
 */
std::ostream &
operator<<(std::ostream &os, const City &city)
{
    os << city.mCity << ";" << city.mPopulation;
    return os;
}

// Binary heap class that does the binary heap operations
class BinaryHeap
{
protected:
    static int left_child(int idx) { return 2 * idx; }
    static int right_child(int idx) { return (2 * idx) + 1; }
    static int parent(int idx) { return idx / 2; }

public:
    static void max_heapify(std::vector<City *> &, int, int);
    static void build_max_heap(std::vector<City *> &, int);
    static void heap_sort(std::vector<City *> &, int);
    // Used for printing the priority queue
    static void print(const std::vector<City *> &, int heap_size, std::fstream &);
};

// Binary priority queue class that does the priority queue operations
// Priority queue inherits binary heap since it is a binary heap
class PriorityQueue : public BinaryHeap
{
private:
    // Priority queue is stored, 1 indexed heap, first element is empty
    std::vector<City *> pq{{NULL}};
    // Size of the priority queue is kept here.
    int pq_size{0};

public:
    // Priority queue constructor with incoming vector, it takes it, assigns it then builds a max heap with it.
    PriorityQueue(std::vector<City *> &vect, int heap_size) : pq{vect}, pq_size{heap_size} { BinaryHeap::build_max_heap(pq, pq_size); }

    // For inserting a city object into the priority queue
    void max_heap_insert(City *);

    // For extracting the max from the priority queue. It removes it from the heap.
    City *heap_extract_max();

    // For increasing a key in the vector
    void heap_increase_key(int, int);

    // Returns the maximum element
    City *heap_maximum() { return pq[1]; }

    // Overrides heap_sort to be used in this priority queue
    void heap_sort() { BinaryHeap::heap_sort(pq, pq_size); }

    // Overrides build_max_heap to be used in this priority queue
    void build_max_heap() { BinaryHeap::build_max_heap(pq, pq_size); }

    // Used for printing the priority queue
    void print(std::fstream &);
};

// Class for dary heap
class DaryHeap
{
private:
    // dary heap vector
    std::vector<City *> dary_heap{{NULL}};
    // size of the dary heap
    int dary_heap_size{0};
    // d value of the d-ary heap
    int d{0};

    int parent(int);
    std::vector<int> children(int);

public:
    // Constructor of the dary heap
    DaryHeap(std::vector<City *> &vect, int heap_size, int d) : dary_heap{vect}, dary_heap_size{heap_size}, d{d} { build_dary_heap(); }

    // Max heapify for dary heap
    void dary_max_heapify(int);

    // Builds the dary heap
    void build_dary_heap();

    // Calculates the height of the dary heap
    static int dary_calculate_height(int, int);

    // Insert element to the dary heap
    void dary_insert_element(City *);

    // Increase key of the dary heap
    void dary_increase_key(int, int);

    // For extracting the max from the dary heap. It removes it from the heap.
    City *dary_extract_max();

    // For doing heapsort using dary
    void dary_heapsort();

    // Used for printing the dary heap
    void print(std::fstream &);
};

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        std::cout << "Not enough arguments!\n";
        return 0;
    }
    // Taking the base arguments, input file, function, output file
    char *inFileName = argv[1];
    std::string func = argv[2];
    char *outFileName = argv[3];

    // Heap is 1 indexed, so 0th index is empty
    std::vector<City *>
        vect(1, NULL);

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
            vect.push_back(new City{line});
        }
    }
    inFile.close();
    // heap size is the vector size - 1, because it is 1 indexed heap.
    int heap_size = vect.size() - 1;

    // Heap Functions
    if (func == "max_heapify")
    {
        // Max heapify takes index argument so total argunents is 5
        if (argc < 5)
        {
            std::cout << "Not enough arguments!\n";
            return 0;
        }
        // Take the argv[4] and parse it
        std::stringstream ss;
        ss << argv[4];
        char k = '\0';
        ss >> k;
        // Check parameter type
        if (k != 'k')
        {
            std::cout << "Wrong parameter type!\n";
            return 0;
        }
        // Check parameter value
        int idx = 0;
        ss >> idx;
        if (idx <= 0)
        {
            std::cout << "Wrong parameter value!\n";
            return 0;
        }
        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        BinaryHeap::max_heapify(vect, heap_size, idx);
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for max_heapify: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        BinaryHeap::print(vect, heap_size, outFile);
        outFile.close();
    }
    else if (func == "build_max_heap")
    {
        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        BinaryHeap::build_max_heap(vect, heap_size);
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for build_max_heap: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        BinaryHeap::print(vect, heap_size, outFile);
        outFile.close();
    }
    else if (func == "heapsort")
    {
        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        BinaryHeap::heap_sort(vect, heap_size);
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for heapsort: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        BinaryHeap::print(vect, heap_size, outFile);
        outFile.close();
    }
    // Priority queue functions
    else if (func == "max_heap_insert")
    {
        // Both city and population should be provided under k argument
        if (argc < 5)
        {
            std::cout << "Not enough arguments!\n";
            return 0;
        }
        if (argv[4][0] != 'k')
        {
            std::cout << "Wrong parameter type!\n";
            return 0;
        }
        // Take the argv[4] and parse it
        std::string s = argv[4];
        std::string delimiter = "_";
        // Found parsing technique from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
        size_t pos = 0;
        // The first token is the argument type, which is checked already
        if ((pos = s.find(delimiter)) != std::string::npos)
            s.erase(0, pos + delimiter.length());
        // The second token is the city name
        std::string city = "";
        if ((pos = s.find(delimiter)) != std::string::npos)
        {
            city = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
        }
        // The remaining string is the population
        int population = 0;
        std::stringstream ss;
        ss << s;
        ss >> population;
        // Check parameter values
        if (population <= 0 && city == "")
        {
            std::cout << "Wrong parameter value!\n";
            return 0;
        }

        // Build the priority queue
        PriorityQueue pq(vect, heap_size);
        City *newCity = new City{city, population};

        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        pq.max_heap_insert(newCity);
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for max_heap_insert: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        pq.print(outFile);
        outFile.close();

        // Deleting the new city to prevent memory leak
        // It is not in the original vector so it is not deleted in the end
        delete newCity;
    }
    else if (func == "heap_extract_max")
    {
        // Build priority queue
        PriorityQueue pq(vect, heap_size);

        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        City *maximum = pq.heap_extract_max();
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for heap_extract_max: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        outFile << *maximum << "\n";
        outFile.close();
    }
    else if (func == "heap_increase_key")
    {
        // Both index and key should be provided
        if (argc < 6)
        {
            std::cout << "Not enough arguments!\n";
            return 0;
        }
        // Take the argv[4] and parse it
        std::stringstream ss;
        ss << argv[4];
        char par1 = '\0';
        ss >> par1;
        int val1 = 0;
        ss >> val1;
        // Clear ss to take parameter properly
        ss.clear();
        // Take the argv[5] and parse it
        ss << argv[5];
        char par2 = '\0';
        ss >> par2;
        int val2 = 0;
        ss >> val2;
        // Check parameter types
        if ((par1 != 'i' || par2 != 'k') && (par1 != 'k' || par2 != 'i'))
        {
            std::cout << "Wrong parameter types!\n";
            return 0;
        }
        // Take index
        int idx = 0;
        if (par1 == 'i')
            idx = val1;
        else
            idx = val2;
        // Take key
        int key = 0;
        if (par1 == 'k')
            key = val1;
        else
            key = val2;
        if (idx <= 0)
        {
            std::cout << "Wrong parameter value!\n";
            return 0;
        }

        // Build the prioirty queue
        PriorityQueue pq(vect, heap_size);

        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        pq.heap_increase_key(idx, key);
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for heap_increase_key: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        pq.print(outFile);
        outFile.close();
    }
    else if (func == "heap_maximum")
    {
        // Build the prioirity queue
        PriorityQueue pq(vect, heap_size);

        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        City *maximum = pq.heap_maximum();
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for heap_maximum: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        outFile << maximum << "\n";
        outFile.close();
    }
    // Dary-heap functions
    else if (func == "dary_calculate_height")
    {
        // dary_calculate_height takes d as argument so total argunents is 5
        if (argc < 5)
        {
            std::cout << "Not enough arguments!\n";
            return 0;
        }
        // Take the argv[4] and parse it
        std::stringstream ss;
        ss << argv[4];
        char d = '\0';
        ss >> d;
        // Check parameter type
        if (d != 'd')
        {
            std::cout << "Wrong parameter type!\n";
            return 0;
        }
        // Check parameter value
        int dary = 0;
        ss >> dary;
        if (dary <= 0)
        {
            std::cout << "Wrong parameter value!\n";
            return 0;
        }

        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        // No need to build DaryHeap since it can be calculated mathematically
        int height = DaryHeap::dary_calculate_height(heap_size, dary);
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for dary_calculate_height: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        outFile << height << "\n";
        outFile.close();
    }
    else if (func == "dary_extract_max")
    {
        // dary_calculate_height takes d as argument so total argunents is 5
        if (argc < 5)
        {
            std::cout << "Not enough arguments!\n";
            return 0;
        }
        // Take the argv[4] and parse it
        std::stringstream ss;
        ss << argv[4];
        char d = '\0';
        ss >> d;
        // Check parameter type
        if (d != 'd')
        {
            std::cout << "Wrong parameter type!\n";
            return 0;
        }
        // Check parameter value
        int dary = 0;
        ss >> dary;
        if (dary <= 0)
        {
            std::cout << "Wrong parameter value!\n";
            return 0;
        }

        // Build the dary heap
        DaryHeap daryHeap = DaryHeap(vect, heap_size, dary);

        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        City *maximum = daryHeap.dary_extract_max();
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for dary_extract_max: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        outFile << *maximum << "\n";
        outFile.close();
    }
    else if (func == "dary_insert_element")
    {
        // Insert element takes d as argument and k argument so total arguments are 6
        if (argc < 6)
        {
            std::cout << "Not enough arguments!\n";
            return 0;
        }
        // Check the letters of arguments first
        char par1 = argv[4][0];
        char par2 = argv[5][0];
        if ((par1 != 'k' || par2 != 'd') && (par1 != 'd' || par2 != 'k'))
        {
            std::cout << "Wrong parameter types!\n";
            return 0;
        }
        std::string city_parse;
        std::string dary_parse;
        // Parse arguments according to the parameter types
        if (par1 == 'k')
        {
            city_parse = argv[4];
            dary_parse = argv[5];
        }
        else
        {
            city_parse = argv[5];
            dary_parse = argv[4];
        }
        // Parse the arguments
        std::stringstream ss;
        ss << dary_parse;
        char d = '\0';
        ss >> d;
        // Check parameter type
        if (d != 'd')
        {
            std::cout << "Wrong parameter type!\n";
            return 0;
        }
        // Check parameter value
        int dary = 0;
        ss >> dary;
        if (dary <= 0)
        {
            std::cout << "Wrong parameter value!\n";
            return 0;
        }
        // Clearing the stringstream to parse the city
        ss.clear();
        // Parse the city
        // Found parsing technique from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
        size_t pos = 0;
        std::string delimiter = "_";
        // The first token is the argument type, which is checked already
        if ((pos = city_parse.find(delimiter)) != std::string::npos)
            city_parse.erase(0, pos + delimiter.length());

        // The second token is the city name
        std::string city = "";
        if ((pos = city_parse.find(delimiter)) != std::string::npos)
        {
            city = city_parse.substr(0, pos);
            city_parse.erase(0, pos + delimiter.length());
        }
        // The remaining string is the population
        int population = 0;
        ss << city_parse;
        ss >> population;
        // Check parameter value
        if (population <= 0 && city == "")
        {
            std::cout << "Wrong parameter value!\n";
            return 0;
        }

        // Build the dary heap
        DaryHeap daryHeap = DaryHeap(vect, heap_size, dary);
        City *newCity = new City{city, population};

        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        daryHeap.dary_insert_element(newCity);
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for dary_insert_element: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        daryHeap.print(outFile);
        outFile.close();

        // Deleting the new city to prevent memory leak
        // It is not in the original vector so it is not deleted in the end
        delete newCity;
    }
    else if (func == "dary_increase_key")
    {
        // dary, index and key should be provided
        if (argc < 7)
        {
            std::cout << "Not enough arguments!\n";
            return 0;
        }
        // Take the argv[4] and parse it
        std::stringstream ss;
        ss << argv[4];
        char par1 = '\0';
        ss >> par1;
        int val1 = 0;
        ss >> val1;
        // Clear ss to take parameter properly
        ss.clear();
        // Take the argv[5] and parse it
        ss << argv[5];
        char par2 = '\0';
        ss >> par2;
        int val2 = 0;
        ss >> val2;
        // Clear ss to take parameter properly
        ss.clear();
        // Take the argv[6] and parse it
        ss << argv[6];
        char par3 = '\0';
        ss >> par3;
        int val3 = 0;
        ss >> val3;
        // Check parameter types
        // all permutations
        // i, k, d
        // i, d, k
        // k, i, d
        // k, d, i
        // d, i, k
        // d, k, i
        if ((par1 != 'i' || par2 != 'k' || par3 != 'd') && (par1 != 'i' || par2 != 'd' || par3 != 'k') && (par1 != 'k' || par2 != 'i' || par3 != 'd') && (par1 != 'k' || par2 != 'd' || par3 != 'i') && (par1 != 'd' || par2 != 'i' || par3 != 'k') && (par1 != 'd' || par2 != 'k' || par3 != 'i'))
        {
            std::cout << "Wrong parameter types!\n";
            return 0;
        }
        // Take index
        int idx = 0;
        if (par1 == 'i')
            idx = val1;
        else if (par2 == 'i')
            idx = val2;
        else
            idx = val3;
        // Take key
        int key = 0;
        if (par1 == 'k')
            key = val1;
        else if (par2 == 'k')
            key = val2;
        else
            key = val3;
        // Take d
        int dary = 0;
        if (par1 == 'd')
            dary = val1;
        else if (par2 == 'd')
            dary = val2;
        else
            dary = val3;
        // Index can't be smaller or equal to 0
        if (idx <= 0)
        {
            std::cout << "Wrong parameter value!\n";
            return 0;
        }
        // Dary can't be smaller or equal to 0
        if (dary <= 0)
        {
            std::cout << "Wrong parameter value!\n";
            return 0;
        }

        // Build the dary heap
        DaryHeap daryHeap(vect, heap_size, dary);

        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        daryHeap.dary_increase_key(idx, key);
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for dary_increase_key: " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        daryHeap.print(outFile);
        outFile.close();
    }
    else if (func == "dary_heapsort")
    {
        // dary_heapsort takes d as argument so total argunents is 5
        if (argc < 5)
        {
            std::cout << "Not enough arguments!\n";
            return 0;
        }
        // Take the argv[4] and parse it
        std::stringstream ss;
        ss << argv[4];
        char d = '\0';
        ss >> d;
        // Check parameter type
        if (d != 'd')
        {
            std::cout << "Wrong parameter type!\n";
            return 0;
        }
        // Check parameter value
        int dary = 0;
        ss >> dary;
        if (dary <= 0)
        {
            std::cout << "Wrong parameter value!\n";
            return 0;
        }

        // Build the dary heap
        DaryHeap daryHeap = DaryHeap(vect, heap_size, dary);

        // Begin chronometer
        const auto beginChrono{std::chrono::steady_clock::now()};
        // Do the operation
        daryHeap.dary_heapsort();
        // End chronometer
        const auto endChrono{std::chrono::steady_clock::now()};
        const std::chrono::duration<int64_t, std::nano> timeTaken{endChrono - beginChrono};
        // Print chronometer results
        std::cout << "Time taken for dary_heapsort with d = " << dary << ": " << timeTaken.count() << " nanoseconds\n";

        // Print the result
        std::fstream outFile(outFileName, std::ios::out);
        assert(outFile.is_open());
        daryHeap.print(outFile);
        outFile.close();
    }
    else
    {
        std::cout << "Wrong function name!\n";
        return 0;
    }
    // Deleting the read values to prevent memory leak
    for (City *city : vect)
        if (city != NULL)
            delete city;

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

// BinaryHeap functions
void BinaryHeap::max_heapify(std::vector<City *> &vect, int heap_size, int idx)
{
    // idx should never be greater than heap size.
    // if it is equal to heap size, then it should stop.
    if (idx >= heap_size)
        return;

    // Initially, largest is the current index
    int largest = idx;

    // Checking the left index
    int left = BinaryHeap::left_child(idx);
    // left should be in the bouundaries and it should be larger than the previous largest
    if (left <= heap_size && vect[left]->mPopulation > vect[largest]->mPopulation)
        largest = left;

    // Checking the right index
    int right = BinaryHeap::right_child(idx);
    // right should be in the bouundaries and it should be larger than the previous largest
    if (right <= heap_size && vect[right]->mPopulation > vect[largest]->mPopulation)
        largest = right;

    // If the largest is not the current element, swap them and continue recursively to bottom.
    if (largest != idx)
    {
        City *temp = vect[largest];
        vect[largest] = vect[idx];
        vect[idx] = temp;
        max_heapify(vect, heap_size, largest);
    }
}

void BinaryHeap::build_max_heap(std::vector<City *> &vect, int heap_size)
{
    // heapifying should start from heap_size / 2, no need to heapify leaves
    int start_from = heap_size / 2;

    // from floor(heap_size / 2) to 1, do max_heapify
    for (int i = start_from; i > 0; i--)
        max_heapify(vect, heap_size, i);
}
void BinaryHeap::heap_sort(std::vector<City *> &vect, int heap_size)
{
    // First build max_heap
    build_max_heap(vect, heap_size);

    // From the last element to top of the heap, top element should be swapped and
    // put to the end and always, heap size should be decreased and heap should be heapified.
    for (int i = heap_size; i > 0; i--)
    {
        // swap the top with last element
        City *temp = vect[1];
        vect[1] = vect[i];
        vect[i] = temp;

        // decrease the heap size
        heap_size -= 1;

        // call heapify to the top
        max_heapify(vect, heap_size, 1);
    }
}

void BinaryHeap::print(const std::vector<City *> &vect, int heap_size, std::fstream &output)
{
    // Print using City's overloaded << operator
    for (int i = 1; i <= heap_size; i++)
        output << *vect[i] << '\n';
}

// Priority queue operations
City *PriorityQueue::heap_extract_max()
{
    // Assertion to check priority queue size
    assert(pq_size > 0);

    // Get the maximum element
    City *maximum = pq[1];

    // Swap the top element with bottom element and resize the pq to exclude the old maximum
    pq[1] = pq[pq_size];

    // Since it is a vector with 1 indexing, actual size is pq_size + 1 so resizing it to pq_size
    // will remove the redundant element
    pq.resize(pq_size);
    pq_size -= 1;

    // Then max_heapify the priority queue again to maintain heap structure
    max_heapify(pq, pq_size, 1);

    return maximum;
}

void PriorityQueue::max_heap_insert(City *new_element)
{
    // First, add the new element to the end of the priority queue and increase heap size.
    pq.push_back(new_element);
    pq_size += 1;

    // Then, work your way up to top
    int current_idx = pq_size;
    // Check the parent node and work your way up
    while (current_idx > 1 && pq[current_idx]->mPopulation > pq[parent(current_idx)]->mPopulation)
    {
        // Swap current with parent
        City *temp = pq[current_idx];
        pq[current_idx] = pq[parent(current_idx)];
        pq[parent(current_idx)] = temp;

        // update current idx
        current_idx = parent(current_idx);
    }
}

void PriorityQueue::print(std::fstream &output)
{
    BinaryHeap::print(pq, pq_size, output);
}

void PriorityQueue::heap_increase_key(int idx, int key)
{
    // Ckeck if the index is in range
    if (idx > pq_size)
    {
        std::cout << "Index is bigger than priority queue size.\n";
        return;
    }
    // Check if the key is bigger than the item
    if (pq[idx]->mPopulation > key)
    {
        std::cout << "Key value " << key << " is smaller than the City " << pq[idx]->mCity
                  << " at index " << idx << " with population " << pq[idx]->mPopulation << "\n";
        return;
    }

    // Update the value
    pq[idx]->mPopulation = key;

    // As in the insert element, work your way up the heap.
    int current_idx = idx;
    while (current_idx > 1 && pq[current_idx]->mPopulation > pq[parent(current_idx)]->mPopulation)
    {
        // Swap current with parent
        City *temp = pq[current_idx];
        pq[current_idx] = pq[parent(current_idx)];
        pq[parent(current_idx)] = temp;

        // update current idx
        current_idx = parent(current_idx);
    }
}

// Methods of the dary heap
int DaryHeap::dary_calculate_height(int dary_heap_size, int d)
{
    // Heihgt is 0 initially
    int height = 0;
    // limit is the limit of the heap size for that given height
    int limit = 1;
    // Increment is the increment value for the limit as the height increases
    int increment = d;
    // We try to find upper bound for the size of the heap
    while (limit < dary_heap_size)
    {
        // Increase the limit by increment
        limit += increment;
        // Multiply the increment by d to get it one level down
        increment *= d;
        // Increase the height
        height += 1;
    }
    return height;
}

int DaryHeap::parent(int children)
{
    // d = 5
    // 1 -> 2, 3, 4, 5, 6
    // 2 -> 7, 8, 9, 10, 11
    // 3 -> 12, 13, 14, 15, 16
    // 4 -> 17, 18, 19, 20, 21
    // 5 -> 22, 23, 24, 25, 26
    // 6 -> 27, 28, 29, 30, 31

    // d = 8
    // 1 -> 2,3,4,5,6,7,8,9
    // 2 -> 10,11,12,13,14,15,16,17
    // 3 -> 18,19,20,21,22,23,24,25
    // 4 -> 26,27,28,29,30,31,32,33
    // 5 -> 34,35,36,37,38,39,40,41
    // 6- > 42,43,44,45,46,47,48,49
    // 7 -> 50,51,52,53,54,55,56,57
    // 8 -> 58,59,60,61,62,63,64,65

    // childs = (p - 1)*d + 2, (p - 1)*d + 3, ..., (p - 1)*d + d + 1
    // parent = (c - 2)/d + 1

    // If check to put root to index 0, stop condition.
    if (children <= 1)
        return 0;

    return (children - 2) / d + 1;
}

std::vector<int> DaryHeap::children(int parent)
{
    // Check parent's value, it can't be less than 1
    if (parent < 1)
        // Return empty vector to prevent errors
        return std::vector<int>{};

    std::vector<int> children;

    // With the logic explained above, childs are located between these bounds
    int lower_bound = (parent - 1) * d + 2;
    int upper_bound = (parent - 1) * d + d + 1;
    for (int i = lower_bound; i <= upper_bound; i++)
        children.push_back(i);
    // Return a vector of the indexes of children
    return children;
}

void DaryHeap::dary_max_heapify(int idx)
{
    // Checking the bounds of the index
    // If it is equal to the size, it is a leaf, so stop
    if (idx >= dary_heap_size)
        return;

    std::vector<int> children_indexes = children(idx);
    // Initially, largest is the current index
    int largest = idx;
    for (int i = 0; i < (int)children_indexes.size(); i++)
    {
        int child = children_indexes[i];
        // Check if the child is in the boundaries
        // If it is out of bounds, no neet to look further.
        if (child > dary_heap_size)
            break;

        // Check if the child is larger than the previous largest
        if (dary_heap[child]->mPopulation > dary_heap[largest]->mPopulation)
            largest = child;
    }
    // If the largest is not the current element, swap them and continue recursively to bottom
    if (largest != idx)
    {
        City *temp = dary_heap[largest];
        dary_heap[largest] = dary_heap[idx];
        dary_heap[idx] = temp;
        dary_max_heapify(largest);
    }
}

void DaryHeap::build_dary_heap()
{
    // heapifying should start from the parent of the last leaf, no need to heapify leaves
    int start_from = parent(dary_heap_size);

    // from the last parent, to 1, do max_heapify
    for (int idx = start_from; idx >= 1; idx--)
        dary_max_heapify(idx);
}

void DaryHeap::dary_insert_element(City *newCity)
{
    // First, add the new element to the end of the dary heap heap size.
    dary_heap.push_back(newCity);
    dary_heap_size += 1;

    // Then, work your way up to top
    int current_idx = dary_heap_size;
    // Check the parent node and work your way up
    // Swap if current node is bigger than the parent node
    while (current_idx > 1 && dary_heap[current_idx]->mPopulation > dary_heap[parent(current_idx)]->mPopulation)
    {
        // Swap current with parent
        City *temp = dary_heap[current_idx];
        dary_heap[current_idx] = dary_heap[parent(current_idx)];
        dary_heap[parent(current_idx)] = temp;

        // update current idx as parent
        current_idx = parent(current_idx);
    }
}

void DaryHeap::dary_increase_key(int idx, int key)
{
    // Ckeck if the index is in range
    if (idx > dary_heap_size)
    {
        std::cout << "Index is bigger than dary heap size.\n";
        return;
    }
    // Check if the key is bigger than the item
    if (dary_heap[idx]->mPopulation > key)
    {
        std::cout << "Key value " << key << " is smaller than the City " << dary_heap[idx]->mCity
                  << " at index " << idx << " with population " << dary_heap[idx]->mPopulation << "\n";
        return;
    }

    // Update the value
    dary_heap[idx]->mPopulation = key;

    // As in the insert element, work your way up the heap.
    int current_idx = idx;
    while (current_idx > 1 && dary_heap[current_idx]->mPopulation > dary_heap[parent(current_idx)]->mPopulation)
    {
        // Swap current with parent
        City *temp = dary_heap[current_idx];
        dary_heap[current_idx] = dary_heap[parent(current_idx)];
        dary_heap[parent(current_idx)] = temp;

        // update current idx
        current_idx = parent(current_idx);
    }
}

void DaryHeap::print(std::fstream &output)
{
    // Binary heap's print function can't be used here since dary_heapsort will modify dary heap size
    for (unsigned int i = 1; i < dary_heap.size(); i++)
        output << *dary_heap[i] << "\n";
}

City *DaryHeap::dary_extract_max()
{
    // Assertion to check priority queue size
    assert(dary_heap_size > 0);

    // Get the maximum element
    City *maximum = dary_heap[1];

    // Swap the top element with bottom element and resize the dary_heap to exclude the old maximum
    dary_heap[1] = dary_heap[dary_heap_size];

    // Since it is a vector with 1 indexing, actual size is dary_heap_size + 1 so resizing it to dary_heap_size
    // will remove the redundant element
    dary_heap.resize(dary_heap_size);
    dary_heap_size -= 1;

    // Then max_heapify the priority queue again to maintain heap structure
    dary_max_heapify(1);

    return maximum;
}

void DaryHeap::dary_heapsort()
{
    // Dary heap is already built, so just do the heap sort

    // From the last element to top of the heap, top element should be swapped and
    // put to the end and always, heap size should be decreased and heap should be heapified.
    for (int i = dary_heap_size; i > 0; i--)
    {
        // swap the top with last element
        City *temp = dary_heap[1];
        dary_heap[1] = dary_heap[i];
        dary_heap[i] = temp;

        // decrease the heap size
        dary_heap_size -= 1;

        // call heapify to the top
        dary_max_heapify(1);
    }
}