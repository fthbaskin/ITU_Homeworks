// Fatih Baskın
// 150210710

// Included libraries
#include "thread_head.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

// Global counters
unsigned int global_Customer_ID = 1;
unsigned int global_Product_ID = 1;

// Customers and products are kept as global
Customer *customer_Array[CUSTOMER_COUNT];
Product *product_Array[PRODUCT_COUNT];

// Global locks
pthread_mutex_t printlock = PTHREAD_MUTEX_INITIALIZER;

// Functions for freeing products and customers
void free_All();

// Multithread functions
// Single buy function, Product_Customer contains Product ID and Quantity to be purchased
bool order_Product(Product_Customer *order, double *balance, unsigned int ID);

// Multiple buy function, order is now as an array
bool *order_Products(Product_Customer *order_Array, unsigned int order_Size, double *balance, unsigned int ID);

// Threaded customer function
void customer_Thread(Customer *current);

int main()
{
    // Setting the seed for rand
    srand(time(NULL));

    // Initializing a randomized customer array
    for (int i = 0; i != CUSTOMER_COUNT; i++)
        customer_Array[i] = init_Customer_Random(&global_Customer_ID);
    // Initializing a randomized product array
    for (int i = 0; i != PRODUCT_COUNT; i++)
        product_Array[i] = init_Product_Random(&global_Product_ID);

    // Creating customer threads
    pthread_t customer_Thread_IDs[CUSTOMER_COUNT];
    for (int i = 0; i < CUSTOMER_COUNT; i++)
        pthread_create(&customer_Thread_IDs[i], NULL, (void *)customer_Thread, (void *)customer_Array[i]);

    // Joining customer threads, waiting for them to end
    for (int i = 0; i < CUSTOMER_COUNT; i++)
        pthread_join(customer_Thread_IDs[i], NULL);

    // Printing final customer data
    printf("Final customer data:\n");
    for (int i = 0; i != CUSTOMER_COUNT; i++)
        print_Customer(customer_Array[i]);

    // Freeing customers and products to prevent memory leak
    free_All();

    return 0;
}

void free_All()
{
    for (int i = 0; i != CUSTOMER_COUNT; i++)
    {
        // Freeing customers individually (they are allocated on heap)
        // They require special attention because they also hold some data as an array
        free(customer_Array[i]->ordered_Items);
        free(customer_Array[i]->purchased_Items);
        free(customer_Array[i]);
        customer_Array[i] = NULL;
    }
    for (int i = 0; i != PRODUCT_COUNT; i++)
    {
        // Freeing products individually (they are allocated on heap)
        free(product_Array[i]);
        product_Array[i] = NULL;
    }
}

void customer_Thread(Customer *current)
{
    // Case for single transaction
    if (current->ordered_Items_Counter == 1)
    {
        // Transaction flag
        bool successful_Transaction = false;
        successful_Transaction = order_Product(current->ordered_Items, &current->customer_Balance, current->customer_ID);
        // Successful transaction
        if (successful_Transaction)
        {
            // Create ordered items from scratch
            current->purchased_Items_Counter = 1;
            current->purchased_Items = malloc(sizeof(Product_Customer));
            current->purchased_Items->product_ID = current->ordered_Items->product_ID;
            current->purchased_Items->product_Quantity = current->ordered_Items->product_Quantity;
        }
    } // Case for multiple transactions
    else
    {
        bool *transactions = order_Products(current->ordered_Items, current->ordered_Items_Counter, &current->customer_Balance, current->customer_ID);
        unsigned int successful_Counter = 0;
        for (unsigned int i = 0; i < current->ordered_Items_Counter; i++)
            if (transactions[i])
                successful_Counter += 1;
        // After counting successful transactions allocate space for purchased_Items
        current->purchased_Items_Counter = successful_Counter;
        current->purchased_Items = malloc(sizeof(Product_Customer) * successful_Counter);
        // Then, fill purchased_Items data
        int purchased_Itr = 0;
        for (unsigned int i = 0; i < current->ordered_Items_Counter; i++)
        {
            if (transactions[i])
            {
                current->purchased_Items[purchased_Itr].product_ID = current->ordered_Items[i].product_ID;
                current->purchased_Items[purchased_Itr].product_Quantity = current->ordered_Items[i].product_Quantity;
                purchased_Itr += 1;
            }
        }
        // free transactions in the end to prevent memory leak
        free(transactions);
    }
}

bool order_Product(Product_Customer *order, double *balance, unsigned int customer_ID)
{

    // Array is 0 indexed, so our wanted product is at ID - 1'th index
    Product *wanted_Product = product_Array[order->product_ID - 1];

    // Firstly, doing the balance check, if customer balance is not enough, there is no need to do locking
    double paid_Amount = wanted_Product->product_Price * order->product_Quantity;
    if (*balance < paid_Amount)
    {
        // Print current transaction message (using printlock)
        pthread_mutex_lock(&printlock);
        printf("Customer %d (%d,%d) fail! Insufficient funds.\n", customer_ID, order->product_ID, order->product_Quantity);
        pthread_mutex_unlock(&printlock);
        return false;
    }
    // If balance check is successful, then do inventory checks and modifications while locked because another thread can modify it while we are doing checks and modifications
    pthread_mutex_lock(&wanted_Product->product_Lock);
    if (order->product_Quantity > wanted_Product->product_Quantity)
    {
        // Release the lock if there are not enough stocks
        pthread_mutex_unlock(&wanted_Product->product_Lock);
        // Print message (using print lock) and result is false
        pthread_mutex_lock(&printlock);
        printf("Customer %d (%d,%d) fail! Only %d left in stock.\n", customer_ID, order->product_ID, order->product_Quantity, wanted_Product->product_Quantity);
        pthread_mutex_unlock(&printlock);
        return false;
    }
    // If there are enough stocks, just continue without releasing the lock and release it finally
    // Print initial products data with using print lock
    pthread_mutex_lock(&printlock);
    printf("Customer %d:\n", customer_ID);
    printf("Initial products:\n");
    print_Products(product_Array, PRODUCT_COUNT);
    // Uptade wanted product quantity (while being locked), update customer balance then print message
    wanted_Product->product_Quantity -= order->product_Quantity;
    *balance -= paid_Amount;
    printf("Bought %d of product %d for $%.2lf\n", order->product_Quantity, order->product_ID, paid_Amount);
    // Print final products data with using print lock and relase lock
    printf("Updated products:\n");
    print_Products(product_Array, PRODUCT_COUNT);
    pthread_mutex_unlock(&printlock);
    // Print final message
    printf("Customer %d (%d,%d) success! Paid $%.2lf for each.\n", customer_ID, order->product_ID, order->product_Quantity, wanted_Product->product_Price);
    // After checks and modifications (if needed), release product lock
    pthread_mutex_unlock(&wanted_Product->product_Lock);
    return true;
}

bool *order_Products(Product_Customer *order_Array, unsigned int order_Size, double *balance, unsigned int ID)
{
    // This array will return a bool array, which will be used to construct purchased items (will hold successful transactions)
    bool *transactions = malloc(order_Size * sizeof(bool));
    for (int i = 0; i < order_Size; i++)
        transactions[i] = order_Product(&order_Array[i], balance, ID);
    // order_Product is very useful, that function will evaluate everything by itself.
    return transactions;
}