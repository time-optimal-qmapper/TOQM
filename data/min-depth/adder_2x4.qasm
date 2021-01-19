OPENQASM 2.0;
include "qelib1.inc";
qreg q[8];
creg c[8];
u3(1.570796, 0.000000, 3.141593) q[1]; //cycle: 0 //u3(1.570796, 0.000000, 3.141593) logical_q[3]
u3(3.141593, 0.000000, 3.141593) q[3]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[0]
u3(3.141593, 0.000000, 3.141593) q[2]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[1]
u3(0.000000, 0.000000, 0.785398) q[2]; //cycle: 1 //u3(0.000000, 0.000000, 0.785398) logical_q[1]
u3(0.000000, 0.000000, 0.785398) q[3]; //cycle: 1 //u3(0.000000, 0.000000, 0.785398) logical_q[0]
cx q[0],q[1]; //cycle: 1 //cx logical_q[2],logical_q[3]
u3(0.000000, 0.000000, 0.785398) q[0]; //cycle: 2 //u3(0.000000, 0.000000, 0.785398) logical_q[2]
cx q[3],q[2]; //cycle: 2 //cx logical_q[0],logical_q[1]
u3(0.000000, 0.000000, -0.785398) q[1]; //cycle: 2 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
cx q[0],q[1]; //cycle: 3 //cx logical_q[2],logical_q[3]
cx q[1],q[3]; //cycle: 4 //cx logical_q[3],logical_q[0]
cx q[2],q[0]; //cycle: 4 //cx logical_q[1],logical_q[2]
cx q[3],q[2]; //cycle: 5 //cx logical_q[0],logical_q[1]
cx q[0],q[1]; //cycle: 5 //cx logical_q[2],logical_q[3]
u3(0.000000, 0.000000, -0.785398) q[3]; //cycle: 6 //u3(0.000000, 0.000000, -0.785398) logical_q[0]
u3(0.000000, 0.000000, 0.785398) q[1]; //cycle: 6 //u3(0.000000, 0.000000, 0.785398) logical_q[3]
u3(0.000000, 0.000000, -0.785398) q[0]; //cycle: 6 //u3(0.000000, 0.000000, -0.785398) logical_q[2]
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 6 //u3(0.000000, 0.000000, -0.785398) logical_q[1]
cx q[3],q[2]; //cycle: 7 //cx logical_q[0],logical_q[1]
cx q[0],q[1]; //cycle: 7 //cx logical_q[2],logical_q[3]
u3(0.000000, 0.000000, 1.570796) q[1]; //cycle: 8 //u3(0.000000, 0.000000, 1.570796) logical_q[3]
cx q[1],q[3]; //cycle: 9 //cx logical_q[3],logical_q[0]
u3(1.570796, 0.000000, 3.141593) q[1]; //cycle: 10 //u3(1.570796, 0.000000, 3.141593) logical_q[3]
//23 original gates
//23 final gates
//11 original depth (cycles)
//11 cycles in selected mapping
//70 nodes expanded (popped from queue).
//21 nodes remain in queue.
