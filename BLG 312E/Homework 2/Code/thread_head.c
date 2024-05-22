// Fatih Baskın
// 150210710

// Included libraries
#include "thread_head.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

// To initialize a product with parameters
Product *init_Product(unsigned int *global_ID, double price, unsigned int quantity)
{
    Product *current = malloc(sizeof(Product));
    // Product takes the current value of global_ID counter and then global_ID is incremented
    current->product_ID = *global_ID;
    *global_ID += 1;
    // Mutex lock initialization
    pthread_mutex_init(&current->product_Lock, NULL);
    // Product price is defined as the price value in the range of PRICE_MIN and PRICE_MIN
    if (price < PRICE_MIN)
        current->product_Price = PRICE_MIN;
    else if (price > PRICE_MAX)
        current->product_Price = PRICE_MAX;
    else
        current->product_Price = price;
    // Product quantity is defined as the quantity value in the range of STOCK_MIN and STOCK_MAX
    if (quantity < STOCK_MIN)
        current->product_Quantity = STOCK_MIN;
    else if (quantity > STOCK_MAX)
        current->product_Quantity = STOCK_MAX;
    else
        current->product_Quantity = quantity;
    // Finally, return current
    return current;
}
// To initialize a product with random values
Product *init_Product_Random(unsigned int *global_ID)
{
    Product *current = malloc(sizeof(Product));
    // Product takes the current value of global_ID counter and then global_ID is incremented
    current->product_ID = *global_ID;
    *global_ID += 1;
    // Mutex lock initialization
    pthread_mutex_init(&current->product_Lock, NULL);
    // Random price calculation is done here:
    {
        // 1) Get a value between 0 and 1
        double random_value = (double)rand() / (double)RAND_MAX;
        // 2) Expand it to interval of PRICE_MIN and PRICE_MAX
        random_value = random_value * (PRICE_MAX - PRICE_MIN) + PRICE_MIN;
        // 3) Append the value to product_Price
        current->product_Price = random_value;
    }
    // Random stock calculation is done here:
    {
        // 1) Take a random value in range of 0 to STOCK_MAX - STOCK_MIN
        unsigned int random_value = (unsigned int)rand() % (STOCK_MAX - STOCK_MIN + 1);
        // 2) Add STOCK_MIN to random value to expand this number's range from STOCK_MIN to STOCK_MAX
        random_value = random_value + STOCK_MIN;
        // 3) Append the value to product_Quantity
        current->product_Quantity = random_value;
    }
    // Finally, return current
    return current;
}

// Product print fuction
void print_Product(Product *current)
{
    // Padding for print function is in accordance with main print_Products function
    printf("%-10d  %-8d  %.2lf\n", current->product_ID, current->product_Quantity, current->product_Price);
}

// Product print from array fuction
void print_Products(Product *array[], unsigned int size)
{
    printf("Product ID  Quantity  Price\n");
    for (int i = 0; i != size; i++)
        print_Product(array[i]);
}

// --------

// Product_Customer print fuction
void print_Product_Customer(Product_Customer *current)
{
    // Padding for print function is in accordance with main print_Products function
    printf("%-10d  %-8d\n", current->product_ID, current->product_Quantity);
}

// Product_Customer print from array fuction
void print_Products_Customer(Product_Customer array[], unsigned int size)
{
    printf("Product ID  Quantity\n");
    if (size != 0)
    {
        for (int i = 0; i != size; i++)
            print_Product_Customer(&array[i]);
    }
    else
        printf("-No data--  -No data\n");
}

// --------

// Customer initializer with arguements
Customer *init_Customer(unsigned int *global_ID, double balance)
{
    Customer *current = malloc(sizeof(Customer));
    // Customer takes the current value of global_ID counter and then global_ID is incremented
    current->customer_ID = *global_ID;
    *global_ID += 1;
    // Customer balance is defined as the balance value in the range of BALANCE_MIN and BALANCE_MAX
    if (balance < BALANCE_MIN)
        current->customer_Balance = BALANCE_MIN;
    else if (balance > BALANCE_MAX)
        current->customer_Balance = BALANCE_MAX;
    else
        current->customer_Balance = balance;
    // initial_Balance is set
    current->initial_Balance = current->customer_Balance;
    // Array sizes are defined as zero and arrays have null pointers
    current->ordered_Items_Counter = 0;
    current->purchased_Items_Counter = 0;
    current->purchased_Items = NULL;
    current->ordered_Items = NULL;
    // Finally, return current
    return current;
}

// Customer initializer with random values
Customer *init_Customer_Random(unsigned int *global_ID)
{
    // Memory allocation for Customer
    Customer *current = malloc(sizeof(Customer));
    // Customer takes the current value of global_ID counter and then global_ID is incremented
    current->customer_ID = *global_ID;
    *global_ID += 1;
    // Random balance calculation is done here:
    {
        // 1) Get a value between 0 and 1
        double random_value = (double)rand() / (double)RAND_MAX;
        // 2) Expand it to interval of BALANCE_MIN and BALANCE_MAX
        random_value = random_value * (BALANCE_MAX - BALANCE_MIN) + BALANCE_MIN;
        // 3) Append the value to customer_Balance
        current->customer_Balance = random_value;
        // initial_Balance is set
        current->initial_Balance = current->customer_Balance;
    }
    // Randomly generating ordered items list
    // This will hold how much random items do we have.
    unsigned int rand_count = 0;
    // This is very crutial because it will be used for randomization process
    unsigned int last_rand = 0;
    // This will hold the quantites required
    unsigned int order_array[PRODUCT_COUNT];
    for (int i = 0; i < PRODUCT_COUNT; i++)
        order_array[i] = 0;
    // Randomization process
    while (1)
    {
        // This will give a number from last_rand to PRODUCT_COUNT + last_rand - 1
        unsigned int product_random = rand() % (PRODUCT_COUNT) + last_rand;
        // Break if generated number is out of bounds
        if (product_random >= PRODUCT_COUNT)
            break;
        // Increment rand count, this is the number of elements in the ordered_Products array
        rand_count++;
        // Now pick a random data which will give quatity of the ordered item
        order_array[product_random] = (rand() % (ORDER_MAX - ORDER_MIN + 1)) + ORDER_MIN;
        // And incrementing product random to not include current random
        last_rand = product_random + 1;
    }
    // Initializing customer ordered items array and counter
    current->ordered_Items_Counter = rand_count;
    current->ordered_Items = malloc(sizeof(Product_Customer) * rand_count);
    // This is used for iterating over ordered_items array
    int itemsItr = 0;
    for (int i = 0; i < PRODUCT_COUNT; i++)
    {
        if (order_array[i] != 0)
        {
            current->ordered_Items[itemsItr].product_ID = i + 1;
            current->ordered_Items[itemsItr].product_Quantity = order_array[i];
            itemsItr += 1;
        }
    }
    // Purchased items array and counter are defined as NULL and 0
    current->purchased_Items = NULL;
    current->purchased_Items_Counter = 0;
    // Finally, return current
    return current;
}

// Customer print fuction
void print_Customer(Customer *current)
{
    printf("Customer ID: %d, initial balance: %.2lf, current balance: %.2lf\n", current->customer_ID, current->initial_Balance, current->customer_Balance);
    printf("Ordered items:\n");
    print_Products_Customer(current->ordered_Items, current->ordered_Items_Counter);
    printf("Purchased items:\n");
    print_Products_Customer(current->purchased_Items, current->purchased_Items_Counter);
}
