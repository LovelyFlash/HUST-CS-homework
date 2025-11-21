n = int(input())
o = []
for i in range(0, n + 1):
    a, b = map(int, input().split())
    o.append((a, b))
o[1:] = sorted(o[1:], key=lambda x: x[0] * x[1])
ans = 0
pre = o[0][0]
for i in range(1, n + 1):
    ans = max(ans, pre // o[i][1])
    pre *= o[i][0]
print(ans)
