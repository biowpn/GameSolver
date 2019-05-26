# GameSolver
Solve arbitrary two-player zero-sum game.

## But what is a "two-player zero-sum game"?
It's exactly what its name suggests!
Consider a game involving two players. Each player has some options and they make a choice simultaneously (without know other's choice).
The payoff (a real value) for each player will be solely dependent on the actions they take.
It just happens that, for every possible outcome, the two payoffs for the two players sum up to exactly to zero, hence "zero-sum".

A classic example of "two-player zero-sum game" is one-round Rock-Paper-Scissor:
If I win, you pay me 1 buck; if you win, I pay you 1 buck; otherwise (draw), no one pays anything.

## OK, but what exactly do we solve?
For a given game (payoff), we're interested in the optimal strategy that maximizes the expected payoff. That's what this program does: find out one optimal strategy for each player!
How do we know there is definitely an optimal strategy? Well, according to serious Game Theory stuff, there is; just trust me that it's been proven (by John Nash).

A two-player zero-sum game can be specified as a matrix, which is the payoff for the row player. 
Using the Rock-Paper-Scissor example, assuming the actions for both sides are {Rock, Paper, Scissor}, the payoff matrix will be:

|   |   |   |
|----|----|----|
| 0 | -1 | 1 |
| 1 | 0 | -1 | 
| -1 | 1 | 0 | 


It can shown that, the optimal strategy for both players is the same: use Rock, Paper, and Scissor each 1/3 of the time.

## OK, enough talk, show me the code!

The simpler way is using the Python wrapper:

```
game = Game([[0, -1, 1], [1, 0, -1], [-1, 1, 0]])
game.solve()
print(game.get_solution(True))
```

You can also refer to `Game.h`/`GameSolver.h` to use it with C/C++.

A DLL "GameSolver.dll" has been compiled. The Python wrapper relies on it.
The DLL is compatible for 64-bit Windows only. If you use other operating system, you need to re-compile the cpp codes.

