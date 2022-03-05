#include"./queue.h"
#include<stdio.h>
#include<stdlib.h>

struct queue* queue_empty(){
  struct queue* queue=(struct queue*)calloc(1,sizeof(struct queue));
  queue->length=0;
  //queue->begin et queue->end sont de type struct capsule*
  //donc devront etre implementes explicitement ici meme si calloc
  //en gros malloc rend le meme service ici des le but de calloc avec
  //LE GESTIONNAIRE: brk/(--sbrk--).
  queue->begin=(struct capsule*)calloc(1,sizeof(struct capsule));
  queue->end=queue->begin;
  return queue;
}

int is_empty(struct queue* queue){
  return queue->length==0;
}

unsigned int queue_size(struct queue* queue){
  return queue->length;
}

void push_front(struct queue* queue,int x){
  //queue contient les champs pointeurs vers le debut et la fin +
  //l'indicateur de longueur COURANTE.

  //queue->length++;(probleme apres(effet de bord interne!!! pour les tests
  //ca peut tout plenter!!!)).///

  /*struct capsule* add=(struct capsule*)malloc(sizeof(*add));
  add->data=x;
  add->next=NULL;*/
  //processus d'affectation direct=>autre methode de structurer
  //les elements de la file a 100% et en modifier selon notre hiarchie
  //le prototype ainsi que le contenu(<<) de la fonction qui retourne
  //une nouvelle **instance d'une filevide;;
  if(is_empty(queue)){
    queue->length++;
    queue->begin->data=x;
    queue->begin->next=NULL;
    queue->end->data=x;
    queue->end->next=NULL;
    return;
  }
  else{
    /*
    queue->length++;//return dans les 2 structures de controle --contenus
    //cela implique que la factorisation du code en terme de mise a jour
    //de l'information queue->length est impossible a priori ici suivant
    //cette logique de code.
    
    //le champ begin de queue ne vas pas bouger.
    struct capsule* add=(struct capsule*)malloc(sizeof(*add));
    add->data=x;
    add->next=NULL;*/
    /*struct capsule* tmp=queue->end;
    tmp->next=add;
    queue->end=add;*///up peu direct.
    /*
    struct capsule* temp=queue->begin;
    while(temp->next!=NULL) temp=temp->next;
    temp->next=add;
    queue->end=add;
    return;*/
    //ca fait un push a la dernier position alors que ca devrait en faire des
    //le debut car c'est une file avec le schema, on defile depuis la fin
    //et on enfile depuis le debut.
    queue->length++;
    struct capsule* add=(struct capsule*)malloc(sizeof(*add));
    add->data=x;
    add->next=NULL;
    struct capsule* debut=queue->begin;
    queue->begin=add;
    add->next=debut;
    return;
  }
}

void pop_back(struct queue* queue){
  if(is_empty(queue)){
    fprintf(stdout,"removing an element from empty queue(error)\n");
    exit(0);
  }
  else if(queue_size(queue)==1){
    //queue->length=0;(voir les dernieres lignes)
    //free(queue->begin);
    //free(queue->end);(creation depuis ces elements dans push_front())./////
    /*queue->begin=NULL;
      queue->end=NULL;*///ca ne sert a rien
    //on doit retourner a la configuration de base
    //avec une 'sentinelle forte d'information fonctionnelle: set_size()=..///'.
    free2(queue);
    queue=queue_empty();//pas essentiel vu le test de sortie de
    //(premier) ::debug_data sur is_mepty soit la fameuse info --sentinelle:
    //QUI EST:>> ''queue->length''.
    
    return;
  }
  else{//size>=2.
    queue->length--;
    struct capsule* but;
    struct capsule* temp=queue->begin;
    while(temp->next!=NULL){
      but=temp;
      temp=temp->next;
    }
    //but represente l'avant derniere capsule.
    but->next=NULL;
    queue->end=but;
    free(temp);
    return;
  }
}

int find(struct queue* queue, int y){
  if(is_empty(queue)==1) return 0;
  else{
    struct capsule* debut=queue->begin;
    while(debut!=NULL){
      if(debut->data==y) return 1;
      debut=debut->next;
    }
    return 0;
  }
}

void free2(struct queue* queue){
  if(is_empty(queue)){
    //free(queue->end);
    free(queue->begin);
    free(queue);
  }
  else if(queue_size(queue)==1){
    free(queue->begin);
    //free(queue->end);(ca va se faire comme ca..; il faut voir
    //l'origine mere du probleme).
    free(queue);
  }
  else{
    struct capsule* inter=queue->begin;
    struct capsule* inter_2;
    while(inter!=NULL){
      inter_2=inter->next;
      free(inter);
      inter=inter_2;
    }
    //contenance meme DANS UN SHEMA DE POINTAGE
    //justifie la mise en commentaire de free(queue->end)..
    //free(queue->end);//presence de divergence des que empty depase
    //par enfilement la taille de 1 elmnt.///
    //voir plus haut.
    //pas deuxieme methode deja supprimee pas mise
    //en commentaire plutot.////
    free(queue);
  }
  return;
}

void debug_data(struct queue* queue){
  if(is_empty(queue)){
    printf("Aucune chose a afficher: file vide.\n");
    return;
  }
  else{//queue->begin!=NULL
    struct capsule* debut=queue->begin;
    while(debut!=NULL){
      printf("%d\t",debut->data);
      debut=debut->next;
    }
    printf("\n");
    return;
  }
}
