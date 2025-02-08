# trading-rollouts

This project implements a Monte Carlo Tree Search (MCTS) algorithm using the Message Passing Interface (MPI) for parallel processing. The goal is to efficiently simulate and evaluate multiple rollouts in a trading environment.

## Project Structure

- **Makefile**: Contains the build instructions for the project.
- **simulate.sh**: Script to run the compiled program with MPI.
- **src/**: Directory containing the source code files (`main.c`, `utils.c`).

## Building the Project

To build the project, run the following command:

```bash
make
```

## Running the Simulation

To run the simulation with a specific number of processes, use the following command:

```bash
./simulate.sh <num_processes>
```
