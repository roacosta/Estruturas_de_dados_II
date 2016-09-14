#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


using namespace std;




int main(void){

    Node* tree = CreateEmptyTree();
    int value = 0;

    do{
        printf("\n\nOpções: \n\n");
        printf("1 = Inserir\n");
        printf("2 = Remover\n");
        printf("3 = Imprimir\n");

        printf("\nOpção: ");
        cin >> value;

        switch(value){
            case 1:
                printf("\n Valor a ser inserido: ");
                cin >> value;
                CreateNode(value, &tree);
                tree = Balance(tree);
                break;
            case 2:
                printf("\n Valor a ser removido: ");
                cin >> value;
                tree = removet(tree,tree,value);
                tree = Balance(tree);
                break;
            case 3:

                printTree(tree, 0);
                break;
            default:
                break;
        }
        if (value == 0){
            break;
        }
    } while(1);
    cout << "Altura: " << GetHeight(tree) << "\n";
}
