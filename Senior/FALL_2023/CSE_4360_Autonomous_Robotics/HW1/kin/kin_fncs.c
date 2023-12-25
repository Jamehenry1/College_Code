//Nghia Lam
//1001699317

#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415927
#endif

// Distances joints 
double D1 = -0.040;
double D2 = 0.040;
double D3 = -0.040;
double D4 = -0.040;

// Lengths Between Joints
double L0 = 0.250;
double L1 = .200;
double L2 = .200;
double L3 = .150;

fwd_kin(theta, x) //terriable notation
double *theta;
double x[3];
{
    //gets the FWD Kin from using Trig 
    x[0] = cos(theta[0]) * (L1 * cos(theta[1]) + L2 * cos(theta[1] + theta[2])
                                + D4*sin(theta[1]+theta[2]+theta[3]) + L3 * cos(theta[1] + theta[2] + theta[3])) - (D3 * sin(theta[0]));

    x[1] = sin(theta[0]) * (L1 * cos(theta[1]) + L2 * cos(theta[1] + theta[2])
                                + D4*sin(theta[1]+theta[2]+theta[3]) + L3 * cos(theta[1] + theta[2] + theta[3])) + (D3 * cos(theta[0]));

    x[2] = L0 - L1* sin(theta[1]) - L2 * sin(theta[1] + theta[2]) +  D4*cos(theta[1]+theta[2]+theta[3]) - L3 * sin(theta[1] + theta[2] + theta[3]);


    //Jacobian Matrix
    double dxT0 = -sin(theta[0]) * (L1 * cos(theta[1]) + L2 * cos(theta[1] + theta[2])
                                + D4*sin(theta[1]+theta[2]+theta[3]) + L3 * cos(theta[1] + theta[2] + theta[3])) - (D3 * cos(theta[0]));
    double dxT1 = cos(theta[0]) * (L1 * -sin(theta[1]) + L2 * -sin(theta[1] + theta[2])
                                + D4*cos(theta[1]+theta[2]+theta[3]) + L3 * -sin(theta[1] + theta[2] + theta[3]));
    double dxT2 = cos(theta[0]) * (L2 * -sin(theta[1] + theta[2])
                                + D4*cos(theta[1]+theta[2]+theta[3]) + L3 * -sin(theta[1] + theta[2] + theta[3]));
    double dxT3 = cos(theta[0]) * (D4*cos(theta[1]+theta[2]+theta[3]) + L3 * -sin(theta[1] + theta[2] + theta[3]));


    double dyT0 = cos(theta[0]) * (L1 * cos(theta[1]) + L2 * cos(theta[1] + theta[2])
                                + D4*sin(theta[1]+theta[2]+theta[3]) + L3 * cos(theta[1] + theta[2] + theta[3])) + (D3 * -sin(theta[0]));
    double dyT1 = sin(theta[0]) * (L1 * -sin(theta[1]) + L2 * -sin(theta[1] + theta[2])
                                + D4*cos(theta[1]+theta[2]+theta[3]) + L3 * -sin(theta[1] + theta[2] + theta[3]));
    double dyT2 = sin(theta[0]) * (L2 * -sin(theta[1] + theta[2])
                                + D4*cos(theta[1]+theta[2]+theta[3]) + L3 * -sin(theta[1] + theta[2] + theta[3]));
    double dyT3 = sin(theta[0]) * (D4*cos(theta[1]+theta[2]+theta[3]) + L3 * -sin(theta[1] + theta[2] + theta[3]));
    
    double dzT0 = 0;
    double dzT1 = -L1* cos(theta[1]) - L2 * cos(theta[1] + theta[2]) +  D4*-sin(theta[1]+theta[2]+theta[3]) - L3 * cos(theta[1] + theta[2] + theta[3]);
    double dzT2 = -L2 * cos(theta[1] + theta[2]) +  D4*-sin(theta[1]+theta[2]+theta[3]) - L3 * cos(theta[1] + theta[2] + theta[3]);
    double dzT3 = D4*-sin(theta[1]+theta[2]+theta[3]) - L3 * cos(theta[1] + theta[2] + theta[3]);
}


inv_kin(x, theta)
double *x;
double theta[6];
{
    
    // Gets the offset angle as there is an offset for d3 when rotating around z
    double offsetAngle = asin(D3/sqrt((x[0]*x[0]) + (x[1]*x[1])));
    theta[0]  = atan(x[1]/x[0]) - offsetAngle;

    if (x[0] < 0){
        theta[0] = theta[0] + M_PI;
    }

    // theta 3 to wrist: did l0 to theta 1 in here as well
    double x1 = x[0] - D4 * cos(theta[0]) + D3 * sin(theta[0]);
    double y1 = x[1] - D3 * cos(theta[0]) - D4 * sin(theta[0]); 
    double z1 = x[2] + L3 - L0;

    // Flatten so we can use slide equation 
    double x2 = sqrt(pow(x1,2)+pow(y1,2));
    double y2 = -z1;

    // Slide Equations 
    double s = pow(x2,2) + pow(y2,2);
    double B = atan(y2/x2);
    double t2 = (s - pow(L1,2)-pow(L2,2))/(2*L1*L2);
    double a = (s + pow(L1,2)-pow(L2,2))/(2*sqrt(s)*L1);

    // These whiles are use before it is inputed into acos as it can only take 1, -1
    while (a > 1){
        a = a - 2;
    }
    double A = acos(a);

    while (t2 > 1){
        t2 = t2 - 2;
    }

    theta[2] = acos(t2);

    if (theta[2] >= 0){
        theta[1] = B - A;
    }
    else{
        theta[1] = B + A;
    }

    theta[3] = M_PI/2 - theta[1] - theta[2];

}









