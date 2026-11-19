# Debugging

## Valgrind
Command: valgrind --leak-check=full ./dotsboxes
Result: All heap blocks were freed, 0 errors from 0 contexts.

## GDB
Breakpoint on board_apply_move. Used bt, print *b, print r1, next, continue
to confirm the move 0 0 0 1 was applied to the right horizontal edge.
