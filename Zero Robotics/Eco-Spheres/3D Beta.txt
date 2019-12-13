float debris[41][4];
float pos[3];
float mystate[12];
float otherState[12];
float distance[6];
float side[6];
float box[4];
int step;
int phase;
int counter;
int health;

void init(){
    game.getDebris(debris);
    step = 0;
    counter = 0;
}

void loop(){
    api.getMyZRState(mystate);
    api.getOtherZRState(otherState);
    phase = game.getGamePhase();
    health = game.getThrusterHealth();
    counter++;
    
    distance[0] = sqrt(mathSquare(debris[33][0] - debris[32][0]) + mathSquare(debris[33][1] - debris[32][1]) + mathSquare(debris[33][2] - debris[32][2]));
    distance[1] = sqrt(mathSquare(debris[34][0] - debris[33][0]) + mathSquare(debris[34][1] - debris[33][1]) + mathSquare(debris[34][2] - debris[33][2]));
    distance[2] = sqrt(mathSquare(debris[36][0] - debris[35][0]) + mathSquare(debris[36][1] - debris[35][1]) + mathSquare(debris[36][2] - debris[35][2]));
    distance[3] = sqrt(mathSquare(debris[37][0] - debris[36][0]) + mathSquare(debris[37][1] - debris[36][1]) + mathSquare(debris[37][2] - debris[36][2]));
    distance[4] = sqrt(mathSquare(debris[39][0] - debris[38][0]) + mathSquare(debris[39][1] - debris[38][1]) + mathSquare(debris[39][2] - debris[38][2]));
    distance[5] = sqrt(mathSquare(debris[40][0] - debris[39][0]) + mathSquare(debris[40][1] - debris[39][1]) + mathSquare(debris[40][2] - debris[39][2]));
    
    side[0]  = sqrt(mathSquare(debris[35][0] - debris[32][0]) + mathSquare(debris[35][1] - debris[32][1]) + mathSquare(debris[35][2] - debris[32][2]));
    side[1] = sqrt(mathSquare(debris[38][0] - debris[35][0]) + mathSquare(debris[38][1] - debris[35][1]) + mathSquare(debris[38][2] - debris[35][2]));
    side[2] = sqrt(mathSquare(debris[36][0] - debris[33][0]) + mathSquare(debris[36][1] - debris[33][1]) + mathSquare(debris[36][2] - debris[33][2]));
    side[3] = sqrt(mathSquare(debris[39][0] - debris[36][0]) + mathSquare(debris[39][1] - debris[36][1]) + mathSquare(debris[39][2] - debris[36][2]));
    side[4] = sqrt(mathSquare(debris[37][0] - debris[34][0]) + mathSquare(debris[37][1] - debris[34][1]) + mathSquare(debris[37][2] - debris[34][2]));
    side[5] = sqrt(mathSquare(debris[40][0] - debris[37][0]) + mathSquare(debris[40][1] - debris[37][1]) + mathSquare(debris[40][2] - debris[37][2]));


    box[0]  = distance[0]  + distance[2] + side[0] + side[2];
    box[1] = distance[1] + distance[3] + side[2] + side[4];
    box[2] = distance[2] + distance[4] + side[1] + side[3];
    box[3] = distance[3] + distance[5] + side[3] + side[5];
    
    navigate();
    Rendezvous();
    hook();
    //DEBUG(("Step %d",step));
}
void navigate(){
    float large = box[0];
    int i;
    
    if(step == 0){
        for(i = 1; i < 4; i++){
            if(box[i] > large){
                large = box[i];
            }
        }
        if(large == box[0]){
            pos[0] = (debris[33][0] + debris[32][0] + debris[36][0] + debris[35][0])/4;
            pos[1] = -0.2;
            pos[2] = (debris[33][2] + debris[32][2] + debris[36][2] + debris[35][2])/4; 
    
            move(pos);
            if(mystate[1] < 0){
                step++;
            }
        }
        else if(large == box[1]){
                pos[0] = (debris[33][0] + debris[34][0] + debris[36][0] + debris[37][0])/4;
                pos[1] = -0.2;
                pos[2] = (debris[33][2] + debris[34][2] + debris[36][2] + debris[37][2])/4; 
            move(pos);
            if(mystate[1] < 0){
                step++;
            }   
        }
        else if(large == box[2]){
                pos[0] = (debris[35][0] + debris[36][0] + debris[38][0] + debris[39][0])/4;
                pos[1] = -0.2;
                pos[2] = (debris[35][2] + debris[36][2] + debris[38][2] + debris[39][2])/4; 
            move(pos);
            if(mystate[1] < 0){
                step++;
            }
        }
        else{
                pos[0] = (debris[37][0] + debris[39][0] + debris[36][0] + debris[40][0])/4;
                pos[1] = -0.2;
                pos[2] = (debris[37][2] + debris[39][2] + debris[36][2] + debris[40][2])/4;
            move(pos);
            if(mystate[1] < 0){
                step++;
            }
        }
}
}
void Rendezvous(){
    float vectorBetween[3];
    float att[3];
    
    if(step == 1){
        if(health <= 25){
        pos[0] = 0;
        pos[1] = otherState[1] + 0.26;
        pos[2] = 0.16;
        
         api.setPositionTarget(pos);    
        }
       else if(counter > 76 && phase != 3){
        pos[0] = 0;
        pos[1] = otherState[1] + 0.26;
        pos[2] = otherState[2] + 0.07;
        
         move1(pos); 
        }
        else{
        pos[0] = 0.16;
        pos[1] = otherState[1] + 0.26;
        pos[2] = otherState[2] + 0.07;
        
         move1(pos); }
        
        att[0] = otherState[6];
        att[1] = -otherState[7];
        att[2] = otherState[8];
    
        mathVecSubtract(vectorBetween,att,mystate,3);
        mathVecNormalize(vectorBetween,3);
        api.setAttitudeTarget(vectorBetween);
        
        game.completeRendezvous();
        if(phase == 3){
            step++;
        }
    }
}
void hook(){
    float distance;
    float vectorBetween[3];
    float att[3];
    float rotate90[3];
    bool col = game.getHookCollision();
        if(step == 2){
            
        pos[0] = otherState[0];
        pos[1] = (otherState[1] + 0.3019) - 0.00385;
        pos[2] = otherState[2] ;
        
        move1(pos);
        
        mathVecSubtract(vectorBetween,pos,mystate,3);
        distance = mathVecMagnitude(vectorBetween,3);
        
        DEBUG(("distance %f",distance));
        
        att[0] = otherState[6];
        att[1] = -otherState[7];
        att[2] = otherState[8];
    
        api.setAttitudeTarget(att);
    if(mystate[8] - otherState[8] != 0.05){
        rotate90[0] = 0.005;
        rotate90[1] = 0;
        rotate90[2] = 0;
        api.setAttRateTarget(rotate90);
    }
}}
//hook is messing up Rendezvous
void move1(float target[3]){
    float distance;
    float vectorBetween[3];
    float zero[3];
    float percent[3];
    float ratio = 50;
    
    mathVecSubtract(vectorBetween,target,mystate,3);
    distance = mathVecMagnitude(vectorBetween,3);
    
    percent[0] = fabs((distance/target[0]) * 100);
    
    zero[0] = 0;
    zero[1] = 0;
    zero[2] = 0;
    
    if(percent[0] > 85){
        api.setPositionTarget(target);
    }
    else if(percent[0] >= ratio){
        api.setVelocityTarget(vectorBetween);
    }
    else if(percent[0] <= ratio &&  percent[0] > 45){
        api.setVelocityTarget(zero);
    }
    else{
            api.setPositionTarget(target);
        }
} // Short distance movement 
void move(float target[3]){
    
    api.setPositionTarget(target);
    /*float distance;
    float vectorBetween[3];
    float AvgVelocity;
    
    AvgVelocity = fabs((mystate[3] + mystate[4])/2);

    mathVecSubtract(vectorBetween,target,mystate,3);
    distance = mathVecMagnitude(vectorBetween,3);
        
    if(AvgVelocity < 0.030 && distance > 0.40){
        api.setVelocityTarget(vectorBetween);
    }    
    else{
            api.setPositionTarget(target);
        }*/
}

/* 0 is the 1st of small layer(start from left side)
   16 is the 1st of medium layer(start from left side)
   32 is the 1st of large layer(start from left side)*/

   
