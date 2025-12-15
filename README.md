# skip-list

## Introduction

A skip list is a probabilistic data structure that maintains a sorted collection of keys and supports searching, insertion, and deletion operations in expected logarithmic time.  
By maintaining multiple forward pointers at different levels for each node, a skip list achieves performance comparable to balanced binary search trees while being significantly simpler to implement.

This project provides a complete implementation of a skip list in the C programming language, together with automated test generation, benchmarking, correctness checking, and logging using Python scripts.


## Supported Operations

The implemented skip list supports the following operations:

- Insert(key): insert an integer key into the skip list if it does not already exist.
- Delete(key): remove an integer key from the skip list if it exists.
- Search(key): determine whether a given key is present in the skip list.

All operations are designed to run in expected $O(\log N)$ time.

## Input and Output Specification

### Input Format

Each input file consists of a sequence of operations:

- The first line contains a single integer $N$, representing the number of operations.
- Each of the following N lines contains an operation of the form:
  - `I x` : insert key `x`
  - `D x` : delete key `x`
  - `S x` : search key `x`

All keys are integers.

### Output Format

For each search operation `S x`, the program outputs one line:

- Found if `x` exists in the skip list
- NotFound otherwise

Insertion and deletion operations do not produce output.

## How to Use

### Step 1: Generate Test Cases

Run the test generator script to create random inputs.

```bash
cd benchmark
python generator.py
```

### Step 2: Compile and Evaluate

Run the evaluator script to compile the C program, execute all tests, and collect performance data.

```bash
cd benchmark
python benchmark/evaluator.py
```

### Step 3: Inspect Results

- Output files can be found under `data/output/random` and `data/output/sample`
- Evaluation logs can be found under `benchmark/log` in JSON format

## Notes

- The skip list uses a randomized strategy, so performance results are reported in expectation.
- All source code comments are written in English, as required.
- Only standard C and Python libraries are used, ensuring portability.
- The benchmarking framework is designed to be easily extensible for additional test cases or data structures.
