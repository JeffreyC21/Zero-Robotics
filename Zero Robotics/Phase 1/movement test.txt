float start[3];
int step;
float item1[3];
float item2[3];
float zero[3];
void init(){
	
	item1[0]=-0.5;
	item1[1]=0.354;
	item1[2]=0.5;

	item2[0]=0;
	item2[1]=1;
	item2[2]=0;
	
	step = 0;
	
	
}

void loop(){//void loop starts
   game.dropSPS();
 if(step==0){
    move(item1);// setPosition takes 26 sec 
      api.setAttitudeTarget(item2);
    game.dockItem();
    
} 
    
}//end of void loop
void move(float item[3]){
float vectorBetween[3];
float state[12];
float distance;
float percent;
float percent1;
float percent2;
float ratio = 87;
float ratio2=20;
float zero[3];

    zero[0]=0;
    zero[1]=0;
    zero[2]=0;
    
    api.getMyZRState(state);
    mathVecSubtract(vectorBetween,target,state,3);
    distance=mathVecMagnitude(vectorBetween,3);
    percent  = fabsf((distance/target[0]) * 100);
    percent1 = fabsf((distance/target[1]) * 100);
    percent2 = fabsf((distance/target[2]) * 100);
    
    if(percent>ratio&&percent1>ratio&&percent2>ratio){
        api.setVelocityTarget(vectorBetween);
    }
        
    else if(percent>=ratio2&&percent1>=ratio2&&percent2>=ratio2){
        api.setVelocityTarget(zero);
    }
    else{
        api.setPositionTarget(item);
    }
}
