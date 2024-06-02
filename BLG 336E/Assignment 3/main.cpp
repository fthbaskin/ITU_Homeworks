/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 3
 * Fatih Baskın
 * 150210710
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
// These libraries are used to manage floors and rooms easily
#include <set>
#include <map>
// This library is used to round the decimal part of the double values
#include <cmath>

/* YOU CAN INCLUDE ANY OTHER NECESSARY LIBRARIES */

/* YOU CAN DEFINE EXTRA FUNCTIONS AND MODIFY THE CODE TEMPLATE */

/* YOU HAVE TO CONSIDER THE OUTPUT FORMAT TO TEST YOUR CODE WITH CALICO */

using namespace std;

// This function is used to print double values with the specified format.
string print_double(double value)
{
    // Adding small values to the double values to prevent floating point errors
    value += 0.01;

    string number_representation;
    // Take the part before the point.
    int integer_part = (int)value;
    // Append the part into the number representation
    number_representation += to_string(integer_part);
    // Append the point
    number_representation += ".";
    // Take the part after the point.
    double decimal_part = value - integer_part;
    // Round the decimal part to 1 digit.
    decimal_part = round(decimal_part * 10) / 10;
    // Append the decimal part into the number representation
    int decimal_part_int = (int)(decimal_part * 10);
    number_representation += to_string(decimal_part_int);
    return number_representation;
}

// Time struct to represent time in HH:MM format
struct Time
{
    uint8_t hour;
    uint8_t minute;
    // Default constructor
    Time() {}
    // Constructor
    Time(uint8_t h, uint8_t m) : hour(h), minute(m) {}
    // Operator overload << to print
    friend ostream &operator<<(ostream &os, const Time &time)
    {
        if (time.hour < 10)
            os << "0";
        os << (int)time.hour << ":";
        if (time.minute < 10)
            os << "0";
        os << (int)time.minute;
        return os;
    }
    // Operator overload >> to read from file easily
    friend istream &operator>>(istream &is, Time &time)
    {
        // Read HH:MM
        string str;
        is >> str;
        // Parse HH:MM
        stringstream ss(str);
        string token;
        // Get hour
        getline(ss, token, ':');
        time.hour = stoi(token);
        // Get minute
        getline(ss, token, ':');
        time.minute = stoi(token);
        return is;
    }
    // Function to convert time to minutes
    int to_minutes() const
    {
        return (int)hour * 60 + (int)minute;
    }
};

struct TimeIntervals
{
    string floor;
    string room;
    Time start;
    Time end;
    // Default constructor
    TimeIntervals() {}
    // Constructor
    TimeIntervals(string f, string r, Time s, Time e) : floor(f), room(r), start(s), end(e) {}
    // Operator overload >> to read from file easily
    friend istream &operator>>(istream &is, TimeIntervals &time_intervals)
    {
        is >> time_intervals.floor >> time_intervals.room >> time_intervals.start >> time_intervals.end;
        return is;
    }
};

struct Priority
{
    string floor;
    string room;
    int priority;
    // Default constructor
    Priority() {}
    // Constructor
    Priority(string f, string r, int p) : floor(f), room(r), priority(p) {}
    // Opeator overlaod >> to read from file easily
    friend istream &operator>>(istream &is, Priority &priority)
    {
        is >> priority.floor >> priority.room >> priority.priority;
        return is;
    }
};

struct Item
{
    string name;
    int price;
    double value;
    // Default constructor
    Item() {}
    // Constructor
    Item(string n, int p, double v) : name(n), price(p), value(v) {}
    // Overload operator >> to read from file easily
    friend istream &operator>>(istream &is, Item &item)
    {
        is >> item.name >> item.price >> item.value;
        return is;
    }
};

// To read files easily, this function is used
template <typename T>
vector<T> read_file(const string &path)
{
    vector<T> data;
    ifstream file(path);
    // Check if file is open
    if (!file.is_open())
    {
        cerr << "Error: " << path << " could not be opened." << endl;
        exit(1);
    }
    // Skip the first line
    string line;
    getline(file, line);
    line.clear();
    // Read the rest of the file
    while (getline(file, line))
    {
        stringstream ss(line);
        T t;
        ss >> t;
        data.push_back(t);
    }
    return data;
}

/* START: WEIGHTED INTERVAL SCHEDULING (for each floor) */

struct Schedule
{
    string room;
    Time start;
    Time end;
    int priority;
    // Default constructor
    Schedule() {}
    // Constructor
    Schedule(string r, Time s, Time e, int p) : room(r), start(s), end(e), priority(p) {}
    // Operator overload << to print in specified format
    friend ostream &operator<<(ostream &os, const Schedule &schedule)
    {
        os << schedule.room << '\t' << schedule.start << '\t' << schedule.end;
        return os;
    }
    // Sort the schedules by end time
    static bool compare_end_time(const Schedule &a, const Schedule &b)
    {
        return a.end.to_minutes() < b.end.to_minutes();
    }
};

// function to find the best schedule for each floor
vector<Schedule> weighted_interval_scheduling(vector<Schedule> schedules)
{
    // Some preprocessing is needed to use the weighted interval scheduling algorithm
    // Sort the schedules by end time
    sort(schedules.begin(), schedules.end(), Schedule::compare_end_time);

    int num_schedules = (int)schedules.size();

    // Vector to hold previously compatible schedule's index for each schedule
    vector<int> compatible_schedule(num_schedules, -1);
    for (int i = 1; i < num_schedules; i++)
    {
        int current_start_time = schedules[i].start.to_minutes();
        for (int j = i - 1; j >= 0; j--)
        {
            int previous_end_time = schedules[j].end.to_minutes();
            if (previous_end_time <= current_start_time)
            {
                compatible_schedule[i] = j;
                break;
            }
        }
    }

    // Dynammic programming table to store the solution until schedule i
    vector<double> dynammic_programming(num_schedules, 0);
    // Base case, the first schedule has the highest priority by itself
    dynammic_programming[0] = schedules[0].priority;

    // Calculate the optimal schedule for schedules until i using the previous compatible schedule
    for (int i = 1; i < num_schedules; i++)
    {
        // Calculate the value of the current schedule
        int current_priority = schedules[i].priority;
        // If there is a compatible schedule, add value of the optimal solution until the compatible schedule to the current schedule
        int priority_with_current = current_priority;
        if (compatible_schedule[i] != -1)
            priority_with_current += dynammic_programming[compatible_schedule[i]];
        // Calculate the value without the current schedule
        int priority_without_current = dynammic_programming[i - 1];
        // Select the schedule if it is more valuable
        dynammic_programming[i] = max(priority_with_current, priority_without_current);
    }

    // Vector to store the optimal schedules
    vector<Schedule> optimal_schedules;

    // Backtrack to find the selected schedules
    int i = num_schedules - 1;
    while (i >= 0)
    {
        // If the current schedule is selected, add it to the optimal schedules
        // Current schedule is selected if the value of the current schedule is different than the value of the previous schedule
        if (i == 0 || dynammic_programming[i] != dynammic_programming[i - 1])
        {
            optimal_schedules.push_back(schedules[i]);
            // Move to the previous compatible schedule
            i = compatible_schedule[i];
        }
        else
            i--;
    }

    // Optimal schedules are in the reverse order, sort them to give true output.
    sort(optimal_schedules.begin(), optimal_schedules.end(), Schedule::compare_end_time);

    return optimal_schedules;
}

// *** END ***

/* START: KNAPSACK (for items) */

// Function to select the most valuable items that can be purchased with a certain budget
vector<Item> knapsack(const vector<Item> &Items, int budget)
{
    // Get the number of items
    int num_items = (int)Items.size();

    vector<Item> selected_items;

    // Knapsack table, rows = item i, columns = budget b
    vector<vector<double>> dynamic_programming(num_items + 1, vector<double>(budget + 1, 0));

    // For budget b at item i, we need to check budget b - price of item i at i - 1
    for (int i = 1; i <= (int)num_items; i++)
    {
        int item_index = i - 1;
        int current_price = Items[item_index].price;
        for (int b = 1; b <= budget; b++)
        {
            int previous_budget = b - current_price;
            // Check if b - price of item i is less than 0
            if (previous_budget < 0)
            {
                // If so, we cannot select the item since we don't have enough budget to purchase it
                dynamic_programming[i][b] = dynamic_programming[i - 1][b];
                continue;
            }
            // Calculate the best value for the current budget
            double value_with_item = dynamic_programming[i - 1][previous_budget] + Items[item_index].value;
            double value_without_item = dynamic_programming[i - 1][b];
            // Select the item if it is more valuable
            dynamic_programming[i][b] = max(value_with_item, value_without_item);
        }
    }

    // Find the selected items by backtracking
    int b = budget;
    for (int i = num_items; i > 0; i--)
    {
        int item_index = i - 1;
        int current_price = Items[item_index].price;
        // Check if the value of the current item is selected
        // If current value is equal to the value of the previous item, it means the item is not selected
        // If not, it means the item is selected
        if (dynamic_programming[i][b] != dynamic_programming[i - 1][b])
        {
            // If so, add the item to the selected items
            selected_items.push_back(Items[item_index]);
            // Update the budget
            b -= current_price;
        }
    }

    return selected_items;
}

// *** END ***

int main(int argc, char *argv[])
{
    // TODO: Change to read from command line.
    string case_no = argv[1];
    string case_name = "case_" + case_no;
    string path = "./inputs/" + case_name;

    int total_budget = 200000;

    // Path to the input files
    const string time_intervals_path = path + "/room_time_intervals.txt";
    const string priorities_path = path + "/priority.txt";
    const string items_path = path + "/items.txt";

    // Vectors to store the data
    vector<TimeIntervals> time_intervals = read_file<TimeIntervals>(time_intervals_path);
    vector<Priority> priorities = read_file<Priority>(priorities_path);
    vector<Item> items = read_file<Item>(items_path);

    // Some preprocessing is needed to use the weighted interval scheduling algorithm
    // For each floor, we need to create schedules containing room, start time, end time and priority
    // Map is a key-value pair data structure using a red-black tree
    // This map is for storing priority of room x in floor y
    map<string, map<string, int>> floor_room_priority;
    for (const auto &priority : priorities)
        floor_room_priority[priority.floor][priority.room] = priority.priority;

    // Using the floor_room_priority map, we can create schedules for each floor
    map<string, vector<Schedule>> schedules;
    for (const auto &time_interval : time_intervals)
    {
        // Get the floor, room, start time, end time and priority
        string floor = time_interval.floor;
        string room = time_interval.room;
        Time start = time_interval.start;
        Time end = time_interval.end;
        int priority = floor_room_priority[floor][room];
        // Add the schedule to the schedules of the floor
        schedules[floor].emplace_back(room, start, end, priority);
    }

    // Call the weighted interval scheduling function for each floor
    map<string, vector<Schedule>> optimal_schedules;
    // Iterator will have the floor and the schedules of the floor (key - value) as pair
    for (const auto &floor_schedule : schedules)
    {
        string floor = floor_schedule.first;
        vector<Schedule> floor_schedules = floor_schedule.second;
        vector<Schedule> optimal_floor_schedules = weighted_interval_scheduling(floor_schedules);
        optimal_schedules[floor] = optimal_floor_schedules;
    }

    // Print the optimal schedules
    cout << "Best Schedule for Each Floor";
    for (const auto &optimal_schedules_floor : optimal_schedules)
    {
        string floor = optimal_schedules_floor.first;
        int sum_priority = 0;
        for (const auto &schedule : optimal_schedules_floor.second)
            sum_priority += schedule.priority;

        vector<Schedule> floor_schedules = optimal_schedules_floor.second;
        cout << floor << " --> Priority Gain: " << sum_priority << endl;
        for (const auto &schedule : floor_schedules)
            cout << floor << "\t" << schedule << endl;
    }
    // TODO: Print the optimal schedules in the specified format

    // Call the knapsack function to find the selected items
    vector<Item> selected_items = knapsack(items, total_budget);
    // Get the total value of the selected items
    double total_value = 0;
    for (const auto &item : selected_items)
        total_value += item.value;

    // Print the selected items with using the print_double function
    cout << "Best Use of Budget" << endl
         << "Total Value --> " << print_double(total_value) << endl;

    for (const auto &item : selected_items)
        cout << item.name << endl;

    return 0;
}