#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5
#define TQ 4
#define MAX_ORDER 200 

typedef struct {
    char name[3];
    int burst;
    int arrival;
    int priority;
    int remaining;
    int waiting;
    int turnaround;
} Process;

Process base[N] = {
    {"P1",9,1,3,0,0,0},
    {"P2",3,1,5,0,0,0},
    {"P3",5,3,1,0,0,0},
    {"P4",4,4,4,0,0,0},
    {"P5",2,7,2,0,0,0}
};

void reset(Process p[]) {
    for(int i=0;i<N;i++){
        p[i]=base[i];
        p[i].remaining=p[i].burst;
        p[i].waiting=0;
        p[i].turnaround=0;
    }
}

void print_standard_format(char *title, Process p[], int order[], int ocount) {
    printf("\n=== %s ===\n", title);
    printf("Sequence: ");
    for(int i=0; i<ocount; i++) {
        printf("%s%s", p[order[i]].name, (i == ocount - 1) ? "" : " -> ");
    }
    printf("\n\n%-10s | %-10s | %-10s\n", "Process", "Waiting", "Turnaround");
    printf("------------------------------------------\n");
    
    double aw = 0, at = 0;
    for(int i=0; i<N; i++) {
        printf("%-10s | %-10d | %-10d\n", p[i].name, p[i].waiting, p[i].turnaround);
        aw += p[i].waiting; 
        at += p[i].turnaround;
    }
    printf("------------------------------------------\n");
    printf("Average Waiting Time: %.2f ms\n", aw/N);
    printf("Average Turnaround Time: %.2f ms\n", at/N);
}

void print_calculated(Process p[]) {
    printf("\nName  Burst  Arrival  Priority  Remaining  Waiting  Turnaround\n");
    printf("----------------------------------------------------------------\n");
    for(int i = 0; i < N; i++) {
        printf("%-4s  %-5d  %-7d  %-8d  %-9d  %-7d  %-10d\n",
            p[i].name,
            p[i].burst,
            p[i].arrival,
            p[i].priority,
            p[i].remaining,
            p[i].waiting,
            p[i].turnaround
        );
    }
}

/* ================= SJF (Non-preemptive) ================= */
void sjf_nonpreemptive(){
    Process p[N]; reset(p);
    int t=0, done=0, used[N]={0}, order[MAX_ORDER], k=0;

    while(done < N){
        int idx = -1, min = 1e9;
        for(int i=0; i<N; i++) {
            if(!used[i] && p[i].arrival <= t && p[i].burst < min) { 
                min = p[i].burst; 
                idx = i; 
            }
        }
        if(idx == -1) { t++; continue; }

        order[k++] = idx;
        t += p[idx].burst;
        p[idx].turnaround = t - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        used[idx] = 1; 
        done++;
    }
    print_standard_format("Non-preemptive SJF", p, order, k);
    print_calculated(p);
}

/* ================= SJF (Preemptive / SRTF) ================= */
void sjf_preemptive(){
    Process p[N]; reset(p);
    int t=0, done=0, order[MAX_ORDER], k=0, last_idx = -1;

    while(done < N){
        int idx = -1, min = 1e9;
        for(int i=0; i<N; i++) {
            if(p[i].arrival <= t && p[i].remaining > 0 && p[i].remaining < min) { 
                min = p[i].remaining; 
                idx = i; 
            }
        }
        if(idx == -1) { t++; continue; }
        
        if(idx != last_idx) {
            order[k++] = idx;
            last_idx = idx;
        }

        p[idx].remaining--; 
        t++;

        if(p[idx].remaining == 0){
            done++;
            p[idx].turnaround = t - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
        }
    }
    print_standard_format("Preemptive SJF (SRTF)", p, order, k);
    print_calculated(p);
}

/* ================= Round Robin ================= */
void round_robin(){
    Process p[N]; reset(p);
    int t=0, done=0, order[MAX_ORDER], k=0;
    int q[MAX_ORDER], f=0, r=0, inq[N]={0};

    for(int i=0; i<N; i++) {
        if(p[i].arrival <= t && !inq[i]) { 
            q[r++] = i; 
            inq[i] = 1; 
        }
    }

    while(done < N){
        if(f == r) { 
            t++; 
            for(int i=0; i<N; i++) {
                if(p[i].arrival <= t && !inq[i] && p[i].remaining > 0) { 
                    q[r++] = i; 
                    inq[i] = 1; 
                }
            }
            continue; 
        }

        int i = q[f++];
        order[k++] = i;
        int run = (p[i].remaining < TQ) ? p[i].remaining : TQ;
        
        for(int m=0; m<run; m++) {
            t++;
            for(int j=0; j<N; j++) {
                if(p[j].arrival <= t && !inq[j] && p[j].remaining > 0) { 
                    q[r++] = j; 
                    inq[j] = 1; 
                }
            }
        }
        
        p[i].remaining -= run;

        if(p[i].remaining > 0) {
            q[r++] = i; 
        } else {
            done++;
            p[i].turnaround = t - p[i].arrival;
            p[i].waiting = p[i].turnaround - p[i].burst;
        }
    }
    print_standard_format("Round Robin (TQ=4)", p, order, k);
    print_calculated(p);
}

/* ================= Priority Scheduling (Non-preemptive) ================= */
void priority_nonpreemptive(){
    Process p[N]; reset(p);
    int t=0, done=0, used[N]={0}, order[MAX_ORDER], k=0;

    while(done < N){
        int idx = -1, best = 1e9;
        for(int i=0; i<N; i++){
            // priority น้อย = สำคัญกว่า
            if(!used[i] && p[i].arrival <= t && p[i].priority < best){
                best = p[i].priority;
                idx = i;
            }
        }

        if(idx == -1){
            t++;
            continue;
        }

        order[k++] = idx;
        t += p[idx].burst;
        p[idx].turnaround = t - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        used[idx] = 1;
        done++;
    }

    print_standard_format("Priority Scheduling (Non-preemptive)", p, order, k);
    print_calculated(p);
}

/* ================= main ================= */
int main(){
    printf("--- CPU Scheduling Simulation ---\n");

    sjf_nonpreemptive();
    sjf_preemptive();
    round_robin();
    priority_nonpreemptive();

    return 0;
}