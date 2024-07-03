#include <stdio.h>
#include <limits.h>
#include <unistd.h>

void main()
{
    int n;
    printf("enter the number of nodes : ");
    scanf("%d", &n);
    int arr[n][n];
    printf("Enter the cost matrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);
    }

    int change;
    int dist_AB, dist_BC, dist_AC;
    do
    {
        change = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) // iterates over each node j and considers i to j distances.
            {
                if (arr[i][j] != -1 && i != j) // Ensures there is a direct path from i to j and avoids self-loops
                {
                    for (int k = 0; k < n; k++)
                    {
                        // Iterates over each node k to check potential paths i -> j -> k
                        dist_AB = arr[i][j];
                        // If no direct path exist between two nodes (-1) ,then dist = infinity
                        dist_AC = arr[i][k] == -1 ? INT_MAX : arr[i][k];
                        dist_BC = arr[j][k] == -1 ? INT_MAX : arr[j][k];

                        if (dist_BC == INT_MAX || dist_AC == INT_MAX)
                            continue; // Skip if there's no valid path through j

                        // If the path i -> j -> k is shorter than i -> k
                        // update arr[i][k] and increment change
                        if (dist_AB + dist_BC < dist_AC)
                        {
                            arr[i][k] = dist_AB + dist_BC;
                            change++;
                        }
                    }
                }
            }
        }
    } while (change != 0);

    printf("After Distance Vector Routing:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}