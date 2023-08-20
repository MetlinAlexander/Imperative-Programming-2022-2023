#include <stdio.h>
#include <stdlib.h>

typedef struct Tokens_s{
    int num;    //количество слов в строке
    char **arr; //массив слов (каждый элемент –- строка, т.е. char*)
} Tokens;
// tokens: структура, в которую нужно положить результаты
// str: строка, в которой нужно искать слова
// delims: все символы-разделители в виде строки
void tokensSplit(Tokens *tokens, const char *str, const char *delims){
    // printf("--%s\n--%s\n", str, delims);
    // check what should funstions do
    if(tokens->arr==NULL){ // count words and initialization array
        // printf("arr is empty\n");
        tokens->num=0;
        int word_before = 0;
        int in_delims= 0;
        for(int i=0; str[i]; i++){
            // check if cur char in delims
            for(int j=0; delims[j]; j++){
                if(str[i]==delims[j]){
                    in_delims=1;
                    break;
                }
                else in_delims = 0;
            }
            // check if now word
            if(word_before==0 && in_delims==0) {
                tokens->num++;
                word_before = 1;
            }
            else if (in_delims==1) word_before = 0;
            // printf("-%c-", str[i]);
        }
        // initialization array
        tokens->arr = (char**) malloc((tokens->num + 1) * sizeof(char*)); // выделение памяти под указатели на массивы
    }
    else{
        // printf("arr is full\n");
        // count words and write words
        tokens->num=0;
        int cur_word_index=0;
        char temp[1000000];
        int temp_index=0;
        int cur_size = 0;
        int word_before = 0;
        int in_delims= 0;
        int end_i=0;
        for(int i=0; str[i]; i++){
            end_i++;
            // check if cur char in delims
            for(int j=0; delims[j]; j++){
                if(str[i]==delims[j]){
                    in_delims=1;
                    break;
                }
                else in_delims = 0;
            }
            // check if now word
            if(word_before==0 && in_delims==0) { // update num
                tokens->num++;
            }
            if(in_delims==0) { // write word in temp
                cur_size++;
                temp[temp_index]=str[i];
                temp_index++;
                word_before = 1;
            }
            else if (in_delims==1) { // update vars
                word_before = 0;
            }
            if(in_delims==1 && cur_size!=0) { // write word in array
                temp[temp_index]='\0';
                // printf("%s %d %d %d\n", temp, temp_index, cur_size, cur_word_index);
                // give memory with malloc
                tokens->arr[cur_word_index]  = (char*) malloc((cur_size+1) * sizeof(char));
                // tokens->arr[cur_word_index]  = temp
                for(int z=0; z<cur_size+1; z++){
                    tokens->arr[cur_word_index][z] = temp[z];
                }
                // printf("%s----\n", tokens->arr[cur_word_index]);
                // update vars
                temp_index=0;
                cur_size=0;
                cur_word_index++;
            }
        }
        end_i--;
        // check if cur char in delims
        for(int j=0; delims[j]; j++){
            if(str[end_i]==delims[j]){
                in_delims=1;
                break;
            }
            else in_delims = 0;
        }
        if(in_delims==0){
            temp[temp_index]='\0';
            // printf("%s %d %d %d\n", temp, temp_index, cur_size, cur_word_index);
            // give memory with malloc
            tokens->arr[cur_word_index]  = (char*) malloc((cur_size+1) * sizeof(char));
            // tokens->arr[cur_word_index]  = temp
            for(int z=0; z<cur_size+1; z++){
                tokens->arr[cur_word_index][z] = temp[z];
            }
        }

    }
}
//удаляет все ресурсы внутри tokens
void tokensFree(Tokens *tokens){
    if(tokens->arr!=NULL){ // check if pointers is exist
        for(int i=0; i<tokens->num; i++){
            free(tokens->arr[i]);
        }
        free(tokens);
    }
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan string
    char string[1000001]; fscanf(in, "%s", &string);
    // const string;
    // array of separators
    char separ[] = {'.', ',', ':', ';', '\0'};
    // printf("%s\n", separ);
    // printf("%s\n", string);
    // make struct tokens
    Tokens token; token.arr=NULL;token.num=0;
    // start functions firts time
    tokensSplit(&token, &string[0], &separ[0]);
    // start functions second time
    tokensSplit(&token, &string[0], &separ[0]);
    // print results
    // printf("%d\n", token.num);
    fprintf(out, "%d\n", token.num);
    for(int i=0; i<token.num; i++){
        fprintf(out, "%s\n", token.arr[i]);
        // printf("%s\n", token.arr[i]);
    }
    // clean memory
    tokensFree(&token);
    // for tests
    // tokensFree(&token);
    // tokensFree(&token);
    return 0;
}