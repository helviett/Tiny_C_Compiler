f, o = open('FAC.csv', 'r'), open('output.txt', 'w')
f.readline()
print("{", file=o)
for l in f:
	vs = l.strip().split(',')
	vs.pop(0)
	print("\t{%s}," % ", ".join(vs), file=o)
print("}", file=o)
o.close()