#include "functions.h"
#include <fstream>

 Product products[number_of_categories][products_per_category] = {
	{ {"ADDE", 49}, {"POÄNG", 309}, {"FLINTAN", 299.99f}, {"TEODORES", 125}, {"MARIUS", 25}}, //chairs
	{ {"LAGKAPTEN", 428}, {"UTESPELARE", 599.99f}, {"SANDSBERG", 179}, {"MITTZON", 799}, {"KNARREVIK", 39}}, //tables
	{ {"LERBERG", 89}, {"KALLAX", 299}, {"LACK", 299}, {"FRÖSJÖN", 99}, {"FRYKSÅS", 149}} //shelves
};

 Customer users[20] = { "admin", "password" };
 Customer user = { "Bob", "hi", {}, {{1, 2, 3, 4}, {2, 3, 4,5 }, {5, 6, 7, 8} } , 1};

void display_logo() {
	ifstream logo("logo.dat");
	
	if (!logo) {
		cout << "Error opening file to display logo\n";
		return;
	}
	
	string line;
	while (getline(logo, line)) cout << line << '\n';
	logo.close();
}

string calculate_time() {
	const int t = time(NULL);
	const int seconds = t % 60;
	const int minutes = (t % (60 * 60)) / 60;
	const int hours = ((t % (60 * 60 * 60)) / 3600 + 7) % 24;//change time zone to UTC+7

	string times[number_of_categories] = {to_string(seconds), to_string(minutes), to_string((hours % 12) + 1)};
	for (int i = 0; i < number_of_categories; ++i) if (times[i].length() < 2) times[i].insert(0, "0");

	return times[2] + ':' + times[1] + ':' + times[0] + ((hours >= 11) ? "PM" : "AM");
}

void new_customer() {
	while (true) {
		system("cls");
		display_table();

		cout << calculate_time() << '\n';

		int choice = 0;
		cout << "\nActions\n"
			"1. Add to Cart\n"
			"2. Remove from Cart\n"
			"3. Clear Cart\n"
			"4. Show Invoice\n"
			"5. Cancel\n";
		choice = get_input("Enter next action[1-5]: ", 1, 5, "Invalid action, please try again", false);
		cout << '\n';
		switch (choice) {
			case 1: // add order
				add_to_cart();
				break;
			case 2: //remove order
				remove_from_cart();
				break;
			case 3: //remove order
				clear_cart();
				break;
			case 4:
				if (invoice()) return; //if receipt is generated and payment is made, return true
				break;
			case 5:
				for (int i = 0; i < number_of_categories; ++i) {
					for (int j = 0; j < products_per_category; ++j) {
						products[i][j].currently_ordered = 0;
					}
				}
				return; // cancel
			default:
				break;
		}
	}
}

int main() {
	while (true) {
		system("cls");
		display_logo();
		cout << "\nWelcome!\n"
				"1. New Order Entry\n"
				"2. Cancel Order\n"
				"3. Log Out\n"
				"4. Exit\n";
		int choice = get_input("Please select an action[1-3]: ", 1, 4, "Invalid action, please try again", false);
		cout << '\n';
	
		switch (choice) {
			case 1:
				new_customer();
				break;
			case 2:
				cancel_order();
				break;
			case 3:
				return 0; //exit
			case 4:
				return 0; //exit
		}
	}

	//while (true) {
	//	system("cls");
	//	display_logo();
	//	cout << "\nWelcome!\n"
	//			"1. Report\n"
	//			"2. Import\n"
	//			"3. Log Out\n"
	//			"4. Exit\n";
	//	int choice = get_input("Please select an action[1-4]: ", 1, 4, "Invalid action, please try again", false), customer_id = 0;
	//	cout << '\n';

	//	switch (choice) {
	//		case 1:
	//			report();
	//			break;
	//		case 2:
	//			import();
	//			break;
	//		case 3:
	//			return 0; //exit
	//		case 4:
	//			return 0; //exit
	//	}
	//}
}
