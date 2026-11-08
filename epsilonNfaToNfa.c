#include <stdio.h>
#include <string.h>

#define MAX 20

int n_states, n_inputs;

/* epsilon-NFA transition table */
int t_table[MAX][MAX][MAX];
int trans_count[MAX][MAX];

/* epsilon closures */
int closure[MAX][MAX];

/* resulting NFA */
int nfa[MAX][MAX][MAX];
int nfa_count[MAX][MAX];

/* ---------- E-CLOSURE ---------- */

void dfs(int start, int state)
{
    closure[start][state] = 1;

    for(int i=0;i<trans_count[state][0];i++)
    {
        int next = t_table[state][0][i];

        if(!closure[start][next])
            dfs(start,next);
    }
}

void findClosure(int state)
{
    memset(closure[state],0,sizeof(closure[state]));
    dfs(state,state);
}

/* ---------- NFA CONVERSION ---------- */

void addState(int arr[], int *size, int value)
{
    for(int i=0;i<*size;i++)
        if(arr[i]==value)
            return;

    arr[(*size)++] = value;
}

void convertToNFA()
{
    for(int q=0;q<n_states;q++)
    {
        for(int input=1;input<n_inputs;input++)
        {
            int temp[MAX];
            int size = 0;

            /* For every state in E(q) */
            for(int p=0;p<n_states;p++)
            {
                if(!closure[q][p])
                    continue;

                /* δ(p,input) */
                for(int k=0;k<trans_count[p][input];k++)
                {
                    int next = t_table[p][input][k];

                    /* E(next) */
                    for(int r=0;r<n_states;r++)
                    {
                        if(closure[next][r])
                            addState(temp,&size,r);
                    }
                }
            }

            nfa_count[q][input] = size;

            for(int i=0;i<size;i++)
                nfa[q][input][i] = temp[i];
        }
    }
}

/* ---------- MAIN ---------- */

int main()
{
    printf("Enter number of states: ");
    scanf("%d",&n_states);

    printf("Enter number of inputs (including epsilon as input 0): ");
    scanf("%d",&n_inputs);

    for(int i=0;i<n_states;i++)
    {
        for(int j=0;j<n_inputs;j++)
        {
            printf("Number of transitions from q%d on input %d: ",i,j);
            scanf("%d",&trans_count[i][j]);

            printf("Enter destination states: ");

            for(int k=0;k<trans_count[i][j];k++)
                scanf("%d",&t_table[i][j][k]);
        }
    }

    /* Compute epsilon closures */
    for(int i=0;i<n_states;i++)
        findClosure(i);

    /* Convert epsilon-NFA to NFA */
    convertToNFA();

    /* Display resulting NFA */
    printf("\nNFA Transition Table:\n");

    for(int q=0;q<n_states;q++)
    {
        for(int input=1;input<n_inputs;input++)
        {
            printf("δ'(q%d,%d) = { ",q,input);

            for(int k=0;k<nfa_count[q][input];k++)
                printf("q%d ",nfa[q][input][k]);

            printf("}\n");
        }
    }

    return 0;
}