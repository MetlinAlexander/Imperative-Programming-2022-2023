#include <stdio.h>
#include <stdlib.h>



/*
3) Кольцевой буфер (в принципе, тоже на массиве).
Решение проблемы с очередью: давайте зациклим конец массива на начало.
Тогда вместо массива у нас будет кольцо элементов, и это полностью устраняет проблему.

Реализация:
  int arr[1<<20];
  int beg, end;             //может быть beg > end --- тогда последовательность переходит через край массива

  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |8|9|A| | | | | | |1|2|3|4|5|6|7|
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         ^           ^
       (end)       (beg)

При выполнении операций нужно не забывать циклически переносить счётчики beg и end, когда это нужно.

Кольцевой буфер размера N достаточен, пока количество живых элементов меньше N.
Кольцевой буфер реализует все операции дека за O(1), в т.ч. добавления в начало.

*/

int scan_hex(FILE* in){
    char temp;
    fscanf(in, "%c", &temp);
    if((int) temp<=57){
        return ((int) temp) - 48;
    }else{
        return ((int) temp) - 55;
    }
}
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan len and scan how many operations
    int n, m; fscanf(in, "%d %d\n", &n, &m); 
    // printf("%d %d\n", n, m);
    //make two ring buffers of cards
    //make left
    int* left = (int*) calloc(2*n+1, sizeof(int));
    int l_beg=n+1, l_end=n+1, l_count=0;
    //fill left 
    for(int i=1; i<n+1; i++){
        left[l_end] = i;
        l_end++;
        l_count++;
    }
    if(l_end>=2*n+1) l_end = 0;
    // printf("%d %d\n", l_beg, l_end);
    //make right
    int* right = (int*) calloc(2*n+1, sizeof(int));
    int r_beg=n+1, r_end=n+1, r_count;
    //fill right 
    for(int i=1; i<n+1; i++){
        right[r_end] = (-1)*i;
        r_end++;
        r_count++;
    }
    if(r_end>=2*n+1) r_end = 0;
    // printf("%d %d\n", r_beg, r_end);
    //scan and do operations

    int oper, cur_bit, temp_card, end_ind;
    for(int i=0; i<m; i++){
        oper = scan_hex(in);
        /*
        1 вверх
        2
        3
        4
        5 низ
        */
        if(oper==0 || oper==15 || oper==10 || oper==5){
            continue;
        }
        //if stopka is empty
        if(  ((oper>>3)&&1) == 1  & r_count==0) continue;
        if(  ((oper>>3)&&1) == 0  & l_count==0) continue;
        //solve what type of operation will be
        //0001 1
        if(oper==1){ 
            temp_card = left[l_beg];
            l_beg++;
            if(l_beg==2*n+1) l_beg = 0;
            //-----------
            left[l_end] = temp_card;
            l_end++;
            if(l_end>=2*n+1) l_end = 0;
            //-----------
            // l_count--;
            // r_count++;
        }
        //0010 2
        if(oper==2){
            temp_card = left[l_beg];
            l_beg++;
            if(l_beg==2*n+1) l_beg = 0;
            //-----------
            if(r_beg==0) r_beg = 2*n+1;
            right[--r_beg] = temp_card;
            //-----------
            l_count--;
            r_count++;
        }
        //0011 3
        if(oper==3){
            temp_card = left[l_beg];
            l_beg++;
            if(l_beg==2*n+1) l_beg = 0;
            //-----------
            right[r_end] = temp_card;
            r_end++;
            if(r_end>=2*n+1) r_end = 0;
            //-----------
            l_count--;
            r_count++;
        }
        //0100 4
        if(oper==4){
            if(l_end==0) l_end = 2*n+1; 
            temp_card = left[--l_end];
            //-----------
            if(l_beg==0) l_beg = 2*n+1;
            left[--l_beg] = temp_card;
            //-----------
        }
        //0110 6
        if(oper==6){
            if(l_end==0) l_end = 2*n+1; 
            temp_card = left[--l_end];
            //-----------
            if(r_beg==0) r_beg = 2*n+1;
            right[--r_beg] = temp_card;
            //-----------
            l_count--;
            r_count++;
        }
        //0111 7
        if(oper==7){
            if(l_end==0) l_end = 2*n+1; 
            temp_card = left[--l_end];
            //-----------
            right[r_end] = temp_card;
            r_end++;
            if(r_end>=2*n+1) r_end = 0;
            //-----------
            l_count--;
            r_count++;
        }
        //1000 8
        if(oper==8){
            temp_card = right[r_beg];
            r_beg++;
            if(r_beg==2*n+1) r_beg = 0;
            //-----------
            if(l_beg==0) l_beg = 2*n+1;
            left[--l_beg] = temp_card;
            //------
            l_count++;
            r_count--;
        }
        //1001 9
        if(oper==9){
            temp_card = right[r_beg];
            r_beg++;
            if(r_beg==2*n+1) r_beg = 0;
            //-----------
            left[l_end] = temp_card;
            l_end++;
            if(l_end>=2*n+1) l_end = 0;
            //------
            l_count++;
            r_count--;
        }
        //1011 B 11
        if(oper==11){
            temp_card = right[r_beg];
            r_beg++;
            if(r_beg==2*n+1) r_beg = 0;
            //-----------
            right[r_end] = temp_card;
            r_end++;
            if(r_end>=2*n+1) r_end = 0;
            //------
            // l_count++;
            // r_count--;
        }
        //1100 C 12
        if(oper==12){
            if(r_end==0) r_end = 2*n+1; 
            temp_card = right[--r_end];
            //-----------
            if(l_beg==0) l_beg = 2*n+1;
            left[--l_beg] = temp_card;
            //------
            l_count++;
            r_count--;
        }
        //1101 D 13
        if(oper==13){
            if(r_end==0) r_end = 2*n+1; 
            temp_card = right[--r_end];
            //-----------
            left[l_end] = temp_card;
            l_end++;
            if(l_end>=2*n+1) l_end = 0;
            //------
            l_count++;
            r_count--;
        }
        //1110 E 14
        if(oper==14){
            if(r_end==0) r_end = 2*n+1; 
            temp_card = right[--r_end];
            //-----------
            if(r_beg==0) r_beg = 2*n+1;
            right[--r_beg] = temp_card;
        }


        // printf("\n");
    }



    //print cards
    //left
    // printf("%d ", l_count);
    fprintf(out, "%d ", l_count);
    if(l_count>0){
        if(l_beg<l_end){
            //situation when everuthing in one part
            for(int i=l_beg; i<l_end; i++){
                // printf("%d ", left[i]);
                fprintf(out, "%d ", left[i]);
            }
        }else{
            //print 1 part
            for(int i=l_beg; i<2*n+1; i++){
                // printf("%d ", left[i]);
                fprintf(out, "%d ", left[i]);
            }
            //print 2 part
            for(int i=0; i<l_end; i++){
                // printf("%d ", left[i]);
                fprintf(out, "%d ", left[i]);
            }
        }
    }
    // printf("\n");
    fprintf(out, "\n");
    //right
    // printf("%d ", r_count);
    fprintf(out, "%d ", r_count);
    if(r_count>0){
        if(r_beg<r_end){
            //situation when everuthing in one part
            for(int i=r_beg; i<r_end; i++){
                // printf("%d ", right[i]);
                fprintf(out, "%d ", right[i]);
            }
        }else{
            //print 1 part
            for(int i=r_beg; i<2*n+1; i++){
                // printf("%d ", right[i]);
                fprintf(out, "%d ", right[i]);
            }
            //print 2 part
            for(int i=0; i<r_end; i++){
                // printf("%d ", right[i]);
                fprintf(out, "%d ", right[i]);
            }
        }
    }
    // printf("\n");
    // fprintf(out, "\n");
    //free space
    free(left);
    free(right);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}

/*
//scan 8 bit
        cur_bit = ((int) 1) & (oper>>3);
        printf("%d", cur_bit);
        if(cur_bit==0){

        }else{

        }
        //scan 4 bit
        cur_bit = ((int) 1) & (oper>>2);
        printf("%d", cur_bit);
        if(cur_bit==0){

        }else{
            
        }
        // scan 2 bit
        cur_bit = ((int) 1) & (oper>>1);
        printf("%d", cur_bit);
        if(cur_bit==0){

        }else{
            temp_card = 
        }
        // scan 1 bit
        cur_bit = ((int) 1) & oper;
        printf("%d", cur_bit);
        if(cur_bit==0){

        }else{
            
        }
*/