import pandas as pd
import requests
import matplotlib.pyplot as plt

searchPlayer = {}

response = requests.get(f"https://api.nhle.com/stats/rest/en/skater/summary?isAggregate=false&isGame=false&sort=%5B%7B%22property%22:%22goals%22,%22direction%22:%22DESC%22%7D,%7B%22property%22:%22playerId%22,%22direction%22:%22ASC%22%7D%5D&start=0&limit=50&cayenneExp=gameTypeId=2%20and%20seasonId%3C=20252026%20and%20seasonId%3E=20252026")
data = response.json()

playerStats = data["data"]
df = pd.DataFrame(playerStats)

max_goals_row = df[df["goals"] == df["goals"].max()]
topPoints = df.sort_values("points", ascending= False).head(10)

print("goal average: ", df["goals"].mean())
print(max_goals_row[["skaterFullName", "goals"]])
print(topPoints[["skaterFullName", "points"]])

plt.scatter(df["goals"], df["assists"])
plt.xlabel("Goals")
plt.ylabel("Assists")
plt.title("Goals vs Assists")
plt.show()