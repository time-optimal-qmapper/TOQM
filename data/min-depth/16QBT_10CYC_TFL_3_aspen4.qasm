OPENQASM 2.0;
include "qelib1.inc";
qreg q[16];
creg c[16];
u3(3.141593, 0.000000, 3.141593) q[0]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[10]
u3(3.141593, 0.000000, 3.141593) q[10]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[3]
u3(3.141593, 0.000000, 3.141593) q[5]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[0]
u3(3.141593, 0.000000, 3.141593) q[8]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[2]
cx q[6],q[7]; //cycle: 0 //cx logical_q[13],logical_q[6]
cx q[3],q[2]; //cycle: 0 //cx logical_q[14],logical_q[12]
u3(3.141593, 0.000000, 3.141593) q[13]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[7]
u3(3.141593, 0.000000, 3.141593) q[11]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[5]
u3(3.141593, 0.000000, 3.141593) q[14]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[4]
u3(3.141593, 0.000000, 3.141593) q[4]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[11]
u3(3.141593, 0.000000, 3.141593) q[12]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[9]
cx q[7],q[0]; //cycle: 1 //cx logical_q[6],logical_q[10]
u3(3.141593, 0.000000, 3.141593) q[5]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[0]
u3(3.141593, 0.000000, 3.141593) q[13]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[7]
cx q[2],q[1]; //cycle: 1 //cx logical_q[12],logical_q[1]
u3(3.141593, 0.000000, 3.141593) q[14]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[4]
u3(3.141593, 0.000000, 3.141593) q[10]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[3]
cx q[8],q[15]; //cycle: 1 //cx logical_q[2],logical_q[8]
cx q[12],q[11]; //cycle: 1 //cx logical_q[9],logical_q[5]
u3(3.141593, 0.000000, 3.141593) q[13]; //cycle: 2 //u3(3.141593, 0.000000, 3.141593) logical_q[7]
cx q[5],q[4]; //cycle: 2 //cx logical_q[0],logical_q[11]
cx q[2],q[1]; //cycle: 2 //cx logical_q[12],logical_q[1]
u3(3.141593, 0.000000, 3.141593) q[0]; //cycle: 2 //u3(3.141593, 0.000000, 3.141593) logical_q[10]
u3(3.141593, 0.000000, 3.141593) q[12]; //cycle: 2 //u3(3.141593, 0.000000, 3.141593) logical_q[9]
u3(3.141593, 0.000000, 3.141593) q[15]; //cycle: 2 //u3(3.141593, 0.000000, 3.141593) logical_q[8]
cx q[9],q[8]; //cycle: 2 //cx logical_q[15],logical_q[2]
cx q[10],q[11]; //cycle: 2 //cx logical_q[3],logical_q[5]
u3(3.141593, 0.000000, 3.141593) q[14]; //cycle: 2 //u3(3.141593, 0.000000, 3.141593) logical_q[4]
cx q[4],q[3]; //cycle: 3 //cx logical_q[11],logical_q[14]
cx q[2],q[13]; //cycle: 3 //cx logical_q[12],logical_q[7]
cx q[6],q[5]; //cycle: 3 //cx logical_q[13],logical_q[0]
u3(3.141593, 0.000000, 3.141593) q[15]; //cycle: 3 //u3(3.141593, 0.000000, 3.141593) logical_q[8]
cx q[7],q[0]; //cycle: 3 //cx logical_q[6],logical_q[10]
u3(3.141593, 0.000000, 3.141593) q[1]; //cycle: 3 //u3(3.141593, 0.000000, 3.141593) logical_q[1]
u3(3.141593, 0.000000, 3.141593) q[12]; //cycle: 3 //u3(3.141593, 0.000000, 3.141593) logical_q[9]
u3(3.141593, 0.000000, 3.141593) q[9]; //cycle: 3 //u3(3.141593, 0.000000, 3.141593) logical_q[15]
cx q[10],q[11]; //cycle: 3 //cx logical_q[3],logical_q[5]
u3(3.141593, 0.000000, 3.141593) q[4]; //cycle: 4 //u3(3.141593, 0.000000, 3.141593) logical_q[11]
u3(3.141593, 0.000000, 3.141593) q[13]; //cycle: 4 //u3(3.141593, 0.000000, 3.141593) logical_q[7]
u3(3.141593, 0.000000, 3.141593) q[2]; //cycle: 4 //u3(3.141593, 0.000000, 3.141593) logical_q[12]
u3(3.141593, 0.000000, 3.141593) q[3]; //cycle: 4 //u3(3.141593, 0.000000, 3.141593) logical_q[14]
cx q[6],q[5]; //cycle: 4 //cx logical_q[13],logical_q[0]
u3(3.141593, 0.000000, 3.141593) q[15]; //cycle: 4 //u3(3.141593, 0.000000, 3.141593) logical_q[8]
u3(3.141593, 0.000000, 3.141593) q[0]; //cycle: 4 //u3(3.141593, 0.000000, 3.141593) logical_q[10]
cx q[10],q[11]; //cycle: 4 //cx logical_q[3],logical_q[5]
cx q[2],q[13]; //cycle: 5 //cx logical_q[12],logical_q[7]
cx q[8],q[15]; //cycle: 5 //cx logical_q[2],logical_q[8]
u3(3.141593, 0.000000, 3.141593) q[5]; //cycle: 5 //u3(3.141593, 0.000000, 3.141593) logical_q[0]
u3(3.141593, 0.000000, 3.141593) q[0]; //cycle: 5 //u3(3.141593, 0.000000, 3.141593) logical_q[10]
u3(3.141593, 0.000000, 3.141593) q[4]; //cycle: 5 //u3(3.141593, 0.000000, 3.141593) logical_q[11]
u3(3.141593, 0.000000, 3.141593) q[3]; //cycle: 5 //u3(3.141593, 0.000000, 3.141593) logical_q[14]
u3(3.141593, 0.000000, 3.141593) q[6]; //cycle: 5 //u3(3.141593, 0.000000, 3.141593) logical_q[13]
cx q[4],q[3]; //cycle: 6 //cx logical_q[11],logical_q[14]
cx q[2],q[1]; //cycle: 6 //cx logical_q[12],logical_q[1]
u3(3.141593, 0.000000, 3.141593) q[8]; //cycle: 6 //u3(3.141593, 0.000000, 3.141593) logical_q[2]
u3(3.141593, 0.000000, 3.141593) q[15]; //cycle: 6 //u3(3.141593, 0.000000, 3.141593) logical_q[8]
cx q[6],q[7]; //cycle: 6 //cx logical_q[13],logical_q[6]
cx q[13],q[12]; //cycle: 6 //cx logical_q[7],logical_q[9]
u3(3.141593, 0.000000, 3.141593) q[4]; //cycle: 7 //u3(3.141593, 0.000000, 3.141593) logical_q[11]
u3(3.141593, 0.000000, 3.141593) q[3]; //cycle: 7 //u3(3.141593, 0.000000, 3.141593) logical_q[14]
cx q[2],q[1]; //cycle: 7 //cx logical_q[12],logical_q[1]
u3(3.141593, 0.000000, 3.141593) q[13]; //cycle: 7 //u3(3.141593, 0.000000, 3.141593) logical_q[7]
u3(3.141593, 0.000000, 3.141593) q[12]; //cycle: 7 //u3(3.141593, 0.000000, 3.141593) logical_q[9]
cx q[6],q[7]; //cycle: 7 //cx logical_q[13],logical_q[6]
cx q[15],q[14]; //cycle: 7 //cx logical_q[8],logical_q[4]
u3(3.141593, 0.000000, 3.141593) q[4]; //cycle: 8 //u3(3.141593, 0.000000, 3.141593) logical_q[11]
u3(3.141593, 0.000000, 3.141593) q[1]; //cycle: 8 //u3(3.141593, 0.000000, 3.141593) logical_q[1]
cx q[3],q[2]; //cycle: 8 //cx logical_q[14],logical_q[12]
cx q[13],q[12]; //cycle: 8 //cx logical_q[7],logical_q[9]
cx q[15],q[14]; //cycle: 8 //cx logical_q[8],logical_q[4]
u3(3.141593, 0.000000, 3.141593) q[4]; //cycle: 9 //u3(3.141593, 0.000000, 3.141593) logical_q[11]
u3(3.141593, 0.000000, 3.141593) q[2]; //cycle: 9 //u3(3.141593, 0.000000, 3.141593) logical_q[12]
u3(3.141593, 0.000000, 3.141593) q[3]; //cycle: 9 //u3(3.141593, 0.000000, 3.141593) logical_q[14]
//73 original gates
//73 final gates
//10 original depth (cycles)
//10 cycles in selected mapping
//392622 nodes expanded (popped from queue).
//78 nodes remain in queue.
