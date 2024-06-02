/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 1
 * Fatih Baskın
 * 150210710
 */

/* * * * * * * * * * * * * * * * * *
 * DO NOT MODIFY UNLESS REQUESTED  *
 * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <chrono> // For time measurement

/* INCLUDE ANY OTHER NECESSARY LIBRARIES HERE */
/* START YOUR CODE HERE */

#include <cstring> // For memset

/* END YOUR CODE HERE */

using namespace std;
using namespace std::chrono;

/* USE HERE IF YOU NEED TO DEFINE EXTRA FUNCTIONS */
/* START YOUR CODE HERE */

/**
 * @struct CompareColonies
 * @brief CompareColonies struct is used to compare the colonies in the priority queue in descending order by overloading the operator().
 */
struct CompareColonies
{
    /**
     * @brief Overload the operator for the priority queue to sort the colonies in descending order.
     *
     * @param a
     * @param b
     * @return true
     * @return false
     */
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)
    {
        // If the colony sizes are equal, compare the resource types (> will return smallest one in heap)
        if (a.first == b.first)
            return a.second > b.second;
        // Return the largest colony type (< will return largest one in heap)
        return a.first < b.first;
    }
};

/**
 * @brief Get the up coordinate of the given coordinate in circular manner.
 *
 * @param coordinate pair<int, int> coordinate
 * @param row_max number of rows in the map
 * @param col_max number of columns in the map
 * @return pair<int, int> up coordinate in circular manner
 */
inline pair<int, int> get_up_coordinate(pair<int, int> &coordinate, int row_max, int col_max)
{
    int row = (coordinate.first + row_max - 1) % row_max;
    int col = coordinate.second;
    return make_pair(row, col);
}

/**
 * @brief Get the down coordinate of the given coordinate in circular manner.
 *
 * @param coordinate pair<int, int> coordinate
 * @param row_max number of rows in the map
 * @param col_max number of columns in the map
 * @return pair<int, int> down coordinate in circular manner
 */
inline pair<int, int> get_down_coordinate(pair<int, int> &coordinate, int row_max, int col_max)
{
    int row = (coordinate.first + 1) % row_max;
    int col = coordinate.second;
    return make_pair(row, col);
}

/**
 * @brief Get the left coordinate of the given coordinate in circular manner.
 *
 * @param coordinate pair<int, int> coordinate
 * @param row_max number of rows in the map
 * @param col_max number of columns in the map
 * @return pair<int, int> left coordinate in circular manner
 */
inline pair<int, int> get_left_coordinate(pair<int, int> &coordinate, int row_max, int col_max)
{
    int row = coordinate.first;
    int col = (coordinate.second + col_max - 1) % col_max;
    return make_pair(row, col);
}

/**
 * @brief Get the right coordinate of the given coordinate in circular manner.
 *
 * @param coordinate pair<int, int> coordinate
 * @param row_max number of rows in the map
 * @param col_max number of columns in the map
 * @return pair<int, int> right coordinate in circular manner
 */
inline pair<int, int> get_right_coordinate(pair<int, int> &coordinate, int row_max, int col_max)
{
    int row = coordinate.first;
    int col = (coordinate.second + 1) % col_max;
    return make_pair(row, col);
}

/* END YOUR CODE HERE */

/**
 * Perform Depth-First Search (DFS) traversal on a map.
 *
 * @param map The map represented as a 2D vector of integers.
 * @param row The starting row index for the DFS traversal.
 * @param col The starting column index for the DFS traversal.
 * @param resource The resource value to search for during the traversal.
 * @return The size of the colony found during the DFS traversal.
 */
int dfs(vector<vector<int>> &map, int row, int col, int resource)
{

    /* START YOUR CODE HERE */

    // Return 0 if the map is empty
    // Return 0 if the starting cell is out of the map
    // Return 0 if the starting cell is not the resource type
    // Return 0 if the starting cell is already visited
    // Return positive integer if the size of the colony is found

    // Modify the map to mark the visited cells, for visited, I will use -1

    // Get the map dimensions
    int row_max = map.size();
    int col_max = map[0].size();

    // If the map is empty, return 0
    if (row_max == 0 || col_max == 0)
        return 0;

    // If the starting cell is out of the map, return 0
    if (row < 0 || row >= row_max || col < 0 || col >= col_max)
        return 0;

    // If the starting cell is not the resource type, return 0
    if (map[row][col] != resource)
        return 0;

    // Check if the starting cell is already visited, for visited, I will use 0
    if (map[row][col] == -1)
        // If it is already visited, return 0
        return 0;

    // Mark the current cell as visited
    map[row][col] = -1;

    // Used for the size of the colony, initially 1
    pair<int, int> current_coordinate = make_pair(row, col);

    // Get the up, down, left and right cells of the current coordinate
    pair<int, int> up = get_up_coordinate(current_coordinate, row_max, col_max);
    pair<int, int> down = get_down_coordinate(current_coordinate, row_max, col_max);
    pair<int, int> left = get_left_coordinate(current_coordinate, row_max, col_max);
    pair<int, int> right = get_right_coordinate(current_coordinate, row_max, col_max);

    // Since the current cell is the resource type, initialize the colony size as 1
    int colony_size = 1;

    // For each neighbouring cell, if the cell is not visited and the cell is the resource type,
    // call the dfs function and add the size of the colony to the current colony size
    if (map[up.first][up.second] != -1 && map[up.first][up.second] == resource)
        colony_size += dfs(map, up.first, up.second, resource);
    if (map[down.first][down.second] != -1 && map[down.first][down.second] == resource)
        colony_size += dfs(map, down.first, down.second, resource);
    if (map[left.first][left.second] != -1 && map[left.first][left.second] == resource)
        colony_size += dfs(map, left.first, left.second, resource);
    if (map[right.first][right.second] != -1 && map[right.first][right.second] == resource)
        colony_size += dfs(map, right.first, right.second, resource);

    // Return the size of the colony
    return colony_size;

    /* END YOUR CODE HERE */
}

/**
 * Perform Breadth-First Search (BFS) traversal on a map.
 *
 * @param map The map represented as a 2D vector of integers.
 * @param row The starting row index for the BFS traversal.
 * @param col The starting column index for the BFS traversal.
 * @param resource The resource value to search for during the traversal.
 * @return The size of the colony found during the BFS traversal.
 */
int bfs(vector<vector<int>> &map, int row, int col, int resource)
{

    /* START YOUR CODE HERE */

    // Return 0 if the map is empty
    // Return 0 if the starting cell is out of the map
    // Return 0 if the starting cell is not the resource type
    // Return 0 if the starting cell is already visited
    // Return positive integer if the size of the colony is found

    // Modify the map to mark the visited cells, for visited, I will use -1

    // Get the map dimensions
    int row_max = map.size();
    int col_max = map[0].size();

    // If the map is empty, return 0
    if (row_max == 0 || col_max == 0)
        return 0;

    // If the starting cell is out of the map, return 0
    if (row < 0 || row >= row_max || col < 0 || col >= col_max)
        return 0;

    // If the starting cell is not the resource type, return 0
    if (map[row][col] != resource)
        return 0;

    // Check if the starting cell is already visited, for visited, I will use 0
    if (map[row][col] == -1)
        // If it is already visited, return 0
        return 0;

    // Used for the bfs queue
    queue<pair<int, int>> bfs_queue;

    // Used for the size of the colony, initially 0
    int colony_size = 0;
    // Push the starting cell to the queue
    bfs_queue.emplace(row, col);
    // Mark the starting cell as visited prematurely
    map[row][col] = -1;

    // While the queue is not empty, do bfs until the queue is empty
    while (!bfs_queue.empty())
    {
        // Get the current cell from the queue and pop it
        pair<int, int> current_coordinate = bfs_queue.front();
        bfs_queue.pop();

        // Increase the size of the colony
        colony_size++;

        // Get the up, down, left and right cells of the current coordinate
        pair<int, int> up = get_up_coordinate(current_coordinate, row_max, col_max);
        pair<int, int> down = get_down_coordinate(current_coordinate, row_max, col_max);
        pair<int, int> left = get_left_coordinate(current_coordinate, row_max, col_max);
        pair<int, int> right = get_right_coordinate(current_coordinate, row_max, col_max);

        // For each neighbouring cell, if the cell is not visited and the cell is the resource type, push the cell to the queue
        // Also mark them as visited prematurely
        if (map[up.first][up.second] != -1 && map[up.first][up.second] == resource)
        {
            bfs_queue.emplace(up.first, up.second);
            map[up.first][up.second] = -1;
        }
        if (map[down.first][down.second] != -1 && map[down.first][down.second] == resource)
        {
            bfs_queue.emplace(down.first, down.second);
            map[down.first][down.second] = -1;
        }
        if (map[left.first][left.second] != -1 && map[left.first][left.second] == resource)
        {
            bfs_queue.emplace(left.first, left.second);
            map[left.first][left.second] = -1;
        }
        if (map[right.first][right.second] != -1 && map[right.first][right.second] == resource)
        {
            bfs_queue.emplace(right.first, right.second);
            map[right.first][right.second] = -1;
        }
    }

    // Return the size of the colony
    return colony_size;

    /* END YOUR CODE HERE */
}

/**
 * Finds the top-k largest colonies in a given map.
 *
 * @param map The map represented as a 2D vector of integers.
 * @param useDFS A boolean flag indicating whether to use Depth-First Search (DFS) or Breadth-First Search (BFS) algorithm.
 * @param k The number of top colonies to find.
 * @return A vector of pairs representing the size and resource type of the top-k largest colonies.
 */
vector<pair<int, int>> top_k_largest_colonies(vector<vector<int>> &map, bool useDFS, unsigned int k)
{

    auto start = high_resolution_clock::now(); // Start measuring time

    /* START YOUR CODE HERE */

    // First: colony size, Second: resource type
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareColonies> colonies;

    // Find all the colonies in the map
    for (unsigned int x_coordinate = 0; x_coordinate < map.size(); x_coordinate++)
    {
        for (unsigned int y_coordinate = 0; y_coordinate < map[0].size(); y_coordinate++)
        {
            if (map[x_coordinate][y_coordinate] != -1)
            {
                int colony_size = 0;
                int resource_type = map[x_coordinate][y_coordinate];
                if (useDFS)
                    colony_size = dfs(map, x_coordinate, y_coordinate, resource_type);
                else
                    colony_size = bfs(map, x_coordinate, y_coordinate, resource_type);

                if (colony_size > 0)
                    colonies.emplace(colony_size, resource_type);
            }
        }
    }

    /* END YOUR CODE HERE */

    auto stop = high_resolution_clock::now();                 // Stop measuring time
    auto duration = duration_cast<nanoseconds>(stop - start); // Calculate the duration
    cout << "Time taken: " << duration.count() << " nanoseconds" << endl;

    /* START YOUR CODE HERE */

    // Answer, the top-k largest colonies
    vector<pair<int, int>> top_k_colonies;

    // Get the top-k largest colonies
    while (!colonies.empty() && top_k_colonies.size() < k)
    {
        top_k_colonies.push_back(colonies.top());
        colonies.pop();
    }

    // Return the top-k largest colonies
    return top_k_colonies;

    /* END YOUR CODE HERE */
}

// Main function
int main(int argc, char *argv[])
{

    // Check the command line arguments
    if (argc != 4)
    {

        // It should be: <1 or 0> <k> <filename.txt>
        cerr << "Usage: " << argv[0] << " <1 or 0> <k> <filename.txt>" << endl;
        return 1;
    }

    // Get the arguments
    bool useDFS = (atoi(argv[1]) == 1);
    int k = atoi(argv[2]);

    // Read the map from the text file
    string filename = argv[3];
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    vector<vector<int>> sector_map;
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        vector<int> row;
        int num;
        while (iss >> num)
        {
            row.push_back(num);
        }
        sector_map.push_back(row);
    }
    file.close();

    // Find the largest colony
    vector<pair<int, int>> result = top_k_largest_colonies(sector_map, useDFS, k);

    // Print the result
    cout << "Algorithm: " << (useDFS ? "DFS" : "BFS") << endl;
    cout << "Map: " << filename << endl;

    // If no colonies are found
    if (result.empty())
    {
        cout << "No colonies found." << endl;
        return 0;
    }

    // Print the top-k colonies
    for (size_t i = 0; i < result.size(); ++i)
    {
        cout << "Colony " << i + 1 << ": Size = " << result[i].first << ", Resource Type = " << result[i].second << endl;
    }

    return 0;
}