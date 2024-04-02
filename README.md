# Digital-Logic
 
### This program generates truth tables for digital logic circuits based on a circuit specification file. The circuit specification uses a custom language to define the inputs, outputs, and logic gates that make up the circuit.

## Implementation Details

### The program uses a linked list data structure to represent the circuit gates and their connections. Each gate is represented by a struct gate that contains information about the gate type, inputs, and outputs.

### The program reads the circuit specification file, creates the corresponding gate structures, and then generates the truth table by evaluating the circuit for each possible combination of input values.