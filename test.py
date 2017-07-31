import sys
import numpy as np
import subprocess
import sys
def test(binTest, binRef, pathTest, pathRef):
   f = open(sys.argv[1], "rt")
   data = f.readlines()
   n = len(data)
   resRef = ""
   resTest = ""
   argsTest =  [binTest, pathTest]
   argsRef =  [binRef, pathRef]
   note = np.zeros(100)
   for i in range(100):
     rnd = np.random.randint(n)
     word =  data[rnd].split()[0]
     dist =  data[rnd].split()[1]
     argIn = "\"" + word + " " + dist + "\""
     #echo =  subprocess.run(["echo", argIn],  stdout=subprocess.PIPE)
     std = subprocess.Popen(["echo", argIn], stdout=subprocess.PIPE, shell=True)
     std.wait()
     rt = subprocess.run(args = argsTest, stdin =std.stdout,   stdout=subprocess.PIPE)
     rr = subprocess.run(args = argsRef, stdin =std.stdout,  stdout=subprocess.PIPE)
     resTest = rt.stdout # other version resTest += rt.stdout
     resRef = rr.stdout  # other version resRef += rr.stdout
     print(resTest)
     print((resTest == resRef))
     note[i] = int(resTest == resRef)
   print('your score is ', note.mean(), " on 100")

test("./TextMiningApp", "./TextMiningAppRef", "dic.bin", "dicRef.bin")
