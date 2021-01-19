OPENQASM 2.0;
include "qelib1.inc";
qreg q[5];
creg c[5];
u3(0.000000, 0.000000, 0.785398) q[3]; //cycle: 0 //u3(0.000000, 0.000000, 0.785398) logical_q[0]
cx q[0],q[2]; //cycle: 0 //cx logical_q[1],logical_q[3]
u3(1.570796, 0.000000, 3.141593) q[4]; //cycle: 0 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
u3(0.000000, 0.000000, 0.785398) q[1]; //cycle: 0 //u3(0.000000, 0.000000, 0.785398) logical_q[2]
u3(3.141593, 0.000000, 3.141593) q[2]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[3]
u3(0.000000, 0.000000, 0.785398) q[4]; //cycle: 1 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
u3(0.000000, 0.000000, 0.785398) q[2]; //cycle: 2 //u3(0.000000, 0.000000, 0.785398) logical_q[3]
cx q[3],q[2]; //cycle: 3 //cx logical_q[0],logical_q[3]
cx q[4],q[3]; //cycle: 4 //cx logical_q[4],logical_q[0]
u3(0.000000, 0.000000, -0.785398) q[3]; //cycle: 5 //u3(0.000000, 0.000000, -0.785398) logical_q[0]
cx q[2],q[4]; //cycle: 5 //cx logical_q[3],logical_q[4]
cx q[2],q[3]; //cycle: 6 //cx logical_q[3],logical_q[0]
u3(0.000000, 0.000000, 0.785398) q[4]; //cycle: 6 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 7 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
u3(0.000000, 0.000000, -0.785398) q[3]; //cycle: 7 //u3(0.000000, 0.000000, -0.785398) logical_q[0]
cx q[4],q[3]; //cycle: 8 //cx logical_q[4],logical_q[0]
cx q[2],q[4]; //cycle: 9 //cx logical_q[3],logical_q[4]
u3(1.570796, 0.000000, 3.141593) q[4]; //cycle: 10 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
cx q[3],q[2]; //cycle: 10 //cx logical_q[0],logical_q[3]
u3(1.570796, 0.000000, 3.141593) q[4]; //cycle: 11 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
u3(0.000000, 0.000000, 0.785398) q[2]; //cycle: 11 //u3(0.000000, 0.000000, 0.785398) logical_q[3]
swp q[0],q[2]; //cycle: 12
u3(0.000000, 0.000000, 0.785398) q[4]; //cycle: 12 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
swp q[2],q[4]; //cycle: 13
cx q[1],q[0]; //cycle: 13 //cx logical_q[2],logical_q[3]
cx q[2],q[1]; //cycle: 14 //cx logical_q[4],logical_q[2]
cx q[0],q[2]; //cycle: 15 //cx logical_q[3],logical_q[4]
u3(0.000000, 0.000000, -0.785398) q[1]; //cycle: 15 //u3(0.000000, 0.000000, -0.785398) logical_q[2]
cx q[0],q[1]; //cycle: 16 //cx logical_q[3],logical_q[2]
u3(0.000000, 0.000000, 0.785398) q[2]; //cycle: 16 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
u3(0.000000, 0.000000, -0.785398) q[0]; //cycle: 17 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
u3(0.000000, 0.000000, -0.785398) q[1]; //cycle: 17 //u3(0.000000, 0.000000, -0.785398) logical_q[2]
cx q[2],q[1]; //cycle: 18 //cx logical_q[4],logical_q[2]
cx q[0],q[2]; //cycle: 19 //cx logical_q[3],logical_q[4]
cx q[1],q[0]; //cycle: 20 //cx logical_q[2],logical_q[3]
u3(1.570796, 0.000000, 3.141593) q[2]; //cycle: 20 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
cx q[0],q[2]; //cycle: 21 //cx logical_q[3],logical_q[4]
//35 original gates
//37 final gates
//9332 nodes expanded (popped from queue).
//1387 nodes remain in queue.
