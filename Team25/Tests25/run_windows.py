import os

TESTDIRS = ["AdvancedSPA", "BasicSPA"]
QUERY = "queries"
AUTOTESTER_PATH = os.path.join(os.getcwd(), "Code25", "out", "build", "x64-Debug", "src", "autotester", "autotester.exe")

def isQueryFile(fname):
    return QUERY in fname

def getPrefix(fname):
    q_index = fname.find(QUERY)
    prefix = fname[0 : q_index - 1]
    return prefix

def getMatchingSource(fname):
    files = os.listdir()
    prefix = getPrefix(fname)
    for otherFile in files:
        if prefix in otherFile and QUERY not in otherFile:
            return otherFile

def runTests(dir, originalDir):
    os.chdir(dir)
    outputPrefix = os.path.join(os.getcwd(), "..", "..", "Results")
    files = os.listdir()
    for fname in files:
        if isQueryFile(fname):
            queryFile = fname
            sourceFile = getMatchingSource(fname)  
            prefix = getPrefix(fname)
            outFile = os.path.join(outputPrefix, prefix + ".xml")
            os.system(f"{AUTOTESTER_PATH} {sourceFile} {queryFile} {outFile}")
            print(outFile)
            print(" ")
    os.chdir(originalDir)

os.chdir("Tests25")
for testPrefix in TESTDIRS:
    currDir = os.getcwd()
    testDir = os.path.join(currDir, testPrefix)
    os.chdir(testDir)
    subDirs = os.listdir()
    for item in subDirs:
        runTests(item, testDir)
    os.chdir("..")