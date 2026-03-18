def change(fc):
    new_fc = []
    count = 0
    for char in fc:
        if char == '\"':
            count = -1
        if char == ' ':
            new_fc.extend([' ' for x in range(7-count)])
            continue
        count += 1
        new_fc.append(char)
        # print(''.join(new_fc), count)
        # input()
    return ''.join(new_fc)

with open("ops.txt", "r+") as f:
    fc = f.read()
    fc = change(fc)
    f.seek(0)
    f.write(fc)
    f.truncate()