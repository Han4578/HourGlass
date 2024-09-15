#include "functions.h"

int get_input(string message, int min, int max, string invalid_message, bool escapable) {
	int input = 0;
	string invalid_input = "";
	while (true) {
		cout << message;
		cin >> input;
		cin.clear();
		getline(cin, invalid_input);

		if (escapable && input == 0 && (invalid_input == "Q" || invalid_input == "q")) return -1;
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
		input = toupper(input);
		if (input == 'Q') return -1;
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
	cout << "\nAdd order selected. Enter Q at any time to cancel.\n";
	const Order order = get_order(true);
	if (order.category == -1 || order.product_number == -1 || order.quantity == -1) return;

	products[order.category][order.product_number - 1].currently_ordered += order.quantity;
	if (products[order.category][order.product_number - 1].currently_ordered > 10) {
		cout << "Each product has a purchase limit of 10, the quantity for this product has been set to 10.\n";
		products[order.category][order.product_number - 1].currently_ordered = 10;
	}
	cout << "\nProduct " << products[order.category][order.product_number - 1].name << " has been added.\n";

	system("pause");
}

void remove_order() {
	cout << "\nRemove order selected. Enter -1 at any time to cancel.\n";
	const Order order = get_order(false);
	if (order.category == -1) return;

	if (products[order.category][order.product_number - 1].currently_ordered == 0) {
		cout << "\nProduct " << products[order.category][order.product_number - 1].name << " was not ordered.\n\n";
	} else {
		products[order.category][order.product_number - 1].currently_ordered = 0;
		cout << "\nProduct " << products[order.category][order.product_number - 1].name << " has been removed.\n\n";
	}

	system("pause");
}

void cancel_order() {
	system("cls");
	cout << "The 3 most recent orders are saved, please select the order you wish to cancel\n\n";
	int i = 0;

	for (i = 0; i < 3; ++i) {
		bool is_filled = false;
		for (int j = 0; j < number_of_categories; ++j) {
			for (int k = 0; k < products_per_category; ++k) {
				if (user.recent_orders[(user.order_index - i + 2) % 3][j][k] > 0) {
					is_filled = true;
					break;
				}
			}
			if (is_filled) break;
		}

		if (!is_filled) break;

		float total = 0;
		cout << "Order " << i + 1 << '\n';
		cout << setfill('_') << setw(22) << '_' << '\n';
		cout << setfill(' ') << "| Name " << "   | Quantity" << " |\n";
		for(int j = 0; j < number_of_categories; ++j) {
			for (int k = 0; k < products_per_category; ++k) {
				if (user.recent_orders[(user.order_index - i + 2) % 3][j][k] == 0) continue;

				cout << '|' << left << setw(9) << products[j][k].name << '|' << right << setw(10) << user.recent_orders[((user.order_index - i + 2) % 3) % 3][j][k] << "|\n";
				total += products[j][k].price * user.recent_orders[(user.order_index - i + 2) % 3][j][k];
			}
		}
		cout << '|' << setw(20) << setfill('_') << '_' << "|\n";
		cout << '|' << setw(10) << setfill(' ') << "Total: RM " << setw(10) << fixed << setprecision(2) << total << "|\n";
		cout << '|' << setw(20) << setfill('_') << '_' << "|\n\n";
	}
	if (i == 0) {
		cout << "There are no past orders saved\n\n";
		system("pause");
		return;
	}

	int order = get_input("Please enter order number to cancel, or press Q to return: ", 1, i, "Invalid input, please try again", true);
	if (order == -1) return;

	int index = (user.order_index - order + 3) % 3;

	for (int j = 0; j < number_of_categories; ++j) {
		for (int k = 0; k < products_per_category; ++k) {
			products[j][k].total_sold -= user.recent_orders[index][j][k];
		}
	}

	while (index != user.order_index) {
		for (int j = 0; j < number_of_categories; ++j) {
			for (int k = 0; k < products_per_category; ++k) {
				user.recent_orders[index][j][k] = user.recent_orders[(index - 1) % 3][j][k];
			}
		}
		index = (index - 1 + 3) % 3;
	}

	for (int j = 0; j < number_of_categories; ++j) {
		for (int k = 0; k < products_per_category; ++k) {
			user.recent_orders[index][j][k] = 0;
		}
	}
}