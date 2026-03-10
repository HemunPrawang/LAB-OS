#include <stdio.h>

#define FRAMES 4
#define N 19

int pages[N] = {2,1,2,3,7,6,2,3,4,2,1,5,6,3,2,3,6,2,1};

// ---------------- FIFO ----------------
void fifo() {
    int f[FRAMES], idx=0, faults=0;
    int table[FRAMES][N];

    for(int i=0;i<FRAMES;i++) f[i]=-1;

    for(int i=0;i<N;i++){
        int hit=0;
        for(int j=0;j<FRAMES;j++)
            if(f[j]==pages[i]) hit=1;

        if(!hit){
            f[idx]=pages[i];
            idx=(idx+1)%FRAMES;
            faults++;
        }

        for(int r=0;r<FRAMES;r++)
            table[r][i]=f[r];
    }

    printf("\nFIFO\n--------------------------------------------------------------\nRef: ");
    for(int i=0;i<N;i++) printf("%2d ", pages[i]);
    printf("\n");

    for(int r=0;r<FRAMES;r++){
        printf("F%d : ", r+1);
        for(int c=0;c<N;c++){
            if(table[r][c]==-1) printf(" - ");
            else printf("%2d ", table[r][c]);
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------");
    printf("\n");
    printf("Page faults = %d\n", faults);
}

// ---------------- LRU ----------------
void lru() {
    int f[FRAMES], time[FRAMES], faults=0;
    int table[FRAMES][N];

    for(int i=0;i<FRAMES;i++){ f[i]=-1; time[i]=0; }

    for(int i=0;i<N;i++){
        int hit=0;
        for(int j=0;j<FRAMES;j++){
            if(f[j]==pages[i]){
                hit=1;
                time[j]=i;
            }
        }

        if(!hit){
            int min=0;
            for(int j=1;j<FRAMES;j++)
                if(time[j]<time[min]) min=j;

            f[min]=pages[i];
            time[min]=i;
            faults++;
        }

        for(int r=0;r<FRAMES;r++)
            table[r][i]=f[r];
    }

    printf("\nLRU\n--------------------------------------------------------------\nRef: ");
    for(int i=0;i<N;i++) printf("%2d ", pages[i]);
    printf("\n");

    for(int r=0;r<FRAMES;r++){
        printf("F%d : ", r+1);
        for(int c=0;c<N;c++){
            if(table[r][c]==-1) printf(" - ");
            else printf("%2d ", table[r][c]);
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------");
    printf("\n");
    printf("Page faults = %d\n", faults);
}

// ---------------- Optimal ----------------
int findOptimal(int f[], int start){
    int idx=-1, farthest=start;

    for(int i=0;i<FRAMES;i++){
        int j;
        for(j=start;j<N;j++)
            if(f[i]==pages[j]) break;

        if(j==N) return i; // not used again
        if(j>farthest){
            farthest=j;
            idx=i;
        }
    }
    return idx==-1?0:idx;
}

void optimal() {
    int f[FRAMES], faults=0;
    int table[FRAMES][N];

    for(int i=0;i<FRAMES;i++) f[i]=-1;

    for(int i=0;i<N;i++){
        int hit=0;
        for(int j=0;j<FRAMES;j++)
            if(f[j]==pages[i]) hit=1;

        if(!hit){
            int pos=findOptimal(f, i+1);
            f[pos]=pages[i];
            faults++;
        }

        for(int r=0;r<FRAMES;r++)
            table[r][i]=f[r];
    }

    printf("\nOptimal\n--------------------------------------------------------------\nRef: ");
    for(int i=0;i<N;i++) printf("%2d ", pages[i]);
    printf("\n");

    for(int r=0;r<FRAMES;r++){
        printf("F%d : ", r+1);
        for(int c=0;c<N;c++){
            if(table[r][c]==-1) printf(" - ");
            else printf("%2d ", table[r][c]);
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------");
    printf("\n");
    printf("Page faults = %d\n", faults);
}

// ---------------- main ----------------
int main(){
    fifo();
    lru();
    optimal();
    return 0;
}