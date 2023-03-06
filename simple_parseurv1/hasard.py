import os
import random

def main():
    num = random.randint(0, 999)
    print('test'+str(num)+'.txt')
    print(['mon_Test'])
    os.system('./main /home/azazhel/Documents/3A_S2/NE302/simple_parseurv1/testFile/test'+str(num)+'.txt')
    print(['Prof_Test'])
    os.system('./testsimplegrammar /home/azazhel/Documents/3A_S2/NE302/simple_parseurv1/testFile/test'+str(num)+'.txt')

main()