#include <stdio.h>
#include <string.h>
#include <ctype.h>

char inp[50];        /* input string */
char prod[20][20];   /* productions, e.g. "S=cAd" */
int  n;              /* number of productions */
int  idx = 0;        /* current position in input */

int parseNT(char nt);

/* Try to match ONE production (row p) at the current input position */
int matchProd(int p) {
    int j = 2;                       /* RHS starts after "A=" */

    if (prod[p][j] == '#')           /* epsilon production */
        return 1;

    while (prod[p][j] != '\0') {
        char c = prod[p][j];

        if (isupper((unsigned char)c)) {      /* non-terminal: recurse */
            if (!parseNT(c))
                return 0;
        } else {                              /* terminal: must match input */
            if (inp[idx] == c)
                idx++;
            else
                return 0;
        }
        j++;
    }
    return 1;
}

/* Try every alternative of non-terminal 'nt'; backtrack on failure */
int parseNT(char nt) {
    int save = idx;                  /* remember position for backtracking */

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == nt) {
            idx = save;              /* restore before each alternative */
            if (matchProd(i))
                return 1;
        }
    }
    idx = save;                      /* all alternatives failed */
    return 0;
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (format A=alpha, use # for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    printf("Enter expression: ");
    scanf("%s", inp);

    char start = prod[0][0];

    if (parseNT(start) && inp[idx] == '\0') {
        printf("Parsing Successful\n");
    } else {
        printf("Parsing Failed\n");
    }
    return 0;
}