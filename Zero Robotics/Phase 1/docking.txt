float start[3];
float sps2[3];
float sps3[3];
float mystate[12];
float target[3];
int step;
float item1[3];
float item2[3];
float zinfo[4];
float state[12];
float vectorBetween[3];
float distance;
float myPos[3];
float length;
float itemstate[12];
void init(){
	api.getMyZRState(mystate);
	start[0] = mystate[0];
	start[1] = mystate[1];
	start[2] = mystate[2];
	
	item1[0]=-0.5;
	item1[1]=0.354;
	item1[2]=0;
	
	sps2[0] = -0.70;
	sps2[1] = 0.70;
	sps2[2] = 0.0;
	
	sps3[0] = 0.70;
	sps3[1] = 0.70;
	sps3[2] = 0.0;
	
	item2[0]=0;
	item2[1]=1;
	item2[2]=0;
	
	step = 0;
	
	
	game.dropSPS();
	move(sps3);
}

void loop(){//void loop starts
   game.getItemZRState(itemstate,4);
   game.getZone(zinfo);
    DropSPS();
 if(step==2){
    move(item1);
      api.setAttitudeTarget(item2);
    game.dockItem();
} if(game.hasItemBeenPickedUp(4)==true){step++;} 
 //inside step 2
if(step==3){
    move(zinfo);
 step++;
}
if(step==4){
    if(itemstate[0]>=zinfo[0]&&itemstate[1]>=zinfo[1]||itemstate[0]<=zinfo[0]&&itemstate[1]<=zinfo[1]){
        game.dropItem();
    }
}
    
}//end of void loop
void move(float a[3]){
    api.getMyZRState(state);
    for(int i=0;i<3;i++){
        myPos[i]=state[i];
            }
    mathVecSubtract(vectorBetween,a,myPos,3);
    distance=mathVecMagnitude(vectorBetween,3);
    length=99/100*distance;
    if(distance<length){
        api.setVelocityTarget(vectorBetween);
        
    }
    else{
        api.setPositionTarget(a);
        
    }
}
void DropSPS(){
    api.getMyZRState(mystate);
    	if (step == 0){
	    target[0] = 0.7;
	
	if (mystate[0] < target[0]){
	    move(sps3);
	}
	else{
	    game.dropSPS();
	    step++;
	}  
}
	else if (step == 1){
	    target[0] = -0.7;
	
	if (mystate[0] > target[0]){
	    move(sps2);
	}
	else{
	    game.dropSPS();
	    step++;
	}}
}

