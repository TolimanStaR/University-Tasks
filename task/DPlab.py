from collections import deque

n, m, k = map(int, input().split())
sf, ss = map(int, input().split())
ff, fs = map(int, input().split())
table = [str(input()) for _ in range(n)]
dp = [[[float('inf')] * (k + 1) for _ in range(m)] for ___ in range(n)]
used = [[[False] * (k + 1) for _ in range(m)] for __ in range(n)]

wall = '#'
free_cell = '*'

dimension_conditions = [deque() for _ in range(k + 1)]


def add_condition(i, j, k, a):
    if -1 < i < n and -1 < j < m and (not used[i][j][k] or a < dp[i][j][k]):
        if table[i][j] == free_cell:
            dimension_conditions[k].append([i, j, k, a])
            used[i][j][k] = True
        elif table[i][j] == wall and k > 0:
            if not used[i][j][k - 1]:
                kth_dimension(i, j, k - 1, a)
                used[i][j][k - 1] = True


def kth_dimension(i, j, k, a):
    dimension_conditions[k].append([i, j, k, a])
    while dimension_conditions[k]:
        condition = dimension_conditions[k].popleft()
        ic, jc, k, ans = condition[0], condition[1], condition[2], condition[3]

        dp[ic][jc][k] = ans
        used[ic][jc][k] = True

        add_condition(ic - 1, jc, k, ans + 1)
        add_condition(ic, jc - 1, k, ans + 1)
        add_condition(ic, jc + 1, k, ans + 1)
        add_condition(ic + 1, jc, k, ans + 1)


kth_dimension(sf, ss, k, 0)
print(min(dp[ff][fs]))
