f = open('bla').readlines()

count = [] 
num = []
for i in f[:-1]:
    # print(i)
    a, b = i.split(',')
    a = int(a)
    b = int(b)
    count.append(a)
    num.append(b)

m = max(count)
index = count.index(m)
print("count = ", count[index], "num = ", num[index], bin(num[index]))

