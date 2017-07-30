#!/usr/bin/python3

import sys
import numpy as np

words = open(sys.argv[1], "rt").read().split()
w = []
freq = []
for i in range(0, len(words) - 1, 2):
    w.append(words[i])
    freq.append(words[i + 1])

w = np.array(w)
freq = np.array(freq)

ind = np.argsort(w)
w = w[ind]
freq = freq[ind]

f = open(sys.argv[2], "w")
for i in range(len(w)):
    f.write("%s %s\n" % (w[i], freq[i]))
f.close()
