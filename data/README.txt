README
## Resulted qasm files

* min-depth is for all benchmarks in OLSQ depth optimality testing
* min-gate is for all benchmarks in OLSQ gate optimality testing
* coupling-graph is for all the hardware coupling graphs used

In the output .qasm files, each original instruction is placed as comments to the right of its transformed one such that the qubit location for each gate is described. For instance in the following instruction:

“u3(3.141593, 0.000000, 3.141593) q[0]; //cycle: 0 //u3(3.141593, 0.000000, 3.141593) logical_q[1]” 

It means the original logical_q[1] is mapped to the physical qubit q[0]. 

We provide hardware coupling graphs in the coupling graphs folder. 

Example:

6 7
0 1
0 2
1 3
2 3
2 4
3 5
4 5

0-2-4
| | |
1-3-5

The first number describes the number of vertices. The second number describes the number of edges. Then it describes the adjacency list, followed by a pictorial description of the hardware. 


