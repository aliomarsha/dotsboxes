#include <stdio.h>
#include <stdlib.h>
#include "board.h"

static const char PLAYER_CHAR[2] = {'A', 'B'};

void board_init(Board *b)
{
    for (int r = 0; r <= ROWS; r++)
        for (int c = 0; c < COLS; c++)
            b->h[r][c] = 0;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c <= COLS; c++)
            b->v[r][c] = 0;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            b->owner[r][c] = ' ';
    b->score[0] = b->score[1] = 0;
    b->boxes_claimed = 0;
}

void board_print(const Board *b)
{
    printf("  ");
    for (int c = 0; c <= COLS; c++)
        printf("%d ", c);
    printf("\n");

    for (int r = 0; r <= ROWS; r++) {
        /* dot row */
        printf("%d ", r);
        for (int c = 0; c <= COLS; c++) {
            putchar('.');
            if (c < COLS)
                putchar(b->h[r][c] ? '-' : ' ');
        }
        putchar('\n');

        /* vertical-edge / box row */
        if (r < ROWS) {
            printf("  ");
            for (int c = 0; c <= COLS; c++) {
                putchar(b->v[r][c] ? '|' : ' ');
                if (c < COLS)
                    putchar(b->owner[r][c]);
            }
            putchar('\n');
        }
    }
}

MoveStatus board_validate_move(const Board *b, int r1, int c1, int r2, int c2)
{
    if (r1 < 0 || r1 > ROWS || r2 < 0 || r2 > ROWS ||
        c1 < 0 || c1 > COLS || c2 < 0 || c2 > COLS)
        return MOVE_OUT_OF_RANGE;

    int dr = abs(r1 - r2), dc = abs(c1 - c2);
    if (dr + dc != 1)
        return MOVE_NOT_ADJACENT;

    if (dr == 0) {                       /* horizontal */
        int c = c1 < c2 ? c1 : c2;
        if (b->h[r1][c]) return MOVE_ALREADY_DRAWN;
    } else {                             /* vertical */
        int r = r1 < r2 ? r1 : r2;
        if (b->v[r][c1]) return MOVE_ALREADY_DRAWN;
    }
    return MOVE_OK;
}

/* O(1): a box is complete when its 4 surrounding edges are drawn. */
static int box_complete(const Board *b, int r, int c)
{
    return b->h[r][c] && b->h[r + 1][c] && b->v[r][c] && b->v[r][c + 1];
}

static int claim_if_complete(Board *b, int r, int c, int player)
{
    if (b->owner[r][c] == ' ' && box_complete(b, r, c)) {
        b->owner[r][c] = PLAYER_CHAR[player];
        b->score[player]++;
        b->boxes_claimed++;
        return 1;
    }
    return 0;
}

int board_apply_move(Board *b, int r1, int c1, int r2, int c2, int player)
{
    int completed = 0;

    if (r1 == r2) {                      /* horizontal edge */
        int c = c1 < c2 ? c1 : c2;
        b->h[r1][c] = 1;
        if (r1 > 0)    completed += claim_if_complete(b, r1 - 1, c, player);
        if (r1 < ROWS) completed += claim_if_complete(b, r1, c, player);
    } else {                             /* vertical edge */
        int r = r1 < r2 ? r1 : r2;
        b->v[r][c1] = 1;
        if (c1 > 0)    completed += claim_if_complete(b, r, c1 - 1, player);
        if (c1 < COLS) completed += claim_if_complete(b, r, c1, player);
    }
    return completed;
}

int board_is_full(const Board *b)
{
    return b->boxes_claimed == TOTAL_BOXES;
}
