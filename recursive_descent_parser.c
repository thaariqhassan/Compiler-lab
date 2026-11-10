#include<stdio.h>
char inp[20];
int top = 0;

int E1(){
    int i = 0;
    
    if (inp[top] == '+') {
        top++;
        if (inp[top] == 'i') {
        top++;
        E1();
        }
    }
    else{
        if (inp[top] == '$') return 1;
        else return 0;
    }
    
}

void E(){
   
    if (inp[top] == 'i') {
        top++;

        if (E1()) printf("Valid\n");
        else printf("Invalid\n");
    }
    else printf("Invalid\n");
    
}

int main(){

    printf("Grammar:\n");
    printf("E  → i E'\n");
    printf("E' → + i E' | ε\n");

    printf("Enter input: ");
    scanf("%s",inp);
    E();

    return 0;
}