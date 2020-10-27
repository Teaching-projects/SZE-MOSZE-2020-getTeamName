import os, sys

def main():
    excepted_outputs = []
    commands = []
    outputs = []

    error = ""

    # commandsok beolvasása
    file = open("commands.txt", "r")
    for line in file:
        commands.append(line.strip())
    file.close

    # excepted_outputs beolvsása
    file = open("outputs.txt", "r")
    for line in file:
        excepted_outputs.append(line.strip())
    file.close

    # futási eredmények elmentése
    for i in range(len(excepted_outputs)):
        outputs.append(os.popen(commands[i]).read().strip())

    # futási eredmények és várt eredmények vizsgálata
    for i in range(len(outputs)):
        if outputs[i] != excepted_outputs[i]:
            error += "Found some error...\n"
    
    if len(error) == 0: 
        sys.exit(0)
    else: 
        sys.exit(1)

if __name__ == "__main__":
    main()
