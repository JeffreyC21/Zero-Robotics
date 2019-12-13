n=10
star = "+".center(n*2)
leaves = "*".center(2)
trunk = "#".center(n*2)
k = int(n/6)
Base = ("="*int(2*k+1)).center(2)

for i in range (1,n+1):
    if(i == 1):
        print(star)
    elif(i>1):
        print((leaves*i).center(n*2))

if(i == n and n<12):
        print(trunk)
elif(i == n and n>=12):
        print(trunk)
        print(trunk)

if(i == n):
        print(Base.center(n*2))

