#include "functions.h"

void display_table() {
	cout << setfill('_') << setw(101) << '_' << '\n';

	for (int t = 0; t < number_of_categories; ++t) {
		cout << "| " << setfill(' ') << (char)('A' + t) << ". " << left << setw(95) << categories[t] << "|" << '\n';
		cout << "|" << setfill('_') << right << setw(100) << "|" << '\n';
		cout << "|" << setfill(' ') << setw(5) << "No." << "|" << setw(35) << "Name" << setw(34) << "|" << setw(24) << "RM" << "|" << '\n';
		cout << "|" << setfill('_') << setw(6) << '|' << setw(69) << '|' << setw(25) << '|' << '\n';
		for (int p = 0; p < products_per_category; ++p)
		{
			cout << "|" << setfill(' ') << setw(4) << p + 1 << ".|" << left << setw(68) << products[t][p].name << "|" << fixed << setprecision(2) << right << setw(24) << products[t][p].price << "|" << '\n';
		}
		cout << "|" << setfill('_') << setw(6) << '|' << setw(69) << '|' << setw(25) << '|' << '\n';
	}
}