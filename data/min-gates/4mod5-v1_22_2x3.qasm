OPENQASM 2.0;
include "qelib1.inc";
qreg q[6];
creg c[6];
cx q[0],q[2]; //cycle: 0 //cx logical_q[1],logical_q[3]
u3(3.141593, 0.000000, 3.141593) q[3]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[4]
cx q[5],q[4]; //cycle: 0 //cx logical_q[0],logical_q[2]
u3(0.000000, 0.000000, 0.785398) q[2]; //cycle: 1 //u3(0.000000, 0.000000, 0.785398) logical_q[3]
u3(0.000000, 0.000000, 0.785398) q[4]; //cycle: 1 //u3(0.000000, 0.000000, 0.785398) logical_q[2]
u3(1.570796, 0.000000, 3.141593) q[3]; //cycle: 1 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
u3(0.000000, 0.000000, 0.785398) q[3]; //cycle: 2 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
cx q[2],q[4]; //cycle: 2 //cx logical_q[3],logical_q[2]
cx q[3],q[2]; //cycle: 3 //cx logical_q[4],logical_q[3]
swp q[2],q[4]; //cycle: 4
u3(0.000000, 0.000000, -0.785398) q[4]; //cycle: 5 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
cx q[2],q[3]; //cycle: 5 //cx logical_q[2],logical_q[4]
cx q[2],q[4]; //cycle: 6 //cx logical_q[2],logical_q[3]
u3(0.000000, 0.000000, 0.785398) q[3]; //cycle: 6 //u3(0.000000, 0.000000, 0.785398) logical_q[4]
u3(0.000000, 0.000000, -0.785398) q[4]; //cycle: 7 //u3(0.000000, 0.000000, -0.785398) logical_q[3]
u3(0.000000, 0.000000, -0.785398) q[2]; //cycle: 7 //u3(0.000000, 0.000000, -0.785398) logical_q[2]
swp q[2],q[3]; //cycle: 8
cx q[2],q[4]; //cycle: 9 //cx logical_q[4],logical_q[3]
cx q[3],q[2]; //cycle: 10 //cx logical_q[2],logical_q[4]
swp q[3],q[5]; //cycle: 11
u3(1.570796, 0.000000, 3.141593) q[2]; //cycle: 11 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
cx q[4],q[5]; //cycle: 12 //cx logical_q[3],logical_q[2]
cx q[5],q[4]; //cycle: 13 //cx logical_q[2],logical_q[3]
cx q[4],q[2]; //cycle: 14 //cx logical_q[3],logical_q[4]
//21 original gates
//24 final gates
//5778 nodes expanded (popped).
//5888 nodes remain in queue.
