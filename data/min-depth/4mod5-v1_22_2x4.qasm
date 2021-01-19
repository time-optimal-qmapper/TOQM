OPENQASM 2.0;
include "qelib1.inc";
qreg q[8];
creg c[8];
cx q[1],q[3]; //cycle: 0 //cx logical_q[1],logical_q[3]
u3(3.141593, 0.000000, 3.141593) q[5]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[4]
cx q[0],q[2]; //cycle: 0 //cx logical_q[0],logical_q[2]
u3(0.000000, 0.000000, 0.785398) q[3]; //cycle: 1 //u3(0.000000, 0.000000, 0.785398) logical_q[3]
u3(0.000000, 0.000000, 0.785398) q[2]; //cycle: 1 //u3(0.000000, 0.000000, 0.785398) logical_q[2]
u3(1.570796, 0.000000, 3.141593) q[5]; //cycle: 1 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
u3(0.000000, 0.000000, 0.785398) q[5]; //cycle: 2 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
cx q[3],q[2]; //cycle: 2 //cx logical_q[3],logical_q[2]
cx q[5],q[3]; //cycle: 3 //cx logical_q[4],logical_q[3]
swp q[2],q[3]; //cycle: 4
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 7 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
cx q[3],q[5]; //cycle: 7 //cx logical_q[2],logical_q[4]
cx q[3],q[2]; //cycle: 8 //cx logical_q[2],logical_q[3]
u3(0.000000, 0.000000, 0.785398) q[5]; //cycle: 8 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
swp q[3],q[5]; //cycle: 9
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 9 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
u3(0.000000, 0.000000, -0.785398) q[5]; //cycle: 12 //u3(0.000000, 0.000000, -0.785398) logical_q[2]
cx q[3],q[2]; //cycle: 12 //cx logical_q[4],logical_q[3]
swp q[2],q[4]; //cycle: 13
cx q[5],q[3]; //cycle: 13 //cx logical_q[2],logical_q[4]
u3(1.570796, 0.000000, 3.141593) q[3]; //cycle: 14 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
swp q[2],q[3]; //cycle: 16
cx q[4],q[5]; //cycle: 16 //cx logical_q[3],logical_q[2]
cx q[5],q[4]; //cycle: 17 //cx logical_q[2],logical_q[3]
cx q[4],q[2]; //cycle: 19 //cx logical_q[3],logical_q[4]
//21 original gates
//25 final gates
//12 original depth (cycles)
//20 cycles in selected mapping
//2746 nodes expanded (popped from queue).
//3948 nodes remain in queue.
