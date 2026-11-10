#include <stdio.h>
#include <string.h>

#define MAX 20
#define MAX_DFA 100

int n_states, n_inputs;

int nfa[MAX][MAX][MAX];
int trans_count[MAX][MAX];

int dfa_states[MAX_DFA][MAX];
int dfa_count = 0;

int dfa_table[MAX_DFA][MAX];


/* Check whether two sets are equal */
int sameSet(int a[], int b[])
{
    for(int i = 0; i < n_states; i++)
    {
        if(a[i] != b[i])
            return 0;
    }

    return 1;
}


/* Find a DFA state */
int findDFAState(int set[])
{
    for(int i = 0; i < dfa_count; i++)
    {
        if(sameSet(dfa_states[i], set))
            return i;
    }

    return -1;
}


/* Add a new DFA state */
int addDFAState(int set[])
{
    for(int i = 0; i < n_states; i++)
        dfa_states[dfa_count][i] = set[i];

    return dfa_count++;
}


/* Convert NFA to DFA */
void convertToDFA()
{
    int start[MAX] = {0};

    /* Starting state of NFA is q0 */
    start[0] = 1;

    addDFAState(start);

    int current = 0;

    while(current < dfa_count)
    {
        for(int input = 0; input < n_inputs; input++)
        {
            int nextSet[MAX] = {0};

            /*
               For every NFA state present
               in current DFA state
            */
            for(int state = 0; state < n_states; state++)
            {
                if(dfa_states[current][state])
                {
                    for(int k = 0;
                        k < trans_count[state][input];
                        k++)
                    {
                        int next = nfa[state][input][k];

                        nextSet[next] = 1;
                    }
                }
            }

            /* Find whether this set already exists */
            int index = findDFAState(nextSet);

            if(index == -1)
                index = addDFAState(nextSet);

            dfa_table[current][input] = index;
        }

        current++;
    }
}


/* Print a set of NFA states */
void printSet(int set[])
{
    printf("{ ");

    int empty = 1;

    for(int i = 0; i < n_states; i++)
    {
        if(set[i])
        {
            printf("q%d ", i);
            empty = 0;
        }
    }

    if(empty)
        printf("NULL ");

    printf("}");
}


int main()
{
    printf("Enter number of NFA states: ");
    scanf("%d", &n_states);

    printf("Enter number of inputs: ");
    scanf("%d", &n_inputs);


    /* Read NFA transitions */
    for(int i = 0; i < n_states; i++)
    {
        for(int j = 0; j < n_inputs; j++)
        {
            printf("Number of transitions from q%d on input %d: ",i, j);

            scanf("%d", &trans_count[i][j]);

            printf("Enter destination states: ");

            for(int k = 0; k < trans_count[i][j]; k++)
            {
                scanf("%d", &nfa[i][j][k]);
            }
        }
    }


    convertToDFA();


    /* Display DFA states */
    printf("\nDFA States:\n");

    for(int i = 0; i < dfa_count; i++)
    {
        printf("D%d = ", i);
        printSet(dfa_states[i]);
        printf("\n");
    }


    /* Display DFA transition table */
    printf("\nDFA Transition Table:\n");

    for(int i = 0; i < dfa_count; i++)
    {
        for(int input = 0; input < n_inputs; input++)
        {
            printf("D%d --%d--> D%d\n",
                   i,
                   input,
                   dfa_table[i][input]);
        }
    }

    return 0;
}