scores = []

for i in range(10):
    score = int(input("Enter score {}: ".format(i + 1)))
    scores.append(score)

while scores != sorted(scores):
    for i in range(9):
        if scores[i] > scores[i + 1]:

            scores[i], scores[i+1] = scores[i+1], scores[i]

print("Sorted scores:", scores)