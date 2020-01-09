
import os
from GameSolver import Game


with open(os.path.join(os.path.split(__file__)[0], "matrix.csv")) as F:
    m = []
    for line in F:
        m.append([float(x) for x in line.strip().split(',')])


game = Game(m)
game.solve()

print(game.get_solution(True))
print("success: test passed")
