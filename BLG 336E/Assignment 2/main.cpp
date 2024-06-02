/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 2
 * Fatih Baskın
 * 150210710
 */

#include <iostream>  // For input/output
#include <cmath>     // For distance calculations
#include <vector>    // For vector operations
#include <algorithm> // For sorting operations
#include <limits>    // For min(), max() functions
#include <fstream>   // To read/write files
#include <chrono>    // For time measurement

//(These libraries are sufficient for this assignment.)

using namespace std;

// Structure to represent a point in 2D space
struct Point
{
    double x, y;
};

// Helper function to calculate distance between two points
double distance(Point p1, Point p2)
{

    // YOUR CODE HERE

    // Get x and y coordinates differances.
    double x_diff = p1.x - p2.x;
    double y_diff = p1.y - p2.y;

    // Return euclidean distance
    return sqrt((x_diff * x_diff) + (y_diff * y_diff));
}

// Helper function to compare points based on x-coordinate, can use this for sorting.
bool compareX(Point p1, Point p2)
{

    // YOUR CODE HERE

    // Return boolean result of the smaller operator on x coordinates.
    return p1.x < p2.x;
}

// Helper function to compare points based on y-coordinate, can use this for sorting.
bool compareY(Point p1, Point p2)
{

    // YOUR CODE HERE

    // Return boolean result of the smaller operator on y coordinates.
    return p1.y < p2.y;
}

// Function to find the closest pair of points using brute force.
pair<Point, Point> bruteForceClosestPair(vector<Point> &points, int start, int end)
{

    // YOUR CODE HERE

    // Initially, minimum distance pair is undefined and minimum distance is infinity;
    double min_dist = __DBL_MAX__;
    pair<Point, Point> min_pair = {{-1, -1}, {-1, -1}};

    // Then, try each combination of points in range [start, end] to get pair with minimum distance
    for (int i = start; i <= end; i++)
    {
        for (int j = i + 1; j <= end; j++)
        {
            // Calculate distance of current pair
            double curr_dist = distance(points[i], points[j]);
            // If current pair distance is smaller than the previous minimum, set current pair as minimum
            if (curr_dist < min_dist)
            {
                // Update min dist
                min_dist = curr_dist;

                // Take current points
                Point p1 = points[i];
                Point p2 = points[j];

                // While saving the current pair, save smallest y, x first
                if (p1.y < p2.y)
                    min_pair = {p1, p2};
                else if (p1.y == p2.y)
                {
                    if (p1.x < p2.x)
                        min_pair = {p1, p2};
                    else
                        min_pair = {p2, p1};
                }
                else
                    min_pair = {p2, p1};
            }
        }
    }

    return min_pair;
}

// The main objective of the assignment. This is the function to find the closest pair of points recursively using divide and conquer.
pair<Point, Point> closestPair(vector<Point> &points, int start, int end)
{

    // YOUR CODE HERE

    // Base case: start > end, there are 0 elements
    if (start > end)
        // Return invalid pair
        return {{-1, -1}, {-1, -1}};

    // Base case: start == end, there are 1 element
    if (start == end)
        // Return single point and invalid point
        return {points[start], {-1, -1}};

    // Base case: 2 elements
    if (start + 1 == end)
    {
        // Take these points
        Point p1 = points[start];
        Point p2 = points[end];

        // While saving the current pair, save smallest y, x first
        if (p1.y < p2.y)
            return {p1, p2};
        else if (p1.y == p2.y)
        {
            if (p1.x < p2.x)
                return {p1, p2};
            else
                return {p2, p1};
        }
        else
            return {p2, p1};
    }

    // Base case: 3 elements, 3 combinations, use brute force, can be considered O(1)
    if (start + 2 == end)
        // Use brute force to return closest pair of 3
        return bruteForceClosestPair(points, start, end);

    // Mid point to divide array into two
    int mid = (start + end) / 2;

    // Calculate the closest pair for left half and right half
    pair<Point, Point> pair_l = closestPair(points, start, mid);
    double delta_l = distance(pair_l.first, pair_l.second);

    pair<Point, Point> pair_r = closestPair(points, mid + 1, end);
    double delta_r = distance(pair_r.first, pair_r.second);

    // Get the minimum delta from left and right halves
    double delta_min = min(delta_l, delta_r);

    // Determine the elements that are delta distance away fom the mid point considering x coordinate
    Point mid_point = points[mid];
    vector<Point> strip;

    for (int i = start; i <= end; i++)
    {
        Point p = points[i];

        // If current point's X coordinate is mid - delta <= x <= mid + delta range, add it to strip
        if (p.x <= (delta_min + mid_point.x) && p.x >= (mid_point.x - delta_min))
            strip.push_back(p);
    }

    // Calculate the minimum pair from left and right halves
    pair<Point, Point> min_pair;
    if (delta_l <= delta_r)
        min_pair = pair_l;
    else
        min_pair = pair_r;

    // Then, determine the minimum pair using the strip.
    // If strip consists of only one element, then skip this step.
    if (strip.size() > 1)
    {
        // First, sort the strip about elements' y coordinate
        sort(strip.begin(), strip.end(), compareY);

        // Then compare a point with its next 7 elements
        for (int i = 0; i < (int)strip.size(); i++)
        {
            // The limit of compared elements is the strip size or i + 8 (next 7 elements are i + 1, i + 2 ... i + 7)
            for (int j = i + 1; j < min((int)strip.size(), i + 8); j++)
            {
                // Take the current points
                Point p1 = strip[i];
                Point p2 = strip[j];

                // Calculate distance of current pair
                double curr_dist = distance(p1, p2);
                // If current pair distance is smaller than the previous minimum, set current pair as minimum
                if (curr_dist < delta_min)
                {
                    // Update delta min
                    delta_min = curr_dist;

                    // While saving the current pair, save smallest y, x first
                    if (p1.y < p2.y)
                        min_pair = {p1, p2};
                    else if (p1.y == p2.y)
                    {
                        if (p1.x < p2.x)
                            min_pair = {p1, p2};
                        else
                            min_pair = {p2, p1};
                    }
                    else
                        min_pair = {p2, p1};
                }
            }
        }
    }

    // Return the minimum pair.
    return min_pair;
}

// Function to remove a pair of points from the point vector. Returns the newly formed vector.
vector<Point> removePairFromVector(vector<Point> &point_vector, pair<Point, Point> point_pair)
{

    // YOUR CODE HERE

    // A vector to save points that are not in the pair.
    vector<Point> updated_points;

    for (Point p : point_vector)
    {
        // If a point is not in the pair, add it to the new vector.
        if (p.x == point_pair.first.x && p.y == point_pair.first.y)
            continue;

        if (p.x == point_pair.second.x && p.y == point_pair.second.y)
            continue;

        updated_points.push_back(p);
    }

    return updated_points;
}

// This function should wrap up the entire algorithm. It should:
//    1- Find the closest pair
//    2- Add the pair to the "pairs" vector
//    3- Remove the paired result from the map
// at each iteration.
// Then it should set "unconnected" variable as the final, unconnected city (if it exists).
void findClosestPairOrder(vector<Point> points)
{
    vector<pair<Point, Point>> pairs; // add your pairs to this vector
    Point unconnected = {-1, -1};     // set this as the unconnected point if it exists, leave as is otherwise.

    // YOUR CODE HERE

    // before printing, please make sure that within each pair, the city with the smaller y coordinate is printed first...
    //...if the y coordinates are the same, print the city with the smaller x coordinate first.

    // Timer begin
    // auto begin = chrono::high_resolution_clock::now();

    // First, sort the array about x coordinates
    sort(points.begin(), points.end(), compareX);

    // Until there are 0 or 1 points left, find closest pair, save it and remove it from the points
    while (points.size() > 1)
    {
        // pair<Point, Point> closest_pair = bruteForceClosestPair(points, 0, points.size() - 1);

        // Get the closest pair using recursive divide and conquer algorithm.
        pair<Point, Point> closest_pair = closestPair(points, 0, points.size() - 1);
        // Save the closest pair and remove it from the elements
        pairs.push_back(closest_pair);
        points = removePairFromVector(points, closest_pair);
    }

    // If there is one point left in the points, set it as unconnected
    if (points.size() == 1)
        unconnected = points[0];

    // Timer end
    // auto end = chrono::high_resolution_clock::now();
    // auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    // cout << "Algorithm took " << duration.count() << " nanoseconds." << endl;

    // This part prints the output, don't modify.
    for (size_t i = 0; i < pairs.size(); i++)
    {
        cout << "Pair " << i + 1 << ": " << pairs[i].first.x << ", " << pairs[i].first.y << " - " << pairs[i].second.x << ", " << pairs[i].second.y << endl;
    }
    if (unconnected.x != -1)
    {
        cout << "Unconnected " << unconnected.x << ", " << unconnected.y;
    }
}

// Read the coordinates from the file and convert them to a vector. Return the vector as a "vector<Point>"
vector<Point> readCoordinatesFromFile(const string &filename)
{
    vector<Point> points;

    // YOUR CODE HERE

    // Open a input file stream.
    ifstream read_file(filename);

    // Error check.
    if (!read_file.is_open())
    {
        cout << "Error reading file!";
        exit(1);
    }

    double x, y;

    // Read x, y coordinates.
    while (read_file >> x >> y)
    {
        // Initialize a point and push it to the vector.
        Point read_point{x, y};
        points.push_back(read_point);
    }

    return points;
}

// Main function. Ideally, you don't need to modify this.
int main(int argc, char *argv[])
{
    vector<Point> points = readCoordinatesFromFile(argv[1]);
    findClosestPairOrder(points);
    return 0;
}
