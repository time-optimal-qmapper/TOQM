OPENQASM 2.0;
include "qelib1.inc";
qreg q[5];
creg c[5];
u3(1.570796, 0.000000, 3.141593) q[0]; //cycle: 0 //u3(1.570796, 0.000000, 3.141593) logical_q[2]
u3(3.141593, 0.000000, 3.141593) q[2]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[0]
u3(0.000000, 0.000000, -0.785398) q[1]; //cycle: 0 //u3(0.000000, 0.000000, -0.785398) logical_q[1]
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 1 //u3(0.000000, 0.000000, -0.785398) logical_q[0]
cx q[0],q[1]; //cycle: 1 //cx logical_q[2],logical_q[1]
u3(0.000000, 0.000000, -0.785398) q[0]; //cycle: 2 //u3(0.000000, 0.000000, -0.785398) logical_q[2]
u3(0.000000, 0.000000, 0.785398) q[1]; //cycle: 2 //u3(0.000000, 0.000000, 0.785398) logical_q[1]
u3(0.000000, 0.000000, -1.570796) q[0]; //cycle: 3 //u3(0.000000, 0.000000, -1.570796) logical_q[2]
cx q[2],q[1]; //cycle: 3 //cx logical_q[0],logical_q[1]
u3(0.000000, 0.000000, 0.785398) q[1]; //cycle: 4 //u3(0.000000, 0.000000, 0.785398) logical_q[1]
cx q[0],q[2]; //cycle: 4 //cx logical_q[2],logical_q[0]
u3(0.000000, 0.000000, 0.785398) q[2]; //cycle: 5 //u3(0.000000, 0.000000, 0.785398) logical_q[0]
cx q[0],q[1]; //cycle: 5 //cx logical_q[2],logical_q[1]
cx q[0],q[2]; //cycle: 6 //cx logical_q[2],logical_q[0]
u3(0.000000, 0.000000, -0.785398) q[1]; //cycle: 6 //u3(0.000000, 0.000000, -0.785398) logical_q[1]
u3(1.570796, 0.000000, 3.141593) q[0]; //cycle: 7 //u3(1.570796, 0.000000, 3.141593) logical_q[2]
cx q[2],q[1]; //cycle: 7 //cx logical_q[0],logical_q[1]
//17 original gates
//17 final gates
//8 original depth (cycles)
//8 cycles in selected mapping
//10 nodes expanded (popped from queue).
//11 nodes remain in queue.
