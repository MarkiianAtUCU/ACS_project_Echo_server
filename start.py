import subprocess
import os
import sys

TEST_PROGRAM = "./build/tester"+".exe" if os.name == "nt" else "./build/tester"


def main(number_of_iterations):

    for i in range(int(number_of_iterations)):
        result = subprocess.run([TEST_PROGRAM], stdout=subprocess.PIPE)
        temp = result.stdout.decode('utf-8').strip().split()
        print(temp)
        f = open("results.txt", "a")
        f.write(f"{temp[0]} {temp[1]} {temp[2]}\n")
        f.close()


if __name__ == "__main__":

    if len(sys.argv) < 2:
        print("Invalid number of agruments")
    else:
        main(sys.argv[1])