import os, sys
import subprocess

def main():
    excepted_outputs1 = []
    excepted_outputs2 = []
    commands = []
    outputs1 = []
    outputs2 = []

    error = ""

    # commandsok beolvasása
    file = open("commands.txt", "r")
    for line in file:
        commands.append(line.strip())
    file.close

    # excepted_outputs beolvsása
    file = open("output1.txt", "r")
    for line in file:
        excepted_outputs1.append(line.strip())
    file.close

    file = open("output2.txt", "r")
    for line in file:
        excepted_outputs2.append(line.strip())
    file.close

    # futási eredmények elmentése
    p = subprocess.Popen([commands[0]], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    for i in range(17):
        outputs1.append(p.stdout.readline().decode().strip())

    p = subprocess.Popen([commands[1]], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    for i in range(17):
        outputs2.append(p.stdout.readline().decode().strip())

    # futási eredmények és várt eredmények vizsgálata
    for i in range(len(outputs1)):
        if outputs1[i] != excepted_outputs1[i]:
            error += "Found some error...\n"

    for i in range(len(outputs2)):
        if outputs2[i] != excepted_outputs2[i]:
            error += "Found some error...\n"
    
    #valgrind futása
    for i in commands:
        os.system("valgrind --leak-check=full --error-exitcode=5 " + i)
        if (os.system("echo $?") == 5):
            print("Memory leak...\n")
            sys.exit(5)

    if len(error) == 0: 
        sys.exit(0)
    else: 
        sys.exit(1)

if __name__ == "__main__":
    main()
