#include "functions.h"
#include <cctype>

void generate_daily_report() {
	system("cls");
	const string unsold = "---No products sold---";
	cout << "Daily Report\n\n";

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

	system("pause");
}

void generate_top_revenue_report() {
	system("cls");
	Product total_products[number_of_categories * products_per_category] = {};
	int number = 0;

	for (int category = 0; category < number_of_categories; category++) {
		for (int product = 0; product < products_per_category; product++) {
			total_products[number++] = products[category][product];
		}
	}


	for (int i = 0; i < 10; i++) {
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

	cout << "_____________________________________________________\n";
	cout << "|" << setw(34) << "TOP REVENUE REPORT" << setw(19) << "|\n";
	cout << "|___________________________________________________|\n";
	cout << "| " << left << setw(15) << "No. Product" << "|" << right << setw(12) << "PRICE(RM)" << "|" << right << setw(9) << "QUANTITY" << "|" << right << setw(11) << "TOTAL(RM)" << "|" << endl;
	cout << "|---------------------------------------------------|\n";
	for (int i = 0; i < 10; i++) {
		cout << "| " << right << setw(2) << i + 1 << ". " << left << setw(10) << total_products[i].name;
		cout << " | " << right << setw(10) << fixed << setprecision(2) << total_products[i].price;
		cout << " | " << right << setw(7) << total_products[i].total_sold;
		cout << " | " << right << setw(10) << total_products[i].price * total_products[i].total_sold << "|\n";
	}
	cout << "|________________|____________|_________|___________|\n";
}

void generate_summary_report() {
	system("cls");
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
	cout << '|' << setw(width / 2 - 1) << setfill(' ') << right << "Number of Customers: " << setw(width / 2 - 1) << left << 0 << "|\n";
	cout << '|' << setw(width - 2) << setfill('_') << '_' << setfill(' ') << "|\n";

	system("pause");
}

void report() {
	do {
		system("cls");
		cout << "Enter report type[1-4]\n";
		cout << "1. Daily Report\n";
		cout << "2. Top Revenue Report\n";
		cout << "3. Summary Report\n";
		cout << "4. Exit\n";
		int input = get_input("Enter report type[1-4]: ", 1, 4, "Invalid input, please re_enter.", false);

		switch (input) {
			case 1:
				generate_daily_report();
				break;
			case 2:
				generate_top_revenue_report();
				break;
			case 3:
				generate_summary_report();
				break;
			case 4:
				return;
			default:
				cout << "Invalid input, please re_enter.\n";
				break;
		}

	} while (get_bool("Continue? [Y/N]: ", "Invalid input, please try again"));
}