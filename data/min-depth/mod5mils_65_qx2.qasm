OPENQASM 2.0;
include "qelib1.inc";
qreg q[5];
creg c[5];
u3(0.000000, 0.000000, 0.785398) q[1]; //cycle: 0 //u3(0.000000, 0.000000, 0.785398) logical_q[0]
cx q[2],q[3]; //cycle: 0 //cx logical_q[1],logical_q[3]
u3(1.570796, 0.000000, 3.141593) q[4]; //cycle: 0 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
u3(0.000000, 0.000000, 0.785398) q[0]; //cycle: 0 //u3(0.000000, 0.000000, 0.785398) logical_q[2]
swp q[1],q[2]; //cycle: 1
u3(3.141593, 0.000000, 3.141593) q[3]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[3]
u3(0.000000, 0.000000, 0.785398) q[4]; //cycle: 1 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
u3(0.000000, 0.000000, 0.785398) q[3]; //cycle: 2 //u3(0.000000, 0.000000, 0.785398) logical_q[3]
cx q[2],q[3]; //cycle: 4 //cx logical_q[0],logical_q[3]
cx q[4],q[2]; //cycle: 5 //cx logical_q[4],logical_q[0]
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 6 //u3(0.000000, 0.000000, -0.785398) logical_q[0]
cx q[3],q[4]; //cycle: 6 //cx logical_q[3],logical_q[4]
cx q[3],q[2]; //cycle: 7 //cx logical_q[3],logical_q[0]
u3(0.000000, 0.000000, 0.785398) q[4]; //cycle: 7 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
u3(0.000000, 0.000000, -0.785398) q[3]; //cycle: 8 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 8 //u3(0.000000, 0.000000, -0.785398) logical_q[0]
cx q[4],q[2]; //cycle: 9 //cx logical_q[4],logical_q[0]
cx q[3],q[4]; //cycle: 10 //cx logical_q[3],logical_q[4]
u3(1.570796, 0.000000, 3.141593) q[4]; //cycle: 11 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
cx q[2],q[3]; //cycle: 11 //cx logical_q[0],logical_q[3]
swp q[0],q[2]; //cycle: 12
u3(1.570796, 0.000000, 3.141593) q[4]; //cycle: 12 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
u3(0.000000, 0.000000, 0.785398) q[3]; //cycle: 12 //u3(0.000000, 0.000000, 0.785398) logical_q[3]
u3(0.000000, 0.000000, 0.785398) q[4]; //cycle: 13 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
cx q[2],q[3]; //cycle: 15 //cx logical_q[2],logical_q[3]
cx q[4],q[2]; //cycle: 16 //cx logical_q[4],logical_q[2]
cx q[3],q[4]; //cycle: 17 //cx logical_q[3],logical_q[4]
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 17 //u3(0.000000, 0.000000, -0.785398) logical_q[2]
cx q[3],q[2]; //cycle: 18 //cx logical_q[3],logical_q[2]
u3(0.000000, 0.000000, 0.785398) q[4]; //cycle: 18 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
u3(0.000000, 0.000000, -0.785398) q[3]; //cycle: 19 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 19 //u3(0.000000, 0.000000, -0.785398) logical_q[2]
cx q[4],q[2]; //cycle: 20 //cx logical_q[4],logical_q[2]
cx q[3],q[4]; //cycle: 21 //cx logical_q[3],logical_q[4]
cx q[2],q[3]; //cycle: 22 //cx logical_q[2],logical_q[3]
u3(1.570796, 0.000000, 3.141593) q[4]; //cycle: 22 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
cx q[3],q[4]; //cycle: 23 //cx logical_q[3],logical_q[4]
//35 original gates
//37 final gates
//21 original depth (cycles)
//24 cycles in selected mapping
//156 nodes expanded (popped from queue).
//393 nodes remain in queue.
