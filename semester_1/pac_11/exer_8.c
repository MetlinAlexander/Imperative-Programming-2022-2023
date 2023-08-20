#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//string compare
int Compare_Strings(char *Str1, char *Str2){
	int i = 0;
  	while(Str1[i] == Str2[i]){
  		if(Str1[i] == '\0' && Str2[i] == '\0')
	  		break;
		i++;
	}
	return Str1[i] - Str2[i];
}
//string copy
void CopyString(char *Str2, char *Str1){
    int i=0;
    while(1){
        Str2[i] = Str1[i];
        if(Str1[i]=='\0'){
            break;
        }
        i++;
    }
}

// create string from STRING [start, end)
char* create_substring(char* string, int start, int end){
    char* sub = (char*) malloc((end-start +1)*sizeof(char));
    for(int i=start; i<end; i++){
        sub[i-start] = string[i];
        printf("%c ", string[i]);
    }
    sub[end-start] = '\0'; 
    return sub;
}

//my hash fuction for strings
int string_hash(char* string){
    int i=0;
    int hash=0;
    while(string[i]!='\0'){
        hash += ( (int) string[i] )*i;
        // hash = hash % 1000000;
        i++;
    }
    return hash%100000;
}
//node for substring
typedef struct Node_s{
    char* sub;
    struct Node_s* next;
    int colour;
}Node;


//add to hash and return colour
int add_toHash_withColour(Node** hash, char* cur_sub, int* colour_count, int size_of_sub){
    // printf("%s\n", cur_sub);
    int sub_hash = string_hash(cur_sub);
    Node* temp = hash[sub_hash];
    // if first elem
    if(temp==NULL){
        hash[sub_hash] = malloc(sizeof(Node*));
        // temp->next = NULL;
        hash[sub_hash]->sub = (char*) malloc(sizeof(char)*(size_of_sub+1));
        CopyString(hash[sub_hash]->sub, cur_sub);
        hash[sub_hash]->colour = (*colour_count);
        hash[sub_hash]->next = NULL;
        (*colour_count) +=1;
        printf("%d\n", hash[sub_hash]->colour);
        return hash[sub_hash]->colour;
    }
    while(1){
        // printf("%s\n", temp->sub);
        if(Compare_Strings(cur_sub, temp->sub)==0){
            printf("%s %s %d\n", cur_sub, temp->sub, temp->colour);
            return temp->colour;
        }
        if(temp->next==NULL){
            temp->next = malloc(sizeof(Node*));
            temp->next->sub = (char*) malloc(sizeof(char)*(size_of_sub+1));
            CopyString(temp->next->sub, cur_sub);
            temp->next->next = NULL;
            temp->next->colour = (*colour_count);
            (*colour_count) +=1;
            return temp->next->colour;
        }
        temp = temp->next;
    }
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan N and K
    int n, b; fscanf(in, "%d %d\n", &n, &b);
    // printf("n = %d\nb = %d\n", n, b);
    //scan string
    char* string = (char*) malloc((n+1)*sizeof(char));
    fscanf(in, "%s", string);
    printf("%s\n", string);
    //create hash table
    Node** hash  = (Node**) calloc(100000, sizeof(Node*));
    //paint every substring
    char* cur_sub;
    int cur_hash;
    int colour_count = 0;
    int cur_colour;
    for(int i=0; i<n-b+1; i++){
        cur_sub = create_substring(string, i, i+b);
        printf("%s\n", cur_sub);
        // cur_hash = string_hash(cur_sub);
        cur_colour = add_toHash_withColour(hash, cur_sub, &colour_count, b);
        fprintf(out, "%d ", cur_colour);
        // printf("%d ", cur_colour);
        printf("[%d, %d) _%d_ hash %d: %s\n----------------\n", i, (i+b), hash[string_hash(cur_sub)]->colour, string_hash(cur_sub),cur_sub);
    }
   
   
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}