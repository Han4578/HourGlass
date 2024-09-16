#include "functions.h"
#include <fstream>

 Product products[number_of_categories][products_per_category] = {
	{ {"ADDE", 49}, {"POANG", 309}, {"FLINTAN", 299.99f}, {"TEODORES", 125}, {"MARIUS", 25}}, //chairs
	{ {"LAGKAPTEN", 428}, {"UTESPELARE", 599.99f}, {"SANDSBERG", 179}, {"MITTZON", 799}, {"KNARREVIK", 39}}, //tables
	{ {"LERBERG", 89}, {"KALLAX", 299}, {"LACK", 299}, {"FROSJON", 99}, {"FRYKSAS", 149}} //shelves
};


 Customer users[20] = { {"admin","password"}, {"bob", "123"}};
 int userID = 0;

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

void new_order() {
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
			"5. Save and Leave\n";
		choice = get_input("Enter next action[1-5]: ", 1, 5, "Invalid action, please try again", false);
		cout << '\n';
		switch (choice) {
			case 1: 
				add_to_cart();
				break;
			case 2: 
				remove_from_cart();
				break;
			case 3: 
				clear_cart();
				break;
			case 4:
				if (invoice()) return; //if receipt is generated and payment is made, return true
				break;
			case 5:
				return; // cancel
		}
	}
}

void customer() {
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
			new_order();
			break;
		case 2:
			cancel_order();
			break;
		case 3:
			return ; //exit
		case 4:
			abort() ; //exit
		}
	}
}
void admin() {
	while (true) {
		system("cls");
		display_logo();
		cout << "\nWelcome!\n"
			"1. Report\n"
			"2. Import\n"
			"3. Log Out\n"
			"4. Exit\n";
		int choice = get_input("Please select an action[1-4]: ", 1, 4, "Invalid action, please try again", false);
		cout << '\n';

		switch (choice) {
		case 1:
			report();
			break;
		case 2:
			import();
			break;
		case 3:
			return;
		case 4:
			abort();
		}
	}
}

bool register_user() {
	string password = "", name = "";
	cout << "Register" << endl;
	cout << "Input Q to exit" << endl;
	cout << "Enter Your Name : ";
	getline(cin, name);
	if (name == "Q" || name == "q") return true;
	
	for (int i = 0; i < 20; i++) {
		if (name == users[i].name) {
			cout << "Name has been taken" << endl;
			system("pause");
			system("cls");
			return false;
		}
	}
	cout << "Enter Your Password : ";
	getline(cin, password);
	for (int i = 0; i < 20; i++) {
		if (users[i].name == "") {
			users[i] = { name, password };
			break;
		}
	}
	return true;
}

bool login() {
	string crtpassword = "", password = "", name = "";
	bool valid = false;
	cout << "Login\nInput Q to exit\nEnter Your Name : ";
	getline(cin, name);

	if (name == "Q" || name == "q") return true;

	if (name != "") {
		for (userID = 0; userID < 20; ++userID) {
			if (name == users[userID].name) {
				crtpassword = users[userID].password;
				valid = true;
				break;
			}
		}
		if (!valid) {
			cout << "User does not exist" << endl;
			return false;
		}
	} else {
		cout << "Name cannot be empty" << endl;
		return false;
	}

	cout << "Enter Your Password : ";
	getline(cin, password);
	if (password == crtpassword) {
		if (name == "admin") admin();
		else customer();
		return true;

	} else {
		cout << "Wrong password" << endl;
		return false;
	}
}

int main() {
	while (true) {
		bool success = false;
		system("cls");
		display_logo();
		cout << "Main Menu\n1.Log In\n2.Sign Up\n3.Exit\n";
		string ans;
		getline(cin, ans);
		system("cls");
		if (ans == "1") {
			while (success == 0) {
				success = login();
				system("pause");
				system("cls");
			}
		} else if (ans == "2") {
			while (success == 0) {
				success = register_user();
			}
		} else if (ans == "3") {
			return;
		}
	}
}
