#include <stdio.h>
#include <stdlib.h>


//    _ k _              Это называется "нумерация кучи".
//   /     \             Отец вершины v имеет номер (v-1)/2
//  2k+1  2k+2

typedef struct Node_s{         //тип вершины бинарного дерева 
    int value;
}Node;

void swap(Node** heap, int ind_a, int ind_b){
    int temp = heap[ind_a]->value;
    heap[ind_a]->value = heap[ind_b]->value;
    heap[ind_b]->value = temp;
}

void SiftUp(Node** heap, int index){
    //if this root
    if(index==0) return ;
    //parent == root
    if((index-1)<= 1){
        if(heap[0]->value > heap[index]->value){
            swap(heap, 0, index);
        }
        return ;
    }
    //otherwise
    int p_ind = (index-1)/2;
    if(heap[p_ind]->value > heap[index]->value){
        swap(heap, p_ind, index);
        SiftUp(heap, p_ind);
    }

}

void Add_to_Heap(int elem, Node** heap, int* lenHeap){
    heap[*lenHeap] = (Node*) malloc(sizeof(Node));
    heap[*lenHeap]->value = elem;
    (*lenHeap)+=1;
    //siftup ...
    SiftUp(heap, (*lenHeap)-1);
}

void SiftDown(Node** heap, int index, int max_index){
    //index of sons
    int l_son = 2*index+1;
    int r_son = 2*index+2;
    // if no sons
    if(r_son >= max_index && l_son >= max_index){
        return ;
    }
    //if onlu left
    if(r_son >= max_index){
        if(heap[l_son]->value < heap[index]->value){
            swap(heap, l_son, index);
            SiftDown(heap, l_son, max_index);
        }
        return ;
    }
    //if only right
    if(l_son >= max_index){
        if(heap[r_son]->value < heap[index]->value){
            swap(heap, r_son, index);
            SiftDown(heap, r_son, max_index);
        }
        return ;
    }
    //otherwise
    int min;
    if(heap[r_son]->value < heap[l_son]->value){
        min = r_son;
    }else{
        min = l_son;
    }
    if(heap[min]->value < heap[index]->value){
        swap(heap, min, index);
        SiftDown(heap, min, max_index);
    }

}

void ExtractMin(Node** heap, int* len_of_heap){
    if(*len_of_heap==1){
        free(heap[0]);
        return ;
    }
    //корень всегда имеет номер 0
    (*len_of_heap)-=1;
    swap(heap, 0, *len_of_heap); //меняем корень с самым правым листом (он является последним
    //удаляем этот лист
    free(heap[*len_of_heap]);
    //инвариант от корня к сыновьям может нарушаться, запускаем просеивание вниз
    SiftDown(heap, 0, (*len_of_heap)); 
}

int main(){
    // open files
    FILE *in = fopen("input.bin", "rb");
    FILE *out = fopen("output.bin", "wb");
    // scan len of elem
    int n;
    fread(&n, sizeof(int), 1, in);
    //heap
    Node** heap = (Node**) calloc((n+1), sizeof(Node*));  //массив элементов, в котором хранится куча
    int len = 0; //текущий размер кучи    
    //scan elements and sort them
    int cur;
    for(int i=0; i<n; i++){
        fread(&cur, sizeof(int), 1, in);
        Add_to_Heap(cur, heap, &len);
    }
    //print sort arr
    for(int i=0; i<n; i++){
        fwrite(&heap[0]->value, sizeof(int), 1, out);
        ExtractMin(heap, &len);
        // ExtractMin
        
    }
    //free space
    free(heap);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}