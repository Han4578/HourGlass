#include "functions.h"

float generate_invoice() {
    int totalitems = 0;
    float total = 0;
    const string title = "HOURGLASS ", motto = "HOURGLASS FURNITURE, WILL LAST FOR LONG ", tel = "tel : 012-4356999 ", time = calculate_time();

    cout << setw(54) << setfill('_') << "_" << endl;
    cout << '|' << setw((52 - title.length()) / 2) << setfill(' ') << ' ' << title << setw((52 - title.length()) / 2) << ' ' << '|' << endl;
    cout << '|' << setw((52 - motto.length()) / 2) << ' ' << motto << setw((52 - motto.length()) / 2) << ' ' << '|' << endl;
    cout << '|' << setw((52 - tel.length()) / 2) << ' ' << tel << setw((52 - tel.length()) / 2) << ' ' << '|' << endl;
    cout << '|' << setw((52 - time.length()) / 2) << ' ' << time << setw((52 - time.length()) / 2) << ' ' << '|' << endl;

    for (int inv = 0; inv < number_of_categories; inv++) {
        for (int inv2 = 0; inv2 < products_per_category; inv2++) {
            if (products[inv][inv2].currently_ordered > 0) {
                float totalprice;
                totalitems += products[inv][inv2].currently_ordered;
                totalprice = products[inv][inv2].price * products[inv][inv2].currently_ordered;
                total += totalprice;
                cout << "|  " << setw(17) << setfill(' ') << left << products[inv][inv2].name << right << "(RM" << setprecision(2) << setw(6) << products[inv][inv2].price << " X " << setw(2) << products[inv][inv2].currently_ordered << left << setw(6) << ")" << "RM" << right << setw(8) << round(totalprice * 100) / 100 << "   |" << endl;
            }
        }
    }

    cout << "|" << setw(52) << setfill('_') << '_' << "|\n";
    cout << "|" << setfill(' ') << setw(28) << right << "Subtotal : RM" << setw(23) << left << total << " | " << endl;
    cout << "|" << setw(26) << right << "Discount : " << setw(26) << left << "5%" << "| " << endl;
    cout << "|" << setw(26) << right << "Service Charge : " << setw(26) << left << "2%" << "|" << endl;
    cout << "|" << setw(26) << right << "Tax : " << setw(26) << left << "5%" << "|" << endl;
    cout << "|" << setw(52) << setfill('_') << '_' << "|\n";
    cout << "|" << setfill(' ') << setw(26) << right << "Total items : " << setw(25) << left << totalitems << " | " << endl;
    cout << "|" << setw(28) << right << "Total payable : RM" << setw(23) << left << total * 0.95 * 1.02 * 1.05 << " | " << endl;
    cout << "|" << setw(52) << setfill('_') << '_' << "|\n";

    return total;
}

bool invoice() {
    string pay1 = "", payment = "", disval = "true", payval = "false", excluded = "";
    char answer = ' ';
    float pay = 0;
    const float total = generate_invoice();   

    if (total == 0) {
        cout << "No items bought, cannot confirm purchase\n";
        return false;
    }

    while (answer != 'Y' && answer != 'N') {
        cout << "Confirm purchase? (Y/N)" << endl;
        cin >> answer;
        answer = toupper(answer);
        getline(cin, excluded);
        if (answer != 'Y' && answer != 'N') cout << "Please re-enter a valid data!" << endl;
    }

    if (answer == 'N') return false;

    while (payment != "Cash" && payment != "E-wallet") {
        cout << "Payment method ? (Cash or E-wallet)" << endl;
        getline(cin, payment);
        if (payment != "Cash" && payment != "E-wallet") {
            cout << "Please re-enter a valid data!" << endl;
        }
    }

    while (pay < (total * 0.95 * 1.02 * 1.05) || pay - (total * 0.95 * 1.02 * 1.05) > 1000) {
        cout << "Payment amount ?" << endl;
        cin >> pay;
        cin.clear();
        getline(cin, excluded);
        if (pay < (total * 0.95 * 1.02 * 1.05)) {
            cout << "Please Enter sufficient amount!" << endl;
        }
        if (pay - (total * 0.95 * 1.02 * 1.05) > 1000) {
            cout << "Payment cannot be more than RM1,000 of total!" << endl;
        }
    }

    generate_invoice();

    cout << "|" << setfill(' ') << setw(26) << right << "Payment method : " << setw(26) << left << payment << "|" << endl;
    cout << "|" << setw(28) << right << "Payment amount : RM" << setw(24) << left << pay << "|" << endl;
    cout << "|" << setw(28) << right << "  Change : RM" << setw(24) << left << pay - (total * 0.95 * 1.02 * 1.05) << "|" << endl;
    cout << "|" << setw(53) << right << setfill('_') << "|" << endl;

    for (int inv = 0; inv < number_of_categories; ++inv) {
        for (int inv2 = 0; inv2 < products_per_category; ++inv2) {
            if (products[inv][inv2].currently_ordered == 0) continue;
            products[inv][inv2].total_sold += products[inv][inv2].currently_ordered;
            products[inv][inv2].currently_ordered = 0;
        }
    }

    return true;
}