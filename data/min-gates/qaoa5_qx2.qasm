OPENQASM 2.0;
include "qelib1.inc";
qreg q[5];
creg c[5];
u3(1.570796, 0.000000, 3.141593) q[1]; //cycle: 0 //u3(1.570796, 0.000000, 3.141593) logical_q[4]
u3(1.570796, 0.000000, 3.141593) q[2]; //cycle: 0 //u3(1.570796, 0.000000, 3.141593) logical_q[2]
u3(1.570796, 0.000000, 3.141593) q[4]; //cycle: 0 //u3(1.570796, 0.000000, 3.141593) logical_q[0]
u3(1.570796, 0.000000, 3.141593) q[3]; //cycle: 0 //u3(1.570796, 0.000000, 3.141593) logical_q[1]
u3(1.570796, 0.000000, 3.141593) q[0]; //cycle: 0 //u3(1.570796, 0.000000, 3.141593) logical_q[3]
cx q[4],q[3]; //cycle: 1 //cx logical_q[0],logical_q[1]
u3(0.000000, 0.000000, 1.571000) q[3]; //cycle: 2 //u3(0.000000, 0.000000, 1.571000) logical_q[1]
cx q[4],q[3]; //cycle: 3 //cx logical_q[0],logical_q[1]
u3(2.356000, -1.570796, 1.570796) q[4]; //cycle: 4 //u3(2.356000, -1.570796, 1.570796) logical_q[0]
cx q[3],q[2]; //cycle: 4 //cx logical_q[1],logical_q[2]
u3(0.000000, 0.000000, 1.571000) q[2]; //cycle: 5 //u3(0.000000, 0.000000, 1.571000) logical_q[2]
cx q[3],q[2]; //cycle: 6 //cx logical_q[1],logical_q[2]
cx q[2],q[0]; //cycle: 7 //cx logical_q[2],logical_q[3]
u3(2.356000, -1.570796, 1.570796) q[3]; //cycle: 7 //u3(2.356000, -1.570796, 1.570796) logical_q[1]
u3(0.000000, 0.000000, 1.571000) q[0]; //cycle: 8 //u3(0.000000, 0.000000, 1.571000) logical_q[3]
cx q[2],q[0]; //cycle: 9 //cx logical_q[2],logical_q[3]
u3(2.356000, -1.570796, 1.570796) q[2]; //cycle: 10 //u3(2.356000, -1.570796, 1.570796) logical_q[2]
cx q[0],q[1]; //cycle: 10 //cx logical_q[3],logical_q[4]
u3(0.000000, 0.000000, 1.571000) q[1]; //cycle: 11 //u3(0.000000, 0.000000, 1.571000) logical_q[4]
cx q[0],q[1]; //cycle: 12 //cx logical_q[3],logical_q[4]
u3(2.356000, -1.570796, 1.570796) q[1]; //cycle: 13 //u3(2.356000, -1.570796, 1.570796) logical_q[4]
u3(2.356000, -1.570796, 1.570796) q[0]; //cycle: 13 //u3(2.356000, -1.570796, 1.570796) logical_q[3]
//22 original gates
//22 final gates
//37 nodes expanded (popped from queue).
//14 nodes remain in queue.
