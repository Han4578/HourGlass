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

bool get_bool(string message, string error) {
	string answer = "";
	while (answer != "Y" && answer != "N" && answer != "y" && answer != "n") {
		cout << message << endl;
		getline(cin, answer);
		if (answer != "Y" && answer != "N" && answer != "y" && answer != "n") cout << error << endl;
	}
	return answer == "Y" || answer == "y";
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
	int index = 0;

	while (true) {
		system("cls");
		cout << "The " << recently_ordered_limit << " most recent orders are saved, please select the order you wish to cancel\n\n";
		int i = 0;
		
		for (i = 0; i < recently_ordered_limit; ++i) {
			bool is_filled = false;
			for (int j = 0; j < number_of_categories; ++j) {
				for (int k = 0; k < products_per_category; ++k) {
					if (user.recent_orders[(user.order_index - i + recently_ordered_limit - 1) % recently_ordered_limit][j][k] > 0) { //check for past orders
						is_filled = true;
						break;
					}
				}
				if (is_filled) break;
			}

			if (!is_filled) break;

			float total = 0;
			cout << "Order " << i + 1 << '\n';											//lists orders from newest to oldest regardless of index
			cout << setfill('_') << setw(22) << '_' << '\n';
			cout << setfill(' ') << "| Name " << "   | Quantity" << " |\n";
			for (int j = 0; j < number_of_categories; ++j) {
				for (int k = 0; k < products_per_category; ++k) {
					if (user.recent_orders[(user.order_index - i + recently_ordered_limit - 1) % recently_ordered_limit][j][k] == 0) continue;

					cout << '|' << left << setw(9) << products[j][k].name << '|' << right << setw(10) << user.recent_orders[((user.order_index - i + recently_ordered_limit - 1) % recently_ordered_limit) % recently_ordered_limit][j][k] << "|\n";
					total += products[j][k].price * user.recent_orders[(user.order_index - i + recently_ordered_limit - 1) % recently_ordered_limit][j][k];
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
		index = (user.order_index - order + recently_ordered_limit) % recently_ordered_limit;		//get actual index of the order selected as order number is relative to order index
		float total = 0;

		cout << "Order " << order << '\n';
		cout << setfill('_') << setw(22) << '_' << '\n';
		cout << setfill(' ') << "| Name " << "   | Quantity" << " |\n";
		for (int j = 0; j < number_of_categories; ++j) {
			for (int k = 0; k < products_per_category; ++k) {
				if (user.recent_orders[index][j][k] == 0) continue;

				cout << '|' << left << setw(9) << products[j][k].name << '|' << right << setw(10) << user.recent_orders[(index) % recently_ordered_limit][j][k] << "|\n";
				total += products[j][k].price * user.recent_orders[index][j][k];
			}
		}
		cout << '|' << setw(20) << setfill('_') << '_' << "|\n";
		cout << '|' << setw(10) << setfill(' ') << "Total: RM " << setw(10) << fixed << setprecision(2) << total << "|\n";
		cout << '|' << setw(20) << setfill('_') << '_' << "|\n\n";

		if (get_bool("Confirm cancel? [Y/N]", "Invalid input, please try again")) break;
	}

	for (int j = 0; j < number_of_categories; ++j) {						//reduce total sold based on cancelled order
		for (int k = 0; k < products_per_category; ++k) {
			products[j][k].total_sold -= user.recent_orders[index][j][k];
		}
	}

	while (index != user.order_index) {										//shift all orders older than the cancelled order to the left so order
		for (int j = 0; j < number_of_categories; ++j) {					//index inserts the next order into the empty slot instead of replacing
			for (int k = 0; k < products_per_category; ++k) {
				user.recent_orders[index][j][k] = user.recent_orders[(index - 1 + recently_ordered_limit) % recently_ordered_limit][j][k];
			}
		}
		index = (index - 1 + recently_ordered_limit) % recently_ordered_limit;
	}

	for (int j = 0; j < number_of_categories; ++j) {						//clear the slot of order index
		for (int k = 0; k < products_per_category; ++k) {
			user.recent_orders[index][j][k] = 0;
		}
	}
}