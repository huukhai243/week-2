#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<Windows.h>
 


struct ToDoList
{
    char time[100];
    char place[100];
    char people[100];
    char description[1000];
};

void outToDoList(struct ToDoList tdl)
{
    printf("Time: %s\n", tdl.time);
    printf("Place: %s\n", tdl.place);
    printf("People: %s\n", tdl.people);
    printf("Description: %s\n", tdl.description);
}

void inputToDoList(struct ToDoList* tdl, char time[], char place[], char peolpe[], char des[])
{
    strcpy(tdl->time, time);
    strcpy(tdl->place, place);
    strcpy(tdl->people, peolpe);
    strcpy(tdl->description, des);
}
struct Queue {
    int front, rear, size;
    unsigned capacity;
    struct ToDoList* list;
};


struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
 
    queue->rear = capacity - 1;
    queue->list = (struct ToDoList*)malloc(
        queue->capacity * sizeof(struct ToDoList));
    return queue;
}
 

int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}
 

int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}


void enqueue(struct Queue* queue, struct ToDoList tdl)
{
    if (isFull(queue))
        return ;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->list[queue->rear] = tdl;
    queue->size = queue->size + 1;
}


struct ToDoList dequeue(struct Queue* queue)
{
    struct ToDoList nothing;
    if (isEmpty(queue))
        return nothing;
    struct ToDoList item = queue->list[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

void modify(struct Queue* queue,struct ToDoList tdl )
{
    queue->list[queue->front] = tdl;
}

struct ToDoList front(struct Queue* queue)
{
    struct ToDoList nothing;
    if (isEmpty(queue))
        return nothing;
    return queue->list[queue->front];
}
 

struct ToDoList rear(struct Queue* queue)
{
    struct ToDoList nothing;
    if (isEmpty(queue))
        return nothing;
    return queue->list[queue->rear];
}
 
void menu(struct Queue* queue) {
	struct ToDoList a;
	int c;
	char time[100],place[100],people[100],des[100];
	while(10>0)
	{

        printf("Input time: ");
        fgets(time,100,stdin);
        printf("Input place: ");
        fgets(place,100,stdin);
        printf("Input people: ");
        fgets(people,100,stdin);
        printf("Input description: ");
        fgets(des,100,stdin);
        inputToDoList(&a,time,place,people,des); 

		printf("Enter 1 to Enqueue\n");
		printf("Enter 2 to Denqueue\n");
		printf("Enter 3 to Modify\n");
        printf("Enter 0 to Exit\n");
		printf("Your choice: " );
		scanf("%d", &c);
		getchar();
		if (c == 1) 
		{
			enqueue(queue,a);
            printf("Enqueue successful\n");
		}
		else if (c == 2) 
		{
			dequeue(queue);
            printf("Denqueue successful\n");
		}
			
		else if (c == 3) 
		{
			modify(queue, a);
            printf("Modify successful\n");
		}
		else if(c == 0)
			break;
        printf("Front item is \n");
        outToDoList(front(queue));
        printf("Rear item is \n");
        outToDoList(rear(queue));
	}

}
int main()
{

    struct Queue* queue = createQueue(1000);
	menu(queue);

 
    return 0;
}
