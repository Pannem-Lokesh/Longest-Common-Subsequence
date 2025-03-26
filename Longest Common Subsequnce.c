#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestCommonSubsequence(char *str1, char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int lcs_length = dp[m][n];

    // Free allocated memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return lcs_length;
}

char* reconstructLCS(char *str1, char *str2) {
    int m = strlen(str1);
    int n = strlen(str2);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int i = m, j = n;
    int index = dp[m][n];
    char *lcs = (char *)malloc((index + 1) * sizeof(char));
    lcs[index] = '\0'; // Null-terminate the string

    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            lcs[index - 1] = str1[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Free allocated memory
    for (int k = 0; k <= m; k++) {
        free(dp[k]);
    }
    free(dp);

    return lcs;
}

int main() {
    char str1[] = "AGGTAB";
    char str2[] = "GXTXAYB";

    int lcs_length = longestCommonSubsequence(str1, str2);
    printf("Length of LCS is: %d\n", lcs_length);

    char *lcs_string = reconstructLCS(str1, str2);
    printf("One of the LCS strings is: %s\n", lcs_string);

    free(lcs_string); // Free the allocated memory for the LCS string
    return 0;
}