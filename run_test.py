import os, sys

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
    for line in os.popen(commands[0]).read().strip().split('\n'):
        outputs1.append(line.strip())

    for line in os.popen(commands[1]).read().strip().split('\n'):
        outputs2.append(line.strip())

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
