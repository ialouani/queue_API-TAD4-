#include"./queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

static void creation_file_vide(){
  struct queue* f=queue_empty();
  assert(is_empty(f));
  assert(queue_size(f)==0);
  debug_data(f);
  push_front(f,1);
  push_front(f,2);
  push_front(f,3);
  assert(queue_size(f)==3);
  assert(!is_empty(f));
  assert(find(f,2)==1 && find(f,1)==1 && find(f,3)==1 && find(f,0)==0 && find(f,4)==0 && find(f,5)==0);
  debug_data(f);
  //reste pop_back;;
  //apres..///
  free2(f);
  printf("OK: tests 1/2 passés.\n");
  return;
}

static void test_last_removing(){
  struct queue* f=queue_empty();
  push_front(f,11);
  push_front(f,22);
  push_front(f,33);
  push_front(f,55);
  push_front(f,66);
  printf("***********************\n\n\n");
  debug_data(f);
  pop_back(f);
  debug_data(f);
  assert(queue_size(f)==4);
  pop_back(f);pop_back(f);
  assert(queue_size(f)==2);
  debug_data(f);
  pop_back(f);debug_data(f);
  push_front(f,100);pop_back(f);push_front(f,200);push_front(f,300);
  pop_back(f);debug_data(f);
  free2(f);
  printf("OK: 2/2 tests passes.\n");
  return;
}
  
int main(){
  creation_file_vide();
  test_last_removing();
  puts("TOUT EST OK.\n*******************************************\n");
  return 0;
}
