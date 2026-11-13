#include <stdio.h>
#include <string.h>
#include "board.h"
#include "game.h"

#define LINE_BUF 128

static void print_stars(void)
{
    for (int i = 0; i < 78; i++) putchar('*');
    putchar('\n');
}

static void print_scores(const Board *b)
{
    print_stars();
    printf("Player A score: %d\n", b->score[0]);
    printf("Player B score: %d\n", b->score[1]);
    print_stars();
}

/* Reads "r1 c1 r2 c2". Returns 1 on success, 0 on bad input, -1 on EOF. */
static int read_move(int *r1, int *c1, int *r2, int *c2)
{
    char line[LINE_BUF];
    char extra;

    if (fgets(line, sizeof line, stdin) == NULL)
        return -1;
    if (strchr(line, '\n') == NULL) {          /* discard overlong input */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        return 0;
    }
    if (sscanf(line, "%d %d %d %d %c", r1, c1, r2, c2, &extra) != 4)
        return 0;
    return 1;
}

void game_run(void)
{
    Board board;
    int player = 0;                            /* 0 = A, 1 = B */

    board_init(&board);
    board_print(&board);

    while (!board_is_full(&board)) {
        int r1, c1, r2, c2;

        printf("Player %c's turn. Enter the row and column of the first dot "
               "(e.g., A0 -> 0 0) and second dot:\n", player == 0 ? 'A' : 'B');
        fflush(stdout);

        int rc = read_move(&r1, &c1, &r2, &c2);
        if (rc < 0) {
            printf("\nInput closed. Exiting game.\n");
            return;
        }
        if (rc == 0) {
            printf("Invalid input. Type four numbers: row1 col1 row2 col2.\n");
            continue;
        }

        switch (board_validate_move(&board, r1, c1, r2, c2)) {
        case MOVE_OUT_OF_RANGE:
            printf("Out of range. Rows are 0-%d and columns are 0-%d.\n", ROWS, COLS);
            continue;
        case MOVE_NOT_ADJACENT:
            printf("Dots must be directly next to each other (horizontally or vertically).\n");
            continue;
        case MOVE_ALREADY_DRAWN:
            printf("That line has already been drawn. Try another.\n");
            continue;
        case MOVE_OK:
            break;
        }

        int completed = board_apply_move(&board, r1, c1, r2, c2, player);

        print_scores(&board);
        board_print(&board);

        if (completed == 0)
            player = 1 - player;               /* extra turn only if a box was completed */
    }

    printf("\n");
    print_stars();
    printf("GAME OVER\n");
    printf("Final score -> Player A: %d | Player B: %d\n",
           board.score[0], board.score[1]);
    if (board.score[0] > board.score[1])
        printf("Player A wins!\n");
    else if (board.score[1] > board.score[0])
        printf("Player B wins!\n");
    else
        printf("It's a tie!\n");
    print_stars();
}
