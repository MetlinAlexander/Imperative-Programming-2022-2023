#include <stdio.h>
int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    char symbol;
    char point = '.';
    int answer = 0;
    int cur_word = 0;
    int word_before = 0;
    while(1){
        fscanf (in, "%c", & symbol );
        if(symbol == '\n') break;
        if(word_before==0 && symbol!='.') {
            answer++;
            word_before = 1;
        }
        else if (symbol=='.') word_before = 0;
    }
    fprintf(out, "%d", answer);
    return 0;
}