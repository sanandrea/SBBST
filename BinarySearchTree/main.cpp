//
//  main.cpp
//  BinarySearchTree
//
//  Created by Andi Palo on 20/11/2016.
//  Copyright © 2016 Andi Palo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} Node;


typedef struct asciinode_struct
{
    asciinode_struct * left, * right;
    //length of the edge from this node to its children
    int edge_length;
    int height;
    int lablen;
    //-1=I am left, 0=I am root, 1=right
    int parent_dir;
    //max supported unit32 in dec, 10 digits max
    char label[11];
} asciinode;

Node* create(int val);
Node* add(Node* root, int val);
Node* remove(Node* root, int val);
void print(Node* root, int value);
Node* find(Node *root, int value);
void freeBST(Node* root);


void printInorder(Node *node);
void printPreorder(Node *node);
void printPostorder(Node *node);
void prettyPrint(Node* node);

//Balancing ==> https://en.wikipedia.org/wiki/Day%E2%80%93Stout%E2%80%93Warren_algorithm
Node* balance(Node* node);
void treeToVine(Node *node, int &size);
void vineToTree(Node *node, int size);
void compression(Node* node, int size);
int fullSize(int size);


int _print_t(Node *tree, int is_left, int offset, int depth, char s[20][255]);

int main(int argc, const char * argv[]) {
    int option; // user's entered option will be saved in this variable
    Node *input = NULL;
    
    do {
        //Displaying Options for the menu
        std::cout << "1) Create BST " << std::endl;
        std::cout << "2) Add element to BST " << std::endl;
        std::cout << "3) Remove element from BST" << std::endl;
        std::cout << "4) Find element" << std::endl;
        std::cout << "5) Print BST" << std::endl;
        std::cout << "6) Free BST" << std::endl;
        std::cout << "7) Balance BST" << std::endl;
        std::cout << "8) Exit Program " << std::endl;
        //Prompting user to enter an option according to menu
        std::cout << "Please select an option : ";
        std::cin >> option;  // taking option value as input and saving in variable "option"
        
        if (option == 1) {
            int element;
            if (input != NULL) {
                std::cout << "BST is already created, select other options" << std::endl;
                continue;
            }
            std::cout << "Creating BST" << std::endl;
            std::cout << "Provide root element value" << std::endl;
            std::cin >> element;
            input = create(element);
        }
        else if (option == 2) // Checking if user selected option 1
        {
            int element;
            if (input == NULL) {
                std::cout << "Please create BST first" << std::endl;
                continue;
            }
            std::cout << "Adding element to BST" << std::endl;
            std::cout << "Provide element value" << std::endl;
            std::cin >> element;
            input = add(input, element);
        }
        else if (option == 3) // Checking if user selected option 2
        {
            int element;
            if (input == NULL) {
                std::cout << "Please create BST first" << std::endl;
                continue;
            }
            std::cout << "Removing element to BST" << std::endl;
            std::cout << "Provide element value to remove" << std::endl;
            std::cin >> element;
            input = remove(input, element);
        }
        else if (option == 4) // Checking if user selected option 3
        {
            int element;
            if (input == NULL) {
                std::cout << "Please create BST first" << std::endl;
                continue;
            }
            std::cout << "Find element in BST" << std::endl;
            std::cout << "Provide element value to find" << std::endl;
            std::cin >> element;
            find(input, element);
        }
        else if (option == 5) // Checking if user selected option 4
        {
            int element;
            std::cout << "Print all BST" << std::endl;
            std::cout << "Provide order: " << std::endl;
            std::cout << "1) Preorder" << std::endl;
            std::cout << "2) Inorder" << std::endl;
            std::cout << "3) Postorder" << std::endl;
            std::cout << "4) Pretty" << std::endl;
            std::cin >> element;
            switch (element) {
                case 1:
                    printPreorder(input);
                    std::cout<<std::endl;
                    break;
                case 2:
                    printInorder(input);
                    std::cout<<std::endl;
                    break;
                case 3:
                    printPostorder(input);
                    std::cout<<std::endl;
                case 4:
                    prettyPrint(input);
                    std::cout<<std::endl;
                default:
                    break;
            }
        }
        else if (option == 6)
        {
            std::cout << "Removing all BST" << std::endl;
            freeBST(input);
            input = NULL;
        }
        else if (option == 7)
        {
            std::cout << "Balancing BST" << std::endl;
            Node* res = balance(input);
            prettyPrint(res);
            
        }
        else //if user has entered invalid choice (other than 1,2,3 or 4)
        {
            std::cout << "Quitting program..." << std::endl;
            break;
        }
    } while (option <= 7);
    return 0;
}

Node* create(int val) {
    size_t sizeNode = sizeof(Node);
    
    Node *newNode = (Node*)malloc(sizeNode);
    
    newNode->value = val;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

Node* add(Node* input, int val) {
    /* If the tree is empty, return a new node */
    if (input == NULL) return create(val);
    
    /* Otherwise, recur down the tree */
    if (val < input->value)
        input->left  = add(input->left, val);
    else if (val > input->value)
        input->right = add(input->right, val);
    
    /* return the (unchanged) node pointer */
    return input;
    
}
Node* FindMin(Node *node)
{
    if(node==NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }
    if(node->left) /* Go to the left sub tree to find the min element */
        return FindMin(node->left);
    else
        return node;
}
Node* FindMax(Node *node)
{
    if(node==NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }
    if(node->right) /* Go to the left sub tree to find the min element */
        return FindMax(node->right);
    else
        return node;
}

Node* remove(Node* node, int data) {

    
    Node *temp;
    if(node==NULL)
    {
        printf("Element Not Found");
    }
    else if(data < node->value)
    {
        node->left = remove(node->left, data);
    }
    else if(data > node->value)
    {
        node->right = remove(node->right, data);
    }
    else
    {
        /* Now We can delete this node and replace with either minimum element
         in the right sub tree or maximum element in the left subtree */
        if(node->right && node->left)
        {
            /* Here we will replace with minimum element in the right sub tree */
            temp = FindMin(node->right);
            node -> value = temp->value;
            /* As we replaced it with some other node, we have to delete that node */
            node -> right = remove(node->right,temp->value);
        }
        else
        {
            /* If there is only one or zero children then we can directly
             remove it from the tree and connect its parent to its child */
            temp = node;
            if(node->left == NULL)
                node = node->right;
            else if(node->right == NULL)
                node = node->left;
            free(temp); /* temp is longer required */
        }
    }
    return node;
}

Node* find(Node *input, int value) {
    if(input==NULL)
    {
        /* Element is not found */
        return NULL;
    }
    if(value > input->value)
    {
        /* Search in the right sub tree. */
        return find(input->right,value);
    }
    else if(value < input->value)
    {
        /* Search in the left sub tree. */
        return find(input->left,value);
    }
    else
    {
        /* Element Found */
        return input;
    }
}

void printInorder(Node *node)
{
    if(node==NULL)
    {
        return;
    }
    printInorder(node->left);
    printf("%d ",node->value);
    printInorder(node->right);
}

void printPreorder(Node *node)
{
    if(node==NULL)
    {
        return;
    }
    printf("%d ",node->value);
    printPreorder(node->left);
    printPreorder(node->right);
}

void printPostorder(Node *node)
{
    if(node==NULL)
    {
        return;
    }
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ",node->value);
}

void PrettyPrint(Node *node){
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");
    
    _print_t(node, 0, 0, 0, s);
    
    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

void freeBST(Node* root){
    if (root == NULL) {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}


//*******************
int _print_t(Node *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;
    
    if (!tree) return 0;
    
    sprintf(b, "(%3d)", tree->value);
    
    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);
    
#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];
    
    if (depth && is_left) {
        
        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';
        
        s[depth - 1][offset + left + width/2] = '.';
        
    } else if (depth && !is_left) {
        
        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';
        
        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];
    
    if (depth && is_left) {
        
        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';
        
        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';
        
    } else if (depth && !is_left) {
        
        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';
        
        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif
    
    return left + width + right;
}


/*
 ***************** Balancing ******************
 */

Node* balance(Node* node){
    Node *pseudo = create(0);
    pseudo->right = node;
    int count;
    treeToVine(pseudo, count);
    vineToTree(pseudo, count);
    Node *result = pseudo->right;
    free(pseudo);
    return result;
}
void treeToVine(Node *root, int &size){
    Node *vineTail, *remainder, *tempPtr;
    
    vineTail = root;
    remainder = vineTail->right;
    size = 0;
    while ( remainder != NULL )
    {//If no leftward subtree, move rightward
        if ( remainder->left == NULL )
        {  vineTail = remainder;
            remainder = remainder->right;
            size++;
        }
        //else eliminate the leftward subtree by rotations
        else  // Rightward rotation
        {  tempPtr = remainder->left;
            remainder->left = tempPtr->right;
            tempPtr->right = remainder;
            remainder = tempPtr;
            vineTail->right = tempPtr;
        }
    }
}

int fullSize(int size){
    int Rtn = 1;
    while ( Rtn <= size )     // Drive one step PAST FULL
        Rtn = Rtn + Rtn + 1;   // next pow(2,k)-1
    return Rtn/2;
}

void vineToTree(Node *root, int size){
    int full_count = fullSize (size);
    compression(root, size - full_count);
    for ( size = full_count ; size > 1 ; size /= 2 )
        compression ( root, size / 2 );
}
void compression(Node* root, int size){
    Node *scanner = root;
    
    for ( int j = 0; j < size; j++ )
    {//Leftward rotation
        Node *child = scanner->right;
        scanner->right = child->right;
        scanner = scanner->right;
        child->right = scanner->left;
        scanner->left = child;
    }  // end for
}
