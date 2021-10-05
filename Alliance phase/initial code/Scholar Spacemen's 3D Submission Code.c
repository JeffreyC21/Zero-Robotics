//Declare any variables shared between functions here
//

int time, targetNum, timeA, timeB, timeC;
int state; // current state of program e.g. navigation, rendezvous
float distance;
float otherS[3], otherState[12], currentState[12], currentPos[3], hoverPos[3], attitude[3], vectorBetween[3], travelTo[3];
float debris[41][4], torP[3], stop[3];
float goal[3], newPos[3], start[3];
float targetC[3];
float currenty, distanceA, distanceB, minViable;
float edge;
float tugdest[3];
float otherES[12], otherE[3];
float initSet[3], stopX[3];
int iniTime, a;
float orangeGapDists[8];
float gapDists[3][5];
float viableOrangeGap[8];
float closestOrangeGap[1];

// Calculates distances given x,y,z coordinates of both points
float distanceBetween(float x1, float y1, float z1, float x2, float y2, float z2) {
    return (sqrt(mathSquare(x1-x2) + mathSquare(y1-y2) + mathSquare(z1-z2)));
}


// Finds the midpoint given x,y,z coordinates of both points
float * midPointBetween(float x1, float y1, float z1, float x2, float y2, float z2) {
    static float midPoint[3];
    
    midPoint[0] = (x1 + x2)/2;
    midPoint[1] = (y1 + y2)/2;
    midPoint[2] = (z1 + z2)/2;
    return midPoint;
}

void init(){
	//This function is called once when your code is first loaded
	game.getDebris(debris); // Gets positions of debris
	state = 0; // navigation
    time = 0;
    targetNum = 0;
    timeA = 0;
    timeB = 0;
    timeC = 0;
    iniTime = 0;
    distanceA = edge - debris[3][1];
    distanceB = debris[3][1] - debris[2][1];
    initSet[0] = 0.7;
    initSet[1] = 0.75;
    initSet[2] = 0;
    start[1] = 0.6;
    edge = 0.8;
    attitude[0] = -1;
    attitude[1] = -0.5;
    attitude[2] = 0;
    travelTo[0] = 0.19; 
    travelTo[1] = -0.3;
    travelTo[2] = 0.0;
    torP[0] = 0;
    torP[1] = 90*PI/180;
    torP[2] = 0;
    stopX[0] = 0;
    stopX[1] = 100;
    stopX[2] = 0;
    targetC[0] = 0;
    targetC[1] = -0.2;
    targetC[2] = 0;
    minViable = 0.22;
    //Code to put gaps into list (in progress):
	
	//Code to process all orange gaps (between outer debris and centre)
	//Debris is from left to right, top to bottom, obviously skipping 36 which is the centre orange debris
	for (int k = 0; k < 2; k++){ //For each row
	    gapDists[k][0] = 0.11+(0.64 + debris[0 + 4*k][0])- debris[3+4*k][3];
	    for (int i = 1; i<4; i++){ //For each debris within that row //  Hypothesis: the distances are the same for both
	        gapDists[k][i] = distanceBetween(debris[i-1 + 4*k][0], debris[i-1 + 4*k][1], debris[i-1 + 4*k][2], debris[i + 4*k][0], debris[i + 4*k][1], debris[i + 4*k][2]) - 2*debris[i+4*k][3]; //Get the distance between that gap and the next one
	    }
	    gapDists[k][4] = (0.64 - debris[3 + 4*k][0]) + 0.11 - debris[3+4*k][3];
	}
    gapDists[2][0] = 0.11 + (0.64 + debris[8][0]) - debris[8][3];
	gapDists[2][1] = distanceBetween(debris[8][0], debris[8][1], debris[8][2], debris[9][0], debris[9][1], debris[9][2]) - 2*debris[8][3];
	gapDists[2][2] = distanceBetween(debris[9][0], debris[9][1], debris[9][2], debris[10][0], debris[10][1], debris[10][2]) - 2*debris[8][3];
	gapDists[2][3] = 0.11 + (0.64 - debris[10][0]) - debris[8][3];
	
	//Code to process all orange gaps (between outer debris and centre)
	//Debris is from left to right, top to bottom, obviously skipping 36 which is the centre orange debris
/*goal	for (int i = 32; i<36; i++){
	    orangeGapDists[i-32] = distanceBetween(debris[36][0], debris[36][1], debris[36][2], debris[i][0], debris[i][1], debris[i][2]);
	}
	for (int i = 37; i<41; i++){
	    orangeGapDists[i-33] = distanceBetween(debris[36][0], debris[36][1], debris[36][2], debris[i][0], debris[i][1], debris[i][2]);
	}

    bool orthoGapFound = false;
    if(orangeGapDists[1]>0.40){
        targetC[0] = (debris[33][0] + debris[36][0])/2;
        targetC[1] = (debris[33][1] + debris[36][1])/2;
        targetC[2] = (debris[33][2] + debris[36][2])/2;
        orthoGapFound = true;
    }
    if(orangeGapDists[3]>orangeGapDists[1] && orangeGapDists[3]>0.40){
        targetC[0] = (debris[35][0] + debris[36][0])/2;
        targetC[1] = (debris[35][1] + debris[36][1])/2;
        targetC[2] = (debris[35][2] + debris[36][2])/2;
        orthoGapFound = true;
    }
    if(orangeGapDists[4]>orangeGapDists[1] && orangeGapDists[4]>orangeGapDists[3] && orangeGapDists[4]>0.40){
        targetC[0] = (debris[37][0] + debris[36][0])/2;
        targetC[1] = (debris[37][1] + debris[36][1])/2;
        targetC[2] = (debris[37][2] + debris[36][2])/2;
        orthoGapFound = true;
    }
    if(orangeGapDists[6]>orangeGapDists[1] && orangeGapDists[6]>orangeGapDists[3] && orangeGapDists[6]>orangeGapDists[4] && orangeGapDists[6]>0.40){
        targetC[0] = (debris[39][0] + debris[36][0])/2;
        targetC[1] = (debris[39][1] + debris[36][1])/2;
        targetC[2] = (debris[39][2] + debris[36][2])/2;
        orthoGapFound = true;
    }
    
    if(orthoGapFound == false){
    	bool biggestGapFound = false;
    	
    	for(int i = 1;i < 8; ++i)
        {
           // Change < to > if you want to find the smallest element
           if(orangeGapDists[0] < orangeGapDists[i]){
               orangeGapDists[0] = orangeGapDists[i];
            } //gapDists[0][0] is now largest gap
        }
        for(int i = 1; i<4; ++i){ //Cycle through to see which element matches orangeGapDists[0][0]
            if(orangeGapDists[i] == orangeGapDists[0]){
                targetC[0] = (debris[i + 32][0] + debris[36][0])/2;
                targetC[1] = (debris[i + 32][1] + debris[36][1])/2;
                targetC[2] = (debris[i + 32][2] + debris[36][2])/2;
                //targetC = midPointBetween(debris[i+32][0], debris[i+32][1], debris[i+32][2], debris[36][0], debris[36][1], debris[36][2]);
                biggestGapFound = true;
                break;
            }//If it matches go to the midpoint
        }
        
        for(int i = 4; i<8; ++i){ //Cycle through to see which element matches gapDists[0][0]
            if(orangeGapDists[i] == orangeGapDists[0]){
                targetC[0] = (debris[i + 33][0] + debris[36][0])/2;
                targetC[1] = (debris[i + 33][1] + debris[36][1])/2;
                targetC[2] = (debris[i + 33][2] + debris[36][2])/2;
                //targetC = midPointBetween(debris[i+32][0], debris[i+32][1], debris[i+32][2], debris[36][0], debris[36][1], debris[36][2]);
                biggestGapFound = true;
                break;
            }//If it matches go to the midpoint
        }
    
        if (biggestGapFound == false){ //If the bool flag is still unchanged, i.e. Gap 32-36 is biggest
            targetC[0] = (debris[32][0] + debris[36][0])/2;
            targetC[1] = (debris[32][1] + debris[36][1])/2;
            targetC[2] = (debris[32][2] + debris[36][2])/2;
            biggestGapFound = true;
        }
    }
    
    
    DEBUG(("\n OrangeGapDists: %f, %f, %f, %f, %f, %f, %f, %f,", orangeGapDists[0], orangeGapDists[1], orangeGapDists[2], orangeGapDists[3], orangeGapDists[4], orangeGapDists[5], orangeGapDists[6], orangeGapDists[7]));
    DEBUG(("\n Orange row biggest gap: %f, Target: %f, %f, %f", orangeGapDists[0], targetC[0], targetC[1], targetC[2]));
	
	

*/
}
void loop(){
	//This function is called once per second.  Use it to control the satellite.
	game.getOtherEulerState(otherES); //this and ext 3 lines are for hooking
	otherE[0] = otherES[6] + (PI);
	otherE[1] = otherES[7] + (PI);
	otherE[2] = otherES[8];
	api.getMyZRState(currentState);
	api.getOtherZRState(otherState);
	currenty = currentState[1];
	iniTime++;
	for (int b=0; b < 3; b ++) {
	currentPos[b] = currentState[b];
	otherS[b] = otherState[b];
	}
	// if state == 0, navigate
	if (state == 0) {
	    mathVecSubtract(goal, targetC, currentPos, 3);
	    if (currentPos[1] > 0.33) {
            api.setVelocityTarget(goal);
	    }
	    /*else if (currentPos[1] > 0.2) {
            api.setPositionTarget(targetC);
	    }*/
	    else {
	        api.setPositionTarget(stopX);    
	    }
	    if (currenty < 0) {
	        state = 1; // next phase of mission
	        DEBUG(("\nNEXT STAGE"));
    	}
	}
	else if (state == 1) {
	    // rendezvous
	    stop[0] = 0;
	    stop[1] = 0;
	    stop[2] = 0;
	    /*mathVecSubtract(vectorBetween, otherS, currentState, 3);
	    mathVecNormalize(vectorBetween, 3);
	    api.setAttitudeTarget(vectorBetween);*/
	    if ((game.getThrusterHealth()) >= 40) {
	        api.setPositionTarget(travelTo);
	        DEBUG(("\n40 and above"));
	    }
	    else if (((game.getThrusterHealth()) < 40) && ((game.getThrusterHealth()) > 15)) {
	        travelTo[0] = 0.18;
	        api.setPositionTarget(travelTo);
	        DEBUG(("\nAbove 15 - Below 40"));
	    }
	    else {
	        travelTo[0] = 0;
	        travelTo[2] = 0.16;
	         api.setPositionTarget(travelTo);
	         DEBUG(("\n 15 or below"));
	    }
	    if (game.checkRendezvous()) {
	        DEBUG(("\nWE HAVE FINALLY MADE IT WORKED!!!!!!!!!!!!!!!!!1!!!!!!!!!"));
	        game.completeRendezvous();
	        state = 2;
	    }
	}
	else if (state == 2) { // for hooking
	    hoverPos[0] = otherS[0] + 0.048;
	    hoverPos[1] = otherS[1] + 0.401;
	    hoverPos[2] = otherS[2] + 0.01;
	    start[0] = currentPos[0];
	    start[2] = currentPos[2];
	    if (time > 85) {
	        hoverPos[1] = otherS[1] + 0.33;    
	    }
	    if (time > 102) {
	        if (time % 2 == 0 or time > 130) {
	            otherE[0] = otherE[0];
	            otherE[1] = otherES[7] + (PI * 181/180);
	            otherE[2] = otherES[8] + (PI * 8/180);
	        }
	    }
	    if (time > 110) {
	        hoverPos[1] = otherS[1] + 0.336;
	    }
	    api.setPositionTarget(hoverPos);
	    game.setEulerTarget(otherE);
	    if (game.getHookCollision()) {
	        DEBUG(("\nCOLLISION"));
	    }
	    if (game.getHooked()) {
	        DEBUG(("\nIS HOOKER"));
	        state = 3; // moving to tug code
	    }
	    else {
	        DEBUG(("\nNO HOOKER"));
	    }
	}
	else if (state == 3){ //Tug code
	    tugdest[0] = 0;
	    tugdest[1] = 1;
	    tugdest[2] = 0.002;
	    api.setPositionTarget(tugdest);
	    if (game.getHookCollision()) {
	        DEBUG(("\nCOLLISION"));
	    }
	    if (game.getHooked()) {
	        DEBUG(("\nIS HOOKER"));
	    }
	    else {
	        DEBUG(("\nNO HOOKER"));
	    }
	}
	
	time++;
	// api.setPositionTarget(otherS);
}