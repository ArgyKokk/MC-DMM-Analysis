
source = open('another_file.txt','r')
lines=source.readlines()
source.close()

lines1 = ['#include <stdio.h>','#include <stdlib.h>','#include "memluv.h"','#include "global.h"','void main()','{','int * test1, *test2, *test3, *test4, *test5, *test6, *test7, *test8, *test9, *test10, *test0, *test11,*test12,*test13,*test14,*test15,*test16,*test17,*test18,*test19,*test20,*test21,*test22,*test23,*test24,*test25,*test26,*test27,*test28,*test29,*test30,*test31,*test32,*test33,*test34,*test35,*test36,*test37,*test38,*test39,*test40,*test41,*test42,*test43,*test44,*test45,*test46,*test47,*test48,*test49,*test50,*test51,*test52,*test53,*test54,*test55,*test56,*test57,*test58,*test59,*test60,*test61,*test62,*test63,*test64,*test65,*test66,*test67,*test68,*test69,*test70,*test71,*test72,*test73,*test74,*test75,*test76,*test77,*test78,*test79,*test80,*test81,*test82,*test83,*test84,*test85,*test86,*test87,*test88,*test89,*test90,*test91,*test92,*test93,*test94,*test95,*test96,*test97,*test98,*test99,*test100;','int  heap1, heap2, heap3, heap4, heap5, heap6, heap7, heap8, heap9, heap0, heap10, heap11,heap12,heap13,heap14,heap15,heap16,heap17,heap18,heap19,heap20,heap21,heap22,heap23,heap24,heap25,heap26,heap27,heap28,heap29,heap30,heap31,heap32,heap33,heap34,heap35,heap36,heap37,heap38,heap39,heap40,heap41,heap42,heap43,heap44,heap45,heap46,heap47,heap48,heap49,heap50,heap51,heap52,heap53,heap54,heap55,heap56,heap57,heap58,heap59,heap60,heap61,heap62,heap63,heap64,heap65,heap66,heap67,heap68,heap69,heap70,heap71,heap72,heap73,heap74,heap75,heap76,heap77,heap78,heap79,heap80,heap81,heap82,heap83,heap84,heap85,heap86,heap87,heap88,heap89,heap90,heap91,heap92,heap93,heap94,heap95,heap96,heap97,heap98,heap99,heap100;']

with open("./accelerators.c", 'w') as f:
    for line1 in lines1:
        f.write(line1)
        f.write('\n')
    for line in lines:
        f.write(line)
        f.write('\n')
    f.write('}')
    f.close()
with open("./src_no_frag/accelerators.c", 'w') as f:
    for line1 in lines1:
        f.write(line1)
        f.write('\n')
    for line in lines:
        f.write(line)
        f.write('\n')
    f.write('}')
    f.close()
