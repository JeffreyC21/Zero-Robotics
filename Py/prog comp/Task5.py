rows =  ["@","#","#"]
rows1 = ["#","#","#"]
counter = 0
for i in range(0,5):
    if(i==0):
        print(rows)
    else: 
        print(rows1)
def player_A():
    rows.pop(2)
    print(rows1)
    
def player_B():
    rows1.pop(0)
    print(rows1)
    
if (counter%2 == 0):
    player_A()
    counter += 1
elif(counter%2 != 0):
    #Player_B()
    counter += 1
