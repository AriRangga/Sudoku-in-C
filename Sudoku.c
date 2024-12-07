#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define SIZE    9
#define EASY    10
#define MEDIUM  30
#define HARD    50
#define BLUE    "\033[0;34m"
#define RED     "\033[0;31m"
#define PURPLE  "\033[0;35m"
#define GRAY    "\033[1;30m"
#define RESET   "\033[0m"

static int orig[SIZE][SIZE] = {0};
static char msg[100] = "";

int safe(int b[SIZE][SIZE], int r, int c, int n) {
    int br = r - r%3, bc = c - c%3;
    for(int i = 0; i < SIZE; i++)
        if(b[r][i] == n || b[i][c] == n || b[br + i/3][bc + i%3] == n)
            return 0;
    return 1;
}

int solve(int b[SIZE][SIZE], int r, int c) {
    if(r == SIZE) return 1;
    if(c == SIZE) return solve(b, r+1, 0);
    if(b[r][c]) return solve(b, r, c+1);
    
    int nums[SIZE];
    for(int i = 0; i < SIZE; i++) nums[i] = i+1;
    for(int i = SIZE-1; i > 0; i--) {
        int j = rand()%(i+1);
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
    
    for(int i = 0; i < SIZE; i++) {
        if(safe(b, r, c, nums[i])) {
            b[r][c] = nums[i];
            if(solve(b, r, c+1)) return 1;
            b[r][c] = 0;
        }
    }
    return 0;
}

void generate(int b[SIZE][SIZE], int diff) {
    memset(b, 0, sizeof(int)*SIZE*SIZE);
    solve(b, 0, 0);
    for(int cells = diff + (rand()%11); cells > 0;) {
        int r = rand()%SIZE, c = rand()%SIZE;
        if(b[r][c]) {
            int tmp = b[r][c];
            b[r][c] = 0;
            int copy[SIZE][SIZE];
            memcpy(copy, b, sizeof(copy));
            if(solve(copy, 0, 0)) cells--;
            else b[r][c] = tmp;
        }
    }
    memcpy(orig, b, sizeof(orig));
}

int findHint(int b[SIZE][SIZE], int *row, int *col, int *num) {
    int copy[SIZE][SIZE], solution[SIZE][SIZE];
    memcpy(copy, b, sizeof(copy));
    memcpy(solution, b, sizeof(solution));
    
    if(!solve(copy, 0, 0)) {
        for(int r = 0; r < SIZE; r++)
            for(int c = 0; c < SIZE; c++)
                if(b[r][c] && !orig[r][c]) solution[r][c] = 0;
        
        if(solve(solution, 0, 0)) {
            for(int r = 0; r < SIZE; r++)
                for(int c = 0; c < SIZE; c++)
                    if(b[r][c] && b[r][c] != solution[r][c]) {
                        *row = r; *col = c; *num = solution[r][c];
                        return 2;
                    }
        }
    }

    int empty_count = 0;
    int empty_cells[SIZE*SIZE][2];
    for(int r = 0; r < SIZE; r++)
        for(int c = 0; c < SIZE; c++)
            if(!b[r][c]) {
                empty_cells[empty_count][0] = r;
                empty_cells[empty_count][1] = c;
                empty_count++;
            }

    if(!empty_count) return 0;
    int idx = rand() % empty_count;
    *row = empty_cells[idx][0];
    *col = empty_cells[idx][1];
    if(solve(copy, 0, 0)) {
        *num = copy[*row][*col];
        return 1;
    }
    return 0;
}

void printBoard(int b[SIZE][SIZE], time_t start) {
    printf("\033[H\033[J\n    ");
    for(int j = 0; j < SIZE; j++)
        printf("%s%s%d %s", j%3==0 && j ? GRAY"| "RESET : "",
            PURPLE, j+1, RESET);
    
    printf("\n  +-------+-------+-------\n");
    for(int i = 0; i < SIZE; i++) {
        if(i%3==0 && i) printf("--+-------+-------+-------\n");
        printf("%s%d%s%s |%s ", RED, i+1, RESET, GRAY, RESET);
        for(int j = 0; j < SIZE; j++)
            printf("%s%s%c %s", j%3==0 && j ? "| " : "",
                b[i][j] ? (orig[i][j] ? "" : BLUE) : "",
                b[i][j] ? b[i][j] + '0' : '.',
                b[i][j] && !orig[i][j] ? RESET : "");
        printf("\n");
    }
    printf("\n%s\n", msg);
    msg[0] = 0;
    printf("Waktu: %d:%02d\n", (int)difftime(time(NULL), start)/60,
        (int)difftime(time(NULL), start)%60);
}

int checkWin(int b[SIZE][SIZE]) {
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            if(!b[i][j]) return 0;
    return 1;
}

void playGame() {
    int b[SIZE][SIZE] = {0}, d;
    char in[10];
    time_t start;

    printf("Pilih tingkat kesulitan (1-Mudah, 2-Sedang, 3-Sulit): ");
    scanf("%d", &d);
    getchar();
    generate(b, d == 1 ? EASY : d == 2 ? MEDIUM : HARD);
    start = time(NULL);

    while(1) {
        printBoard(b, start);
        if(checkWin(b)) {
            int totalTime = difftime(time(NULL), start);
            system(CLEAR);
            printBoard(b, start);
            printf("\n\nSELAMAT! ANDA MENANG!\n");
            printf("Anda menyelesaikan puzzle dalam %d:%02d!\n",
                totalTime/60, totalTime%60);
            break;
        }

        printf("Masukkan %sbaris%s %skolom%s %sangka%s "
            "(atau 'keluar'/'reset'/'hint'): ",
            RED, RESET, PURPLE, RESET, BLUE, RESET);
        if (!fgets(in, sizeof(in), stdin)) continue;
        
        if(!strncmp(in, "keluar", 6)) return;
        if(!strncmp(in, "reset", 5)) {
            memcpy(b, orig, sizeof(b));
            strcpy(msg, "Papan direset");
            continue;
        }
        
        if(strcmp(in, "hint\n") == 0) {
            int hr, hc, hn, hint_type = findHint(b, &hr, &hc, &hn);
            if(hint_type) {
                b[hr][hc] = hn;
                sprintf(msg, hint_type == 2 ? 
                    "Perbaikan: Angka di baris %d, kolom %d seharusnya %d" :
                    "Hint: %d di baris %d, kolom %d",
                    hint_type == 2 ? hr+1 : hn,
                    hint_type == 2 ? hc+1 : hr+1,
                    hint_type == 2 ? hn : hc+1);
            }
            continue;
        }

        int r, c, n;
        if(sscanf(in, "%d %d %d", &r, &c, &n) != 3 || 
           r < 1 || r > 9 || c < 1 || c > 9 || n < 1 || n > 9) {
            strcpy(msg, "Input tidak valid! Gunakan "
                "baris(1-9) kolom(1-9) angka(1-9) atau perintah dibawah");
            continue;
        }

        r--; c--;
        if(orig[r][c]) strcpy(msg, "Tidak dapat mengubah angka asli!");
        else if(safe(b, r, c, n)) b[r][c] = n;
        else strcpy(msg, "Langkah tidak valid!");
    }
}

int main() {
    char playAgain;
    srand(time(NULL));
    do {
        playGame();
        printf("\nApakah Anda ingin bermain lagi? (y/n): ");
        scanf(" %c", &playAgain);
        getchar();
        printf("\n");
    } while(playAgain == 'y' || playAgain == 'Y');
    return 0;
}