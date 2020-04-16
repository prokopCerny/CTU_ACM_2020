# problem on https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=725
from collections import deque

offsets = [(-1,0), (0, -1), (0, 1), (1, 0)]

def bfs(maze, lenghts, coords, visited):
    visited[coords[0]][coords[1]] = True
    maze[coords[0]][coords[1]] = '#'
    queue = deque()
    queue.append(coords)
    lines = len(maze)

    while queue:
        x, y = queue.popleft()
        for x_off, y_off in offsets:
            neigh_x = x + x_off
            neigh_y = y + y_off
            if 0 <= neigh_x < lines and 0 <= neigh_y < lenghts[neigh_x]:
                if maze[neigh_x][neigh_y] == ' ':
                    maze[neigh_x][neigh_y] = '#'
                    queue.append((neigh_x, neigh_y))



if __name__ == '__main__':
    mazes = int(input())
    for _ in range(mazes):
        maze = []
        lenghts = []
        visited = []
        while True:
            line = input()
            if line[0] == '_':
                sep_line = line
                break
            maze.append([char for char in line])
            cur_len = len(line)
            lenghts.append(cur_len)
            start = line.find('*')
            visited.append([False for _ in range(cur_len)])
            if start >= 0:
                coords = len(lenghts)-1, start
        bfs(maze, lenghts, coords, visited)
        for line in maze:
            print(''.join(line))
        print(sep_line)

