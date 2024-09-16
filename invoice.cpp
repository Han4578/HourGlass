#include "functions.h"

float generate_invoice() {
    int totalitems = 0;
    float subtotal = 0;
    const string title = "HOURGLASS ", motto = "HOURGLASS FURNITURE, WILL LAST FOR LONG ", tel = "tel : 012-4356999 ", time = calculate_time();

    cout << setw(54) << setfill('_') << "_" << endl;
    cout << '|' << setw((52 - title.length()) / 2) << setfill(' ') << ' ' << title << setw((52 - title.length()) / 2) << ' ' << '|' << endl;
    cout << '|' << setw((52 - motto.length()) / 2) << ' ' << motto << setw((52 - motto.length()) / 2) << ' ' << '|' << endl;
    cout << '|' << setw((52 - tel.length()) / 2) << ' ' << tel << setw((52 - tel.length()) / 2) << ' ' << '|' << endl;
    cout << '|' << setw((52 - time.length()) / 2) << ' ' << time << setw((52 - time.length()) / 2) << ' ' << '|' << endl;

    for (int inv = 0; inv < number_of_categories; ++inv) {
        for (int inv2 = 0; inv2 < products_per_category; ++inv2) {
            if (users[userID].cart[inv][inv2] > 0) {
                totalitems += users[userID].cart[inv][inv2];
                float totalprice = products[inv][inv2].price * users[userID].cart[inv][inv2];
                subtotal += totalprice;
                cout << "|  " << setw(17) << setfill(' ') << left << products[inv][inv2].name << right << "(RM" << setprecision(2) << setw(6) << products[inv][inv2].price << " X " << setw(2) << users[userID].cart[inv][inv2] << left << setw(6) << ")" << "RM" << right << setw(8) << round(totalprice * 100) / 100 << "   |" << endl;
            }
        }
    }

    cout << "|" << setw(52) << setfill('_') << '_' << "|\n";
    cout << "|" << setfill(' ') << setw(41) << right << "Subtotal :  RM" << setw(8) << subtotal <<"   |" << endl;
    cout << "|" << setw(41) << right << "Discount(5%) :  RM" << setw(8) << subtotal * 0.05 <<"   |" << endl;
    cout << "|" << setw(41) << right << "Service Charge(2%) :  RM" << setw(8) << subtotal * 0.02 <<"   |" << endl;
    cout << "|" << setw(41) << right << "Tax (5%) :  RM" << setw(8) << subtotal * 0.05 <<"   |" << endl;
    cout << "|" << setw(52) << setfill('_') << '_' << "|\n";
    cout << "|" << setfill(' ') << setw(39) << right << "Total items :  " << setw(10) << totalitems <<"   |" << endl;
    cout << "|" << setw(41) << right << "Total payable :  RM" << setw(8) << subtotal * 0.95 * 1.02 * 1.05 <<"   |" << endl;
    cout << "|" << setw(52) << setfill('_') << '_' << "|\n";

    return subtotal * 0.95f * 1.02f * 1.05f;
}

bool invoice() {
    system("cls");
    string excluded = "";
    char answer = ' ';
    float pay = 0;
    const float total = generate_invoice();   

    if (total == 0) {
        cout << "No items ordered, cannot confirm purchase\n\n";
        system("pause");
        return false;
    }

    if (!get_bool("Confirm purchase? [Y/N]", "Please re-enter a valid data!")) return false;

    while (answer != 'C' && answer != 'E') {
        cout << "Payment method? [C: Cash, E: E-Wallet]: " << endl;
        cin >> answer;
        answer = toupper(answer);
        getline(cin, excluded);

        if (answer != 'C' && answer != 'E') cout << "Please re-enter a valid data!" << endl;
    }

    while (pay < total || pay - total > 1000) {
        cout << "Payment amount ?" << endl;
        cin >> pay;
        cin.clear();
        getline(cin, excluded);
        if (pay < total) {
            cout << "Please Enter sufficient amount!" << endl;
        }
        if (pay - total > 1000) {
            cout << "Payment cannot be more than RM1,000 of total!" << endl;
        }
    }

    system("cls");
    generate_invoice();

    cout << "|" << setfill(' ') << setw(39) << right << "Payment method : " << setw(10) << ((answer == 'C') ? "Cash" : "E-Wallet") << "   |" << endl;
    cout << "|" << setw(41) << right << "Payment amount : RM" << setw(8) << pay << "   |" << endl;
    cout << "|" << setw(41) << "  Change : RM" << setw(8) << pay - total << "   |" << endl;
    cout << "|" << setw(53) << setfill('_') << "|" << endl;

    for (int inv = 0; inv < number_of_categories; ++inv) {
        for (int inv2 = 0; inv2 < products_per_category; ++inv2) {
            users[userID].recent_orders[users[userID].order_index][inv][inv2] = users[userID].cart[inv][inv2];
            if (users[userID].cart[inv][inv2] == 0) continue;
            products[inv][inv2].total_sold += users[userID].cart[inv][inv2];
            users[userID].cart[inv][inv2] = 0;
            if (products[inv][inv2].total_sold > 1000000000 || products[inv][inv2].total_sold < 0) {
                cout << "Each product has a maximum quantity of 1,000,000,000, the quantity for " << products[inv][inv2].name << " has been set to 1,000,000,000";
                products[inv][inv2].total_sold = 1000000000;
            }
        }
    }
    users[userID].order_index = (users[userID].order_index + 1) % recently_ordered_limit;
    system("pause");
    return true;
}
