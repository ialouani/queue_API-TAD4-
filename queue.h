#ifndef ID_queue
#define ID_queue


struct queue{
  int length;
  struct capsule* begin;
  struct capsule* end;
};
//typedef struct queue queue;
struct capsule{
  int data;
  struct capsule* next;
};
//typedef struct capsule capsule;

struct queue* queue_empty(void);
int is_empty(struct queue*);
unsigned int queue_size(struct queue*);
int find(struct queue*, int);//implementee apres push_front && pop_back.
void push_front(struct queue*,int);
void pop_back(struct queue*);
void free2(struct queue*);
void debug_data(struct queue*);

#endif
