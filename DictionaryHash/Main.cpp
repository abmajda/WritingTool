#include "Table.h"

using namespace std;

int main()
{
	Table *dictionary = new Table;
	string input;
	bool finished = false;
	bool valid = false;

	// execute until the user wants to exit
	while (!finished)
	{
		// the main loop
		dictionary->read_file();
		dictionary->delete_duplicates();
		dictionary->get_counts();
		dictionary->print();

		// reset valid
		valid = false;

		// ask if the would like to run the program again until the use gives a valid answer
		while (!valid)
		{
			cout << endl;
			cout << "Would you like to run the program again(Y/N): ";
			cin >> input;

			// if the answer is yes, reset the table
			if (input == "y" || input == "Y")
			{
				valid = true;
				delete dictionary;
				dictionary = new Table;
			}

			// if no, exit the program
			else if (input == "n" || input == "N")
			{
				valid = true;
				finished = true;
			}
		}
	}

	return 0;
}