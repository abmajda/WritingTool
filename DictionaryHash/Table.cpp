#include "Table.h"

using namespace std;

Table::Table()
{
}

Table::~Table()
{
	// free the memory
	delete[] word_list;
	delete[] word_count_pairs;
}

void Table::read_file()
{
	string word;
	string filename;
	ifstream infile;

	// set max size of the array storing our words to 1000, we will dynamically grow it later if needed
	int max_size = 1000;
	word_list = new string[max_size];

	// ask for the file name and then open it
	cout << "Please enter the name of a file to read from. Include the .txt: ";
	cin >> filename;
	infile.open(filename);


	// comment more on change to linux
	while (!infile.eof())
	{
		infile >> word;

		max_size = remove_punctuation(word, max_size);
	}

	// get rid of extra size and handle some formatting
	size--;
	cout << endl;

	infile.close();
}

void Table::sort_by_word(int begin, int end)
{
	// set the pivot point
	int pivot_point;

	// quicksort
	if (begin < end)
	{
		pivot_point = partition_words(begin, end);
		sort_by_word(begin, pivot_point - 1);
		sort_by_word(pivot_point + 1, end);
	}
}

void Table::sort_by_number(int begin, int end)
{
	// set the pivot point
	int pivot_point;

	// quicksort
	if (begin < end)
	{
		pivot_point = partition_numbers(begin, end);
		sort_by_number(begin, pivot_point - 1);
		sort_by_number(pivot_point + 1, end);
	}
}

void Table::print()
{
	// print out the list of words with their respective counts
	for (int i = 0; i <= size; i++)
	{
		cout << word_count_pairs[i].word << " " << word_count_pairs[i].count << endl;
	}

	// sort the list by number
	cout << endl;
	sort_by_number(0, size);

	// print out the list of counts with their respective words
	for (int j = 0; j <= size; j++)
	{
		cout << word_count_pairs[j].count << " " << word_count_pairs[j].word << endl;
	}
	
	cout << endl;
}

int Table::remove_punctuation(string word, int max_size)
{
	int length = word.size();
	int hash_value;
	// start off the word we will add as blank
	string clean_word = "";

	// for as long as the string is, go down and remove punctuation
	for (int i = 0; i <= length; i++)
	{
		// if the character is punctuation, or we have readched the end terminate the string at that point
		if (ispunct(word[i]) || i == length)
		{
			// don't do anything is the string is empty
			if (clean_word == "")
			{ }
			// otherwise take what we have and add it to the hash table and our words list, incrementing the size of the list
			else
			{
				hash_value = hash(clean_word);
				insert(hash_value, clean_word);
				word_list[size] = clean_word;
				size++;

				// if our array gets too big, replace with a new, bigger array and copy it over
				if (size == max_size)
				{
					max_size = max_size + 2000;
					string *temp = new string[max_size];
					string *holder;

					for (int i = 0; i < size; i++)
					{
						temp[i] = word_list[i];
					}

					holder = word_list;
					word_list = temp;
					temp = holder;
					delete[] temp;
				}

				// after adding to the hash table and word list, reset the string
				clean_word = "";
			}
		}

		// otherwise if it is not puntuation add the character to the string
		else
		{
			clean_word = clean_word + word[i];
		}
	}

	// return the maximum size so we can track if the word list array has been resized
	return max_size;
}

int Table::hash(string word)
{
	// set up some constants to modify the hash value with and the hash value itself
	int hash_value;
	long long hash = 0;
	const int mod = 23;

	// for each letter, multiply by 23 and add the value of the next letter
	for (int i = 0; i < word.length(); i++)
	{
		hash = (hash * mod) + word[i];
	}

	// ensure the value is within the size of the hash table
	hash_value = hash % hash_size;

	return hash_value;
}

void Table::insert(int hash_value, string word)
{
	// insert the word into the hash table at the value
	hash_table[hash_value].insert(word);
}
 
int Table::partition_words(int start, int end)
{
	// set the comb and pivot
	int comb = start;
	string pivot = word_list[start];

	// go down the list and sort based on whether the item is less than or greater than the pivot
	for (int i = start + 1; i <= end; i++)
	{
		if (word_list[i] <= pivot)
		{
			comb++;
			swap(word_list[i], word_list[comb]);
		}
	}

	// swap the comb and the pivot
	swap(word_list[comb], word_list[start]);

	return comb;
}

int Table::partition_numbers(int start, int end)
{
	// set the comb and pivot
	int comb = start;
	int pivot = word_count_pairs[start].count;

	// go down the list and sort based on whether the item is less than or greater than the pivot
	for (int i = start + 1; i <= end; i++)
	{
		if (word_count_pairs[i].count >= pivot)
		{
			comb++;
			swap(word_count_pairs[i], word_count_pairs[comb]);
		}
	}

	// swap the comb and the pivot
	swap(word_count_pairs[comb], word_count_pairs[start]);

	return comb;
}

void Table::get_counts()
{
	int hash_value;
	int count;

	// go down the list of words and find it's value in the hash table, then assign counts to it's entry
	for (int i = 0; i <= size; i++)
	{
		hash_value = hash(word_count_pairs[i].word);
		count = hash_table[hash_value].find_counts(word_count_pairs[i].word);
		word_count_pairs[i].count = count;
	}
}

void Table::delete_duplicates()
{
	// sort the list of words
	sort_by_word(0, size);

	// create a new list that contains both words and counts
	word_count_pairs = new Entry[size];

	int word_list_size = size;
	int duplicates_size = 0;

	// go down the size of the word list
	for (int i = 0; i <= word_list_size; i++)
	{
		// if a duplicate is found, do not put anything in the new list and mark how many duplicates are found
		if (word_list[i] == word_list[i + 1])
		{
			duplicates_size++;
			size--;
		}

		// otherwise add it to the new list in proper order
		else
		{
			string testing_word = word_list[i];
			word_count_pairs[i - duplicates_size].word = word_list[i];
		}
	}
}