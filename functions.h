#include "functions.cpp"


Node* CreateEmptyTree();
int GetHeight(Node* node);
Node* SearchDad(int value, Node* node);
void CreateNode(int value, Node** node);
void printTree(Node* Tree, int tabs);
int GetBalance(Node* node);
Node* left_rotate(Node* node);
Node* right_rotate(Node* node);
Node* Double_right_rotate(Node* node);
Node* antecessor(Node *node);
Node* case1(Node **dad, Node **node, Node **root);
Node* case2(Node **dad, Node **node, Node **root);
Node* case3(Node **dad, Node **node, Node **root);
Node* remove(InfoType value, Node *root);
Node* Balance(Node* node);
