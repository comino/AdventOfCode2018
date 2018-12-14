import fileinput
import re

FABRIC_LEN=1000
lines = [x.strip() for x in fileinput.input()]

def solvePart1():
    # O(n)
    UsageMatrix = [[0 for x in range(1000)] for y in range(1000)]
    doubleUsageCounter = 0
    for line in lines:
        id, x0, y0, dx, dy = map(int,  re.findall(r'\d+', line))
        for x in range( x0, x0+dx):
            for y in range(y0, y0+dy):
                UsageMatrix[x][y] += 1
                if UsageMatrix[x][y] == 2:
                    doubleUsageCounter+=1
    return [doubleUsageCounter, UsageMatrix]

def solvePart2():
    # O(2n)
    UsageMatrix = solvePart1()[1]
    for line in lines:
        id, x0, y0, dx, dy = map(int,  re.findall(r'\d+', line))
        hasOverlap = False
        for x in range( x0, x0+dx):
            for y in range(y0, y0+dy):
                if UsageMatrix[x][y]>1:
                    hasOverlap = True
        if not hasOverlap:
            return id
    return ValueError("Could not find unique patch")

print("Solution Part 1: "+ str(solvePart1()[0]))
print("Solution Part 2: "+ str(solvePart2()))

