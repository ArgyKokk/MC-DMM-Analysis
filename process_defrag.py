import re
source = open('outdata_defrag.txt','r')
lines=source.readlines()
source.close()
compaction=[99]*100
start="---"
signalFail = "FAILED"
signalFragmented = "FRAGMENTED"
index = 0
fragmented = 0
failed = 0
all = 0
counter = 0

for line in lines:
    if start in line:
        all = all + 1
        counter=0
    elif signalFail  in line:
        failed = failed + 1
    elif signalFragmented in line:
        fragmented = fragmented + 1
    else:
        com = line.split("=")
        val = int(com[2])
        counter = counter + val
        compaction[all-1] = counter
sum = 0
for i in compaction:
    sum = sum + i
success = all - failed - fragmented
average = sum / 100
print("average compactions : ", average,"\n")
print("Total ",all," Scenarios \n")
print("Failed due to fragmentation: ",fragmented,"\n")
print("Succesful: ",success,"\n")
print("Overall Failed: ",failed+fragmented,"\n\n")
