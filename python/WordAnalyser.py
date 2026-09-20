import os
import re
os.system('cls') 
from collections import Counter

with open("WordAnalysing.txt","r") as file:
    speach_content = file.read()

sentences = re.split(r'[.!?]', speach_content)
sentences = [s.strip() for s in sentences if s.strip() != ""]
sentence_lenghts = [len(sentence.split()) for sentence in sentences]

longest_sentence = ""
shortest_sentence = ""
longest_length = 0
shortest_length = 0

for sentence, length in zip(sentences, sentence_lenghts):
    if length > longest_length:
        longest_length = length
        longest_sentence = sentence
    if length < shortest_length or shortest_length == 0:
            shortest_length = length
            shortest_sentence = sentence

speach_content = speach_content.lower()

no_punct_text = speach_content
for punctuation in [".", ",", "?", "!", ":", ";"]:
    no_punct_text = no_punct_text.replace(punctuation, " ")

chars_count = Counter(no_punct_text.replace(" ", ""))

no_punct_list = no_punct_text.split()

stop_words = ["the", "a", "an", "and", "or", "if"]
clean_list = [n for n in no_punct_list if n not in stop_words]

word_count = Counter(clean_list)

filler_words = word_count['um'] + word_count['uh'] + word_count['uhm'] + word_count['like']

top_word = word_count.most_common(3)
top_char = chars_count.most_common(3)

print("TOP WORDS:")
for items, count in top_word:
    print(f"{items} appeared {count} times")
print("TOP CHARACTERS:")
for items, count in top_char:
    print(f"{items}: {count}")
print(f"{filler_words} filler words used")
print(f'"{longest_sentence}." is the longest sentence with {longest_length} words')
print(f'"{shortest_sentence}." is the shortest sentence with {shortest_length} words')