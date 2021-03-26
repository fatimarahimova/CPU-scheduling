#include "data_structs.h"

using namespace std;

void Stack::init()
{
	head = NULL;
}
void Stack::close()
{
	while (!isEmpty())
		delete pop();
}
void Stack::push(Subtask* in)
{
	in->next = head;
	head = in;
}
Subtask* Stack::pop()
{
	Subtask* temp = head;
	head = head->next;
	return temp;
}
bool Stack::isEmpty()
{
	return head == NULL;
}

void Queue::init()
{
	head = NULL;
	tail = NULL;
}
void Queue::close()
{
	while (!isEmpty())
		delete dequeue();
}
void Queue::queue(Process* in)
{
	if (tail != NULL)
		tail->next = in;
	else
		head = in;

	tail = in;
	tail->next = NULL;
}
Process* Queue::dequeue()
{
	Process* temp = head;
	head = head->next;
	temp->next = NULL;

	if (head == NULL)
		tail = NULL;

	return temp;
}
bool Queue::isEmpty()
{
	return head == NULL;
}
Process* Queue::front()
{
	return head;
}

void MultiQueue::init()
{
	for (int i = 0; i < 3; i++)
		queues[i].init();
}
void MultiQueue::close()
{
	for (int i = 0; i < 3; i++)
		queues[i].close();
}
void MultiQueue::queue(Process* in)
{
	queues[in->priority - 1].queue(in);
}
Process* MultiQueue::dequeue(int priority)
{
	return queues[priority].dequeue();
}
bool MultiQueue::isEmpty()
{
	for (int i = 0; i < 3; i++)
	{
		if (!queues[i].isEmpty())
			return false;
	}
	return true;
}
Process* MultiQueue::front(int priority)
{
	return queues[priority].front();
}
