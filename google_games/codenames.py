#!/usr/bin/env python2.7

def step(words):
    out = []
    for word in words:
        if word != 'communist': #to be honest, I don't remember why it skips this one
            out.extend(asso[word])
    return out

def check(word):
    # these words are a closed loop and none of them are the answer.
    banned = ['north','east','south','west','northern','eastern','southern','western','northeast','northwest','southeast','southwest']
    if word in banned:
        return False
    print "testing " + word
    lastwords = []
    words = step([word])
    found = set()
    # steps through graph until find a red word
    while set(words).isdisjoint(red):
	# if no change from last time, return false
        if set(lastwords) == words:
            return False
	# mark found words
        for w in blue:
            if w in words:
                found.add(w)
	# if found all blue words, it's the clue!
        if len(found) == 9:
            return True
	#otherwise, step further through the graph
        else:
            lastwords = words
            words = step(words)
    return False



blue = ['airplane','basket','plastic','spirit','meltdown','festival','quarter','pink','earth']
red = ['battery','vacation','water','officer','judge','fate','cross','radio']

with open('associations.txt') as f:
    lines = f.read().split()

asso = {}

for line in lines:
    word = line.split(':')[0]
    words = line.split(':')[1]
    asso[word] = words.split(',')

for word in asso.keys():
    if(check(word)):
        print "The clue is: " + word
        break
