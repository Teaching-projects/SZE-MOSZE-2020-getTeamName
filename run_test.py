import os, sys

def main():
    excepted_outputs = ["Sally wins. Remaining HP: 5", "Kakarott wins. Remaining HP: 29970", "Kakarott wins. Remaining HP: 29990", "Maple wins. Remaining HP: 30", "Kakarott wins. Remaining HP: 30000", "Kakarott wins. Remaining HP: 30000"]
    commands = ['./a.out "Units/Sally.json" "Units/Maple.json"', './a.out "Units/Sally.json" "Units/Kakarott.json"', './a.out "Units/Maple.json" "Units/Kakarott.json"', './a.out "Units/Maple.json" "Units/Sally.json"', './a.out "Units/Kakarott.json" "Units/Sally.json"', './a.out "Units/Kakarott.json" "Units/Maple.json"']
    outputs = []

    error = ""

    for i in range(len(excepted_outputs)):
        outputs.append(os.popen(commands[i]).read().strip())

    for i in range(len(outputs)):
        if outputs[i] != excepted_outputs[i]:
            error += "Found some error...\n"

    if len(error) == 0: 
        sys.exit(0)
    else: 
        sys.exit(1)


if __name__ == "__main__":
    main()
