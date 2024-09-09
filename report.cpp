#include "functions.h"

void generate_daily_report() {
	const string unsold = "---No products sold---";
	cout << "Daily Report\n\n";

	float total_earnings = 0.0;
	cout << fixed << "________________________________________________________\n";
	for (int category = 0; category < number_of_categories; ++category) {
		float previous_earnings = total_earnings;
		cout << "|" << setfill(' ') << setw(27) << right << categories[category] << ' ' << setw(26) << left << "Report" << "|\n";
		cout << "|______________________________________________________|\n";
		for (int i = 0; i < products_per_category; ++i) {
			if (products[category][i].total_sold > 0) {
				cout << "| Product: " << setw(10) << left << products[category][i].name
					<< "| Quantity: " << setprecision(0) << products[category][i].total_sold
					<< "| Total: RM" << setw(10) << setprecision(2) << right << products[category][i].price * products[category][i].total_sold << "|\n";
				total_earnings += products[category][i].price * products[category][i].total_sold;
			}
		}
		if (previous_earnings == total_earnings) cout << '|' << right << setw((56 - unsold.length()) / 2 - 1) << ' ' << unsold << setw((56 - unsold.length()) / 2 - 1) << ' ' << "|\n";
		cout << "|______________________________________________________|\n";
	}
	cout << "| Total earnings for the day: RM" << setw(23) << setprecision(2) << left << total_earnings << "|\n";
	cout << "|______________________________________________________|\n\n";
}

void generate_weekly_report() {
	float daily_total_money[7] = {};
	float weekly_total_money = 0.0;

	for (int day = 0; day < 7; day++) {
		cout << "Total earnings for day " << day + 1 << " : ";
		cin >> daily_total_money[day];
		weekly_total_money += daily_total_money[day];
	}

	cout << "___________________________________________\n";
	cout << '|' << right << setw(28) << "WEEKLY REPORT" << setw(15) << "|\n";
	cout << "|_________________________________________|\n";
	cout << left << setw(10) << "|  Day" << right << setw(30) << "Total Earnings (RM)" << "  |\n";
	cout << "|_________________________________________|\n";

	for (int day = 0; day < 7; day++) cout << "|   " << left << setw(9) << (day + 1) << setw(27) << right << fixed << setprecision(2) << daily_total_money[day] << right << "  |\n";

	cout << "|_________________________________________|\n";
	cout << left << setw(30) << "| Weekly Total" << right << setw(10) << weekly_total_money << "  |\n";
	cout << left << setw(30) << "| Weekly Average" << right << setw(10) << weekly_total_money / 7 << "  |\n";
	cout << "|_________________________________________|\n";
}

void generate_summary_report(int customers) {
	const string title = "Summary Report";
	const int width = 70;
	float total = 0;
	int quantity = 0;

	cout << setw(width) << setfill('_') << '_' << '\n';
	cout << '|' << setw(((width - 2) - title.length()) / 2) << setfill(' ') << ' ' << title << setw(((width - 2) - title.length()) / 2) << ' ' << "|\n";
	cout << '|' << setw(width - 2) << setfill('_') << '_' << "|\n";
	cout << setw(6) << setfill(' ') << left << "|No." << setw(20) << "|Name" << setw(15) << "|Price(RM)" << setw(16) << "|Quantity" << setw(12) << "|Total(RM)" << "|\n";

	for (int i = 0; i < number_of_categories; ++i) {
		float subtotal = 0;
		cout << '|' << setfill(' ') << fixed << setw(width - 2) << left << categories[i] << "|\n";

		for (int j = 0; j < products_per_category; ++j) {
			Product product = products[i][j];
			cout << '|' << setw(5) << left << setprecision(0) << j + 1 << '|' << setw(19) << product.name << '|' <<  right << setw(14) << setprecision(2) << product.price << setprecision(0) << '|' << setw(15) << product.total_sold << '|' << setprecision(2) << setw(11) << product.total_sold * product.price << "|\n";
			subtotal += product.total_sold * product.price;
			quantity += product.total_sold;
		}

		cout << '|' << right << setw(width - 13) << setfill(' ') << "Subtotal(RM)|" << setw(11) << subtotal << "|\n";
		cout << '|' << setw(width - 2) << setfill('_') << '_' << "|\n";
		total += subtotal;
	}
	cout << '|' << setw(width / 2 - 1) << setfill(' ') << "Total(RM): " << setw(width / 2 - 1) << setprecision(2) << left << total << "|\n";
	cout << '|' << setw(width / 2 - 1) << setfill(' ') << right << "Total Products Sold: " << setw(width / 2 - 1) << setprecision(0) << left << quantity << "|\n";
	cout << '|' << setw(width / 2 - 1) << setfill(' ') << right << "Number of Customers: " << setw(width / 2 - 1) << left << customers << "|\n";
	cout << '|' << setw(width - 2) << setfill('_') << '_' << setfill(' ') << "|\n";
}

void report(int customers) {
	int a;
	char b;
	string invalid = "";

	cout << "Enter report type[1-4]\n";
	cout << "1. Daily Report\n";
	cout << "2. Weekly Report\n";
	cout << "3. Summary Report\n";
	cout << "4. Exit\n";

	do {
		do {
			cout << "Your number: ";
			cin >> a;

			switch (a) {
				case 1:
					generate_daily_report();
					break;
				case 2:
					generate_weekly_report();
					break;
				case 3:
					generate_summary_report(customers);
					break;
				case 4:
					cout << "Exiting...\n";
					return;
				default:
					cout << "Invalid input, please re_enter.\n";
					break;
			}
		} while (a < 1 || a > 4);

		do {
			cout << "Continue? (Y/N): ";
			cin >> b;
			getline(cin, invalid);
			b = toupper(b);
		} while (b != 'Y' && b != 'N');

	} while (b == 'Y');
}