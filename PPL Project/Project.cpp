/*  
    This program converts infix expression to postfix, infix expression to prefix, postfix to infix, prefix to infix.
    This program assume that there are Five operators: (*, /, +, -,^) 
	In infix expression and operands can be of single-digit only.
    Expression were pushed in the the form of Linked list.
    This program will not work for fractional numbers.
    Further this program does not check whether infix expression is valid or not in terms of number of operators and operands.
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
# define SIZE 100
int top = -1;

struct node
{
    char data;
    struct node *link;
    struct node *prev;
} 
*stack[100];

void push(node *str)
{
    if(top > 100){
        printf("Stack OverFlow");
    }
    else{
        top++;
        stack[top] = str;
    }
}
node *pop()
{   
    struct node *item;
    if(top < 0){
        printf("Stack UnderFlow");
    }
    else{
        item = stack[top];
        top -= 1;
    }
    return item;
}
/* 
define function that is used to determine whether any symbol is operator or not 
this fucntion returns 1 if symbol is opreator else return 0.
*/
bool is_Operator(char symbol)
{
    if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-'){
        return 1;
    }
    else{
        return 0;
    }
}
/* 
    define fucntion that is used to assign precendence to operator.
    Here ^ denotes exponent operator.
    In this fucntion we assume that higher integer value means higher precendence 
*/
int precedence(char symbol)
{
    if(symbol == '^'){
        return 3;
    }
    else if(symbol == '*' || symbol == '/'){
        return 2;
    }
    else if(symbol == '+' || symbol == '-'){
        return 1;
    }
    else{
        return 0;
    }
}
void InfixToPostfix(char infix[],char postfix[])
{
    int j = 0;
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp -> data = '(';
    temp -> link = NULL;
    temp -> prev = NULL;
    push(temp);
    strcat(infix,")");
    char incoming = infix[0];
    for(int i = 0 ; incoming != '\0' ; i++){
        incoming = infix[i];
        if(incoming == '\0'){
            break;
        }
        else if(incoming == '('){
            struct node *First = (struct node*)malloc(sizeof(struct node));
            First -> data = '(';
            First -> link = NULL;
            First -> prev = NULL;
            push(First);
        }
        else if(isdigit(incoming) || isalpha(incoming)){
            postfix[j] = incoming;
            j++;
        }
        else if(is_Operator(incoming)){
            struct node *op = pop();
            while(is_Operator(op -> data) == 1 && precedence(op -> data) > precedence(incoming)){
                postfix[j] = op -> data;       // so pop all higher precendence operator and add them to postfix expresion
                j++;
                op = pop();
            }
            push(op);  	// because just above while loop will terminate we have popped one extra item for which conditon failed
            struct node *incoming_op = (struct node*)malloc(sizeof(struct node));
            incoming_op -> data = incoming;
            incoming_op -> link = NULL;
            incoming_op -> prev = NULL;
            push(incoming_op);                    // now push the incoming operator
        }
        else if(incoming == ')'){      // if current symbol is ')' then pop and keep popping until '(' encounterd
            struct node *temp5 = pop();
            while(temp5 -> data != '('){
                postfix[j] = temp5 -> data;
                j++;
                temp5 = pop();
            }
        }
        else{       // if current symbol is neither operand not '(' nor ')' and nor operator
            printf("Invalid infix Expression.\n");
        }
    }
    postfix[j] = '\0';
}
int getSize(char infix[])
{
    int count = 0;
    char temp = infix[0];
    while(temp != '\0'){
        temp = infix[count];
        count++;
    }
    return count-1;
}
void swap(char *A,char *B)
{
    char temp = *A;
    *A = *B;
    *B = temp;
}
void reverse(char *infix,int size)
{
    for(int i = 0; i < size/2 ; i++){
        swap(&infix[i],&infix[size-1-i]);
    }
    for(int i = 0 ; i < size ; i++){
        if(infix[i] == ')'){
            infix[i] = '(';
        }
        else if(infix[i] == '('){
            infix[i] = ')';
        }
    }
}
void InfixToPrefix(char infix[],char prefix[])
{
    strcat(infix,")");  
    int size = getSize(infix);
    reverse(infix,size);
    InfixToPostfix(infix,prefix);
    size = getSize(prefix);
    reverse(prefix,size);
}
void PostfixToInfix(char postfix[],char infix[])
{   
    int j = 0;
    struct node *op1;
    struct node *op2;
    struct node *temp;
    char incoming = postfix[0];
    for(int i = 0 ; incoming != '\0' ; i++){
        incoming = postfix[i];
        if(incoming == '\0'){
            break;
        }
        else if(isalpha(incoming)){
            temp = (struct node *)malloc(sizeof(struct node));
            temp -> data = incoming;
            temp -> link = NULL;
            temp -> prev = NULL;
            push(temp);
        }
        else if(is_Operator(incoming)){
            op1 = pop();
            op2 = pop();
            temp = (struct node *)malloc(sizeof(struct node));
            temp -> data = incoming;
            temp -> prev = op2;
            temp -> link = op1;
            push(temp);
        }
    }
}
void PrefixToInfix(char prefix[],char infix[])
{
    int j = 0;                         
    struct node *op1;              
    struct node *op2;
    struct node *temp;
    char incoming = prefix[0];
    for(int i = 0 ; incoming != '\0' ; i++){
        incoming = prefix[i];
        if(incoming == '\0'){
            break;
        }
        else if(isalpha(incoming)){
            temp = (struct node *)malloc(sizeof(struct node));
            temp -> data = incoming;
            temp -> link = NULL;
            temp -> prev = NULL;
            push(temp);
        }
        else if(is_Operator(incoming)){
            op1 = pop();
            op2 = pop();
            temp -> data = incoming;
            temp -> prev = op1;
            temp -> link = op2;
            push(temp);
        }
    }
}
void displayPostfixToInfix(struct node *temp)
{
	if (temp == NULL){
        return ;
    }
    else{
		displayPostfixToInfix(temp -> prev);
		printf("%c", temp -> data);
        displayPostfixToInfix(temp -> link);
	}
}
void displayPrefixToInfix(struct node *temp)
{
	if (temp == NULL){
        return ;
    }
    else{
		displayPrefixToInfix(temp -> link);
        printf("%c", temp -> data);
        displayPrefixToInfix(temp -> prev);
	}
}
int main()
{
    char infix[SIZE], postfix[SIZE];
    char prefix[SIZE];
    int input;
    int size;
    printf("ASSUMPTION: The infix expression contains single letter variables and single digit constants only.\n");
    printf("Hit 1 For Infix to Prefix Conversion \nHit 2 For Infix to Postfix Conversion\nHit 3 For Postfix to Infix Conversion \nHit 4 For Prefix to Infix Conversion \n");
    scanf("%d",&input);
    switch(input){
        case 1: 
            printf("Input Infix Expression: ");
            scanf("%s",&infix);
            InfixToPrefix(infix,prefix);
            printf("Prefix Expression: ");
            puts(prefix);
            break;
        case 2:
            printf("Input Infix Expression: ");
            scanf("%s",&infix);
            InfixToPostfix(infix,postfix);
            printf("Postfix Expression: ");
            puts(postfix);
            break;
        case 3:
            printf("Input Postfix Expression: ");
            scanf("%s",&postfix);
            PostfixToInfix(postfix,infix);
            printf("Infix Expression: ");
            displayPostfixToInfix(pop());
            break;
        case 4:
            printf("Input Prefix Expression: ");
            scanf("%s",&prefix);
            size = getSize(prefix);
            reverse(prefix,size);
            PostfixToInfix(prefix,infix);
            printf("Infix Expression: ");
            displayPrefixToInfix(pop());
            break;
    }
}