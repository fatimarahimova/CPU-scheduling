#include <iostream>
#include <string>
#include <fstream>

#include "data_structs.h"

using namespace std;

MultiQueue* processFile(ifstream* file);
void work(MultiQueue* mq);

int main(int argc, char** argv)
{
	ifstream file(argv[1]);

	MultiQueue* myProcesses = processFile(&file);
	file.close();

	work(myProcesses);

	myProcesses->close();
	delete myProcesses;
	return 0;
}

MultiQueue* processFile(ifstream* file)
{
	MultiQueue* mq = new MultiQueue;
	mq->init();
	while (!file->eof())
	{
		Process* tempProcess = new Process;
		*file >> tempProcess->name;
		*file >> tempProcess->priority;
		*file >> tempProcess->arrival_time;
		*file >> tempProcess->task_count;
		tempProcess->deadline = tempProcess->arrival_time;
		tempProcess->task_stack.init();
		for (int i = 0; i < tempProcess->task_count; i++)
		{
			Subtask* tempTask = new Subtask;
			*file >> tempTask->name;
			*file >> tempTask->duration;
			tempProcess->deadline += tempTask->duration;
			tempProcess->task_stack.push(tempTask);
		}
		mq->queue(tempProcess);
	}
	return mq;
}

void work(MultiQueue* mq)
{
	int sc = 0;
	int time = 0;
	int cummLate = 0;

	for (int i = 0; i < 3; i++)
	{
		if (!mq->queues[i].isEmpty())
		{
			Process* p = mq->front(i);
			if (p->arrival_time == 0)
			{
				Subtask* st = p->task_stack.pop();
				time += st->duration;
				if (i == 1)
					sc++;
				cout << p->name << " " << st->name << endl;
				delete st;
				if (p->task_stack.isEmpty())
				{
					cummLate += time - p->deadline;
					delete mq->dequeue(i);
				}
				break;
			}
		}
	}

	while (!mq->isEmpty())
	{
		if (sc == 2 && !mq->queues[2].isEmpty())
		{
			Process* p = mq->front(2);
			Subtask* st = p->task_stack.pop();
			time += st->duration;
			cout << p->name << " " << st->name << endl;
			delete st;
			if (p->task_stack.isEmpty())
			{
				cummLate += time - p->deadline;
				delete mq->dequeue(2);
			}
			sc = 0;
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				if (!mq->queues[i].isEmpty())
				{
					Process* p = mq->front(i);
					Subtask* st = p->task_stack.pop();
					time += st->duration;
					if (i == 1)
						sc++;
					cout << p->name << " " << st->name << endl;
					delete st;
					if (p->task_stack.isEmpty())
					{
						cummLate += time - p->deadline;
						delete mq->dequeue(i);
					}
					break;
				}
			}
		}
	}

	cout << "Cumulative Lateness: " << cummLate << endl;
}
