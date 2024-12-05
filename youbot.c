#include <webots/keyboard.h>
#include <webots/robot.h>

#include <arm.h>
#include <base.h>
#include <gripper.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 32 milliseconds
#define TIME_STEP 32

static void step() {
  // time step is only -1 when user presses stop
  if (wb_robot_step(TIME_STEP) == -1) {
    
    //robot_cleanup() frees the mem allocated by the robot. Only used at the end of the program.
    wb_robot_cleanup();
    exit(EXIT_SUCCESS);
  }
}

// function to wait while the robot does its thing 
static void passive_wait(double sec) {
  double start_time = wb_robot_get_time();
  do {
    step();
  } while (start_time + sec > wb_robot_get_time());
}


int main(int argc, char **argv) {
  wb_robot_init();

  // initializing the components
  base_init();
  arm_init();
  gripper_init();
  
  // grip the gripper
  gripper_grip();
  
  printf("Moving forwards..\n");
  base_forwards();
  
  // wait a few seconds
  passive_wait(3.0);
  
  // stop the base
  printf("stopping");
  base_reset();
  
  wb_robot_cleanup();
  return 0;
 }
