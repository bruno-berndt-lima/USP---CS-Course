def main() :
    arrayLenght = int(input())
    priceOfTickets = list(map(int, input().split()))
    days = list(map(int, input().split()))

    cost = minCost(days, priceOfTickets)
    print(cost)


def minCost(days: list[int], costs: list[int]):
    dp = {}
    for i in range(len(days) - 1, -1, -1):
        dp[i] = float("inf")
        for d, c in zip([1, 7, 30], costs):
            j = i
            while j < len(days) and days[j] < days[i] + d:
                j += 1
            dp[i] = min(dp[i], c + dp.get(j, 0))
    
    return dp[0]

main()

        
    
