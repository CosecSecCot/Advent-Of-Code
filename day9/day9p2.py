f = open("input")
lines = f.readlines()
lines = [list(map(int, line[:-1].split())) for line in lines]
# lines.reverse()
print(lines)


def extrapolate_back(line: list) -> int:
    ans = 0
    for i in range(len(line) - 1, -1, -1):
        ans = line[i] - ans
        # print(ans)
    return ans


ans = 0
for line in lines:
    for i in range(len(line)):
        for j in range(len(line) - 1, i, -1):
            line[j] = line[j] - line[j-1]
        print(line)
    print()
    ans += extrapolate_back(line)

    # ans += sum(line)

print(ans)
