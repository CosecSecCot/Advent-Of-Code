f = open("input")
lines = f.readlines()
lines = [list(map(int, line[:-1].split())) for line in lines]
print(lines)

ans = 0
for line in lines:
    for i in range(len(line)):
        for j in range(len(line) - i - 1):
            line[j] = line[j+1] - line[j]
        print(line)
    ans += sum(line)

print(ans)
