import sys

def checkline():
    glb.linecount += 1
    w = glb.l.split()
    glb.wordcount += len(w)

class glb:
    linecount = 0
    wordcount = 0
    l = []

f = open(sys.argv[1])

for glb.l in f.readlines():
    checkline()

print glb.linecount, glb.wordcount

