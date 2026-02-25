#include <stdio.h>
#include <string.h>

struct process
{
    char pid[20];
    int at, bt, wt, tt, ct, status, rt; // rt = remaining time
} p[20];

struct done
{
    char pid[20];
    int st, ct;
} d[50];  // increased size because preemption can add more entries

void main()
{
    int n, i, j, time = 0, completed = 0, num = 0, idle = 0;
    float avwt = 0, avtt = 0;

    printf("ENTER THE NUMBER OF PROCESSES : ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nENTER DETAILS OF PROCESS %d", i+1);
        printf("\nPROCESS ID : ");
        scanf(" %s", p[i].pid);
        printf("ARRIVAL TIME : ");
        scanf("%d", &p[i].at);
        printf("BURST TIME : ");
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt; // initialize remaining time
        p[i].status = 0;
    }

    while(completed < n)
    {
        int idx = -1;
        int min_rt = 1e9;

        // find process with shortest remaining time that has arrived
        for(i = 0; i < n; i++)
        {
            if(p[i].at <= time && p[i].status == 0 && p[i].rt < min_rt)
            {
                min_rt = p[i].rt;
                idx = i;
            }
        }

        if(idx != -1)
        {
            // If CPU was idle before, mark start of this process in Gantt chart
            if(idle == 1)
            {
                d[num].ct = time;
                num++;
                idle = 0;
            }

            // Check if this is a new entry for Gantt chart
            if(num == 0 || strcmp(d[num-1].pid, p[idx].pid) != 0)
            {
                strcpy(d[num].pid, p[idx].pid);
                d[num].st = time;
                num++;
            }

            // Execute process for 1 time unit
            p[idx].rt--;
            time++;

            // If process finishes
            if(p[idx].rt == 0)
            {
                p[idx].status = 1;
                p[idx].ct = time;
                p[idx].tt = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tt - p[idx].bt;
                completed++;
                d[num-1].ct = time; // mark end time in Gantt chart
            }
        }
        else
        {
            // CPU is idle
            if(idle == 0)
            {
                strcpy(d[num].pid, "Idle");
                d[num].st = time;
                idle = 1;
                num++;
            }
            time++;
        }
    }

    // Display process table
    printf("\nPROCESS ID\tAT\tBT\tCT\tWT\tTT\n");
    for(i = 0; i < n; i++)
    {
        printf("%s\t\t%d\t%d\t%d\t%d\t%d\n",
                p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tt);
        avwt += p[i].wt;
        avtt += p[i].tt;
    }

    // Display Gantt chart
    printf("\nGANTT CHART\n");
    printf("-------------------------------------------\n");
    for(i = 0; i < num; i++)
        printf("| %s ", d[i].pid);
    printf("|\n");
    printf("-------------------------------------------\n");
    for(i = 0; i < num; i++)
        printf("%d\t", d[i].st);
    printf("%d\n", d[num-1].ct);

    printf("\nAverage Waiting Time = %.2f\n", avwt / n);
    printf("Average Turnaround Time = %.2f\n", avtt / n);
}

