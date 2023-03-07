import os
import random

def main():
    num = random.randint(0, 999)
    print('test'+str(num)+'.txt')
    print(['mon_Test'])
    os.system('./simple_parseur testFile/test'+str(num)+'.txt')
    print(['Prof_Test'])
    os.system('./parseur_prof testFile/test'+str(num)+'.txt')

main()
