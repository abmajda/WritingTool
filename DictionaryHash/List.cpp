#include "List.h"


List::List()
{
	// start front out at NULL
	front = NULL;
}

List::~List()
{
	// delete down the list as long as there are values
	while (front != NULL)
	{
		node *temp;
		temp = front;
		front = front->next;
		delete temp;
	}
}

void List::insert(string word)
{
	// if list is empty insert a new node at the front
	if (front == NULL)
	{
		node* temp = new node;
		temp->word = word;
		temp->count = 1;
		temp->next = NULL;
		front = temp;
	}

	// otherwise go down the list to add the node of count as needed
	else
	{
		bool finished = false;
		bool found = false;

		node* temp = front;

		// go down the list
		while (finished == false)
		{
			// if the word is found, add to it's count and mark that a match has been found
			if (temp->word == word)
			{
				temp->count++;
				finished = true;
				found = true;
			}

			// otherwise if we go through the whole list we stop looking
			else if (temp->next == NULL)
			{
				finished = true;
			}

			temp = temp->next;
		}

		// if a match hasn't been found, add a new node containing the word
		if (!found)
		{
			temp = new node;
			temp->word = word;
			temp->count = 1;
			temp->next = front;
			front = temp;
		}
	}
}

int List::find_counts(string word)
{
	int count = 1;
	node *temp = front;
	bool found = false;

	// go through the list until we find the word
	while (!found)
	{
		// if we find the word keep track of it's count
		if (temp->word == word)
		{
			count = temp->count;
			found = true;
		}

		// otherwise keep going through the list
		else
		{
			temp = temp->next;
		}
	}

	// return the found count
	return count;
}
