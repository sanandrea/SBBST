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


Node* create(int val);

Node* add(Node* root, int val);

Node* remove(Node* root, int val);

void print(Node* root, int value);

Node* find(Node *root, int value);

void freeBST(Node* root);


void PrintInorder(Node *node);
void PrintPreorder(Node *node);
void PrintPostorder(Node *node);

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    
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
        std::cout << "7) Exit Program " << std::endl;
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
            std::cin >> element;
            switch (element) {
                case 1:
                    PrintPreorder(input);
                    std::cout<<std::endl;
                    break;
                case 2:
                    PrintInorder(input);
                    std::cout<<std::endl;
                    break;
                case 3:
                    PrintPostorder(input);
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
        else //if user has entered invalid choice (other than 1,2,3 or 4)
        {
            std::cout << "Quitting program..." << std::endl;
            break;
        }
    } while (option <= 6);
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

void PrintInorder(Node *node)
{
    if(node==NULL)
    {
        return;
    }
    PrintInorder(node->left);
    printf("%d ",node->value);
    PrintInorder(node->right);
}

void PrintPreorder(Node *node)
{
    if(node==NULL)
    {
        return;
    }
    printf("%d ",node->value);
    PrintPreorder(node->left);
    PrintPreorder(node->right);
}

void PrintPostorder(Node *node)
{
    if(node==NULL)
    {
        return;
    }
    PrintPostorder(node->left);
    PrintPostorder(node->right);
    printf("%d ",node->value);
}

void freeBST(Node* root){
    if (root == NULL) {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}
