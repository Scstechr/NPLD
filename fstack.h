#ifndef FSTACK_H
#define FSTACK_H

typedef struct{
  //storing values
  int inum;
  double dnum;
  //indices
  int startpoint;
  int next;
  int prev;
  //parameters
  int size;
} Fstack;

void InitFstack(Fstack *list, int size){
  for(int i=0;i<size;i++) {
    list[i].inum = i;
    list[i].dnum = 0;
    list[i].next = i+1;
    list[i].prev = i-1;
  }
  list[0].startpoint = 0;
  list[0].size = size;
}

void DeleteFstack(Fstack *list, int decoded){
  if(decoded<list[0].size){
    list[list[decoded].prev].next = list[decoded].next;
    if(list[decoded].next!=list[0].size) {
      //excluding the tail;
      list[list[decoded].next].prev = list[decoded].prev;
      if(decoded<=list[0].startpoint){
        list[0].startpoint = list[decoded].next;
      }
    }
  } else {
	  ;
    //printf("\nERROR\n");
  }
}

int CountFstack(Fstack *list){
  int index; index = list[0].startpoint; int size; size = 0;
  if(list[0].startpoint!=list[0].size){
    while(1){
      size++;
      index = list[index].next;
      if(index>=list[0].size) break;
    }
  }
  return size;
}

void PrintFstack(Fstack *list){
  int index; index = list[0].startpoint;
  while(1){
    printf("index:%3d\t%3d\t%.4lf\n",index, list[index].inum, list[index].dnum);
    index = list[index].next;
    if(index>=list[0].size) break;
  }
}
#endif
