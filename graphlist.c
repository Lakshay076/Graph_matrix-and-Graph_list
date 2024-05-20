#include<stdio.h>
#include<stdlib.h>


typedef struct{
    int num_vertices;
    int **adj_matrix;

}GraphMatrix;

GraphMatrix *create_graph_matrix(int vertices){
    GraphMatrix *graph = malloc(sizeof(GraphMatrix));
    graph->num_vertices = vertices;
    graph->adj_matrix = malloc(vertices * sizeof(int));

    for(int i = 0; i < vertices ; i++){
        graph->adj_matrix[i] = malloc(sizeof(int) * vertices);

        for(int j = 0; j < vertices; j++){
            if(i == j){
                graph->adj_matrix[i][j] = -1;
            }
            else{
            graph->adj_matrix[i][j] = 0;}
        }
    }

    return graph;
}

int add_edge_matrix(GraphMatrix* graph, int src, int dest){
    graph->adj_matrix[src][dest] = 1;
    graph->adj_matrix[dest][src] = 1;

    return 0;
}

int print_graph_matrix(GraphMatrix *graph){
    for(int i = 0; i < graph->num_vertices; i++){
        printf("%d: ", i);
        for(int j = 0; j < graph->num_vertices; j++){
            printf("%d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main(){
    GraphMatrix *graph = create_graph_matrix(5);
    print_graph_matrix(graph);
    add_edge_matrix(graph,2,4);
    add_edge_matrix(graph,1,0);
    add_edge_matrix(graph,2,1);
    add_edge_matrix(graph,2,3);
    add_edge_matrix(graph,3,4);
    print_graph_matrix(graph);

    return 0;
}