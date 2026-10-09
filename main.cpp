
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

bool validTarget(const string& target) {
    if (target.empty() || !isalnum(
        static_cast<unsigned char>(target[0]))) {
        return false;
    }

    for (unsigned char ch : target) {
        if (!isalnum(ch) && ch != '.' &&
            ch != '-' && ch != ':') {
            return false;
        }
    }

    return true;
}

int main() {
    int choice;

    do {
        cout << "\n=== NETWORK DIAGNOSTICS TOOL ===\n";
        cout << "1. Test connectivity (Ping)\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            return 1;
        }

        cin.ignore(10000, '\n');

        if (choice == 1) {
            string target;

            cout << "Enter hostname or IP address: ";
            getline(cin, target);

            if (!validTarget(target)) {
                cout << "Invalid hostname or IP address.\n";
                continue;
            }

#ifdef _WIN32
            string command = "ping -n 4 " + target;
#else
            string command = "ping -c 4 " + target;
#endif

            cout << "\nTesting connection to "
                 << target << "...\n\n";

            int result = system(command.c_str());

            if (result == 0) {
                cout << "\nThe target responded to ping.\n";
            } else {
                cout << "\nNo successful ping response.\n";
                cout << "The host may be offline or "
                        "blocking ping requests.\n";
            }

        } else if (choice == 2) {
            cout << "Exiting the tool. Goodbye!\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 2);

    return 0;
}
