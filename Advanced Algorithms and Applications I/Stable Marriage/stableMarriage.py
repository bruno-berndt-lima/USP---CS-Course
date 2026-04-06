def main():

    nTests = int(input())

    for i in range(nTests):
        nMarriages = int(input())
        
        womansPreference = []
        mansPreference = []

        mansFree = [True] * nMarriages
        womansFree = [True] * nMarriages

        engagements = {}

        for j in range(2 * nMarriages):
            pref = input()

            if j < nMarriages:
                womansPreference.append(pref.split(" "))
            else:
                mansPreference.append(pref.split(" "))

    
        proposes = [[] for i in range(nMarriages)]
    

        while checkFree(nMarriages, mansFree, proposes):
            for i in range(nMarriages):
                if mansFree[i]:
                    m = i
                    break
            for j in range(nMarriages):
                if int(mansPreference[m][j+1]) not in proposes[m]:
                    w = int(mansPreference[m][j+1])
                    break
            
            if womansFree[w-1]:
                proposes[m].append(w)
                engagements.update({w : m+1})
                mansFree[m] = False
                womansFree[w-1] = False
            else:
                m2 = engagements.get(w)
                for k in range(nMarriages):
                    if int(womansPreference[w-1][k+1]) == m+1:
                        mIndex = k+1
                    elif int(womansPreference[w-1][k+1]) == m2:
                        m2Index = k+1

                proposes[m].append(w)
                if mIndex < m2Index:
                    engagements.update({w : m+1})   
                    mansFree[m] = False
                    womansFree[w-1] = False
                    mansFree[m2-1] = True  
                else:
                    mansFree[m] = True

        
        for i in sorted(engagements, key=engagements.get):
            print(engagements[i], i)


def checkFree(N, mansFree, proposes):
    for i in range(N):
        if mansFree[i] and len(proposes[i]) < N:
            return True
    return False

    


main()