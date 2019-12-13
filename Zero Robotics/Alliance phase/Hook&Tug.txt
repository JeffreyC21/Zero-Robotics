// for scholar spaceman
float otherAttitude[3];
float zero[3];
float mystate[12];
float otherState[12];
float otherAngle[12];
float score;
int step;
int seconds;
bool hooked;


void init(){
    step = 0;
    seconds = 0;
    
}

void loop(){
    seconds++;
   
for(int i = 0; i < 3; i++){
    otherAttitude[i] = otherState[i+6];
}
for(int i = 0; i < 3; i++){
    zero[i] = 0;
}
    
    api.getMyZRState(mystate);
    api.getOtherZRState(otherState);
    game.getOtherEulerState(otherAngle);
    score = game.getScore();
    hooked = game.getHooked();
    
    targetPos();
    hook();
    Tug();
}
float angles[3];
float pos[3];
float vectorBetween[3];

void targetPos(){
    
    if(step == 0){
   // x^2+y^2+z^2 = 1 
        pos[0] = otherAttitude[0]*2*0.17095f + otherState[0];
        pos[1] = otherAttitude[1]*2*0.17095f + otherState[1];
        if(otherState[0] > 0){
        pos[2] = otherAttitude[2]*2*0.17095f + otherState[2] + 0.002;
        }
        else{
        pos[2] = otherAttitude[2]*2*0.17095f + otherState[2] - 0.002;
        }
        if(seconds <= 10){
            mathVecSubtract(vectorBetween,otherState,mystate,3);
            api.setVelocityTarget(vectorBetween);
        }
        else{
        api.setPositionTarget(pos);
        }
        //api.setPositionTarget(pos);
        
        angles[0] = -otherAngle[6] + PI;
        angles[1] = otherAngle[7] + PI;
        angles[2] = otherAngle[8]; 
        game.setEulerTarget(angles);
        
        if(fabs(otherState[1] - mystate[1]) <= 0.325 || game.getGamePhase() == 4){
            step++;
        }
    }
}

void hook(){

    if(step == 1){
for(int i = 0;i < 3; i++){
    pos[i] = otherAttitude[i]*2*0.17099f + otherState[i];
}

    PositionTarget(pos);
    
    angles[0] = -otherAngle[6] + PI;
    angles[1] = otherAngle[7] + PI;
    angles[2] = otherAngle[8];
    game.setEulerTarget(angles);
    
    if(score > 4){
        step++;
    }

}
}

void Tug(){
    
    if(step == 2){

if(otherState[2] > 0 && otherState[1] < 0){
    pos[0] = otherState[0];
    pos[1] = 0.9;
    pos[2] = otherState[2];// - 1;
}
else {
    pos[0] = otherState[0];
    pos[1] = 0.9; 
    pos[2] = otherState[2];// + 1;
}
  api.setPositionTarget(pos);
  
if(mystate[1] > 0){
    pos[0] = otherState[0] - 1;
    pos[1] = 0.7;
    if(otherState[2] > 0){
    pos[2] = mystate[2] - 1;
    }
    else if(otherState[2] < 0){
        pos[2] = mystate[2] + 1;
    }
    angles[0] = -otherAngle[6];
    angles[1] = otherAngle[7];
    angles[2] = otherAngle[8];
     game.setEulerTarget(angles);
      api.setForces(pos);
}
}
}
void PositionTarget(float target[3])
{
    float mystate[12], mypos[3], myvel[3];
    float acc[3], forces[3], AB[3], slope[3], vb[3];
    float lenAB;
     api.getMyZRState(mystate);
    
    for(int i = 0; i < 3; i++)
        mypos[i] = mystate[i];
    for(int i = 0; i < 3; i++)
        myvel[i] = mystate[i+3];
    
    mathVecSubtract(AB, target, mypos, 3);    
    lenAB = mathVecMagnitude(AB, 3);
    
    for(int i = 0; i < 3; i++)
        acc[i] = (-AB[i]*0.0085f)/lenAB;
    for(int i = 0; i < 3; i++)
        slope[i] = (sqrtf(2)*sqrtf(0.0085f)*AB[i])/sqrtf(lenAB);
    for(int i = 0; i < 3; i++)
        vb[i] = slope[i]+acc[i]-myvel[i];
    
    
    for(int i = 0; i < 3; i++)
        forces[i] = vb[i] * 5 * (100.0f/(float)game.getThrusterHealth());
    api.setForces(forces);
}
