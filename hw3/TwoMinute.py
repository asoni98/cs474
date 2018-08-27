import sys
import scipy.optimize
import pickle

gameStates = pickle.load(open("two_minute.pickle"))

# rows = 3
# cols = 3

# a1 = [[-0.30, -0.26, -0.28],
#       [-0.25, -0.33, -0.30],
#       [-0.20, -0.28, -0.33]]
# bounds = (0.0, 5.0)
# b_ub = [-1.0] * cols
# c = [1.0] * rows

# result = scipy.optimize.linprog(c, a1, b_ub, None, None, bounds)

# value = 1.0 / result.fun
# x = [xi * value for xi in result.x]

# # now solve for P2's strategy
# a2 = [[0.30, 0.25, 0.20],
#       [0.26, 0.33, 0.28],
#       [0.28, 0.30, 0.33]]
# b_ub = [1.0] * rows
# c = [-1.0] * cols

# result = scipy.optimize.linprog(c, a2, b_ub, None, None, bounds)

# y = [-yi * value for yi in result.x]

# print(x)
# print(y)
# print(value)

# defenses are 4-3 Blast Man-to-man, 4-3 Sam-Will Blitz, Prevent
# outcomes are (yards, time, turnover)
# probability of outcomes are .20, .05, .25, .1, .4 (not measured carefully)

slant_37 = [[(-1, 4, False), (20, 3, False), (10, 2, False), (7, 2, False), (4, 2, False)],
           [(1, 3, False), (10, 2, False), (5, 2, False), (1, 4, False), (2, 2, False)],
           [(8, 2, False), (20, 3, False), (4, 2, False), (2, 2, False), (6, 2, False)]]

y_cross_80 = [[(0, 1, True), (-7, 4, False), (0, 1, False), (0, 1, True), (24, 2, False)],
              [(0, 1, False), (0, 1, True), (-6, 4, False), (18, 2, False), (13, 2, False)],
              [(19, 4, False), (0, 1, True), (22, 2, False), (47, 3, False), (0, 1, False)]]

z_corner_82 = [[(28, 3, False), (-9, 4, False), (47, 3, False), (0, 1, False), (0, 1, False)],
               [(30, 3, False), (-9, 4, False), (8, 2, False), (-8, 4, False), (0, 1, False)],
               [(38, 3, False), (0, 1, True), (0, 1, False), (-9, 4, False), (0, 1, False)]]

plays = [slant_37, y_cross_80, z_corner_82]
prob = [0.20, 0.05, 0.25, 0.1, 0.4]



def main():
	if len(sys.argv) == 4:
		down = int(sys.argv[1])
		down_yards = int(sys.argv[2])
		touchdown_yards = int(sys.argv[3])
		time = int(sys.argv[4])
		#call some function

	if (len(sys.argv) == 5) and (sys.argv[1] == "-matrix"):
		down = int(sys.argv[2])
		down_yards = int(sys.argv[3])
		touchdown_yards = int(sys.argv[4])
		time = int(sys.argv[5])
		#call some function
		


if __name__ == '__main__':
	main()