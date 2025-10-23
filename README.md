# 8-Bit ALU in VHDL

Hardware description of an 8-bit Arithmetic Logic Unit implemented on Altera FPGA.

## Features
- 16 operations (8 arithmetic, 8 logic)
- Carry flag handling
- 7-segment HEX display output
- State machine (OpCode/Execute modes)

## Operations
**Arithmetic:** Load, Increment, Decrement, Add, Add with Carry
**Logic:** NOT, AND, OR, NAND, NOR, XOR, XNOR

## Technical Details
- Clock-driven synchronous design
- Reset functionality
- Overflow detection (9-bit result handling)

## What I Learned
- Hardware-level bit manipulation
- VHDL state machines
- FPGA synthesis and timing constraints
