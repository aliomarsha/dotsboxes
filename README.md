# Dots and Boxes – Sprint 1 (two players)

Board: 4x5 boxes (5x6 dots). Enter a move as `row1 col1 row2 col2`, e.g. `0 4 0 3`.
Completing a box gives you the box (A/B appears inside) and an extra turn.

## Build / run
    make
    ./dotsboxes

## Debugging
    valgrind --leak-check=full ./dotsboxes
    gdb ./dotsboxes          # built with -g

## Alpine Linux VM: auto-start game with no login
1. Install tools: `apk add build-base git valgrind gdb`
2. `git clone <your repo> && cd DotsAndBoxes && make && make install`   (as root)
3. Edit `/etc/inittab`, replace the tty1 line with:

       tty1::respawn:/sbin/getty -n -l /usr/local/bin/startgame 38400 tty1

4. `reboot` – the game appears immediately, no username/password.
   (If you use the serial console, apply the same change to the ttyS0 line.)

## Files
- board.h / board.c : board state, drawing, box completion (O(1) check)
- game.h / game.c   : turn loop, input validation, scores, winner
- main.c            : entry point
- Makefile, startgame.sh
