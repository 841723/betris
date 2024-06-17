# Betris

Betris is a simple algorithm that can be used to solve the Tetris game. 
Given a sequence of pieces, the algorithm will determine a possible position for each piece in order to complete the requested amount of rows.

To compile Betris, run the following command:

```make```

Betris is execute by running the following command:

```./betris <board n rows> <board n columns> <requested n rows> <delay> <sequence of pieces>```

Where the sequence of pieces can be a negative number, the sequence will be created randomly with that given number of pieces.
The sequence of pieces can also be a string of pieces, where each piece is represented by a number from 0 to 4. The last value in the secuencia of pieces must be -1.

Piece representation:
- 0: 
    >x x x x

- 1
    >x 
    >x
    >x
    >x

- 2: 
    >x x
    > x
    > x

- 3: 
    >x x x
    >&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;x

- 4: 
    >x x
    >x x


Example:
```./betris 6 5 4 20 0 0 4 2 3 2 1 -1```
```./betris 6 5 2 20 -5```

    