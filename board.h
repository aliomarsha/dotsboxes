#ifndef BOARD_H
#define BOARD_H

#define ROWS 4              /* boxes per column  (dots: ROWS+1) */
#define COLS 5              /* boxes per row     (dots: COLS+1) */
#define TOTAL_BOXES (ROWS * COLS)

typedef struct {
    char h[ROWS + 1][COLS];     /* horizontal edges: h[r][c] joins dot (r,c)-(r,c+1) */
    char v[ROWS][COLS + 1];     /* vertical edges:   v[r][c] joins dot (r,c)-(r+1,c) */
    char owner[ROWS][COLS];     /* 'A', 'B' or ' ' */
    int  score[2];              /* score[0] = A, score[1] = B */
    int  boxes_claimed;
} Board;

/* Result codes for board_validate_move */
typedef enum {
    MOVE_OK = 0,
    MOVE_OUT_OF_RANGE,
    MOVE_NOT_ADJACENT,
    MOVE_ALREADY_DRAWN
} MoveStatus;

void       board_init(Board *b);
void       board_print(const Board *b);
MoveStatus board_validate_move(const Board *b, int r1, int c1, int r2, int c2);
/* Draws the line (must be valid). Returns the number of boxes it completed (0-2). */
int        board_apply_move(Board *b, int r1, int c1, int r2, int c2, int player);
int        board_is_full(const Board *b);

#endif
