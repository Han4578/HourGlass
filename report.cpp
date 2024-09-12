#include "functions.h"
#include <cctype>

void generate_daily_report() {
	const string unsold = "---No products sold---";
	cout << "Daily Report\n\n";
	system("cls");

	float total_earnings = 0.0;
	cout << fixed << "________________________________________________________\n";
	for (int category = 0; category < number_of_categories; ++category) {
		float previous_earnings = total_earnings;
		cout << "|" << setfill(' ') << setw(27) << right << categories[category] << ' ' << setw(26) << left << "Report" << "|\n";
		cout << "|______________________________________________________|\n";
		cout << setw(21) << "| Name" << right << setw(12) << "Quantity" << setw(21) << "Total(RM) " << " |\n";
		for (int i = 0; i < products_per_category; ++i) {
			if (products[category][i].total_sold > 0) {
				cout << '|' << setw(20) << left << products[category][i].name
					 << setw(10) << right << setprecision(0) << products[category][i].total_sold
					 << setw(23) << setprecision(2) << products[category][i].price * products[category][i].total_sold << " |\n";
				total_earnings += products[category][i].price * products[category][i].total_sold;
			}
		}
		if (previous_earnings == total_earnings) cout << '|' << right << setw((56 - unsold.length()) / 2 - 1) << ' ' << unsold << setw((56 - unsold.length()) / 2 - 1) << ' ' << "|\n";
		else cout << '|' << setw(35) << right << "Total(RM): " << setw(18) << total_earnings - previous_earnings << " |\n";
		cout << "|______________________________________________________|\n";
	}
	cout << "| Total earnings for the day: RM" << setw(23) << setprecision(2) << left << total_earnings << "|\n";
	cout << "|______________________________________________________|\n\n";
}

void generate_top_sales_report() {
	Product total_products[number_of_categories * products_per_category] = {};
	int number = 0;

	for (int category = 0; category < number_of_categories; category++) {
		for (int product = 0; product < products_per_category; product++) {
			total_products[number++] = products[category][product];
		}
	}

	for (int i = 0; i < number_of_categories * products_per_category; i++) {
		for (int j = i + 1; j < products_per_category; j++) {
			float total1 = total_products[i].price * total_products[i].total_sold;
			float total2 = total_products[j].price * total_products[j].total_sold;
			if (total1 < total2) {
				Product temp = total_products[i];
				total_products[i] = total_products[j];
				total_products[j] = temp;
			}
		}
	}

	cout << fixed << "TOP 10 PRODUCT HOT:" << endl;
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << ". PRODUCT: " << total_products[i].name;
		cout << " , PRICE: " << total_products[i].price;
		cout << setprecision(0) << " , QUANTITY: " << total_products[i].total_sold;
		cout << setprecision(2) << " , TOTAL: " << total_products[i].price * total_products[i].total_sold << endl;
	}
}

void generate_summary_report(int customers) {
	const string title = "Summary Report";
	const int width = 70;
	float total = 0;
	int quantity = 0;

	cout << setw(width) << setfill('_') << '_' << '\n';
	cout << '|' << setw(((width - 2) - title.length()) / 2) << setfill(' ') << ' ' << title << setw(((width - 2) - title.length()) / 2) << ' ' << "|\n";
	cout << '|' << setw(width - 2) << setfill('_') << '_' << "|\n";
	cout << setw(6) << setfill(' ') << left << "|No." << setw(20) << "|Name" << setw(15) << "|Price(RM)" << setw(11) << "|Quantity" << setw(17) << "|Total(RM)" << "|\n";

	for (int i = 0; i < number_of_categories; ++i) {
		float subtotal = 0;
		cout << '|' << setfill(' ') << fixed << setw(width - 2) << left << categories[i] << "|\n";

		for (int j = 0; j < products_per_category; ++j) {
			Product product = products[i][j];
			cout << '|' << setw(5) << left << setprecision(0) << j + 1 << '|' << setw(19) << product.name << '|' <<  right << setw(14) << setprecision(2) << product.price << setprecision(0) << '|' << setw(10) << product.total_sold << '|' << setprecision(2) << setw(16) << product.total_sold * product.price << "|\n";
			subtotal += product.total_sold * product.price;
			quantity += product.total_sold;
		}

		cout << '|' << right << setw(width - 18) << setfill(' ') << "Subtotal(RM)|" << setw(16) << subtotal << "|\n";
		cout << '|' << setw(width - 2) << setfill('_') << '_' << "|\n";
		total += subtotal;
	}
	cout << '|' << setw(width / 2 - 1) << setfill(' ') << "Total(RM): " << setw(width / 2 - 1) << setprecision(2) << left << total << "|\n";
	cout << '|' << setw(width / 2 - 1) << setfill(' ') << right << "Total Products Sold: " << setw(width / 2 - 1) << setprecision(0) << left << quantity << "|\n";
	cout << '|' << setw(width / 2 - 1) << setfill(' ') << right << "Number of Customers: " << setw(width / 2 - 1) << left << customers << "|\n";
	cout << '|' << setw(width - 2) << setfill('_') << '_' << setfill(' ') << "|\n";
}

void report(int customers) {
	string input = "";
	char first_char = ' ';

	cout << "Enter report type[1-4]\n";
	cout << "1. Daily Report\n";
	cout << "2. Top Sales Report\n";
	cout << "3. Summary Report\n";
	cout << "4. Exit\n";

	do {
		do {
			cout << "Your number: ";
			getline(cin, input);
			first_char = input[0];

			switch (first_char) {
				case '1':
					generate_daily_report();
					break;
				case '2':
					generate_top_sales_report();
					break;
				case '3':
					generate_summary_report(customers);
					break;
				case '4':
					cout << "Exiting...\n";
					return;
				default:
					cout << "Invalid input, please re_enter.\n";
					break;
			}
		} while (first_char < '1' || first_char > '4');

		do {
			cout << "Continue? (Y/N): ";
			getline(cin, input);
			first_char = toupper(input[0]);
		} while (first_char != 'Y' && first_char != 'N');

	} while (first_char == 'Y');
}