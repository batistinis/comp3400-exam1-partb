#include<stdio.h>
#include<stdlib.h>

struct pcb {
    int process_id;
    int parent_pid;
    char state;
    int registers[8];
};

struct queue_header {
    int size, capacity, head, tail;
    struct pcb* array;
};

void print_pcb(struct pcb current){
    printf("The PID of this process is %d \n", current.process_id);
    printf("The PID of this process' parent is %d \n", current.parent_pid);
    printf("This process is in the %c state \n", current.state);
    printf("The contents of this process' registers are:\n [%d, %d, %d, %d, %d, %d, %d, %d]\n", current.registers[0], current.registers[1], current.registers[2], current.registers[3], current.registers[4], current.registers[5], current.registers[6], current.registers[7]);
    return;
}

struct queue_header* createQueue(int max) {
    struct queue_header* queue =(struct queue_header*)malloc(sizeof(struct queue_header));
    queue->capacity = max;
    queue->head = 0;
    queue->size = 0;

    queue->tail = queue->capacity - 1;
    queue->array = (struct pcb*)malloc(queue->capacity * sizeof(struct pcb));
    return queue;
};

void enqueue(struct queue_header* queue, struct pcb* process){
    if (queue->size == queue->capacity) return;
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->array[queue->tail] = *process;
    queue->size++;

    printf("The following process was added to the queue");
    print_pcb(*process);
    return;
}

void dequeue(struct queue_header* queue) {
    if (queue->size == 0) return;
    struct pcb* process = &queue->array[queue->head];
    queue->head = (queue->head++);
    queue->size = (queue->head++);

    printf("The following process was removed from the queue");
    print_pcb(*process);
    free(process);
    //process->process_id = NULL;
    //process->parent_pid = NULL;
    //process->state = NULL;
    //process->registers[0] = NULL;
    //process->registers[1] = NULL;
    //process->registers[2] = NULL;
    //process->registers[3] = NULL;
    //process->registers[4] = NULL;
    //process->registers[5] = NULL;
    //process->registers[6] = NULL;
    //process->registers[7] = NULL;
    return;
}

int main() {
    struct queue_header* queue;
    struct pcb *pcb7 = (struct pcb*) malloc(sizeof(struct pcb));
    struct pcb *pcb2 = (struct pcb*) malloc(sizeof(struct pcb));
    struct pcb *pcb4 = (struct pcb*) malloc(sizeof(struct pcb));
    struct pcb *pcb9 = (struct pcb*) malloc(sizeof(struct pcb));

    pcb7->process_id = 123;
    pcb7->parent_pid = 456;
    pcb7->state = 'w';
    pcb7->registers[0] = 85;
    pcb7->registers[1] = 34;
    pcb7->registers[2] = 456;
    pcb7->registers[3] = 9876;
    pcb7->registers[4] = 3529;
    pcb7->registers[5] = 3456;
    pcb7->registers[6] = 36678;
    pcb7->registers[7] = -2345;

    pcb2->process_id = 789;
    pcb2->parent_pid = 123;
    pcb2->state = 'r';
    pcb2->registers[0] = 4567;
    pcb2->registers[1] = 2;
    pcb2->registers[2] = 0;
    pcb2->registers[3] = 987;
    pcb2->registers[4] = 23;
    pcb2->registers[5] = 6;
    pcb2->registers[6] = 0;
    pcb2->registers[7] = 0;

    pcb4->process_id = 3;
    pcb4->parent_pid = 5;
    pcb4->state = 'r';
    pcb4->registers[0] = 234;
    pcb4->registers[1] = 684;
    pcb4->registers[2] = 0;
    pcb4->registers[3] = 23456;
    pcb4->registers[4] = 8765;
    pcb4->registers[5] = 923;
    pcb4->registers[6] = -23456;
    pcb4->registers[7] = 0;

    pcb9->process_id = 9876543;
    pcb9->parent_pid = 3;
    pcb9->state = 't';
    pcb9->registers[0] = 3254;
    pcb9->registers[1] = 987654;
    pcb9->registers[2] = -30000;
    pcb9->registers[3] = 234;
    pcb9->registers[4] = 794;
    pcb9->registers[5] = 3;
    pcb9->registers[6] = 1;
    pcb9->registers[7] = 0;

    queue = createQueue(2);

    enqueue(queue, pcb7);
    enqueue(queue, pcb2);
    dequeue(queue);
    dequeue(queue);
    enqueue(queue, pcb9);
    enqueue(queue, pcb4);


}

