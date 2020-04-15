if __name__ == '__main__':
    [boxes, nailsPerTable, tables] = [int(a) for a in input().split(' ')]
    nails = sorted([int(a) for a in input().split(' ')], reverse=True)
    neededNails = nailsPerTable * tables
    cumSum = 0
    for i in range(boxes):
        cumSum += nails[i]
        if (cumSum >= neededNails):
            print(i+1)
            break