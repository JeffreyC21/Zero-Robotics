float debris[41][4];
float pos[3];
float mystate[12];
float otherState[12];
float otherAngle[12];
float score;
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
    game.getOtherEulerState(otherAngle);
    phase = game.getGamePhase();
    health = game.getThrusterHealth();
    score = game.getScore();
    counter++;
    
    navigate();
    Rendezvous();
    hook();
    Tow();
}
void navigate(){
    float distance[8];
    float side[6];
    float box[10];
    float edgeX[3];
    float edgeNegX[3];
    float edgeZ[3]; 
    float Edge[9];
    float large = box[0];
    float vectorBetween[3];
    int a = 0;
    
    edgeX[0] = 0.64;
    edgeX[1] = 0;
    edgeX[2] = debris[34 + (a * 3)][2];
    
    edgeNegX[0] = -0.64;
    edgeNegX[1] = 0;
    edgeNegX[2] = debris[32 + (a * 3)][2];
    
    edgeZ[0] = debris[38 + (a - 6)][0];
    edgeZ[1] = 0;
    edgeZ[2] = 0.64;
    
    for(int i = 0; i <= 7; i++){
        
        if(i == 2 || i == 5){
            distance[i] = 0;
        }
        else{
        mathVecSubtract(vectorBetween,debris[33 + i],debris[32 + i],3); 
        distance[i] = mathVecMagnitude(vectorBetween,3);
        }
    }
    for(int i = 0; i <= 5; i++){
        
        mathVecSubtract(vectorBetween,debris[35 + i],debris[32 + i],3);
        side[i] = mathVecMagnitude(vectorBetween,3); 
    }
    for( ; a < 9; a++){
        
        if(a < 3){
            mathVecSubtract(vectorBetween,debris[32 + (a * 3)],edgeNegX,3);
            Edge[a] = mathVecMagnitude(vectorBetween,3);
            }
        if(a >= 3 && a < 6){
            mathVecSubtract(vectorBetween,debris[34 + ((a - 3) * 3)],edgeX,3);
            Edge[a] = mathVecMagnitude(vectorBetween,3); 
        }
        
        if(a >= 6){
            mathVecSubtract(vectorBetween,debris[38 + (a - 6)],edgeZ,3);
            Edge[a] = mathVecMagnitude(vectorBetween,3);
        }
    }

    box[0] = distance[0] + distance[3] + side[0] + side[1];
    box[1] = distance[1] + distance[4] + side[1] + side[2];
    box[2] = distance[3] + distance[6] + side[3] + side[4];
    box[3] = distance[4] + distance[7] + side[4] + side[5];
    box[4] = (side[0]) * 4;
    box[5] = (side[1]) * 4;
    box[6] = (side[2]) * 4;
    box[7] = (side[3]) * 4;
    box[8] = (side[4]) * 4;
    box[9] = (side[5]) * 4;
    
    for(int i = 1; i < 10; i++){
        
        if(box[1] >= 1.43 && box[1] > box[0] && box[1] > box[3] && box[1] > box[2]){
            large = box[1];
            i += 14;
        }
        else if(box[3] >= 1.43 && box[3] > box[1] && box[3] > box[2] && box[3] > box[0]){
            large = box[3];
            i += 14;
        }
        else if(box[0] >= 1.43 && box[0] > box[1] && box[0] > box[2] && box[0] > box[3]){
            large = box[0];
            i += 14;
        }
        else if(box[2] >= 1.43 && box[2] > box[0] && box[2] > box[1] && box[2] > box[3]){
            large = box[2];
            i += 14;
        }
        else if(box[i] > large){
            large = box[i];
        }
    }
    if(step == 0 && counter <= 6){
        
        if(large == box[0]){
            pos[0] = (debris[33][0]  + debris[32][0]  + debris[36][0] + debris[35][0])/4;
            pos[1] = 0.75;
            pos[2] = (debris[33][2] + debris[32][2] + debris[36][2] + debris[35][2])/4; 
    
            move(pos);
        }
        else if(large == box[1]){
                pos[0] = (debris[33][0]  + debris[34][0] + debris[36][0]  + debris[37][0])/4;
                pos[1] = 0.75;
                pos[2] = (debris[33][2] + debris[34][2] + debris[36][2] + debris[37][2])/4; 
            move(pos);
        }
        else if(large == box[2]){
                pos[0] = (debris[35][0]  + debris[36][0]  + debris[38][0]  + debris[39][0])/4;
                pos[1] = 0.75;
                pos[2] = (debris[35][2] + debris[36][2] + debris[38][2] + debris[39][2])/4; 
            move(pos);
        }
        else if(large == box[3]){
                pos[0] = (debris[37][0] + debris[39][0] + debris[36][0] + debris[40][0])/4;
                pos[1] = 0.75;
                pos[2] = (debris[37][2] + debris[39][2] + debris[36][2] + debris[40][2])/4;
            move(pos);
        }
        else if(large == box[4]){
            pos[0] = ((debris[32][0] - 0.64) + (debris[35][0] - 0.64))/4;
            pos[1] = 0.75;
            pos[2] = (debris[32][2] +debris[35][2])/2;
            move(pos);
        }
        else if(large == box[5]){
            pos[0] = ((debris[35][0] - 0.64) + (debris[38][0] - 0.64))/4;
            pos[1] = 0.75;
            pos[2] = (debris[35][2] + debris[38][2])/2;
            move(pos);
        }
        else if(large == box[6]){
            pos[0] = (debris[34][0] + 0.64 + debris[37][0] + 0.64)/4;
            pos[1] = 0.75;
            pos[2] = (debris[34][2] + debris[37][2])/2;
            move(pos);
        }
        else if(large == box[7]){
            pos[0] = (debris[37][0] + 0.64 + debris[40][0] + 0.64)/4;
            pos[1] = 0.75;
            pos[2] = (debris[37][2] + debris[40][2])/2;
            move(pos);
        }
        else if(large == box[8]){
            pos[0] = (debris[38][0] + debris[39][0])/2;
            pos[1] = 0.75;
            pos[2] = (debris[38][2] + 0.64 + debris[39][2]  + 0.64)/4; 
            move(pos);
        }
        else{ 
            pos[0] = (debris[39][0] + debris[40][0])/2;
            pos[1] = 0.75;
            pos[2] = (debris[39][2] + 0.64 + debris[40][2] + 0.64)/4;
            move(pos);
        }
}
    if(step == 0 && counter > 6){
        
        if(large == box[0]){
            pos[0] = (debris[33][0] + debris[32][0]   + debris[36][0]  + debris[35][0])/4;
            pos[1] = -0.2; 
            pos[2] = (debris[33][2] + debris[32][2] + debris[36][2] + debris[35][2])/4; 
    
            move1(pos);
            if(mystate[1] < 0){
                step++;
            }
        }
        else if(large == box[1]){
                pos[0] = (debris[33][0] + debris[34][0] + debris[36][0] + debris[37][0])/4;
                pos[1] = -0.2;
                pos[2] = (debris[33][2] + debris[34][2] + debris[36][2] + debris[37][2])/4; 
                move1(pos);
            if(mystate[1] < 0){
                step++;
            }   
        }
        else if(large == box[2]){
                pos[0] = (debris[35][0] + debris[36][0] + debris[38][0] + debris[39][0])/4;
                pos[1] = -0.2;
                pos[2] = (debris[35][2] + debris[36][2] + debris[38][2] + debris[39][2])/4; 
            move1(pos);
            if(mystate[1] < 0){
                step++;
            }
        }
        else if(large == box[3]){
                pos[0] = (debris[37][0] + debris[39][0] + debris[36][0] + debris[40][0])/4;
                pos[1] = -0.2;
                pos[2] = (debris[37][2] + debris[39][2] + debris[36][2] + debris[40][2])/4;
            move1(pos);
            if(mystate[1] < 0){
                step++;
            }
        }
        else if(large == box[4]){
            pos[0] = ((debris[32][0] - 0.64) + (debris[35][0] - 0.64))/4;
            pos[1] = -0.2;
            pos[2] = (debris[32][2] +debris[35][2])/2;
            move1(pos);
            if(mystate[1] < 0){
                step++;
            }
        }
        else if(large == box[5]){
           pos[0] = ((debris[35][0] - 0.64) + (debris[38][0] - 0.64))/4;
            pos[1] = -0.2;
            pos[2] = (debris[35][2] + debris[38][2])/2;
            move1(pos);
                if(mystate[1] < 0){
                step++;
            }
        }
        else if(large == box[6]){
            pos[0] = (debris[34][0] + 0.64 + debris[37][0] + 0.64)/4;
            pos[1] = -0.2;
            pos[2] = (debris[34][2] + debris[37][2])/2;
            move1(pos);
                if(mystate[1] < 0){
                step++;
            }
        }
        else if(large == box[7]){
            pos[0] = (debris[37][0] + 0.64 + debris[40][0] + 0.64)/4;
            pos[1] = -0.2;
            pos[2] = (debris[37][2] + debris[40][2])/2;
            move1(pos);
                if(mystate[1] < 0){
                step++;
            }
        }
        else if(large == box[8]){
            pos[0] = (debris[38][0] + debris[39][0])/2;
            pos[1] = -0.2;
           pos[2] = (debris[38][2] + 0.64 + debris[39][2] + 0.64)/4; 
            move1(pos);
                if(mystate[1] < 0){
                step++;
            }
        }
        else{ 
            pos[0] = (debris[39][0] + debris[40][0])/2;
            pos[1] = -0.2;
            pos[2] = (debris[39][2] + 0.64 + debris[40][2] + 0.64)/4;
            move1(pos);
                if(mystate[1] < 0){
                step++;
            }
        }
}
}
void Rendezvous(){
    float vectorBetween[3];
    float angles[3];
    float att[3];
    
    if(step == 1){
        if(health <= 40){
        pos[0] = 0;
        pos[1] = otherState[1] + 0.26;
        pos[2] = 0.16;
        
         api.setPositionTarget(pos);    
        }
       else if(counter > 76 && phase != 3){
        pos[0] = 0;
        pos[1] = otherState[1] + 0.29;
        pos[2] = otherState[2] - 0.09;
        
         move(pos); 
        }
        else{
        pos[0] = 0.16;
        pos[1] = otherState[1] + 0.29;
        pos[2] = otherState[2] + 0.07;
        
         move(pos); }
         
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
    float angles[3];
    
if(step == 2){
    
    if(health > 75){
    pos[0] = otherState[0];
    pos[1] = otherState[1] + 0.331;
    pos[2] = otherState[2] + 0.030;
    }
    else if(health == 75){
    pos[0] = otherState[0];
    pos[1] = otherState[1] + 0.333;
    pos[2] = otherState[2] + 0.030;
    }
    else if(health == 65){
    pos[0] = otherState[0];
    pos[1] = otherState[1] + 0.325;
    pos[2] = otherState[2] + 0.025;
    }
    else{
    pos[0] = otherState[0];
    pos[1] = otherState[1] + 0.329;
    pos[2] = otherState[2] + 0.025;
    }
    if(health > 25){
    move(pos);
    }
    else{
        api.setPositionTarget(pos);
    }
        angles[0] = otherAngle[6];
        angles[1] = otherAngle[7];
        angles[2] = -otherAngle[8];
        
    game.setEulerTarget(angles);
    
    if(DistanceToPoint(pos) <= 0.02){
        step++;
    }

}
if(step == 3){
    pos[0] = otherState[0];
    pos[1] = otherState[1] + 0.33290;
    pos[2] = otherState[2];
    
    if(health > 25){
    move(pos);
    }
    else{
        api.setPositionTarget(pos);
    }
    
    angles[0] = otherAngle[6];
    angles[1] = otherAngle[7];
    angles[2] = -otherAngle[8];
    
    game.setEulerTarget(angles);

    if(score > 11){
        step++;
}
}
}
void Tow(){
    float angles[3];
    
    if(step == 4){
        
    angles[0] = otherState[6];
    angles[1] = -otherState[7];
    angles[2] = otherState[8];
    
    api.setAttitudeTarget(angles);
        
    pos[0] = otherState[0];
    pos[1] = 0.2;
    pos[2] = mystate[2];
    
     Tug(pos);
    }
}

void move(float target[3]){
    float distance1;
    float vectorBetween1[3];
    float zero[3];
    float percent;
    float ratio = 30;
    
    if (phase == 2 && health <= 15){
        ratio = 10;
    }
    
    mathVecSubtract(vectorBetween1,target,mystate,3);
    distance1 = mathVecMagnitude(vectorBetween1,3);
    
    percent = fabs((distance1/target[0]) * 100);
    
    zero[0] = 0;
    zero[1] = 0;
    zero[2] = 0;
    
    if(percent > 85 && health > 15){
        api.setPositionTarget(target);
    }
    else if(percent >= ratio){
        api.setVelocityTarget(vectorBetween1);
    }
    else if(percent <= ratio &&  percent > 45){
        api.setVelocityTarget(zero);
    }
    else{
            api.setPositionTarget(target);
        }
}

void move1(float target[3]){
api.setPositionTarget(target);
}

void Tug(float target[3]){
    float distance1;
    float vectorBetween1[3];
    
    mathVecSubtract(vectorBetween1,target,mystate,3);
    distance1 = mathVecMagnitude(vectorBetween1,3);

        api.setVelocityTarget(vectorBetween1);
}

float DistanceToPoint(float point[3]){
    float vectorBetween[3];
    float distance;

    mathVecSubtract(vectorBetween,point,mystate,3);
    distance = mathVecMagnitude(vectorBetween,3);
    
    return distance;
}