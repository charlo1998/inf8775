import random

for i in range(10):
    capacite = 10000
    densite = 100
    count =0
    for n in range(1000,11000,1000):
        count+=1
        with open(f"./exemplaires/Gen-{n}-{densite}-{count}.txt", 'w') as out:
            out.write(f"{n}\n")
            for id in range(n):
                qtty = random.randint(0,densite)
                revenu = random.randint(0,densite)
                out.write(f"{id} {qtty} {revenu}\n")
            out.write(f"{capacite}\n")
