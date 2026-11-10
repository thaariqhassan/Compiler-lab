#include <stdio.h>
#include <string.h>

#define MAX 20

int n_states, n_inputs;

/* Transition table */
int t_table[MAX][MAX][MAX];

/* Number of transitions for each state and input */
int trans_count[MAX][MAX];

/* Closure matrix */
int closure[MAX][MAX];

/* DFS for epsilon closure */
void dfs(int start, int state)
{
    closure[start][state] = 1;

    /* Input 0 is epsilon */
    for (int i = 0; i < trans_count[state][0]; i++)
    {
        int next = t_table[state][0][i];

        if (!closure[start][next])
        {
            dfs(start, next);
        }
    }
}

void findClosure(int state)
{
    memset(closure[state], 0, sizeof(closure[state]));
    dfs(state, state);
}

int main()
{
    printf("Enter number of states: ");
    scanf("%d", &n_states);

    printf("Enter number of inputs (including epsilon as input 0): ");
    scanf("%d", &n_inputs);

    /* Read transition table */
    for (int i = 0; i < n_states; i++)
    {
        for (int j = 0; j < n_inputs; j++)
        {
            printf("Number of transitions from q%d on input %d: ", i, j);
            scanf("%d", &trans_count[i][j]);

            printf("Enter destination states: ");

            for (int k = 0; k < trans_count[i][j]; k++)
            {
                scanf("%d", &t_table[i][j][k]);
            }
        }
    }

    /* Compute epsilon closures */
    for (int i = 0; i < n_states; i++)
    {
        findClosure(i);
    }

    /* Display closures */
    printf("\nEpsilon Closures:\n");

    for (int i = 0; i < n_states; i++)
    {
        printf("E-closure(q%d) = { ", i);

        for (int j = 0; j < n_states; j++)
        {
            if (closure[i][j])
            {
                printf("q%d ", j);
            }
        }

        printf("}\n");
    }

    return 0;
}