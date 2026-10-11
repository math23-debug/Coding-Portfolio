import requests

searchPlayer = {}

response = requests.get(f"https://api.nhle.com/stats/rest/en/skater/summary?isAggregate=false&isGame=false&sort=%5B%7B%22property%22:%22goals%22,%22direction%22:%22DESC%22%7D,%7B%22property%22:%22playerId%22,%22direction%22:%22ASC%22%7D%5D&start=0&limit=50&cayenneExp=gameTypeId=2%20and%20seasonId%3C=20252026%20and%20seasonId%3E=20252026")
data = response.json()

playerStats = data["data"]

index = 0

for player in playerStats:
    searchPlayer["".join(player["skaterFullName"].lower().split())] = index
    print("".join(player["skaterFullName"].lower().split()))
    index += 1


playerName = "".join(input("Search a player (Full Name):").lower().split())
while True:
    try:
        index = searchPlayer[playerName]
        break
    except KeyError:
        print("Name not found, try again")
        playerName = "".join(input("Search a player (Full Name):").lower().split())

print("# of goals:")
print(playerStats[index]["goals"])
print("# of assists:")
print(playerStats[index]["assists"])
print("Games played:")
print(playerStats[index]["gamesPlayed"])

playerName = input("Compare against other player:")
while True:
    try:
        index_two = searchPlayer[playerName]
        break
    except KeyError:
        print("Name not found, try again")
        playerName = input("Search a player:")

if int(playerStats[index]["goals"]) >= (playerStats[index_two]["goals"]):
    print(f"{playerStats[index]["lastName"]} has {playerStats[index]["goals"] - playerStats[index_two]["goals"]} more goals than {playerStats[index_two]["lastName"]}")
else:
     print(f"{playerStats[index_two]["lastName"]} has {playerStats[index_two]["goals"] - playerStats[index]["goals"]} more goals than {playerStats[index]["lastName"]}")
    