float pos[3];
float state[12];
void init(){
pos[0]=0.50;
pos[1]=0.50;
pos[2]=0.50;


}

void loop(){
	api.getMyZRState(state);
	move(pos);//setPosition overshoots by 0.02
	DEBUG(("X %f",state[0]));
}
void move(float target[3]){
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
        api.setPositionTarget(target);
    }
}