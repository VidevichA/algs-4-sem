import copy

def suffixArray(s):
    lst = [i for i in range(0, len(s))]
    lst.sort(key = lambda x: s[x:])
    return lst

def check(size, suf, s):
    i = 0
    lst = []
    tlst = []
    for i in suf:
        if len(s[i:]) >= size:
            if len(tlst) == 0:
                tlst.append(i)
            else:
                if s[tlst[-1]:tlst[-1] + size] == s[i:i + size]:
                    tlst.append(i)
                else:
                    if len(tlst) >= 3:
                        tlst.sort()
                        lst.append(tlst.copy())
                    tlst.clear()
                    tlst.append(i)
    if len(tlst) >= 3:
        tlst.sort()
        lst.append(tlst.copy())
    for i in lst:
        for j in i:
            if abs(i[0] - j) >= size and abs(i[-1] - j) >= size:
                return s[j:j + size]
    return ''

def binSearch(s, suf):
    l = 0
    r = len(s) // 3 + 1
    mid = 0
    max = ''
    while l <= r:
        mid = (l + r) // 2
        temp = check(mid, suf, s)
        if len(temp) == 0:
            r = mid - 1
        else:
            if len(max) == 0:
                max = copy.deepcopy(temp)
            else:
                if len(temp) >= len(max):
                    max = copy.deepcopy(temp)
                    l = mid + 1
                else:
                    r = mid - 1
    return max

s = input()
suf = suffixArray(s)
answer = binSearch(s, suf)
print(answer)
