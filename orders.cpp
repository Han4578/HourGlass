#include "functions.h"

int get_input(string message, int min, int max, string invalid_message, bool escapable) {
	int input = 0;
	string invalid_input = "";
	while (true) {
		cout << message;
		cin >> input;
		cin.clear();
		getline(cin, invalid_input);

		if (escapable && input == 0) return -1;
		if (input > min - 1 && input < max + 1) break;
		cout << '\n' << invalid_message << "\n\n";
	}
	return input;
}

int get_input(string message, char min, char max, string invalid_message) {
	char input = 0;
	string invalid_input = "";
	while (true) {
		cout << message;
		cin >> input;
		cin.clear();
		getline(cin, invalid_input);
		if (input == '0') return -1;
		input = toupper(input);
		if (input > min - 1 && input < max + 1) break;
		cout << '\n' << invalid_message << "\n\n";
	}
	return input - min;
}

struct Order {
	int category = 0, product_number = 0, quantity = 0;
};

Order get_order(bool get_quantity) {
	const int category = get_input("Enter Category[A-C]:", 'A', 'C', "Invalid category, please try again.");
	if (category == -1) return { -1 };
	const int product_number = get_input("Enter Product Number[1-5]:", 1, 5, "Invalid product number, please try again.", true);
	if (product_number == -1) return { -1 };
	const int quantity = (get_quantity) ? get_input("Enter Quantity[1-10]:", 1, 10, "Invalid quantity, please try again.", true) : 0;
	if (quantity == -1) return { -1 };

	return { category, product_number, quantity };
}

void add_order() {
	cout << "\nAdd order selected. Enter 0 at any time to cancel.\n";
	const Order order = get_order(true);
	if (order.category == -1 || order.product_number == -1 || order.quantity == -1) return;

	products[order.category][order.product_number - 1].currently_ordered += order.quantity;
	if (products[order.category][order.product_number - 1].currently_ordered > 10) {
		cout << "Each product has a purchase limit of 10, the quantity for this product has been set to 10.\n";
		products[order.category][order.product_number - 1].currently_ordered = 10;
	}
	cout << "\nProduct " << products[order.category][order.product_number - 1].name << " has been added.\n";
}

void remove_order() {
	cout << "\nRemove order selected. Enter 0 at any time to cancel.\n";
	const Order order = get_order(false);
	if (order.category == -1) return;

	if (products[order.category][order.product_number - 1].currently_ordered == 0) {
		cout << "\nProduct " << products[order.category][order.product_number - 1].name << " was not ordered.\n";
	} else {
		products[order.category][order.product_number - 1].currently_ordered = 0;
		cout << "\nProduct " << products[order.category][order.product_number - 1].name << " has been removed.\n";
	}
}