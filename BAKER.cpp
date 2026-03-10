#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int main() {
    int n, m;
    int allocation[MAX_P][MAX_R];
    int max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R]; 
    int total[MAX_R];
    int available[MAX_R];
    int work[MAX_R];
    int finish[MAX_P] = {0};
    int safeSeq[MAX_P];

    printf("Enter number of process: ");
    scanf("%d", &n);

    printf("Enter number of resource: ");
    scanf("%d", &m);

    printf("\nEnter Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);
    }

    printf("\nEnter Max matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("\nEnter Total resources: ");
    for (int j = 0; j < m; j++) {
        scanf("%d", &total[j]);
    }

    // Calculate Available = Total - Sum of Allocation
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += allocation[i][j];
        }
        available[j] = total[j] - sum;
        work[j] = available[j];
    }

    // Calculate Need = Max - Allocation
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    
    printf("\nTotal Resources (AllocationToatal + Available): ");
    for (int j = 0; j < m; j++)
        printf("%2d ",  available[j]);
    printf("\n");

    // Print table header
    printf("\n--> Output state\n");
    printf("Process    Allocation        Max             Need            Available\n");
    printf("           ");
    for (int j = 0; j < m; j++) printf("%02d ", j+1);
    printf("        ");
    for (int j = 0; j < m; j++) printf("%02d ", j+1);
    printf("        ");
    for (int j = 0; j < m; j++) printf("%02d ", j+1);
    printf("        ");
    for (int j = 0; j < m; j++) printf("%02d ", j+1);
    
    printf("\n--------------------------------------------------------------------------\n");

    int count = 0;
    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    printf("P%-10d", i);
                    for (int j = 0; j < m; j++)
                        printf("%3d ", allocation[i][j]);
                    printf("     ");
                    for (int j = 0; j < m; j++)
                        printf("%3d ", max[i][j]);
                    printf("     ");
                    for (int j = 0; j < m; j++)
                        printf("%3d ", need[i][j]);
                    printf("     ");
                    for (int j = 0; j < m; j++)
                        printf("%3d ", work[j]);
                    printf("\n");

                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    finish[i] = 1;
                    safeSeq[count++] = i;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("\nSystem is in UNSAFE state (Deadlock possible)\n");
            return 0;
        }
    }

    printf("TOTAL      ");
    for (int j = 0; j < m; j++) printf("%3d ", 0);
    printf("     ");
    for (int j = 0; j < m; j++) printf("%3d ", 0);
    printf("     ");
    for (int j = 0; j < m; j++) printf("%3d ", 0);
    printf("     ");
    for (int j = 0; j < m; j++) printf("%3d ", work[j]);
    printf("\n");

    printf("--------------------------------------------------------------------------\n");
    printf("Safe Sequence : ");
    
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\nSystem is SAFE\n");


    return 0;
}
