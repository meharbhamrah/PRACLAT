#include<stdio.h>

int main() {
    int a[10], b[10], x[10];
    int waiting[10], turnaround[10], completion[10];
    int i, smallest, count = 0, time, n;
    double avg = 0, tt = 0;

    printf("\nEnter the number of Processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter arrival time of process %d: ", i + 1);
        scanf("%d", &a[i]);
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter burst time of process %d: ", i + 1);
        scanf("%d", &b[i]);
    }

    for (i = 0; i < n; i++)
        x[i] = b[i];

    b[9] = 9999;

    for (time = 0; count != n; time++) {
        smallest = 9;
        for (i = 0; i < n; i++) {
            if (a[i] <= time && b[i] < b[smallest] && b[i] > 0) {
                smallest = i;
            }
        }

        b[smallest]--;

        if (b[smallest] == 0) {
            count++;
            int end = time + 1;
            completion[smallest] = end;
            waiting[smallest] = end - a[smallest] - x[smallest];
            turnaround[smallest] = end - a[smallest];
            if (waiting[smallest] < 0) {
                waiting[smallest] = 0;
            }
        }
    }

    printf("\nPID\tBurst\tArrival\tWaiting\tTurnaround\tCompletion");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%d\t%d\t\t%d", i + 1, x[i], a[i], waiting[i], turnaround[i], completion[i]);
        avg += waiting[i];
        tt += turnaround[i];
    }

    printf("\n\nAverage Waiting Time = %.2lf", avg / n);
    printf("\nAverage Turnaround Time = %.2lf\n", tt / n);

    return 0;
}

