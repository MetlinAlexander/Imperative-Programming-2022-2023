#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//compare actorName in table 2
int compare_table_2(const void * x1, const void * x2){
    ActorInMovie** str1 = (ActorInMovie**) x1;
    ActorInMovie** str2 = (ActorInMovie**) x2;
    // printf("%s %s\n", (*(str1))->ActorName, (*(str2))->ActorName);
    int rez = (Compare_Strings ((*(str1))->ActorName, (*(str2))->ActorName)) ;
    if(rez>0) return 1;
    if (rez==0) return 0;
    if(rez<0) return -1;
}


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
    //sort table 2
    qsort(table_inMovie, m, sizeof(ActorInMovie*), compare_table_2);
    // for(int i=0; i<m;i++){
    //     printf("%s\n", table_inMovie[i]->ActorName);
    // }
    // JOIN with bin_search
    // Join_result** join_table_3 = (Join_result**) malloc((n*m)*sizeof(Join_result*));
    // int cur_index_in_3=0;
    int ind_r = m;
    for(int i=0; i<n; i++){
        ind_r = m;
        //bin searsh
        if( (Compare_Strings(table_inMovie[0]->ActorName, table_acter_bio[i]->Name)<=0 ) & (Compare_Strings(table_inMovie[m-1]->ActorName, table_acter_bio[i]->Name)>=0) ){
            //vars for bin search
            int start = 0, end =(m-1), ind=0;
            while(end>=start & ind >= 0){
                ind = (start+end)/2;
                // printf("%d = [%d, %d]\n", ind, start, end);
                if ( Compare_Strings(table_acter_bio[i]->Name, table_inMovie[ind]->ActorName)<0)
                    end = ind - 1;
                else if (Compare_Strings(table_acter_bio[i]->Name, table_inMovie[ind]->ActorName)>0)
                    start = ind + 1;
                else{
                    if((end - start) == 1){
                        if(Compare_Strings(table_acter_bio[i]->Name, table_inMovie[start]->ActorName)==0) {
                            ind = start;
                        }
                        else if (Compare_Strings(table_acter_bio[i]->Name, table_inMovie[end]->ActorName)==0) {
                            ind = end;
                        }
                    }
                    break;
                }
            }
            if(Compare_Strings(table_acter_bio[i]->Name, table_inMovie[ind]->ActorName)==0) {
                ind_r = ind;
                if(Compare_Strings(table_acter_bio[i]->Name, table_inMovie[m-1]->ActorName)==0) {
                    ind_r = m-1;
                    ind = m-1;
                }
                for(int j=ind; j<m-1; j++){
                    if(Compare_Strings(table_acter_bio[i]->Name, table_inMovie[j+1]->ActorName)!=0){
                        ind_r = j;
                        break;
                    }
                }
            }
        }
        //end of bin searsh
        if(ind_r<m){
            while(ind_r>=0){
                if(Compare_Strings(table_acter_bio[i]->Name, table_inMovie[ind_r]->ActorName)!=0){
                    break;
                }
                // printf("%d %s\n", ind_r, table_inMovie[ind_r]->ActorName);
                fprintf(out, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n", table_acter_bio[i]->Name, table_acter_bio[i]->BirthYear, table_acter_bio[i]->Country, table_inMovie[ind_r]->ActorName, table_inMovie[ind_r]->MovieName);
                ind_r--;
            }
            // printf("%d %s\n", ind_r, table_inMovie[ind_r]->ActorName);
        }
        
    }
    //print join table
    // for(int i=0; i<cur_index_in_3; i++){
    //     fprintf(out, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n", join_table_3[i]->Name, join_table_3[i]->BirthYear, join_table_3[i]->Country, join_table_3[i]->ActorName, join_table_3[i]->MovieName);
    //     // printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", join_table_3[i]->Name, join_table_3[i]->BirthYear, join_table_3[i]->Country, join_table_3[i]->ActorName, join_table_3[i]->MovieName);
    // }
    //free space
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
} 