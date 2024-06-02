/*********************************************
 * OPL 22.1.1.0 Model
 * Author: Fatih Baskın
 * Number: 150210710
 * Creation Date: 18 May 2024 at 04:51:47
 *********************************************/
 
// dvar -> desicion variable
// boolean is used for 0-1 problem
dvar boolean x_1;
dvar boolean x_2;
dvar boolean x_3;
dvar boolean x_4;
dvar boolean x_5;
dvar boolean x_6;
dvar boolean x_7;
dvar boolean x_8;
dvar boolean x_9;

// objective function
// dexpr -> define expression
dexpr int obj_func = 1600 * x_1 + 800 * x_2 + 1200 * x_3 + 150 * x_4 + 650 * x_5 + 100 * x_6 + 550 * x_7 + 250 * x_8 + 1650 * x_9;

// model
minimize obj_func;
// constraints
subject to {
  // for image recognition:
  x_2 + x_8 + x_9 >= 1;
  // for audio recognition:
  x_2 + x_3 + x_9 >= 1;
  // for file analysis:
  x_4 + x_5 + x_9 >= 1;
  // for speech synthesis:
  x_3 + x_6 >= 1;
  // for NLP:
  x_1 + x_3 + x_5 + x_7 >= 1;
  // for anomaly detection:
  x_1 + x_2 + x_8 + x_9 >= 1;
  // for predictive analysis:
  x_1 + x_7 + x_9 >= 1;
}
