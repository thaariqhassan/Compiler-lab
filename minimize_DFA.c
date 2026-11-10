
#include <stdio.h>

#define MAX 20

int n, m;
int trans[MAX][MAX];
int final[MAX];
int group[MAX], newGroup[MAX];
int reachable[MAX];

/* Find reachable states using DFS */
void dfs(int state)
{
    reachable[state] = 1;

    for(int i = 0; i < m; i++)
    {
        int next = trans[state][i];

        if(!reachable[next])
            dfs(next);
    }
}

/* Check whether two states belong to the same new group */
int equivalent(int p, int q)
{
    if(group[p] != group[q])
        return 0;

    for(int i = 0; i < m; i++)
    {
        if(group[trans[p][i]] != group[trans[q][i]])
            return 0;
    }

    return 1;
}

/* Minimize DFA using partition method */
void minimize()
{
    // Step 1: Find reachable states
    dfs(0);

    // Step 2: Initial partition
    int count = 0;

    for(int i = 0; i < n; i++)
    {
        if(!reachable[i])
        {
            group[i] = -1;
            continue;
        }

        if(final[i])
            group[i] = 1;
        else
            group[i] = 0;
    }

    // Step 3: Refine partitions
    int changed;

    do
    {
        count = 0;

        for(int i = 0; i < n; i++)
        {
            if(!reachable[i])
            {
                newGroup[i] = -1;
                continue;
            }

            int found = -1;

            for(int j = 0; j < i; j++)
            {
                if(reachable[j] && equivalent(i, j))
                {
                    found = newGroup[j];
                    break;
                }
            }

            if(found == -1)
                newGroup[i] = count++;
            else
                newGroup[i] = found;
        }

        changed = 0;

        for(int i = 0; i < n; i++)
        {
            if(reachable[i] && group[i] != newGroup[i])
                changed = 1;

            group[i] = newGroup[i];
        }

    } while(changed);

    // Step 4: Display minimized DFA
    printf("\nMinimized DFA States:\n");

    for(int i = 0; i < count; i++)
    {
        printf("M%d = { ", i);

        for(int j = 0; j < n; j++)
        {
            if(group[j] == i)
                printf("q%d ", j);
        }

        printf("}\n");
    }

    // Step 5: Display minimized transition table
    printf("\nMinimized DFA Transition Table:\n");

    for(int i = 0; i < count; i++)
    {
        int state = -1;

        // Find one representative state
        for(int j = 0; j < n; j++)
        {
            if(group[j] == i)
            {
                state = j;
                break;
            }
        }

        for(int j = 0; j < m; j++)
        {
            printf("M%d --%d--> M%d\n",
                   i, j, group[trans[state][j]]);
        }
    }

    // Display final states
    printf("\nFinal States: ");

    for(int i = 0; i < count; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(group[j] == i && final[j])
            {
                printf("M%d ", i);
                break;
            }
        }
    }

    printf("\nStart State: M%d\n", group[0]);
}

int main()
{
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of inputs: ");
    scanf("%d", &m);

    // Read DFA transition table
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            printf("Enter transition from q%d on input %d: ",
                   i, j);

            scanf("%d", &trans[i][j]);
        }
    }

    // Read final states
    int nf, s;

    printf("Enter number of final states: ");
    scanf("%d", &nf);

    printf("Enter final states: ");

    for(int i = 0; i < nf; i++)
    {
        scanf("%d", &s);
        final[s] = 1;
    }

    minimize();

    return 0;
}
