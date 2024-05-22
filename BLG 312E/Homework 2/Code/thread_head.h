// Fatih Baskın
// 150210710

// Include guards
#ifndef SHOP_H
#define SHOP_H

// Included headers
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

// Constants
#define BALANCE_MIN 1
#define BALANCE_MAX 200
#define PRICE_MIN 1
#define PRICE_MAX 200
#define STOCK_MIN 1
#define STOCK_MAX 10
// For benchmarking customer and product counts must be set high
#define CUSTOMER_COUNT 5
#define PRODUCT_COUNT 8
#define ORDER_MIN 1
#define ORDER_MAX 5

// Product struct that holds the product info
typedef struct product
{
    // For threads this is for locking
    pthread_mutex_t product_Lock;
    // Product information
    unsigned int product_ID;
    double product_Price;
    unsigned int product_Quantity;
} Product;

// To initialize a product with parameters
Product *init_Product(unsigned int *global_ID, double price, unsigned int quantity);
// To initialize a product with random values
Product *init_Product_Random(unsigned int *global_ID);
// Product print fuction
void print_Product(Product *current);
void print_Products(Product *array[], unsigned int size);

// --------

// Product_Customer struct that holds minimal version of the product, with only id and quantity
typedef struct product_Customer
{
    unsigned int product_ID;
    unsigned int product_Quantity;
} Product_Customer;

// Product_Customer print fuctions
void print_Product_Customer(Product_Customer *current);
void print_Products_Customer(Product_Customer array[], unsigned int size);

// --------

// Customer struct that holds the customer info
typedef struct customer
{
    // Customer information
    unsigned int customer_ID;
    double customer_Balance;
    double initial_Balance;
    // Ordered items information, they are held in an array
    unsigned int ordered_Items_Counter;
    Product_Customer *ordered_Items;
    // Purchased items information, they are held in an array
    unsigned int purchased_Items_Counter;
    Product_Customer *purchased_Items;
} Customer;

// Customer initializer with arguements
Customer *init_Customer(unsigned int *global_ID, double balance);
// Customer initializer with random values
Customer *init_Customer_Random(unsigned int *global_ID);
// Customer print fuction
void print_Customer(Customer *current);

#endif