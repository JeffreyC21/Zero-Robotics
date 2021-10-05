//Begin page Damage
float Damage(float x)
{
    if(x == 0.03f)
        return 10;
    if(x == 0.045f)
        return 25;
    if(x == 0.09f)
        return 50;
        return 100;
}
//End page Damage
//Begin page absV
float absV(float x)
{
    if(x < 0)
    return x*(-1);
    return x;
}
//End page absV
//Begin page ch_coXY
int ch_coXY(float x1, float y1, float x2, float y2, float x, float y, float r)
{
    float a, b, c;
    a = y1 - y2;
    b = x2 - x1;
    c = (x1 - x2)*y1 + x1*(y2 - y1);
     float dist = (a * x + b * y + c) /  
                     sqrt(a * a + b * b); 
    if(dist < 0) dist = dist*(-1);
    if(r >= dist)
    return 1;
    return 0;
    
}
//End page ch_coXY
//Begin page distanceTo
float distanceTo()
{
    float x0, y0, z0, x, y, z;
    x0 = pos[0]; y0 = pos[1]; z0 = pos[2];
    x = myState[0]; y = myState[1]; z = myState[2];
    float a, b, c;
    a = x - x0; b = y - y0; c = z - z0;
    a = a*a; b = b*b; c = c*c;
    return sqrt(a+b+c);
}
//End page distanceTo
//Begin page main

float debris[41][4], pos[3], myState[12], X, Z, myPos[3], vecBetween[3], mins, attitude[3], otherState[12], a, b, d, myEuler[3], otherEuler[12];
int phase, minimum_res, sp, hoo, pastiu, re;
 float t1 ;
        float radius ;
        float x1 ; float z1;
        float alpha1 ;
        float l1;
        
        float x; 
        float t2 ;
        float v ;
        float alpha2;   
        float z2 ;
        float x2 ;
        float l2 ;
bool passed;
void init()
{re=0;
    sp = 0;
    hoo = 0;
    pastiu = 1;
    phase = 1;
    passed = false;
    X = 0.0f; Z =0.5f;
    minimum_res = 1000;
    mins = 100.0f;
	game.getDebris(debris);
	api.getMyZRState(myState);
    api.getOtherZRState(otherState);
    for(float z = -0.2f; z <= 0.3f; z = z + 0.005f)
        for(float x = -0.3; x <= 0.4f; x = x + 0.005f)
        {
        
                
            if(x != myState[0] && z != myState[2])
            {
                int res = 0;
                for(int i = 0; i < 41; i++)
                {
                    
                    // linia are coordonate {(x, 0.0f, z), (myState[0], myState[1], myState[2])}
                    if(ch_coXY(myState[1], myState[2], 0.001455f, z, debris[i][1], debris[i][2], debris[i][3]+0.125f)==1 && ch_coXY(myState[0], myState[1], x, 0.001455f, debris[i][0], debris[i][1], debris[i][3]+0.13f)==1)
                    {
                        res = res + Damage(debris[i][3]);
                    }
                }
                if(res < minimum_res)
                   minimum_res = res, X = x, Z = z,
                    mins = (x-0.1f)*(x-0.1f)+(z+0.1f)*(z+0.1f), pastiu  = 0;
                else
                    if(res == minimum_res && (x-0.1f)*(x-0.1f)+(z+0.1f)*(z+0.1f) < mins)
                     minimum_res = res, X = x, Z = z,
                    mins = (x-0.1f)*(x-0.1f)+(z+0.1f)*(z+0.1f), pastiu  = 0;
                        
            }
        }
        if(minimum_res > 70)//////////
            pastiu = 1;
   
}

void loop()
{
    float qqq = sinf(0.7f);
    DEBUG(("%f", qqq));
    api.getMyZRState(myState);
    api.getOtherZRState(otherState);
    bool passed1 = passed;
    if(myState[1] <= 0.2f)
        passed = true;
        
    if(passed == true && passed1 == false)
    {
        // primul calcul (pt t = t1)
         t1 = sp;
         radius = 0.2f;
         x1 = otherState[0], z1 = otherState[2];
        alpha1 = atanf(z1/x1);
         l1 = alpha1*radius;
        // al doilea calcul (pt t = t2)
         x = 38.0f; 
         t2 = t1 + x;
         v = l1/t1;v = -0.0065f;
         alpha2 = (l1-v*x)/radius;   
         z2 = sinf(alpha2)*radius;
         x2 = cosf(alpha2)*radius;
         l2 = alpha2*radius;
       DEBUG(("l1 = %f, l2 = %f, alpha1 = %f alpha2 = %f",l1, l2, alpha1, alpha2));
        DEBUG(("x1  = %f si z1 = %f", x1, z1));
        DEBUG(("x2  = %f si z2 = %f", x2, z2));
        
       
    }
    if(passed == true)
    {
       pos[0] = 0.17f;///pos[0] = x2-0.01f;
         
         pos[1] = -0.15f;
        pos[2] = 0.01f;
            
          
         
          api.setPositionTarget(pos);
          
        if(sp >= 12 && sp <= 13)
            {
                 mathVecSubtract(vecBetween,pos,myPos,3);
                api.setVelocityTarget(vecBetween);
            }
            if(sp == 22)
            {
                pos[1] = 0.2f;
                api.setPositionTarget(pos);
            }
            if(sp >= 16 && sp <=21)
            {
                
                pos[1] = 0.2f;
                mathVecSubtract(vecBetween,pos,myPos,3);
                 api.setVelocityTarget(vecBetween);
            }
            
            if(sp == 40)
            {
                 a = myState[0], b = myState[1], d = myState[2];
            }
            
            if(sp > 40 && sp < 45)
                {
                    
                    pos[0] = a; pos[1] = b; pos[2] = d;
                    api.setPositionTarget(pos);
                }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    api.getMyZRState(myState);
    api.getOtherZRState(otherState);
    attitude[0] = 0.5f; attitude[1] = -5.5f; attitude[2] = 0.0f; 
    if(pastiu == 0)
    {
        sp++;
        for(int i =0; i < 3; i++)
            myPos[i] = myState[i];
        
        if(phase == 1)
        {  
            pos[0] = X, pos[1] = -0.0f, pos[2] = Z;
            if(myState[1] <= 0.38f)
                phase++;
            mathVecSubtract(vecBetween,pos,myPos,3);
            api.setVelocityTarget(vecBetween);
            
        }
        if(phase == 2)
        {
            pos[0] = 0.0f;
            pos[1] = 0.7f;
            pos[2] = 0.0f;
            if(myState[1] <= 0.2f)
                phase++;
            mathVecSubtract(vecBetween,pos,myPos,3);
            api.setVelocityTarget(vecBetween);
        }
        /*if(phase == 3)
        {
            pos[0] = 0.19f;
            pos[1] = -0.19f;
            pos[2] = -0.03f;
            //if(Z < 0.1f && X > -0.1f && X <= 0.2f && Z >= -0.175f)
              //  pos[2] = -0.08f;
            api.setPositionTarget(pos);
            if(sp == 21)
            {
                            mathVecSubtract(vecBetween,pos,myPos,3);
            api.setVelocityTarget(vecBetween);
            }
        }
        pos[0] = otherState[0], pos[1] = otherState[1], pos[2] = otherState[2];
        if(myState[1]-0.05f > otherState[1] && distanceTo() < 0.8f)
        {
            api.setPositionTarget(pos);
        }*/
       
    }
    else
    {
        attitude[0] = 0.5f; attitude[1] = -5.5f; attitude[2] = 0.0f;
        sp++;
         for(int i =0; i < 3; i++)
            myPos[i] = myState[i];
        if(phase == 1)
        {
            DEBUG(("fazaaaaaaaaaaaa"));
             pos[0] = 0.5f, pos[1] =0.7f, pos[2] = 0.0f;//0.65
             if(myState[0] > 0.18f)
                phase++;
            mathVecSubtract(vecBetween,pos,myPos,3);
            api.setVelocityTarget(vecBetween);
        }
        
        if(phase == 2)
        {
            pos[0] = 0.0, pos[1] = 0.7f, pos[2] = 0.0f;//la fel
            if(myState[0] > 0.31f)
                phase++;
                
            mathVecSubtract(vecBetween,pos,myPos,3);
            api.setVelocityTarget(vecBetween);
        }
        if(phase == 3)
        {
            pos[0] = 0.4f, pos[1] =0.2f, pos[2] = 0.0f;
            if(myState[1] <= 0.05f)
                phase++;
            mathVecSubtract(vecBetween,pos,myPos,3);
            api.setVelocityTarget(vecBetween);
        }
        if(phase == 4)
        {
            
           
                
            pos[0] = 0.19f;
            pos[1] = -0.17f;
            pos[2] = 0.05f;
            api.setPositionTarget(pos);
             if(sp > 31 && sp < 33)
            {mathVecSubtract(vecBetween,pos,myPos,3);
            api.setVelocityTarget(vecBetween);}
        }
        if(sp == 28 ||sp == 29)
        {
            mathVecSubtract(vecBetween,pos,myPos,3);
            api.setVelocityTarget(vecBetween);
        }
        if(sp >= 50)
        {
            pos[0] = myState[0]; pos[1] = myState[1]; pos[2] = myState[2];
            api.setPositionTarget(pos);
        }
            
         
    }
if(re==0)
    api.setAttitudeTarget(attitude);


    if(game.checkRendezvous())
    {   
        re =1;
        game.completeRendezvous();
    }
    if(re == 1)
	  {
	      pos[0] = otherState[0];
	      pos[1] = otherState[1] + 0.335f;
	      pos[2] = otherState[2];
	      game.getOtherEulerState(otherEuler);
            myEuler[0] = otherEuler[6]; myEuler[1] = otherEuler[7]; myEuler[2] = otherEuler[8]*(-1.0f); 
            game.setEulerTarget(myEuler); 
            api.setPositionTarget(pos);
	  }
}

//End page main
//Begin page returnFactorial
float returnFactorial(float x)
{
    float res = 1;
    if(x == 0.0f)
        return 1;
    for(float q = 1; q <= x; q = q+0.1f)
        res = res*q;
    return res;
}
//End page returnFactorial
//Begin page returnPower
float returnPower(float a, int b)
{
    float res = 1;
    if(b == 0)
        return 1;
    for(int i = 1; i <= b; i++)
        res = res*a;
    return res;
}
//End page returnPower