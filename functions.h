#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
using namespace std;

struct Product {
	string name = "";
	float price = 0;
	int currently_ordered = 0, total_sold = 0;
};

const int number_of_categories = 3, products_per_category = 5, recently_ordered_limit = 3;

struct Customer {
	string name = "";
	string password;
	int cart[number_of_categories][products_per_category] = {0};
	int recent_orders[recently_ordered_limit][number_of_categories][products_per_category] = {0};
	int order_index = 0;
};


extern Product products[number_of_categories][products_per_category];

extern Customer user;

const string categories[number_of_categories] = { "Chairs", "Tables", "Shelves" };


int get_input(string message, int min, int max, string invalid_message, bool escapable);

bool get_bool(string message, string error);

void add_order();

void remove_order();

void cancel_order();

void display_table();

bool invoice();

void report();

void import();

string calculate_time();