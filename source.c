/*Napisati program koji kreira niz od 20 ponavljanja po 100 slucajnih brojeva
u rasponu od 100 i 200
Svaki niz ponavljanja sprema se u binarno stablo nn da se dupliciranima uveca brojac
a)  Ispisati sve koji imaju vise od jednog ponavljanja
b) ispisati sve razl koji imaju vise od jednog ponavljanja u svim serijama
*/
#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 20
struct _arrayNode;
struct _treeNode;
typedef struct _treeNode* treePosition;
typedef struct _arrayNode* arrayPtr;

typedef struct _arrayNode{
    int nbrCounter;
    treePosition root;
}_ARRAYNODE;

typedef struct _treeNode{
    int number;
    int counter;
    treePosition left;
    treePosition right;
}_TREENODE;

arrayPtr createArrayNode();
treePosition createTreeNode();
int setUpArray(arrayPtr);
int mainLoop();
int fillArray(arrayPtr);
treePosition generateSeries(treePosition);
treePosition binaryTreeInsert(treePosition,int);
int printReocurringNumbers(arrayPtr);
int printBinaryTree(treePosition);
int* getReocurringNumbers(treePosition);
int printReocurringSeries(arrayPtr);
treePosition getDuplicates(treePosition,int*,int*);
int getDupsNumber(treePosition);
int contains(int,int*,int);

int main(int argc,char** argv){

    mainLoop();
    return 0;
}

int mainLoop(){
    _ARRAYNODE array[ARRAY_SIZE];
    fillArray(array);
    printReocurringNumbers(array);
    printReocurringSeries(array);
}

int fillArray(arrayPtr array){
    srand(time(NULL));
    if(array==NULL){
        printf("NULL pointer exception!\n");
        return -1;
    }
    int i;
    for(i=0;i<ARRAY_SIZE;i++){
        setUpArray(&(array[i]));
        array[i].root=generateSeries(array[i].root);
        array[i].nbrCounter=getDupsNumber(array[i].root);
    }
    return 0;
}

treePosition generateSeries(treePosition root){
    int i,randomNumber;
    for(i=0;i<100;i++){
        randomNumber=rand()%100+100;
        root=binaryTreeInsert(root,randomNumber);
    }
    return root;
}

int printReocurringNumbers(arrayPtr array){
    int i=0;
    for(i=0;i<ARRAY_SIZE;i++){
        printBinaryTree(array[i].root);
    }
    return 0;
}

int printBinaryTree(treePosition root){
    if(root==NULL)
        return 0;
    printBinaryTree(root->left);
    if(root->counter>1){
        printf("%d\n",root->number);
    }
    printBinaryTree(root->right);
    return 0;
}

int setUpArray(arrayPtr array){
    array->nbrCounter=0;
    array->root=NULL;
    return 0;
}

int printReocurringSeries(arrayPtr array){
    int* reocurringNumbers[ARRAY_SIZE];
    int i,j,flag;
    for(i=0;i<ARRAY_SIZE;i++){
        reocurringNumbers[i]=getReocurringNumbers(array[i].root);
    }
     for(i=1;i<ARRAY_SIZE;i++){
        for(j=0;j<array[i].nbrCounter;j++)
            if(contains(reocurringNumbers[0][j],reocurringNumbers[i],array[i].nbrCounter)){
                printf("%d je sadrzan u svim nizovima!\n",reocurringNumbers[0][j]);
            }
    }
    return 0;

}

int* getReocurringNumbers(treePosition root){
    int* numbers=(int*)malloc(1024*sizeof(int));
    int iter=0;
    getDuplicates(root,numbers,&iter);
    return numbers;
}

int contains(int a,int* array,int len){
    int i=0;
    for(i=0;i<len;i++){
        if(array[i]==a)
            return 1;
    }
    return 0;
}

treePosition getDuplicates(treePosition root,int* nums,int* n){
    if(root==NULL){
        return root;
    }
    getDuplicates(root->left,nums,n);
    if(root->counter>1){
        nums[*n]=root->number;
        (*n)++;
    }
    getDuplicates(root->right,nums,n);
    return root;
}

treePosition binaryTreeInsert(treePosition root,int num){
    if(root==NULL){
        root=createTreeNode();
        root->number=num;
        root->counter++;
        return root;
    }
    if(num>root->number){
        root->right=binaryTreeInsert(root->right,num);
    }
    else if(num<root->number){
        root->left=binaryTreeInsert(root->left,num);
    }
    else{
        printf("**Broj %d vec postoji dodajem ga %d ti put!\n",num,root->counter+1);
        root->counter++;

    }
    return root;
}

int getDupsNumber(treePosition root){
    int n=0;
    if(root==NULL)
        return 0;
    n+=getDupsNumber(root->left);
    if(root->counter>1)
        n++;
    n+=getDupsNumber(root->right);
    return n;
}

arrayPtr createArrayNode(){
    arrayPtr p=(arrayPtr)malloc(sizeof(_ARRAYNODE));
    if(p==NULL){
        printf("Error allocating memory!\n");
        return NULL;
    }
    p->nbrCounter=0;
    p->root=NULL;
    return p;
}

treePosition createTreeNode(){
    treePosition p=(treePosition)malloc(sizeof(_TREENODE));
    if(p==NULL){
        printf("Error allocating memory!\n");
        return NULL;
    }
    p->counter=0;
    p->left=NULL;
    p->right=NULL;
    return p;
}
