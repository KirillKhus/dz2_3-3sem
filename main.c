#include <stdio.h>
#include <stdlib.h>

int is_con(int **v_arr, int *is_c_arr, int cur_v, int v_count){
    int ans = 0;
    for(int j = 0; j < v_count; ++j){
        if(v_arr[cur_v][j] && !is_c_arr[j]){
            is_c_arr[j] = 1;
            ans++;
            ans += is_con(v_arr, is_c_arr, j, v_count);
        }
    }
    return ans;
}

int main(int argc, char **argv){
    FILE *file;
    file = fopen("graph.dot", "w");
    fprintf(file, "graph g {\n");
    int v_count = 0;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &v_count);
    for(int i = 0; i < v_count; ++i){
        fprintf(file, "%d;\n", i);
    }
    printf("Enter the adjacency matrix of a %d by %d graph:\n", v_count, v_count);
    int is_c_arr[v_count];
    int *v_arr[v_count];
    for(int i = 0; i < v_count; ++i){
        is_c_arr[i] = 0;
        v_arr[i] = (int*)malloc(v_count * sizeof(int));
        for(int j = 0; j < v_count; ++j){
            int cur = 0;
            scanf("%d", &v_arr[i][j]);
            if (j >= i){
                int sup = v_arr[i][j];
                while(sup > 0){
                    fprintf(file, "%d -- %d;\n", i, j);
                    sup--;
                }
            }
        }
    }
    
    fprintf(file, "}\n");

    is_c_arr[0] = 1;
    
    if (is_con(v_arr, is_c_arr, 0, v_count) == v_count - 1){
        printf("The given graph turned out to be connected\n");
    }
    else {
        printf("The given graph turned out to be unconnected\n");
    }
    for(int i = 0; i < v_count; ++i){
        
        free(v_arr[i]);
    }
    fclose(file);
    system("dot -Tpng graph.dot -o graph.png");
    system("graph.png");
    
    return 0;
}
