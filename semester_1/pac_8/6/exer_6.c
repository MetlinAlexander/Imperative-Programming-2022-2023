#include <stdio.h>
#include <math.h>

// help to analize what situatin will be
int check_what_first_bait(unsigned char firstBait){
    //1 situations
    if( ((unsigned char) 1) & (firstBait>>7) == (unsigned char) 0){
        return 1;
    }
    //2 situations
    if((firstBait>>5) == ((unsigned char) 0b110) ){
        return 2;
    }
    //3 situations
    if((firstBait>>4) == ((unsigned char) 0b1110)){
        return 3;
    }
    // //4 situations
    if((firstBait>>3) == ((unsigned char) 0b11110)){
        return 4;
    }
    //otherwise
    return 0;
}
//1 0xxxxxxx   7
int first_situation(FILE* out, unsigned char firstBait){
    long int encode = 0; // var for encode
    for(int i=0; i<7; i++){
        encode += ((int) ((firstBait>>i) & ((unsigned char) 1))) * pow(2, i);
    }
    //write num
    fwrite(&encode, sizeof(long int), 1, out);
    return 1;
}

//2 110xxxxx 10xxxxxx   11
int second_situation(FILE* in, FILE* out, unsigned char firstBait){
    long int encode = 0; // var for encode
    unsigned char temp_bait;
    int end_of_File;
    //scan 1 part
    for(int i=0; i<5; i++){
        encode += ((int) ((firstBait>>i) & ((unsigned char) 1))) * pow(2, i+6);
    }
    //scan second part
    end_of_File =  fread(&temp_bait, sizeof(unsigned char), 1, in);
    //check hard mistake
    if(end_of_File==0){
        return 0;
    }
    if((temp_bait>>6) != ((unsigned char) 0b10) ){
        return 0;
    }
    for(int i=0; i<6; i++){
        encode += ((int) ((temp_bait>>i) & ((unsigned char) 1))) * pow(2, i);
    }
    //check overlong encoding
    if(encode<=0b1111111){
        encode = 0xFFFD;
        fwrite(&encode, sizeof(long int), 1, out);
        return 1;
    }
    //write num
    fwrite(&encode, sizeof(long int), 1, out);
    return 1;
}

// 3 1110xxxx 10xxxxxx 10xxxxxx 16
int third_situation(FILE* in, FILE* out, unsigned char firstBait){
    long int encode = 0; // var for encode
    unsigned char temp_bait;
    int end_of_File;
    //scan 1 part
    for(int i=0; i<4; i++){
        encode += ((int) ((firstBait>>i) & ((unsigned char) 1))) * pow(2, i+12);
    }
    //scan second part
    end_of_File =  fread(&temp_bait, sizeof(unsigned char), 1, in);
    //check hard mistake
    if(end_of_File==0){
        return 0;
    }
    if((temp_bait>>6) != ((unsigned char) 0b10) ){
        return 0;
    }
    for(int i=0; i<6; i++){
        encode += ((int) ((temp_bait>>i) & ((unsigned char) 1))) * pow(2, i+6);
    }
    //scan third part
    end_of_File =  fread(&temp_bait, sizeof(unsigned char), 1, in);
    //check hard mistake
    if(end_of_File==0){
        return 0;
    }
    if((temp_bait>>6) != ((unsigned char) 0b10) ){
        return 0;
    }
    for(int i=0; i<6; i++){
        encode += ((int) ((temp_bait>>i) & ((unsigned char) 1))) * pow(2, i);
    }
    //check if in (55296, 57343)
    if(encode>=55296 & encode <=57343){
        encode = 0xFFFD;
        fwrite(&encode, sizeof(long int), 1, out);
        return 1;
    }
    //check overlong encoding
    if(encode<=0b11111111111){
        encode = 0xFFFD;
        fwrite(&encode, sizeof(long int), 1, out);
        return 1;
    }
    //write num
    fwrite(&encode, sizeof(long int), 1, out);
    return 1;
}

// 4 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx   21
int fourth_situation(FILE* in, FILE* out, unsigned char firstBait){
    long int encode = 0; // var for encode
    unsigned char temp_bait;
    int end_of_File;
    //scan 1 part
    for(int i=0; i<3; i++){
        encode += ((int) ((firstBait>>i) & ((unsigned char) 1))) * pow(2, i+18);
    }
    //scan second part
    end_of_File =  fread(&temp_bait, sizeof(unsigned char), 1, in);
    //check hard mistake
    if(end_of_File==0){
        return 0;
    }
    if((temp_bait>>6) != ((unsigned char) 0b10) ){
        return 0;
    }
    for(int i=0; i<6; i++){
        encode += ((int) ((temp_bait>>i) & ((unsigned char) 1))) * pow(2, i+12);
    }
    //scan third part
    end_of_File =  fread(&temp_bait, sizeof(unsigned char), 1, in);
    //check hard mistake
    if(end_of_File==0){
        return 0;
    }
    if((temp_bait>>6) != ((unsigned char) 0b10) ){
        return 0;
    }
    for(int i=0; i<6; i++){
        encode += ((int) ((temp_bait>>i) & ((unsigned char) 1))) * pow(2, i+6);
    }
    //scan fouth part
    end_of_File =  fread(&temp_bait, sizeof(unsigned char), 1, in);
    //check hard mistake
    if(end_of_File==0){
        return 0;
    }
    if((temp_bait>>6) != ((unsigned char) 0b10) ){
        return 0;
    }
    for(int i=0; i<6; i++){
        encode += ((int) ((temp_bait>>i) & ((unsigned char) 1))) * pow(2, i);
    }
    //check if in (55296, 57343)
    if(encode>=55296 & encode <=57343){
        encode = 0xFFFD;
        fwrite(&encode, sizeof(long int), 1, out);
        return 1;
    }
    // check if more then 0x10FFFF  1114111
    if(encode>1114111){
        encode = 0xFFFD;
        fwrite(&encode, sizeof(long int), 1, out);
        return 1;
    }
    //check overlong encoding
    if(encode<=0b1111111111111111){
        encode = 0xFFFD;
        fwrite(&encode, sizeof(long int), 1, out);
        return 1;
    }
    //write num
    fwrite(&encode, sizeof(long int), 1, out);
    return 1;
}


int main(){
    // open files
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");
    //scan bites
    int end_of_File;
    unsigned char cur_bait;
    int count;
    int rez;
    while(1){
        // read first 8 bits
        end_of_File = fread(&cur_bait, sizeof(unsigned char), 1, in);
        // check what situation will be next

        // check if this not end
        if(end_of_File==0){
            break;
        }
        //check how many baits will be
        count = check_what_first_bait(cur_bait);
        //1 situations
        if(count==1){
            rez = first_situation(out, cur_bait);
            //check if mistake
            if(rez!=1){
                break;
            }
        }else
        //2 situations
        if(count==2){
            rez = second_situation(in, out, cur_bait);
            //check if mistake
            if(rez!=1){
                break;
            }
        }else
        //3 situations
        if(count==3){
            rez = third_situation(in, out, cur_bait);
            //check if mistake
            if(rez!=1){
                break;
            }
        }else
        //4 situations
        if(count==4){
            rez = fourth_situation(in, out, cur_bait);
            //check if mistake
            if(rez!=1){
                break;
            }
        }else{ //otherwise
            break;
        }
    }
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}

/*
длина шаблон битов
1 0xxxxxxx                              7
2 110xxxxx 10xxxxxx                     11
3 1110xxxx 10xxxxxx 10xxxxxx            16
4 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx   21
*/
