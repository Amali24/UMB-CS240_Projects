#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Position{
    int line;
    int offset;
    struct Position *next;
};

struct TreeNode{
    char *word;
    struct Position *position;
    struct TreeNode *parent;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* newNode(char* word, struct Position pos){
    struct TreeNode *new_node = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    printf("made a node\n");
    new_node->position = (struct Position*) malloc(1000 * sizeof(struct Position));
    printf("made a pos\n");
    new_node->position->line = pos.line;
    new_node->position->offset = pos.offset;
    printf("assigned a pos\n");
    new_node->position->next = NULL;
    new_node->word = (char*) malloc(100 * sizeof(char));
    printf("made a string\n");
    strcpy(new_node->word, word);
    printf("copied string \"%s\" to node\n", word);
    new_node->left = new_node->right = NULL;
    printf("set the branches to null\n\n");
    return new_node;
}

struct Position* newPosition(int line, int offset){
    struct Position *pos = (struct Position*) malloc(sizeof(struct Position*));
    pos->line = line;
    pos->offset = offset;
    pos->next = NULL;
    return pos;
}

struct TreeNode *insertNode(struct TreeNode *tree, char *word, struct Position pos){
    printf("passed word: %s\n", word);
    printf("passed position: %d, %d\n\n", pos.line, pos.offset);

    if(tree == NULL){
        printf("tree was null\n");
        struct TreeNode *temp = newNode(word, pos);
        printf("made new node...\n\n");
        return temp;
    }

    if(strcmp(word, tree->word) < 0){
        printf("word <, going left\n");
        tree->left = insertNode(tree->left, word, pos);
    }

    else if(strcmp(word, tree->word) > 0){
        printf("word >, going right\n"); 
        tree->right = insertNode(tree->right, word, pos);
    }

    else if (strcmp(word, tree->word) == 0){
        printf("word found\n");
        while(tree->position->next != NULL){
            tree->position = tree->position->next;
        }
        tree->position->next = &pos;
    }

    return tree;
}

struct TreeNode *removeWord(struct TreeNode *tree, char *word){
    return NULL;
}

struct TreeNode *removePosition(struct TreeNode *tree, struct Position pos){
    return NULL;
}

struct TreeNode *removeLine(struct TreeNode *tree, int line){
    return NULL;
}

void output(struct TreeNode *tree){
    // if can go left, do
    // if can't go left, go right.
    // if can't go either, print
    // go up
        if (tree != NULL){
            output(tree->left);
            printf("%s \n", tree->word);
            output(tree->right);
        }

}

int main(){
    const int MAX_NUM_LINES = 1000;
    const int MAX_NUM_COMMANDS = 100;
    const int MAX_LINE_LENGTH = 1000;
    const int MAX_NUM_NODES = 1000;

    char commands[MAX_NUM_COMMANDS][MAX_LINE_LENGTH];
    char text[MAX_NUM_LINES][MAX_LINE_LENGTH];

    int isCommandSection = 1;
    char input[MAX_LINE_LENGTH];

    int num_cmds = 0;
    int num_lines = 0;


    //TODO: Allocate memory for tree

    while (isCommandSection){
        if (fgets(input, MAX_LINE_LENGTH, stdin) == NULL){
            break;
        }
        
        if (strcmp(input, "END\n") == 0){
            isCommandSection = 0;
            continue;
        }

        strcpy(commands[num_cmds++], input);

    }

    while (fgets(input, MAX_LINE_LENGTH, stdin) != NULL){
        strcpy(text[num_lines++], input);
    }

    printf("Commands:\n");

    for (int i = 0; i < num_cmds; i++){
        printf("%s", commands[i]);
    }

    printf("\nText:\n");

    for (int i = 0; i < num_lines; i++){
        printf("%s", text[i]);
    }

    printf("\n\n\n");


    struct TreeNode *root = NULL;

    char delim[] = " \t\r\n\v\f";

    for (int i = 0; i < num_lines; i++){
        int j = 0;
        printf("new for loop (156), i = %d, j = %d\n", i, j);
        printf("current line is \"%s\"\n", text[i]);

        char *token = strtok(text[i], delim);

        while(1){
            printf("Token: %s\n", token );

            // add token to tree
            struct Position *pos = newPosition(i + 1, j);
            printf("made a pos with %d, %d\n\n", i + 1, j);
            j++;


            root = insertNode(root, token, *pos);
    
            token = strtok(NULL, delim);

            if(token == NULL) break;


        }

    }

    // TODO: COMMAND PROCESSING GOES HERE

    output(root);
    return 0;
}