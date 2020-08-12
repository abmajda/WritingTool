#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <iostream>
#include <fstream>
#include "List.h"

using namespace std;

// a structure to hold both a word and it's count
struct Entry
{
	string word = "";
	int count = 1;
};


class Table
{
public:
	Table();
	~Table();
	// read the file, insert it's words into a words list and the hash table
	void read_file();
	// get the count for each word from the hash table
	void get_counts();
	// sorts the list of words and then transfers it into a new array containing Entries without any duplicates
	void delete_duplicates();
	// prints the alphabetized words, then sort by count and prints that
	void print();

private:
	// keeps track of the size of the array
	int size = 0;
	// the hash table is size 200
	int hash_size = 200;
	// an array to hold the words and an array of entries to store the values and counts
	string *word_list;
	struct Entry *word_count_pairs;
	// the hash table of lists
	List hash_table[200];

	// sort by either word or count using quicksort
	void sort_by_word(int begin, int end);
	void sort_by_number(int begin, int end);
	// seperates the string by punctuation and then inserts it into the hash table as well as the list of words
	int remove_punctuation(string word, int max_size);
	// creates a hash value for the word
	int hash(string word);
	// inserts a word at the given hash value
	void insert(int hash_value, string word);
	// helper functions for the quicksort
	int partition_words(int start, int end);
	int partition_numbers(int start, int end);
	
};

#endif