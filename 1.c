#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

typedef struct adj_list
{
    node **adj_matrix;
    int num_vertex;
} adj_list;

adj_list *create_list(int n)
{
    adj_list *list = (adj_list *)malloc(sizeof(adj_list));
    list->adj_matrix = (node **)malloc(n * sizeof(node *));
    for (int i = 0; i < n; i++)
    {
        list->adj_matrix[i] = NULL;
    }
    list->num_vertex = n;
    return list;
}

int add_edge(adj_list *list, int v1, int v2)
{
    node *n1 = (node *)malloc(sizeof(node));
    n1->data = v2;
    n1->next = list->adj_matrix[v1];
    list->adj_matrix[v1] = n1;

    node *n2 = (node *)malloc(sizeof(node));
    n2->data = v1;
    n2->next = list->adj_matrix[v2];
    list->adj_matrix[v2] = n1;

    return 0;
}

int display(adj_list *list)
{
    for (int i = 0; i < list->num_vertex; i++)
    {
        node *ptr = list->adj_matrix[i];
        printf("Index %d:", i);
        while (ptr != NULL)
        {
            printf("%d-->", ptr->data);
            ptr = ptr->next;
        }
        printf("NULL\n");
    }
}

struct stack
{
    int *arr;
    int top;
    int size;
};

int create_stack(struct stack *s1, int size)
{
    s1->size = size;
    s1->arr = (int *)malloc(size * sizeof(int));
    s1->top = -1;
}

int is_empty(struct stack *s1)
{
    return (s1->top == -1);
}

int is_full(struct stack *s1)
{
    return (s1->top == (s1->size - 1));
}

int pop(struct stack *s1)
{
    if (is_empty(s1))
    {
        printf("Your stack is empty\n");
        return -1;
    }
    else
    {
        int popped_element = s1->arr[s1->top];
        s1->top--;
        return popped_element;
    }
}

int push(struct stack *s1, int val)
{
    if (is_full(s1))
    {
        printf("Your stack is full\n");
        return -1;
    }
    else
    {
        s1->top++;
        s1->arr[s1->top] = val;
        return 0;
    }
}

int destroy_stack(struct stack *s1)
{
    free(s1->arr);
    free(s1);
    return 0;
}

int dfs(adj_list *list, int start_vertex)
{
    int *visited = (int *)calloc(list->num_vertex, sizeof(int));
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    create_stack(s, list->num_vertex);
    push(s, start_vertex);
    while (!is_empty(s))
    {
        int curr_vertex = pop(s);
        if (!visited[curr_vertex])
        {
            printf("%d ", curr_vertex);
            visited[curr_vertex] = 1;
        }
        node *temp = list->adj_matrix[curr_vertex];
        while (temp != NULL)
        {
            if (!visited[temp->data])
            {
                push(s, temp->data);
            }
            temp = temp->next;
        }
    }

    free(visited);
    free(s);
    return 0;
}

void dfs2(adj_list *list, int start_vertex, int *visited)
{
    if (!visited[start_vertex])
    {
        printf("%d ", start_vertex);
        visited[start_vertex] = 1;
    }

    node *temp = list->adj_matrix[start_vertex];
    while (temp != NULL)
    {
        if (!visited[temp->data])
        {
            dfs2(list, temp->data, visited);
        }
        temp = temp->next;
    }
}

int main()
{
    adj_list *graph = create_list(5);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 3);
    add_edge(graph, 3, 4);
    display(graph);
    printf("\n");
    // dfs(graph, 0);
    int visited[graph->num_vertex];
    for (int i = 0; i < graph->num_vertex; i++)
    {
        visited[i] = 0;
    }

    dfs2(graph, 0, visited);

    return 0;
}