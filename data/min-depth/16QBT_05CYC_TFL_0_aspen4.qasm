OPENQASM 2.0;
include "qelib1.inc";
qreg q[16];
creg c[16];
u3(3.141593, 0.000000, 3.141593) q[0]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[1]
u3(3.141593, 0.000000, 3.141593) q[1]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[4]
u3(3.141593, 0.000000, 3.141593) q[9]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[2]
u3(3.141593, 0.000000, 3.141593) q[12]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[11]
u3(3.141593, 0.000000, 3.141593) q[3]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[15]
u3(3.141593, 0.000000, 3.141593) q[15]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[6]
u3(3.141593, 0.000000, 3.141593) q[14]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[14]
u3(3.141593, 0.000000, 3.141593) q[8]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[0]
u3(3.141593, 0.000000, 3.141593) q[4]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[7]
cx q[10],q[11]; //cycle: 0 //cx logical_q[8],logical_q[12]
cx q[5],q[6]; //cycle: 0 //cx logical_q[3],logical_q[9]
u3(3.141593, 0.000000, 3.141593) q[7]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[13]
u3(3.141593, 0.000000, 3.141593) q[5]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[3]
u3(3.141593, 0.000000, 3.141593) q[9]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[2]
u3(3.141593, 0.000000, 3.141593) q[6]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[9]
cx q[14],q[15]; //cycle: 1 //cx logical_q[14],logical_q[6]
cx q[2],q[1]; //cycle: 1 //cx logical_q[5],logical_q[4]
cx q[10],q[11]; //cycle: 1 //cx logical_q[8],logical_q[12]
cx q[13],q[12]; //cycle: 1 //cx logical_q[10],logical_q[11]
u3(3.141593, 0.000000, 3.141593) q[0]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[1]
u3(3.141593, 0.000000, 3.141593) q[3]; //cycle: 1 //u3(3.141593, 0.000000, 3.141593) logical_q[15]
u3(3.141593, 0.000000, 3.141593) q[0]; //cycle: 2 //u3(3.141593, 0.000000, 3.141593) logical_q[1]
u3(3.141593, 0.000000, 3.141593) q[11]; //cycle: 2 //u3(3.141593, 0.000000, 3.141593) logical_q[12]
cx q[10],q[9]; //cycle: 2 //cx logical_q[8],logical_q[2]
cx q[5],q[6]; //cycle: 2 //cx logical_q[3],logical_q[9]
cx q[15],q[8]; //cycle: 2 //cx logical_q[6],logical_q[0]
cx q[14],q[13]; //cycle: 2 //cx logical_q[14],logical_q[10]
u3(3.141593, 0.000000, 3.141593) q[13]; //cycle: 3 //u3(3.141593, 0.000000, 3.141593) logical_q[10]
cx q[10],q[11]; //cycle: 3 //cx logical_q[8],logical_q[12]
cx q[14],q[15]; //cycle: 3 //cx logical_q[14],logical_q[6]
cx q[0],q[1]; //cycle: 3 //cx logical_q[1],logical_q[4]
u3(3.141593, 0.000000, 3.141593) q[6]; //cycle: 3 //u3(3.141593, 0.000000, 3.141593) logical_q[9]
u3(3.141593, 0.000000, 3.141593) q[8]; //cycle: 3 //u3(3.141593, 0.000000, 3.141593) logical_q[0]
u3(3.141593, 0.000000, 3.141593) q[0]; //cycle: 4 //u3(3.141593, 0.000000, 3.141593) logical_q[1]
u3(3.141593, 0.000000, 3.141593) q[15]; //cycle: 4 //u3(3.141593, 0.000000, 3.141593) logical_q[6]
cx q[10],q[11]; //cycle: 4 //cx logical_q[8],logical_q[12]
cx q[14],q[13]; //cycle: 4 //cx logical_q[14],logical_q[10]
//37 original gates
//37 final gates
//5 original depth (cycles)
//5 cycles in selected mapping
//13240 nodes expanded (popped from queue).
//91 nodes remain in queue.
