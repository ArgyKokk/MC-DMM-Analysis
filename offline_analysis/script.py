import random
import re

pairs = 20
data = []
nums = [10,14,15,16,17,18,19,20,21,22,23,25,26,32,27,28,24,29,30,31,32] # DAS

updatelist = []
elements = random.sample(nums,20)
print(elements)

for i in range(pairs):
    if i >= len(elements):
        index = i % len(elements)
        granule = elements[index]
    else:
        granule = elements[i]
    malloc = 'test'+str(i)+'=(int*)MemluvAlloc('+str(granule) + '*sizeof(int),0,&heap'+str(i)+');'
    free = 'MemluvFree((void*)test'+str(i)+','+str(granule)+'*sizeof(int),heap'+str(i)+');'
    update = 'test'+str(i)+'=(int*)UpdateAddress(test'+str(i)+','+str(granule)+'*sizeof(int),heap'+str(i)+');'
    updatelist.append((0,update));
    valueMalloc = random.random();
    data.append((valueMalloc,malloc))
    valueFree = random.random();
    while valueFree >= valueMalloc:
        valueFree = random.random();
    data.append((valueFree,free))

data.sort(reverse=True)

with open('new_pattern.txt','w') as target:
        for _, i in data:
            if re.search('.+Alloc.+',i):
                target.write(i+str("\n"))
                command = i.split("=")
                pointer = command[0]
                for j in range (0,len(updatelist)):
                    splitUpdateCommand = updatelist[j][1].split("=")
                    pointerUpdate = splitUpdateCommand[0]
                    if re.search(pointer,pointerUpdate):
                        y = list(updatelist[j])
                        y[0] = 1
                        updatelist[j] = tuple(y)
            if re.search('.+Free.+',i):
                target.write(i+str("\n"))
                freeCommand = i.split(",")
                freeExpression = freeCommand[0].split(")")
                freePointer = freeExpression[1]
                for j in range(0,len(updatelist)):
                    splitUpdateCommand = updatelist[j][1].split("=")
                    pointerUpdate = splitUpdateCommand[0]
                    if re.search(freePointer,pointerUpdate):
                        y = list(updatelist[j])
                        y[0] = 0
                        updatelist[j] = tuple(y)
                    if updatelist[j][0] == int(1):
                        target.write(updatelist[j][1]+str("\n"))
