import sys

txt = open('artifact_cppcheck.txt')

if (txt.find("error")) or (txt.find("warning")):
    sys.exit(1)
else:
    sys.exit(0)

txt.close()