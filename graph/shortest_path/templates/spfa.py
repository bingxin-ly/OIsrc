from sys import stdin, stdout
from queue import Queue
from collections import defaultdict


def SPFA(s):
    dist = [(1 << 31) - 1] * (n + 1)
    dist[s] = 0

    q = Queue()
    q.put(s)

    st = [False] * (n + 1)
    st[s] = True
    while not q.empty():
        t = q.get()
        st[t] = False
        for j, w in graph[t]:
            if (dist[j] > dist[t] + w):
                dist[j] = dist[t] + w
                if not st[j]:
                    q.put(j)
                    st[j] = True
    return dist


if __name__ == '__main__':
    n, m, s = map(int, stdin.readline().split())
    graph = defaultdict(list)
    for _ in range(m):
        a, b, c = map(int, stdin.readline().split())
        graph[a].append((b, c))

    stdout.write(' '.join(map(str, SPFA(s)[1:n + 1])))
