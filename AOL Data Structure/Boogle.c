#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct trie{
    struct trie* child[26];
    bool end;
    char description[256];
}   *root = NULL;

struct trie* createNode(){
    struct trie* node = (struct trie*)malloc(sizeof(struct trie));
    node->end = false;
    for (int i = 0; i < 26; i++) {
        node->child[i] = NULL;
    }
    return node;
}

bool alphabetValid(char word[]){
    bool alphabet = true;
    for(int i = 0; word[i] != '\0'; i++){
        if(!(word[i] >= 'A' && word[i] <= 'Z') && !(word[i] >= 'a' && word[i] <= 'z')){
            alphabet = false;
            break;
        }
    }
    return alphabet;
}

void escape(){
    printf("\n");
    char enter[101];
    printf("Press enter to continue...");
    scanf("[^\n]", enter);
    getchar();
}

char menu(){
    char choice[101];
    printf("\nWELCOME TO BOOGLE\n\n");
    printf("1. Release a new slang word\n");
    printf("2. Search a slang word\n");
    printf("3. View all slang word starting with a specific prefix\n");
    printf("4. View all slang words\n");
    printf("5. Exit\n");
    do{
        printf("Choice: ");
        scanf("%[^\n]", choice);
        getchar();
    }while((choice[0] < '1' || choice[0] > '5') || strlen(choice) > 1);
    return choice[0];
}

void inputSlang(struct trie* root, char word[], char desc[]){
    int length = strlen(word);
    struct trie* current = root;
    for(int i = 0; i < length; i++){
        int index = word[i] - 'a';
        if(current->child[index] == NULL){
            current->child[index] = createNode();
        }
        current = current->child[index];
    }
    current->end = true;
    strcpy(current->description, desc);
}

void releaseSlang(struct trie* root){
    char newSlang[101];
    char description[101];
    int parts;
    printf("\n");
    do{
        printf("Input a new slang word [must be more than 1 alphabetic character and contains no space]: ");
        scanf("%[^\n]", newSlang);
        getchar();
    }while(!(strlen(newSlang) > 1 && strchr(newSlang, ' ') == NULL) || alphabetValid(newSlang) == false);
    for(int i = 0; i < strlen(newSlang); i++){
        newSlang[i] = tolower(newSlang[i]);
    }
    bool found = true;
    struct trie* current = root;
    for(int i = 0; i < strlen(newSlang); i++){
        int index = newSlang[i] - 'a';
        if(current->child[index] == NULL){
            found = false;
            break;
        }
        current = current->child[index];
    }
    do{
        parts = 0;
        printf("Input a new slang word description [must be more than 2 words]: ");
        scanf("%[^\n]", description);
        getchar();
        char descriptionCopy[101];
        strcpy(descriptionCopy, description);
        char* token = strtok(descriptionCopy, " ");
        while(token != NULL){
            parts += 1;
            token = strtok(NULL, " ");
        }
    }while(!(parts > 2));
    if(found == false || (found == true && current->end == false)) printf("\nSuccessfully released new slang word.\n");
    else if(found == true && current->end == true) printf("\nSuccessfully updated a slang word.\n");
    inputSlang(root, newSlang, description);
    escape();
}

void searchSlang(struct trie* root){
    bool data = false;
    for(int i = 0; i < 26; i++){
        if(root->child[i] != NULL){
            data = true;
            break;
        }
    }
    if(data == false){
        printf("\nThere is no slang word yet in the dictionary.\n");
    }
    else{
        char search[101];
        printf("\n");
        do{
            printf("Input a slang word to be searched [Must be more than 1 alphabetic characters and contains no space]: ");
            scanf("%[^\n]", search);
            getchar();
        }while(!(strlen(search) > 1 && strchr(search, ' ') == NULL) || alphabetValid(search) == false);
        bool found = true;
        struct trie* current = root;
        for(int i = 0; i < strlen(search); i++){
            int index = search[i] - 'a';
            if(current->child[index] == NULL){
                found = false;
                break;
            }
            current = current->child[index];
        }
        if(found == false || (found == true && current->end == false)){
            printf("\nThere is no word \"%s\" in the dictionary..\n", search);
        }
        else if(found == true && current->end == true){
            printf("\nSlang word  : %s\n", search);
            printf("Description : %s\n", current->description);
        }
    }
    escape();
}

void printSlang(struct trie* current, char word[], int index, int* count){
    if(current->end == true){
        word[index] = '\0';
        printf("%d. %s\n", *count, word);
        (*count) += 1;
    }
    for(int i = 0; i < 26; i++){
        if(current->child[i] != NULL){
            word[index] = 'a' + i;
            printSlang(current->child[i], word, index+1, count);
        }
    }
}

void printPrefix(struct trie* current, char word[], char prefix[]){
    int skipIndex = strlen(prefix);
    for(int i = 0; i < skipIndex; i++){
        if(current->child[prefix[i]-'a'] != NULL){
            word[i] = prefix[i];
            current = current->child[prefix[i]-'a'];
        }
        else{
            printf("\nThere is no prefix \"%s\" in the dictionary.\n", prefix);
            return;
        }
    }
    int count = 1;
    printSlang(current, word, skipIndex, &count);
}

void viewPrefix(struct trie* root){
    bool data = false;
    for(int i = 0; i < 26; i++){
        if(root->child[i] != NULL){
            data = true;
            break;
        }
    }
    if(data == false){
        printf("\nThere is no slang word yet in the dictionary.\n");
    }
    else{
        char prefix[101];
        printf("\n");
            do{
            printf("Input an alphabetic prefix to be searched: ");
            scanf("%[^\n]", prefix);
            getchar();
        }while(strchr(prefix, ' ') != NULL || alphabetValid(prefix) == false);
        char word[101];
        printPrefix(root,word, prefix);
    }   
    escape();
}

void viewSlang(struct trie* root){
    bool data = false;
    for(int i = 0; i < 26; i++){
        if(root->child[i] != NULL){
            data = true;
            break;
        }
    }
    if(data == false){
        printf("\nThere is no slang word yet in the dictionary.\n");
    }
    else{
        printf("\nList of all slang words in the dictionary:\n");
        char word[101];
        int count = 1;
        printSlang(root, word, 0, &count);
    }
    escape();
}

int main(){
    struct trie* root = createNode();
    int choice;
    do{
        choice = menu() - 48;
        system("cls");
        switch(choice){
            case 1:
                releaseSlang(root);
                break;
            case 2:
                searchSlang(root);
                break;
            case 3:
                viewPrefix(root);
                break;
            case 4:
                viewSlang(root);
                break;
            case 5:
                printf("\nThank you... have a nice day! :)\n");
                exit(0);
                break;
        }
        system("cls");
    }while(choice != 5);
    return 0;
}
