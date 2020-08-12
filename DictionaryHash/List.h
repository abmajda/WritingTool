#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

// a node containing a word, it's count and the next node
struct node
{
	string word;
	int count;
	node *next;
};

class List
{
public:
	List();
	~List();
	// inserts a word into the list or adds to it's count if already founf
	void insert(string word);
	// get the count of a word
	int find_counts(string word);
private:
	// points to the front of the list
	node *front;
};

#endif