// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int length;
    int num_elements;
}ArrInfo;

void* copy(int* source, int* dest,int n){
    memcpy(dest, source, n*sizeof(int));
}

void** DynamicArray(int first, int length){
    ArrInfo* p1 = (ArrInfo *)malloc(sizeof(ArrInfo));
    p1->length = length;
    p1->num_elements = 1;
    
    void** d_array = (void **)malloc(2*sizeof(void*));
    int* data = (int *)malloc(p1->length * sizeof(int));
    data[0] = first;
    d_array[0] = p1;
    d_array[1] = data;
    
    return d_array;
}

void Append(void** d_array, int element)
{
    ArrInfo* info = (ArrInfo*)d_array[0];
    int* data = (int*)d_array[1];
    
    if(info->length == info->num_elements){
        info->length *=2;
        int* new_data = (int *)malloc(info->length*sizeof(int));
        copy(data, new_data,info->num_elements);
        new_data[info->num_elements] = element;
        d_array[1] = new_data;
        info->num_elements +=1;
        free(data);
        print_array(d_array);
        return;
    }
    data[info->num_elements] = element;
    info->num_elements += 1;
    print_array(d_array);
}

void RemoveLastItem(void** d_array)
{
  ArrInfo* info = (ArrInfo*)d_array[0];
  int* data = (int*)d_array[1];
  
  if(info->num_elements == 0)
  {
    printf("Nothing to remove");
  }
  free(data[info->num_elements]);
  info->num_elements -= 1; 

}


void print_array(void** d_array){
    ArrInfo* info = (ArrInfo*)d_array[0];
    int* data = (int*)d_array[1];
    for(int i = 0; i< info->num_elements; i++){
        printf("L'élement %d : %d\n",i+1,data[i]);
    }
    int reste = info->length - info->num_elements;
    printf("Espace restant est : %d\n",reste);
}
int main() {
    void ** arr = DynamicArray(0, 4);
    print_array(arr);
    Append(arr,2);
    Append(arr,5);
    Append(arr,6);
    Append(arr,9);
    return 0;
}