if __name__ == '__main__':
    friends = set()
    friendsOfFriends = set()
    n = int(input())
    for _ in range(n):
        [friend, n, *friendsOfN] = [int(num) for num in input().split(' ')]
        friends.add(friend)
        friendsOfFriends.update(friendsOfN)
    print(len(friendsOfFriends.difference(friends)))

