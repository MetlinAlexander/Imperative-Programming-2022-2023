#include <stdio.h>
#include <stdlib.h>


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

// 1 TABLE ActorBio (
//     Name varchar(30),
//     BirthYear int,
//     Country varchar(10)
// );

// 2 TABLE ActorInMovie (
// ActorName varchar(30),
// MovieName varchar(20)
// );

// table 1
typedef struct ActorBio_s{
    char Name[30+1] ;
    int BirthYear;
    char Country[10+1];
} ActorBio;
// table 2
typedef struct ActorInMovie_s{
    char ActorName[30+1];
    char MovieName[20+1];
}ActorInMovie;

// input line to table 1
void input_line_1(FILE* in, ActorBio** table_1, int line){
    char cur_char;
    // scan name
    // input "
    fscanf(in, "%c", &cur_char);
    for(int i=0; i<31; i++){
        fscanf(in, "%c", &cur_char);
        if(cur_char=='"'){
            table_1[line]->Name[i] = '\0';
            break;
        }else{
            table_1[line]->Name[i] = cur_char;
        }
    }
    //scan Birth Year
    fscanf(in, " %d ", &table_1[line]->BirthYear);
    //scan country
    fscanf(in, "%c", &cur_char);
    for(int i=0; i<11; i++){
        fscanf(in, "%c", &cur_char);
        if(cur_char=='"'){
            table_1[line]->Country[i] = '\0';
            break;
        }else{
            table_1[line]->Country[i] = cur_char;
        }
    }
    //scan \n
    fscanf(in, "%c", &cur_char);
}
// input line to table 2
void input_line_2(FILE* in, ActorInMovie** table_2, int line){
    char cur_char;
    // scan Actorname
    // input "
    fscanf(in, "%c", &cur_char);
    for(int i=0; i<31; i++){
        fscanf(in, "%c", &cur_char);
        if(cur_char=='"'){
            table_2[line]->ActorName[i] = '\0';
            break;
        }else{
            table_2[line]->ActorName[i] = cur_char;
        }
    }
    //scan space
    fscanf(in, "%c", &cur_char);
    //scan MovieName
    fscanf(in, "%c", &cur_char);
    for(int i=0; i<21; i++){
        fscanf(in, "%c", &cur_char);
        if(cur_char=='"'){
            table_2[line]->MovieName[i] = '\0';
            break;
        }else{
            table_2[line]->MovieName[i] = cur_char;
        }
    }
    //scan \n
    fscanf(in, "%c", &cur_char);
}
// table 3
typedef struct Join_result_s{
    char Name[30+1] ;
    int BirthYear;
    char Country[10+1];
    char ActorName[30+1];
    char MovieName[20+1];
}Join_result;



int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan len of 1 table
    int n; fscanf(in, "%d\n", &n);
    //scan 1 table
    ActorBio** table_acter_bio = (ActorBio**) malloc(sizeof(ActorBio*)*n);
    for(int i=0; i<n; i++){
        table_acter_bio[i] = (ActorBio*) malloc(sizeof(ActorBio));
        input_line_1(in, table_acter_bio, i);
    }
    //scan len of 1 table
    int m; fscanf(in, "%d\n", &m);
    //scan table 2
    ActorInMovie** table_inMovie = (ActorInMovie**) malloc(m*sizeof(ActorInMovie*));
    for(int i=0; i<m; i++){
        table_inMovie[i] = (ActorInMovie*) malloc(sizeof(ActorInMovie));
        input_line_2(in, table_inMovie, i);
    }
    // JOIN
    Join_result** join_table_3 = (Join_result**) malloc((n*m)*sizeof(Join_result*));
    int cur_index_in_3=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if( Compare_Strings(table_acter_bio[i]->Name, table_inMovie[j]->ActorName)==0 ){
                //add new line to join table
                join_table_3[cur_index_in_3] = (Join_result*) malloc(sizeof(Join_result));
                CopyString(join_table_3[cur_index_in_3]->Name, table_acter_bio[i]->Name);
                join_table_3[cur_index_in_3]->BirthYear = table_acter_bio[i]->BirthYear;
                CopyString(join_table_3[cur_index_in_3]->Country, table_acter_bio[i]->Country);
                CopyString(join_table_3[cur_index_in_3]->ActorName, table_inMovie[j]->ActorName);
                CopyString(join_table_3[cur_index_in_3]->MovieName, table_inMovie[j]->MovieName);
                cur_index_in_3++;
            }
        }
    }
    //print join table
    for(int i=0; i<cur_index_in_3; i++){
        fprintf(out, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n", join_table_3[i]->Name, join_table_3[i]->BirthYear, join_table_3[i]->Country, join_table_3[i]->ActorName, join_table_3[i]->MovieName);
        // printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", join_table_3[i]->Name, join_table_3[i]->BirthYear, join_table_3[i]->Country, join_table_3[i]->ActorName, join_table_3[i]->MovieName);
    }
    //free space
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
} 