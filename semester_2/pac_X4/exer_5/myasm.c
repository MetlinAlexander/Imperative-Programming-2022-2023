#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dlfcn.h>

typedef struct State{
    char *regs[256];
} State;

State state;

//scan line in cur_line, if EOF return 0

typedef struct Data_s{
    char plugin[35];
    char command[35];
    int arg_cn;
    char *arg0;
    char *arg1;
    char *arg2;
}Data;

//scan line in final_line, if EOF return 0
int scan_line(char* final_line){
    char line[2000];
    if(fgets(line, 2000, stdin)==NULL){
        return 0;
    }
    int index = 0;
    for(int i=0; i<2000;i++){
        if(line[i]=='\n'){
            final_line[index] = '\0';
            break;
        }
        if(line[i]=='\r') continue;
        final_line[index] = line[i];
        if(final_line[index]==' ' && line[i+1]==' ') continue;
        index++;
    }
    return 1;
}

void extract_data(Data* cur_data, const char* line){
    char temp[1000];
    char core_string[] = {'c', 'o', 'r', 'e', '\0'};
    //try extract plugin name, if nothing then core
    int index=0;
    for(int i=0; i<35; i++){
        if(line[i]==':'){
            temp[i]='\0';
            memcpy(cur_data->plugin, temp, sizeof(char)*(i+1));
            index+=i+1;
            //scan command
            for(int j=0; j<35; j++){
                if(line[index]==' ' || line[index]=='\0'){
                    temp[j]='\0';
                    memcpy(cur_data->command, temp, sizeof(char)*(j+1));
                    index+=1;
                    if(line[index-1]=='\0'){
                        cur_data->arg_cn = 0;
                        return;
                    }
                    break;
                }
                temp[j] = line[index];
                index++;
            }
            break;
        }
        if(line[i]==' ' || line[i]=='\0'){
            temp[i]='\0';
            memcpy(cur_data->plugin, core_string, sizeof(char)*5);
            memcpy(cur_data->command, temp, sizeof(char)*(i+1));
            index+=i+1;
            if(line[i]=='\0'){
                cur_data->arg_cn = 0;
                return;
            }
            break;
        }
        temp[i] = line[i];
    }
    //try scan args
    cur_data->arg_cn = 0;
    int temp_index=0;
    while(line[index]==' '){
        index++;
    }
    while(1){
        if(line[index]=='\0' && temp_index==0){
            break;
        }
        if(line[index]=='\0' || line[index]==' '){
            // cur_data->arg_cn += 1;
            temp[temp_index] = '\0';
            temp_index++;
            if(cur_data->arg_cn==0){
                cur_data->arg_cn+=1;
                cur_data->arg0 = (char*) malloc( (strlen(temp)+1) *sizeof(char));
                memcpy(cur_data->arg0, temp, sizeof(char)*temp_index);
            }else if(cur_data->arg_cn==1){
                cur_data->arg_cn+=1;
                cur_data->arg1 = (char*) malloc( (strlen(temp)+1) *sizeof(char));
                memcpy(cur_data->arg1, temp, sizeof(char)*temp_index);
            }else if(cur_data->arg_cn==2){
                cur_data->arg_cn+=1;
                cur_data->arg2 = (char*) malloc( (strlen(temp)+1) *sizeof(char));
                memcpy(cur_data->arg2, temp, sizeof(char)*temp_index);
                break;
            }
            temp_index=0;
            if(line[index]=='\0') break;
        }
        temp[temp_index] = line[index];
        if(line[index]==' '){
            index++;
            continue;
        }
        index++;
        temp_index++;
    }
}

void data_free_args(Data* cur_data){
    if(cur_data->arg0!=NULL){
        free(cur_data->arg0);
    }
    if(cur_data->arg1!=NULL){
        free(cur_data->arg1);
    }
    if(cur_data->arg2!=NULL){
        free(cur_data->arg2);
    }
    cur_data->arg0 = NULL;
    cur_data->arg1 = NULL;
    cur_data->arg2 = NULL;
}

void call_funct(Data* cur_data){
    //find real funct name
    int len = strlen(cur_data->command);
    char real_funct_name[40];
    memcpy(real_funct_name, cur_data->command, len*sizeof(char));
    real_funct_name[len] = '_';
    real_funct_name[len+1] = (char) (cur_data->arg_cn + '0');
    real_funct_name[len+2] = '\0';
    //find real plugin name
    len = strlen(cur_data->plugin);
    char real_plug_name[40];
    real_plug_name[0] = '.';
    real_plug_name[1] = '/';
    memcpy((real_plug_name+2), cur_data->plugin , len*sizeof(char));
    real_plug_name[len+2] = '.';
    real_plug_name[len+3] = 's';
    real_plug_name[len+4] = 'o';
    real_plug_name[len+5] = '\0';


    // fprintf(stdout, "[%s] [%s] [%d] [%s]\n", real_funct_name, real_plug_name, cur_data->arg_cn, cur_data->plugin);

    //try open dll
    void *hDll = dlopen(real_plug_name, RTLD_LAZY);        // подключаем .so-библиотеку с заданным именем
    if (hDll == NULL) {
        fprintf(stdout, "Missing plugin %s\n", cur_data->plugin);
        return;
    }
    //try call function
    if(cur_data->arg_cn==0){
        typedef void (*Zeroargs)(State*); // тип указателя на функцию
        Zeroargs myfunc = (Zeroargs)dlsym(hDll, real_funct_name); // запрашиваем адрес функции с именем myfunc из .so
        if(myfunc==NULL) {
            fprintf(stdout, "Missing function %s in plugin %s\n", real_funct_name, cur_data->plugin);
            return;
        }
        myfunc(&state);
        dlclose(hDll);  
    }else if(cur_data->arg_cn==1){
        typedef void (*Oneargs)(State*, char*);
        Oneargs myfunc = (Oneargs)dlsym(hDll, real_funct_name);
        if(myfunc==NULL) {
            fprintf(stdout, "Missing function %s in plugin %s\n", real_funct_name, cur_data->plugin);
            return;
        }
        myfunc(&state, cur_data->arg0);
        dlclose(hDll);  
    }else if(cur_data->arg_cn==2){
        typedef void (*twoargs)(State*, char*, char*);
        twoargs myfunc = (twoargs)dlsym(hDll, real_funct_name);
        if(myfunc==NULL) {
            fprintf(stdout, "Missing function %s in plugin %s\n", real_funct_name, cur_data->plugin);
            return;
        }
        myfunc(&state, cur_data->arg0, cur_data->arg1);
        dlclose(hDll);  
    }else if(cur_data->arg_cn==3){
        typedef void (*Threeargs)(State*, char*, char*, char*);
        Threeargs myfunc = (Threeargs)dlsym(hDll, real_funct_name);
        if(myfunc==NULL) {
            fprintf(stdout, "Missing function %s in plugin %s\n", real_funct_name, cur_data->plugin);
            return;
        }
        myfunc(&state, cur_data->arg0, cur_data->arg1, cur_data->arg2);
        dlclose(hDll);  
    }



}

int main(){
    for(int i=0; i<256; i++){
        state.regs[i] = NULL;
    }
    char* cur_line = (char*) malloc(sizeof(char)*1010);
    Data cur_data;
    cur_data.arg0 = NULL;
    cur_data.arg1 = NULL;
    cur_data.arg2 = NULL;
    while(scan_line(cur_line)==1){
        // fprintf(stdout, "%s\n", cur_line);
        extract_data(&cur_data, cur_line);
        // fprintf(stdout, "[%s] [%s] [%c] [%s] [%s] [%s]\n", cur_data.plugin, cur_data.command, cur_data.arg_cn + '0', cur_data.arg0, cur_data.arg1, cur_data.arg2);

        call_funct(&cur_data);


        data_free_args(&cur_data);
    }


    // void *hDll = dlopen("./core.so", RTLD_LAZY);        // подключаем .so-библиотеку с заданным именем
    // typedef void (*Zeroargs)(State*);                 // тип указателя на функцию
    // Zeroargs myfunc = (Zeroargs)dlsym(hDll, "echo_0"); // запрашиваем адрес функции с именем myfunc из .so
    // if(myfunc==NULL) fprintf(stdout, "not found\n");
    // myfunc(&state);
    // // int sum = myfunc(3, 5);                            // вызываем функцию по полученному указателю
    // dlclose(hDll);                                     // опционально: отключаем .so из памяти

    return 0;
}