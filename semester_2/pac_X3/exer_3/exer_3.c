#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// реализация без потокового чтения текста
char* text; // весь текст лежит здесь
int pos;    // текущая позиция в тексте

char* token; // текущий токен

//function to scan string and check for unary minus
void scan_string(){
    char pref='\0';
    char cur;   
    int index=0;
    while (1){
        scanf("%c", &cur);
        if(cur=='\n'){
            text[index]='\0';
            break;
        }
        if(isspace(cur)) continue;
        //check for unary minus
        if((pref=='(' || pref=='\0') && cur == '-'){
            text[index] = '0';
            index++;
        }
        text[index] = cur;
        index++;
        pref = cur;
    }
    return ;
}

void readToken(){
    // если символ нулевой, то это конец текста
    if (text[pos] == '\0')
    {
        token[0] = '\0'; // возвращаем токен [eof]
        return;
    }
    // это простой односимвольный токен
    char znaki[] = {'+', '-', '*', '/', '(', ')'};
    for (int i = 0; i < 6; i++)
    {   
        if (text[pos] == znaki[i])
        {
            // копируем его в буфер token и возвращаем
            token[0] = znaki[i];
            token[1] = '\0';
            pos++;
            return;
        }
    }
    // остался один случай: целое число
    int left = pos;
    int index = 0;
    // токен продолжается, пока идут цифры
    while (isdigit(text[pos]))
    {   //(см. функцию isdigit из стандартной библиотеки)
        // копируем отрезок в буфер token и возвращаем
        token[index] = text[pos];
        pos++;
        index++;
    }
    token[index] = '\0';
    return;
}

void peektoken(){
    int oldPos = pos;
    readToken();
    pos = oldPos;
    return;
}

double operation(double a, double b, char oper){
    if(oper=='+'){
        return a + b;
    }else if(oper=='-'){
        return a-b;
    }else if(oper=='*'){
        return a*b;
    }else if(oper=='/'){
        return a/b;
    }
    return 0;
}

// Expr   = Monome | Monome +- Monome | Monome +- ... +- Monome    
// Monome = Atom | Atom */ Atom | Atom */ ... */ Atom            
// Atom   = Number | ( Expr )      
double ParseMonome();

double ParseExpr(){
    double res = ParseMonome(); // в любом случае выражение начинается с монома
    // выражение продолжается, пока после монома идёт плюс или минус
    peektoken();
    char oper;
    while(token[0]=='+' || token[0]=='-'){
        // читаем и запоминаем знак операции (плюс или минус)
        readToken();
        oper = token[0];
        // разбираем идущий далее моном, запоминаем его значение
        double add = ParseMonome();
         // выполняем над res и add операцию oper, запоминаем в res   
        res = operation(res, add, oper);
        peektoken();            
    }
    return res;  // когда выражение закончится, в res будет его значени                                      
}
double ParseAtom();

// пишется аналогично ParseExpr
double ParseMonome(){
    double res = ParseAtom(); // в любом случае выражение начинается с atom
    // выражение продолжается, пока после atoma идёт mult or div
    peektoken();
    char oper;
    while(token[0]=='*' || token[0]=='/'){
        // читаем и запоминаем знак операции (mult or div)
        readToken();
        oper = token[0];
        // разбираем идущий далее atom, запоминаем его значение
        double add = ParseAtom();
         // выполняем над res и add операцию oper, запоминаем в res 
        res = operation(res, add, oper);
        peektoken();  
    }
    return res;  // когда выражение закончится, в res будет его значени  
}

double ParseAtom(){
    // вариант 1: это выражение в скобках
    peektoken();
    if(token[0]=='('){
        readToken(); // не забываем прочитать скобку!
        double res = ParseExpr(); // рекурсивно разбираем выражение
        readToken(); // не забываем прочитать скобку!
        return res;
    }else{ // вариант 2: это целое число
        readToken();
        double num = atoi(token);
        return num;
    }
}

int main(){
    // scan string
    text = (char *)malloc(sizeof(char) * 500005);
    token = (char*) malloc(sizeof(char)*10);
    scan_string();
    pos=0;
    // Рекурсивные вызовы идут по кругу: ParseExpr -> ParseMonome -> ParseAtom -> ParseExpr -> ...
    printf("%0.25g\n", ParseExpr());
    free(text);
    free(token);
    return 0;
}