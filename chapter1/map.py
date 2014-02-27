#!/usr/bin/env python
# Mapper function for Hadoop streaming using python
import sys, string
for line in sys.stdin:
    words = line.strip().split()
    for word in words:
        word = word.lower()
        word = word.translate(None, string.punctuation)
        print("%s\t%d" % (word, 1))
