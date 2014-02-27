import sys

wordmap = {}
for line in sys.stdin:
    word, cnt = line.strip().split("\t")
    if(not wordmap.has_key(word)):
        wordmap[word] = int(cnt)
    else:
        wordmap[word] += int(cnt)

for word in wordmap.keys():
    print("%s\t%d" % (word, wordmap[word]))
