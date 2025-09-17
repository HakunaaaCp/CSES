def main():
    n = int(input())
    vis = (n + 1) * [False]
    arr = list(map(int, input().split()))
    for a in arr:
        vis[a] = 1
    mis = -1
    for i in range(1, n + 1):
        if not vis[i]:
            mis = i
            break
    print(mis, end=" ")

if __name__ == "__main__":
    main()
        