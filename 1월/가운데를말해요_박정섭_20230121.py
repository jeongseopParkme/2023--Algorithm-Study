import heapq as hq

arr=[]
left, right=[], []

n=int(input())

for _ in range(n):
    arr.append(int(input()))

for i in range(n):
    if i==0:
        hq.heappush(left,-arr[i])
    elif len(left)>len(right):
        if(arr[i]<-left[0]):
            hq.heappush(right,-hq.heappop(left))
            hq.heappush(left,-arr[i])
        else:
            hq.heappush(right,arr[i])
    else:
        if(arr[i]<-left[0]):
            hq.heappush(left,-arr[i])
        else:
            hq.heappush(right,arr[i])
            hq.heappush(left,-hq.heappop(right))
    print(-left[0])