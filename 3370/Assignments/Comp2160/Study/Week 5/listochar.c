#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct NODE
{
    struct NODE *next;
    char letter;
} node;

static node *head;
static int nodes = 0;

void init_list(char *);
void print_list();
void delete_node(int);
void destroy_list();

int main(void)
{
    init_list("Yo what's up friend");
    delete_node(5);
    print_list();
    destroy_list();
    return EXIT_SUCCESS;
}

void init_list(char *word)
{
    node *curr;
   
    assert(head == NULL && word!= NULL);
    head = malloc(sizeof(node));

    curr = head;

    for (int i = 0; i < strlen(word); i++)
    {
        curr->letter = word[i];
        curr->next = malloc(sizeof(node));
        nodes++;
        
        if (curr->next != NULL)
        {
            curr = curr->next;
        }
    }
    
    curr->next = NULL;
    curr->letter = '\0';
}

void print_list()
{
    node *curr = head;
    for (int i = 0; i < nodes; i++)
    {
        printf("%c", curr->letter);
        curr = curr->next;
    }
    printf("\n");
}

void delete_node(int node_num)
{
    node *curr = head;
    node *last = NULL;

    while (node_num)
    {
        node_num--;
        last = curr;
        curr = curr->next;
    }
    
    last->next = curr->next;
    free(curr);
}

void destroy_list()
{
    node *curr = head;
    node *next = head->next;
    for (int i = 0; i < nodes; i++)
    {
        free(curr);
        curr = next;
        next = curr->next;
    }
}
