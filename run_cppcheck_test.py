import sys

txt = open("artifact_cppcheck.txt","r")
txt_content = txt.read()
if(("error" in txt_content) or ("warning" in txt_content)):
    sys.exit(1)
else:
    sys.exit(0)
txt.close()