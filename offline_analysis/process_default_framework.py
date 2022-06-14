import re
source = open('outdata_no_defrag.txt','r')
lines=source.readlines()
source.close()
data=[]
frags = []
overall_frag = []
sumOverall = 0
compaction=[100000]*100
start="---"
signalFail = "FAILED"
signalFragmented = "FRAGMENTED"
fragmented = 0
failed = 0
success = 0
all = 0
counter = 0

totalSum =0
fragmentedTimes = 0

for line in lines:
    if start in line:
        counter = 0
        all = all + 1
    elif signalFail  in line:
        failed = failed + 1
    elif signalFragmented in line:
        fragmented = fragmented + 1
    else:
        fragment = line.split(",")
        overall_frag.append(int(fragment[1]))
        sumOverall = int(fragment[1]) + sumOverall
        totalSum = totalSum + 1
        if int(fragment[1]) != 0:
            fragmentedTimes = fragmentedTimes + 1
        data.append(line)
        com = line.split("=")
        val = int(com[2])
        counter = counter + val
        compaction[all-1] = counter
sum = 0
for i in compaction:
    sum = sum + i
success = success - failed
average = sum / 1000
if len(frags) != 0:
	averageFrags = sumF / len(frags)
else:
	averageFrags=0
if len(overall_frag) != 0:
	averageOverall = sumOverall / len(overall_frag)
else:
	averageOverall = 0

print("Average heap fragmentation: ",averageOverall, "\n")
print("Average fragmentation at failures :  ",averageFrags, "\n")
print("average compactions : ", average,"\n")
print("Total ",all," Scenarios \n")
print("Failed due to fragmentation: ",fragmented,"\n")
print("Succesful: ",all-failed-fragmented,"\n")
print("Overall Failed: ",failed+fragmented,"\n\n")
