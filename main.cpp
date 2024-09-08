#include "functions.h"
#include <fstream>

 Product products[number_of_categories][products_per_category] = {
	{ {"ADDE", 49}, {"PO�NG", 309}, {"FLINTAN", 299.99f}, {"TEODORES", 125}, {"MARIUS", 25}}, //chairs
	{ {"LAGKAPTEN", 428}, {"UTESPELARE", 599.99f}, {"SANDSBERG", 179}, {"MITTZON", 799}, {"KNARREVIK", 39}}, //tables
	{ {"LERBERG", 89}, {"KALLAX", 299}, {"LACK", 299}, {"FR�SJ�N", 99}, {"FRYKS�S", 149}} //shelves
};


void display_logo() {
	ifstream logo("logo.txt");
	string line;
	while (getline(logo, line))	cout << line << '\n';
	logo.close();
}

string calculate_time() {
	const int t = time(NULL);
	const int seconds = t % 60;
	const int minutes = (t % (60 * 60)) / 60;
	const int hours = (t % (60 * 60 * 60)) / 3600 + 7;//change time zone to UTC+7

	string times[number_of_categories] = {to_string(seconds), to_string(minutes), to_string((hours % 12) + 1)};
	for (int i = 0; i < number_of_categories; ++i) if (times[i].length() < 2) times[i].insert(0, "0");

	return times[2] + ':' + times[1] + ':' + times[0] + ((hours > 12) ? "PM" : "AM");
}

bool new_customer(int id) {

	display_table();

	cout << "\nCustomer " << id << '\n';
	cout << calculate_time() << '\n';

	int choice = 0;

	while (true) {
		cout << "\nActions\n"
			"1. Add Order\n"
			"2. Remove Order\n"
			"3. Display menu\n"
			"4. Show Invoice\n"
			"5. Cancel\n";
		choice = get_input("Enter next action[1-5]: ", 1, 5, "Invalid action, please try again");

		switch (choice) {
			case 1: // add order
				add_order();
				break;
			case 2: //remove order
				remove_order();
				break;
			case 3:
				display_table();
				break;
			case 4:
				if (invoice()) return true; //if receipt is generated and payment is made, return true
				break;
			case 5:
				return false; // cancel
			default:
				break;
		}
	}
}

int main() {
	display_logo();

	while (true) {
	cout << "\nWelcome!\n"
		"1. New Order Entry\n"
		"2. Report\n"
		"3. Exit\n";
		int choice = get_input("Please select an action[1-3]: ", 1, 3, "Invalid action, please try again"), customer_id = 0;

		switch (choice) {
			case 1:
				if (!new_customer(++customer_id)) --customer_id;
				break;
			case 2:
				report(customer_id);
				break;
			case 3:
				return 0; //exit
		}
	}
}