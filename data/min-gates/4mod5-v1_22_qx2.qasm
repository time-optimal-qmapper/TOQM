OPENQASM 2.0;
include "qelib1.inc";
qreg q[5];
creg c[5];
cx q[3],q[4]; //cycle: 0 //cx logical_q[1],logical_q[3]
u3(3.141593, 0.000000, 3.141593) q[0]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[4]
cx q[2],q[1]; //cycle: 0 //cx logical_q[0],logical_q[2]
u3(0.000000, 0.000000, 0.785398) q[4]; //cycle: 1 //u3(0.000000, 0.000000, 0.785398) logical_q[3]
u3(0.000000, 0.000000, 0.785398) q[1]; //cycle: 1 //u3(0.000000, 0.000000, 0.785398) logical_q[2]
u3(1.570796, 0.000000, 3.141593) q[0]; //cycle: 1 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
swp q[2],q[4]; //cycle: 2
u3(0.000000, 0.000000, 0.785398) q[0]; //cycle: 2 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
cx q[2],q[1]; //cycle: 3 //cx logical_q[3],logical_q[2]
cx q[0],q[2]; //cycle: 4 //cx logical_q[4],logical_q[3]
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 5 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
cx q[1],q[0]; //cycle: 5 //cx logical_q[2],logical_q[4]
cx q[1],q[2]; //cycle: 6 //cx logical_q[2],logical_q[3]
u3(0.000000, 0.000000, 0.785398) q[0]; //cycle: 6 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 7 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
u3(0.000000, 0.000000, -0.785398) q[1]; //cycle: 7 //u3(0.000000, 0.000000, -0.785398) logical_q[2]
cx q[0],q[2]; //cycle: 8 //cx logical_q[4],logical_q[3]
cx q[1],q[0]; //cycle: 9 //cx logical_q[2],logical_q[4]
cx q[2],q[1]; //cycle: 10 //cx logical_q[3],logical_q[2]
u3(1.570796, 0.000000, 3.141593) q[0]; //cycle: 10 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
cx q[1],q[2]; //cycle: 11 //cx logical_q[2],logical_q[3]
cx q[2],q[0]; //cycle: 12 //cx logical_q[3],logical_q[4]
//21 original gates
//22 final gates
//1101 nodes expanded (popped from queue).
//906 nodes remain in queue.
