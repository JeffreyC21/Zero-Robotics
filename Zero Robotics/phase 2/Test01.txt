float dbri [11][4];

float pos[3];

float att[3];

void init(){

    game.getDebris(dbri);

    DEBUG(("Pos of first debri X value %f",dbri[1][0]));

    
    
    pos[0] = 0;

    pos[1] = -0.5;

    pos[2] = 0;

    
    
    att[0] = 0;

    att[1] = 180;

    att[2] = 0;

    
     
    api.setAttitudeTarget(att);

}

void loop(){

    api.setPositionTarget(pos);

    game.completeRendezvous();

}