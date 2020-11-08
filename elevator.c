#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define MAX 100

struct queue{
    int floors[MAX];
    int front;
    int rear;
};

struct node
{
    int floor;
    struct node* next;
};

struct Graph
{
    int floors;
    struct node** adj;
    int* visited;
};



struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);

struct node* createNode(int);

struct Graph* createGraph(int floors);
void addEdge(struct Graph* graph, int src, int dest);
//void printGraph(struct Graph* graph);
void BFS(struct Graph* graph, int start);

int GCD(int u,int d);

int main()
{
    int f,s,g,u,d;

    if(scanf("%d %d %d %d %d", &f,&s,&g,&u,&d)==1){
        while(f>MAX||s<1||g>f||u<0||d>f){
	    if(f>MAX) printf("\nThere must be less than or equal to 100 floors");
	    if(s<1) printf("\nYou must start at a positive-numbered floor");
	    if(g>f) printf("\nThe goal must not be beyond the maximum number of floors");
	    if(u<0) printf("\nThe up button must be a positive number");
	    if(d>f) printf("\nThe down button must not exceed the maximum number of floors");
	    printf("\n");
    }
    }



	//all the cases where you do not need to run BFS
    if(s == g){
        //already there
        printf("\nYou are already at the correct floor");
        return 0;
    } else if(u==0&&s<g){
        //cannot go up
        printf("use the stairs");
        return 0;
    } else if(d==0&&s>g){
        //cannot go down
        printf("use the stairs");
        return 0;
    } else if(u==0&&d==0){
        //cannot go up or down
        printf("use the stairs");
        return 0;
    } else if((s-g)%(GCD(u,d))!=0){
        //GCD is a quick way to determine if you can even get to your destination with the given u and d: the subtraction of s and g give the total number of floors in between, and if it is not divisible by the GCD, then it is not possible to reach your goal
        //if we wanted to, we can simply use this to calculate the number of steps as well as all the floors that will be taken
        //however, this assignment requires us to use BFS(I think), so I will solve the rest of the problem using BFS
        printf("use the stairs");
        return 0;
    }

    //at this point, we know it is possible to get to the goal, we can then run BFS to get all the steps required

    struct Graph* graph = createGraph(f);

    int found=1;
    int start=s;
    int end=f;
    while(found==1){
        while(start<=end) {
            if(start==g) found++;
            if(start+u<end) addEdge(graph,start,start+u);
            start+=u;
        }
        start-=u;
        while(start>=1){
            if(start-d>0) addEdge(graph,start,start-d);
            start-=d;
        }
        start+=d;
    }

    createGraph(f);
    printf("\n");
    BFS(graph,s);
}

int GCD(int u,int d){
    long num1=(long)u;
    long num2=(long)d;

    while(num1*num2!=0){
        if(num1>=num2) num1=num1%num2;
        else num2=num2%num1;
    }
    return(num1+num2);
}

struct Graph* createGraph(int f)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->floors = f;

    graph->adj = malloc(f * sizeof(struct node*));
    graph->visited = malloc(f * sizeof(int));


    int i;
    for (i = 0; i < f; i++) {
        graph->adj[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    struct node* newNode = createNode(dest);
    newNode->next = graph->adj[src];
    graph->adj[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adj[dest];
    graph->adj[dest] = newNode;
}

struct node* createNode(int src)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->floor = src;
    newNode->next = NULL;
    return newNode;
}

void BFS(struct Graph* graph, int s) {

    struct queue* q = createQueue();

    graph->visited[s] = 1;
    enqueue(q, s);

    while(!isEmpty(q)){
        int current = dequeue(q);
        printf("%d\n", current);

       struct node* temp = graph->adj[current];

       while(temp) {
            int adj = temp->floor;

            if(graph->visited[adj] == 0){
                graph->visited[adj] = 1;
                enqueue(q, adj);
            }
            temp = temp->next;
       }
    }
}

struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(struct queue* q, int floor){
    if(q->rear == MAX-1)
        printf("\nQ is Full");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->floors[q->rear] = floor;
    }
}


int dequeue(struct queue* q){
    int item;
    if(isEmpty(q)){
        printf("Q is empty");
        item = -1;
    }
    else{
        item = q->floors[q->front];
        q->front++;
        if(q->front > q->rear){
            printf("Resetting q\n");
            q->front = q->rear = -1;
        }
    }
    return item;
}

int isEmpty(struct queue* q) {
    if(q->rear == -1)
        return 1;
    else
        return 0;
}

