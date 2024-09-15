#include "functions.h"
#include <fstream>

void import() {
	ifstream file;

	while (true) {
		system("cls");

		int imported[number_of_categories][products_per_category] = { 0 };
		string input = "";
		bool warning = false;
		char confirm = ' ';

		cout << "Please ensure that the format of the file is correct, each line should have " << products_per_category << " numbers \n"
				"indicating the quantity sold for each product. Each number should be separated by a space or a tab.\n"
				"There should be " << number_of_categories << " lines in total. Incorrect format may result in incorrect import.\n"
				"Numbers can only be whole numbers with no decimals or negative signs and no more than 7 digits.\nAll symbols will be ignored.\n\n"
				"Enter file name here (.dat), enter Q to cancel: ";
		getline(cin, input);

		if (input == "q" || input == "Q") return;

		if (file) file.close();
		file.open(input + ".dat");
		if (!file) {
			cout << "\nFile not found, please try again\n\n";
			system("pause");
			continue;
		}

		for (int i = 0; i < number_of_categories; ++i) {
			if (!getline(file, input)) {
				cout << "\nWarning: Not enough lines, expected " << number_of_categories << " lines but found " << i + 1 << '\n';
				warning = true;
				break;
			}
			string temp = "";
			int number_index = 0;

			for (int j = 0; j < input.length(); ++j) {
				if (input[j] == ' ' || input[j] == '	') { // space or tab character
					if (temp == "") continue;
					imported[i][number_index++] = stoi(temp);
					temp = "";
				} else if (isdigit(input[j])) {
					if (input[j] == '0' && temp == "") continue;
					if (temp.length() >= 9) {
						cout << "\nWarning: Number cannot be greater than 9 digits, remaining digits after the 9th from the left will be skipped.";
						warning = true;
						while ((input[j] != ' ' || input[j] != '	') && j < input.length()) ++j;
						--j;
					} else temp += input[j];
				}
				else {
					cout << "\nWarning: Unexpected character " << input[j] << " found at line " << i + 1 << " column " << j + 1 << ", results may be affected.\n";
					warning = true;
				}
			}

			if (temp != "") imported[i][number_index++] = stoi(temp);
			if (number_index < products_per_category) {
				cout << "\nWarning: Not enough numbers on line " << i + 1 << ", expected " << products_per_category << " numbers but found " << number_index << '\n';
				warning = true;
			}
		}

		if (!get_bool((warning)? "\nWarnings were found, do you wish to continue?[Y/N]": "\nNo warnings were found, do you wish to continue?[Y/N]", "Invalid input, please try again.\n")) { 
			system("cls");
			continue; 
		}

		for (int i = 0; i < number_of_categories; ++i) {
			for (int j = 0; j < products_per_category; ++j) {
				products[i][j].total_sold += imported[i][j];
				if (products[i][j].total_sold > 1000000000 || products[i][j].total_sold < 0) {
					cout << "Each product has a maximum quantity of 1,000,000,000, the quantity for " << products[i][j].name << " has been set to 1,000,000,000";
					products[i][j].total_sold = 1000000000;
				}
			}
		}

		cout << "Import complete.\n\n";
		system("pause");
		return;
	}
}