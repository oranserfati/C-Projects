#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Worker
{
	long ID;
	char* name;
	unsigned long payCheck;
	char hebYear[6];
	unsigned long year;
} Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;

//Functions
Worker* CreateWorker(int yearType);
void PrintWorker(Worker* worker, int yearType);
WorkerList* AddWorker(WorkerList* head, Worker* w);
WorkerList* DeleteWorstWorker(WorkerList* head);
void UpdateWorker(WorkerList* head, float percent);
WorkerList* Reverse(WorkerList* head);
WorkerList* FreeWorkers(WorkerList* head);
void PrintAllWorkers(WorkerList* head);
int IndexR(WorkerList* head, long unsigned id);
int IndexA(WorkerList* head, long unsigned id);


void main()
{
	//Create head of list and first worker
	printf("Please create first worker:\n");
	WorkerList* workerList = (WorkerList*)malloc(sizeof(WorkerList));
	if (!workerList)
		puts("Allocation Faild");
	Worker* workers[4];
	workers[0] = CreateWorker(0);
	workerList->data = workers[0];
	workerList->next = NULL;


	//Create all workers and add them to the list
	printf("Please create workers:\n");
	for (int i = 0; i < 3; i++)
		workerList = AddWorker(workerList, CreateWorker(0));
	printf("Printing list..\n\n");
	PrintAllWorkers(workerList);


	//Deleting the worst worker
	printf("Deleting worst worker..\n\n");
	workerList = DeleteWorstWorker(workerList);
	printf("Printing list..\n\n");
	PrintAllWorkers(workerList);


	//Update workers
	printf("Updating workers paychecks..\n\n");
	UpdateWorker(workerList, 0.1);
	printf("Printing list..\n\n");
	PrintAllWorkers(workerList);


	//Check for worker index
	printf("Check for workers index..\n\n");
	int check = 208447268;
	printf("Worker index: %d \n",IndexR(workerList, check));
	printf("Worker index: %d \n", IndexA(workerList, check));


	//Reverse list
	workerList = Reverse(workerList, workerList);
	PrintAllWorkers(workerList);


	//Free All
	workerList = FreeWorkers(workerList);
	if (!workerList)
	{
		//workerList = NULL;
		printf("All workers deleted.\n\n");
	}
	
}

Worker* CreateWorker(int yearType)//Create new Worker
{
	//Variable
	char tempName[40];
	Worker* ptrWorker = (Worker*) malloc(sizeof(Worker));//Init new worker
	if (!ptrWorker)
		puts("Not Enough Memory");

	//ID input
	puts("ID number:");
	scanf("%d",&ptrWorker->ID);

	//Name input
	puts("Name:");
	scanf("%s",tempName);
	ptrWorker->name = (char*)malloc(strlen(tempName) + 1);
	if (!ptrWorker->name)
		puts("Not Enough Memory");
	strcpy(ptrWorker->name, tempName);

	//Paycheck input
	puts("PayCheck number:");
	scanf("%d",&ptrWorker->payCheck);

	//Year input
	puts("Start year:");
	if(yearType)
		scanf("%s",&ptrWorker->hebYear);
	else
		scanf("%d",&ptrWorker->year);
	return ptrWorker;
}

void PrintWorker(Worker* worker, int yearType)//Print all worker details
{
	if (yearType)
		printf("ID number: %d\nName: %s\nPayCheck number: %d\nStart year: %s \n\n",
			worker->ID, worker->name, worker->payCheck, worker->hebYear);
	else 
		printf("ID number: %d\nName:% s\nPayCheck number: %d\nStart year : % d \n\n",
			worker->ID,worker->name, worker->payCheck,worker->year);
}

WorkerList* AddWorker(WorkerList* head, Worker* w)
{
	WorkerList* copyHead = head;
	WorkerList* temp = (WorkerList*)malloc(sizeof(WorkerList));
	if (!temp)
		puts("Allocation Faild");
	temp->data = w;//Add worker

	if (temp->data->payCheck >= head->data->payCheck)//If new worker-paycheck is the biggest
	{
		temp->next = head;
		return temp;
	}
		
	while (copyHead->next != NULL)//Goes through all paychecks
	{
		if (temp->data->payCheck > copyHead->next->data->payCheck)
		{
			temp->next = copyHead->next;
			copyHead->next = temp;
			return head;
		}
		copyHead = copyHead->next;
	}
	copyHead->next = temp;
	temp->next = NULL;

	return head;
}

int IndexR(WorkerList* head, long unsigned id)
{
	static res = 1;

	if (head->data->ID = id)
		return res;
	if (head->next == NULL)
		return-1;

	res++;
	return IndexR(head->next, id);
}

int IndexA(WorkerList* head, long unsigned id)
{
	int res = 1;
	while (head != NULL)
	{
		if (head->data->ID == id)
			return res;

		head = head->next;
		res++;
	}
	return -1;
}

WorkerList* DeleteWorstWorker(WorkerList* head)//Worst worker = Last worker in the List
{
	WorkerList* copyHead = head;

	while (copyHead->next->next)//Go to last worker on the list
	{
		copyHead = copyHead->next;
	}
	free(copyHead->next);//free last worker
	copyHead->next = NULL;

	return head;
}

void UpdateWorker(WorkerList* head, float percent)
{
	WorkerList* copyHead = head;

	if(percent > 0)
		while (copyHead)//Goes through all workers
		{
			copyHead->data->payCheck += copyHead->data->payCheck * percent;
			copyHead = copyHead->next;
		}

	return head;
}

WorkerList* Reverse(WorkerList* head, WorkerList* copyHead)
{
	if (!head->next)
	{
		copyHead->next = NULL;//Now the first node point to null
		return head;
	}	

	head->next = Reverse(head->next, copyHead);//Points next node to the current one

	return head;
}

WorkerList* FreeWorkers(WorkerList* head)
{
	WorkerList* copyHead = head;

	while (head)//Goes through all workers
	{
		head = head->next;
		free(copyHead);//Free last node
		copyHead = head;
	}
	free(head);
	return head;
}

void PrintAllWorkers(WorkerList* head)
{
	while (head)
	{
		PrintWorker(head->data, 0);
		head = head->next;
	}
}

