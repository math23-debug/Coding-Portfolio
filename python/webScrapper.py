import requests

from bs4 import BeautifulSoup

all_quotes = []
page_num = 1

while True:
    url = (f"https://quotes.toscrape.com/page/{page_num}")
    response = requests.get(url)
    soup = BeautifulSoup(response.text, "html.parser")

    quotes = soup.find_all("div", class_="quote")

    if not quotes:
        break

    for quote in quotes:
        text = quote.find("span", class_="text").text
        author = quote.find("small", class_="author").text
        all_quotes.append((text, author))

    page_num += 1

print(f"There are {len(all_quotes)} quotes in Quotes To Scrape")
