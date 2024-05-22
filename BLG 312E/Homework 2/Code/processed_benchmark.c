// Fatih Baskın
// 150210710

// Included libraries
#include "process_head.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/wait.h>

// Global counters, these are not required to be in the shared memory
unsigned int global_Customer_ID = 1;
unsigned int global_Product_ID = 1;

// Customers and products are kept as global, they will point to shared memory addresses
Customer *customer_Array[CUSTOMER_COUNT];
Product *product_Array[PRODUCT_COUNT];

// Global lock, this lock will point to shared memory address which contains printlock.
pthread_mutex_t *printlock;

// Functions for releasing shared memory for products and customers
void release_All();

// Multiprocess functions
// Single buy function, Product_Customer contains Product ID and Quantity to be purchased
bool order_Product(Product_Customer *order, double *balance, unsigned int ID);

// Multiple buy function, order is now as an array
bool *order_Products(Product_Customer *order_Array, unsigned int order_Size, double *balance, unsigned int ID);

// customer Process function
void customer_Process(Customer *current);

int main()
{
    // These are for benchmarking
    struct timespec ts1;
    struct timespec ts2;
    timespec_get(&ts1, TIME_UTC);
    // This will continue at the bottom of the program

    // Setting the seed for rand
    srand(0);

    // Printlock is being set in shared memory
    printlock = mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(printlock, &attr);

    // Initializing a randomized customer array (constructors return shared memory adresses)
    for (int i = 0; i != CUSTOMER_COUNT; i++)
        customer_Array[i] = init_Customer_Random(&global_Customer_ID);
    // Initializing a randomized product array (constructors return shared memory adresses)
    for (int i = 0; i != PRODUCT_COUNT; i++)
        product_Array[i] = init_Product_Random(&global_Product_ID);

    // Creating customer processes
    pid_t customer_Process_IDs[CUSTOMER_COUNT];
    for (int i = 0; i < CUSTOMER_COUNT; i++)
    {
        // Forking, if fork returns 0, this is a child process
        customer_Process_IDs[i] = fork();
        if (customer_Process_IDs[i] == 0)
        {
            // Child process directly enters customer_Process, meanwhile parent process continues in the loop.
            customer_Process(customer_Array[i]);
        }
    }

    // Waiting customer processes to end then set their purchased items accordingly
    for (int i = 0; i < CUSTOMER_COUNT; i++)
    {
        // Waiting for specific child pid to end
        waitpid(customer_Process_IDs[i], NULL, 0);
    }

    // Printing final customer data
    // printf("Final customer data:\n");
    // for (int i = 0; i != CUSTOMER_COUNT; i++)
    // print_Customer(customer_Array[i]);

    // Freeing (releasing shared memory) customers and products to prevent memory leak
    release_All();

    // For benchmarking (continue)
    timespec_get(&ts2, TIME_UTC);
    // Take the difference of timespamps and convert to microseconds
    int microSeconds = ((int)(ts2.tv_sec - ts1.tv_sec) * 1000000) + ((int)(ts2.tv_nsec - ts1.tv_nsec) / 1000);
    FILE *file;
    file = fopen("benchmark.txt", "a");
    fprintf(file, "Processed benchmark with %d customers and %d products lasted for %d microseconds.\n", CUSTOMER_COUNT, PRODUCT_COUNT, microSeconds);
    fclose(file);
    return 0;
}

void release_All()
{
    // Since these are using shared memory, shared memory requires to be released with a special way
    for (int i = 0; i != CUSTOMER_COUNT; i++)
    {
        Customer *current = customer_Array[i];
        // Then its subitems purchased_Items and ordered_Items are allocated via shared memory
        munmap(current->ordered_Items, sizeof(Product_Customer) * current->ordered_Items_Counter);
        // purchased_Items were preallocated during initialization with the size of ordered_Items_Counter
        munmap(current->purchased_Items, sizeof(Product_Customer) * current->ordered_Items_Counter);
        // Finally, current customer is allocated vie shared memory
        munmap(current, sizeof(Customer));
    }
    for (int i = 0; i != PRODUCT_COUNT; i++)
    {
        // Products are allocated via shared memory
        munmap(product_Array[i], sizeof(Product));
    }
    // Finally, print lock is released, it was allocated via shared memory
    munmap(printlock, sizeof(pthread_mutex_t));
}

void customer_Process(Customer *current)
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
            // Unlike the threaded one, space was preallocated.
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
        // After counting successful transactions, set the counter
        current->purchased_Items_Counter = successful_Counter;
        // Then, fill purchased_Items data, unlike threaded there is no need to reallocate memory since purchased_Items were preallocated
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
    // To prevent this process to continue in main, process must end here.
    exit(EXIT_SUCCESS);
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
        pthread_mutex_lock(printlock);
        // printf("Customer %d (%d,%d) fail! Insufficient funds.\n", customer_ID, order->product_ID, order->product_Quantity);
        pthread_mutex_unlock(printlock);
        return false;
    }
    // If balance check is successful, then do inventory checks and modifications while locked because another thread can modify it while we are doing checks and modifications
    pthread_mutex_lock(&wanted_Product->product_Lock);
    if (order->product_Quantity > wanted_Product->product_Quantity)
    {
        // Release the lock if there are not enough stocks
        pthread_mutex_unlock(&wanted_Product->product_Lock);
        // Print message (using print lock) and result is false
        pthread_mutex_lock(printlock);
        // printf("Customer %d (%d,%d) fail! Only %d left in stock.\n", customer_ID, order->product_ID, order->product_Quantity, wanted_Product->product_Quantity);
        pthread_mutex_unlock(printlock);
        return false;
    }
    // If there are enough stocks, just continue without releasing the lock and release it finally
    // Print initial products data with using print lock
    pthread_mutex_lock(printlock);
    // printf("Customer %d:\n", customer_ID);
    // printf("Initial products:\n");
    // print_Products(product_Array, PRODUCT_COUNT);
    // Uptade wanted product quantity (while being locked), update customer balance then print message
    wanted_Product->product_Quantity -= order->product_Quantity;
    *balance -= paid_Amount;
    // printf("Bought %d of product %d for $%.2lf\n", order->product_Quantity, order->product_ID, paid_Amount);
    // Print final products data with using print lock and relase lock
    // printf("Updated products:\n");
    // print_Products(product_Array, PRODUCT_COUNT);
    // Print final message
    // printf("Customer %d (%d,%d) success! Paid $%.2lf for each.\n", customer_ID, order->product_ID, order->product_Quantity, wanted_Product->product_Price);
    pthread_mutex_unlock(printlock);
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