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

const int number_of_categories = 3, products_per_category = 5;

extern Product products[number_of_categories][products_per_category];

const string categories[number_of_categories] = { "Chairs", "Tables", "Shelves" };


int get_input(string message, int min, int max, string invalid_message);

void add_order();

void remove_order();

void display_table();

bool invoice();

void report(int customers);

void import();

string calculate_time();