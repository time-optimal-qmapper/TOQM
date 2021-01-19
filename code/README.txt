********************
**DIRECTORY LAYOUT**
********************

The 'src' folder contains our source code.
The 'couplings' folder contains the coupling maps for architectures used in our paper.
The 'circuits' folder contains circuits we used in our paper and/or our response to reviewers.

Within the circuits folder:
-The 'small' folder contains a set of small benchmarks (3 to 5 qubits) used by Robert Wille et. al.
-The 'large' folder contains a set of larger benchmarks (8 to 16 qubits).
-The 'OLSQ' folder contains a set of benchmarks from the OLSQ paper.


********************
*****COMPILATION****
********************

Compile by running 'make'. This will produce the executable 'mapper'.

Note that compilation has been tested successfully on systems with the following setups:
-Linux (Ubuntu 18.04 LTS) with version 7.5.0 of the GNU Compiler Collection.
-Windows 10 with version 5.3.0 of the GNU Compiler Collection.


********************
***** RUNNING ******
***** (small) ******
********************

The small circuits were mapped on the IBM QX2 coupling map, with latencies of 1 cycle for 1 qubit gates, 2 cycles for CX gates, and 6 cycles for swaps.

We ran the program twice: once to try to find a mapping without swaps, and a second time with swaps if that failed. For example to reproduce our results for qft_4, you would use the following two commands (since the first one fails) and add up their runtimes:

./mapper ./circuits/small/qft_4.qasm couplings/qx2.txt -defaults -latency Latency_1_2_6 -expander noSwaps
./mapper ./circuits/small/qft_4.qasm couplings/qx2.txt -defaults -latency Latency_1_2_6 -filter HashFilter -filter HashFilter2 -pureSwapDiameter

In that example, the first command results in the program aborting when it fails to map the circuit without swap gates, and the second command finds an optimal mapping (with one swap gate). An example where mapping without swaps is possible would be the 3_17_13 circuit.


********************
***** RUNNING ******
***** (large) ******
********************

The large circuits were mapped on the IBM Tokyo coupling map, with latencies of 1 cycle for 1 qubit gates, 2 cycles for CX gates, and 6 cycles for swaps.

For example to reproduce our results for qft_10, you could use the following command:

./mapper ./circuits/large/qft_10.qasm couplings/tokyo.txt -defaults -latency Latency_1_2_6 -expander GreedyTopK 10 -queue TrimSlowNodes 2000 1000 -nodeMod GreedyMapper -retain 1

This quickly produces a (non-optimal) mapping for the benchmark.


********************
***** RUNNING ******
***** (OLSQ)  ******
********************

The OLSQ circuits were mapped on the IBM QX2, Rigetti Aspen-4, 2x3, and/or 2x4 coupling maps, with latencies of 3 cycles for swaps and 1 cycle for other gates.

We ran the program twice: once to try to find a mapping without swaps, and a second time with swaps if that failed. For example to reproduce our results for mod5mils_65 on QX2, you would use the following two commands (since the first one fails) and add up their runtimes:

./mapper ./circuits/OLSQ/mod5mils_65.qasm couplings/qx2.txt -defaults -latency Latency_1_3 -expander noswaps
./mapper ./circuits/OLSQ/mod5mils_65.qasm couplings/qx2.txt -defaults -latency Latency_1_3 -filter HashFilter -filter HashFilter2 -pureSwapDiameter

In that example, the first command results in the program aborting when it fails to map the circuit without swap gates, and the second command finds an optimal mapping (with three swap gates). An example where mapping without swaps is possible would be the 16QBT_05CYC_TFL_0 circuit with the aspen4 coupling map.
