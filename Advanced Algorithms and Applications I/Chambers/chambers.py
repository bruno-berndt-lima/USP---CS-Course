from readline import append_history_file
import sys

def main():
    for line in sys.stdin: 
        nChambers, nSpecimens = line.split(" ")
        chambersMass = [0] * int(nChambers)
        chambersSpecs = [[]] * int(nSpecimens)
        s = input()
        specimens = s.split(" ")
        specimens.sort(reverse=False)

        for i in range(int(nSpecimens)):
            chambersSpecs[i%int(nSpecimens)].append(int(specimens[i]))
            #chambersMass[i] = chambersMass[i] + int(specimens[i])
            

        break
    
    print(int(nChambers), int(nSpecimens))
    print(chambersSpecs)

main()