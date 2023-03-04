import glob
import os
import sys
import pytest

BASE_DIR = os.environ.get("BASE_DIR", ".")
EMUL_HTTP = os.path.join(BASE_DIR, "main")
EMUL_HTTP_PROF = os.path.join(BASE_DIR, "testsimplegrammar")
ALL_FILES = glob.glob(os.path.join(BASE_DIR, "../testFile/*.txt"))
ALL_FILES.sort()


class TestHTTP:
    @pytest.mark.parametrize("filename", ALL_FILES)
    def testFiles(self, filename):
        out_put=os.system(f"./{EMUL_HTTP} {filename}>my_resultat.txt")
        os.system(f"./{EMUL_HTTP_PROF} {filename}>prof_resultat.txt")
        resultat =1
        my_resultat = open("my_resultat.txt","r")
        prof_resultat=open("prof_resultat.txt","r")
        a= my_resultat.read()
        b=prof_resultat.read()
        for i in range(0,len(a)):
            if a[i]!=b[i]:
                resultat = 0
        

        if (resultat ==0)or(out_put!=0):
            pytest.fail("Error")
        os.system(f"rm my_resultat.txt")   
        os.system(f"rm prof_resultat.txt")      

pytest.main(sys.argv)
