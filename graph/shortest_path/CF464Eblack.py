import heapq

P = int(1e9 + 7)
graph = [[] for _ in range(50010)]
path = {}


def dijkstra(s, n):
    dist = [float('inf')] * (n + 1)
    vis = [False] * (n + 1)

    dist[s] = 0
    heap = [(0, s)]
    while heap:
        dis, ver = heapq.heappop(heap)
        if vis[ver]:
            continue
        if dist[ver] < dis:
            continue
        for j, w in graph[ver]:
            if dist[j] > dis + w:
                dist[j] = dis + w
                heapq.heappush(heap, (dist[j], j))
                path[j] = ver
    return dist


if __name__ == '__main__':
    n, m = map(int, input().split())
    for i in range(m):
        u, v, w = map(int, input().split())
        w = pow(2, w)
        graph[u].append((v, w))
        graph[v].append((u, w))
    s, t = map(int, input().split())

    dist = dijkstra(s, n)

    if dist[t] == float('inf'):
        print(-1)
        exit(0)
    else:
        print(dist[t] % P)
        output = []
        v = t
        while v != s:
            output.append(v)
            v = path[v]
        output.append(s)
        output.reverse()
        print(len(output))
        [print(x, end=' ') for x in output]
