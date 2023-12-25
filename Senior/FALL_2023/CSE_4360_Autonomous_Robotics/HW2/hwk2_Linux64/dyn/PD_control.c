#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Nghia Lam
int UTA_ID = 1001699317;

double oldV = 0;
double newV = 0;
double Grav = 4.54237;
double Fric = .6296;
double Inertia = .092620;
int counter = 0;
double totalI = 0;

double PD_control(theta, theta_dot, theta_ref, theta_dot_ref)
double theta, theta_dot, theta_ref, theta_dot_ref;
{
  
  double force = 100000000;

  
  printf("theta %f theta_dot %f theta_ref %f theta_dot_ref %f\n", theta,theta_dot,theta_ref,theta_dot_ref);
  
  double t1 = Grav * cos(theta);
  printf("G: %f",Grav);

  //printf("new:%f old:%f cal: %f",newV,oldV,newV - oldV);

  //This is the Torque of friction plus input force; Applied Torque = 1000
  double t2 = (Fric*theta_dot + t1);
  
  //Used this to try to find Inertia to see if my answer was correct
  oldV = newV;
  newV = theta_dot;
  double theta_double_dot = (newV - oldV)*500;
  double I = force/theta_double_dot;

  //PART 2 Start here --------------------------
  double Kp = 10;
  double Kv = 2*sqrt(Kp);
  double t3 = I*theta_double_dot;
  //printf("t1: %f, t2: %f, t3: %f I: %f  acc: %f\n\n",t1,t2,t3,I,theta_double_dot);

  double T4 = Inertia*(-Kp*(theta - theta_ref) - Kv*theta_dot) + t2;

  return(T4);

}
