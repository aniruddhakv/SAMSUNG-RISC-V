# RISC-V Encoding and Spike Simulator Guide

## 3. **Running the Program in Spike Simulator**

The compiled program (`multiplication_table.o`) is executed in the Spike RISC-V simulator. The program uses the Proxy Kernel (PK) to facilitate execution.

### Commands:

1. **Run the program**:
    ```bash
    spike pk multiplication_table.o
    ```
   **Output Example:**
    ```
    Enter an integer: 4
    4 * 1 = 4
    4 * 2 = 8
    4 * 3 = 12
    ...
    4 * 10 = 40
    ```

2. **Debug with Spike:**
    ```bash
    spike -d pk multiplication_table.o
    ```
    This command enables debugging, allowing inspection of registers and program flow.

#### Debugging Example:
- Break at a specific PC (program counter):
    ```
    until pc 0x100b0
    ```
- Inspect registers or memory:
    ```
    reg a0
    ```

---

## 4. **Disassembling the Object File**

The object file is disassembled to view the assembly instructions corresponding to the compiled code. This provides insights into how the program executes at the hardware level.

### Command:
```bash
riscv64-unknown-elf-objdump -d multiplication_table.o
```

**Example Disassembly Output:**
```asm
00000000000100b0 <main>:
100b0:   0002b537                lui     a0,0x2b
100b4:   00f01113                addi    sp,sp,-64
100b8:   ...
```

---

## Tools Used
1. **Compiler**: `riscv64-unknown-elf-gcc`
2. **Simulator**: Spike (RISC-V ISA Simulator)
3. **Disassembler**: `riscv64-unknown-elf-objdump`

---

## Purpose

This task demonstrates:
1. Cross-compilation for a RISC-V architecture.
2. Using the Spike simulator for running and debugging RISC-V binaries.
3. Analyzing the low-level assembly output of a compiled program.

---

## Requirements

- RISC-V GNU Compiler Toolchain.
- Spike RISC-V Simulator.
- A Linux environment (e.g., Ubuntu).

---

## Execution Environment

The screenshots provided illustrate the task being performed in a Linux virtual machine environment, using a terminal for compiling, running, and debugging the program.

---

## Task 3: RISC-V Instruction Encoding Overview

This section provides an overview of encoding various RISC-V instructions with detailed breakdowns, binary formats, and explanations.

### 1. **ADDI sp, sp, -32**

**Explanation**
The `ADDI` instruction adds an immediate value to a register. Here, we subtract 32 from the stack pointer (`sp`).

**Breakdown**
| Field       | Value        |
|-------------|--------------|
| Opcode      | 0010011      |
| Immediate   | -32 = 11111111111111100000 (12 bits) |
| rd (sp)     | 00010        |
| rs1 (sp)    | 00010        |
| funct3      | 000          |

**Encoding Format**
| imm[11:0]       | rs1   | funct3 | rd    | opcode   |
|-----------------|--------|--------|-------|----------|
| 111111100000    | 00010  | 000    | 00010 | 0010011  |

---

### 2. **SD ra, 24(sp)**

**Explanation**
The `SD` instruction stores a doubleword from the source register (`ra`) to a memory location offset by 24 from the stack pointer (`sp`).

**Breakdown**
| Field       | Value        |
|-------------|--------------|
| Opcode      | 0100111      |
| Immediate   | 24 (split into imm[11:5] and imm[4:0]) |
| rs1 (sp)    | 00010        |
| rs2 (ra)    | 00001        |
| funct3      | 011          |

**Encoding Format**
| imm[11:5]    | rs2   | rs1   | funct3 | imm[4:0] | opcode   |
|--------------|-------|-------|--------|----------|----------|
| 0000000      | 00001 | 00010 | 011    | 11000    | 0100111  |

---

### 3. **JAL ra, 10448**

**Explanation**
The `JAL` instruction jumps to a target address relative to the current program counter (PC) and saves the return address in `ra`.

**Breakdown**
| Field          | Value       |
|----------------|-------------|
| Opcode         | 1101111     |
| Immediate      | 10448       |
| rd (ra)        | 00001       |
| imm[20|10:1|11|19:12] | Encoded |

**Encoding Format**
| imm[20] | imm[10:1]  | imm[11] | imm[19:12] | rd    | opcode   |
|---------|-------------|---------|------------|-------|----------|
| 0       | 0010100000  | 0       | 10100000   | 00001 | 1101111  |

---

### 4. **LD ra, 24(sp)**

**Explanation**
The `LD` instruction loads a doubleword from memory at an offset of 24 from the stack pointer (`sp`) into the register `ra`.

**Breakdown**
| Field       | Value        |
|-------------|--------------|
| Opcode      | 0000011      |
| Immediate   | 24           |
| rd (ra)     | 00001        |
| rs1 (sp)    | 00010        |
| funct3      | 011          |

**Encoding Format**
| imm[11:0]    | rs1   | funct3 | rd    | opcode   |
|--------------|-------|--------|-------|----------|
| 000000011000 | 00010 | 011    | 00001 | 0000011  |

---

### 5. **LW a1, 8(sp)**

**Explanation**
The `LW` instruction loads a word from memory at an offset of 8 from the stack pointer (`sp`) into the register `a1`.

**Breakdown**
| Field       | Value        |
|-------------|--------------|
| Opcode      | 0000011      |
| Immediate   | 8            |
| rd (a1)     | 01011        |
| rs1 (sp)    | 00010        |
| funct3      | 010          |

**Encoding Format**
| imm[11:0]    | rs1   | funct3 | rd    | opcode   |
|--------------|-------|--------|-------|----------|
| 000000001000 | 00010 | 010    | 01011 | 0000011  |

---

### 6. **LI a0, 0**

**Explanation**
The `LI` instruction loads an immediate value (`0`) into register `a0`.

**Breakdown**
| Field       | Value        |
|-------------|--------------|
| Opcode      | 0010011      |
| Immediate   | 0            |
| rd (a0)     | 01010        |
| rs1 (x0)    | 00000        |
| funct3      | 000          |

**Encoding Format**
| imm[11:0]    | rs1   | funct3 | rd    | opcode   |
|--------------|-------|--------|-------|----------|
| 000000000000 | 00000 | 000    | 01010 | 0010011  |

---

### 7. **LW a1, 8(sp)**

**Explanation**
The `LW` instruction loads a word from memory at an offset of 8 from the stack pointer (`sp`) into the register `a1`.

**Breakdown**
| Field       | Value        |
|-------------|--------------|
| Opcode      | 0000011      |
| Immediate   | 8            |
| rd (a1)     | 01011        |
| rs1 (sp)    | 00010        |
| funct3      | 010          |

**Encoding Format**
| imm[11:0]    | rs1   | funct3 | rd    | opcode   |
|--------------|-------|--------|-------|----------|
| 000000001000 | 00010 | 010    | 01011 | 0000011  |

---

### 8. **ADDI a0, a0, -920**

**Explanation**
The `ADDI` instruction adds an immediate value (-920) to the value in register `a0` and stores the result in `a0`.

**Breakdown**
| Field       | Value        |
|-------------|--------------|
| Opcode      | 0010011      |
| Immediate   | -920         |
| rd (a0)     | 01010        |
| rs1 (a0)    | 01010        |
| funct3      | 000          |

**Encoding Format**
| imm[11:0]    | rs1   | funct3 | rd    | opcode   |
|--------------|-------|--------|-------|----------|
| 110001101000 | 01010 | 000    | 01010 | 0010011  |

---

### 9. **SD s0, 16(sp)**

**Explanation**
The `SD` instruction stores a double-word (64-bit) value from register `s0` into memory at an offset of 16 from the stack pointer (`sp`).

**Breakdown**
| Field       | Value        |
|-------------|--------------|
| Opcode      | 0100111      |
| Immediate   | 16           |
| rs1 (sp)    | 00010        |
| rs2 (s0)    | 01000        |
| funct3      | 011          |

**Encoding Format**
| imm[11:5]    | rs2   | rs1   | funct3 | imm[4:0] | opcode   |
|--------------|-------|-------|--------|----------|----------|
| 0000001      | 01000 | 00010 | 011    | 10000    | 0100111  |

---

### 10. **LW a5, 12(sp)**

**Explanation**
The `LW` instruction loads a word from memory at an offset of 12 from the stack pointer (`sp`) into the register `a5`.

**Breakdown**
| Field       | Value        |
|-------------|--------------|
| Opcode      | 0000011      |
| Immediate   | 12           |
| rd (a5)     | 01000        |
| rs1 (sp)    | 00010        |
| funct3      | 010          |

**Encoding Format**
| imm[11:0]    | rs1   | funct3 | rd    | opcode   |
|--------------|-------|--------|-------|----------|
| 000000001100 | 00010 | 010    | 01000 | 0000011  |

---

### 11. **ADD a1, a1, a5**

**Explanation**
The `ADD` instruction adds the values in registers `a1` and `a5`, storing the result in `a1`.

**Breakdown**
| Field       | Value        |
|-------------|--------------|
| Opcode      | 0110011      |
| funct7      | 0000000      |
| rs2 (a5)    | 01000        |
| rs1 (a1)    | 01011        |
| funct3      | 000          |
| rd (a1)     | 01011        |

**Encoding Format**
| funct7       | rs2   | rs1   | funct3 | rd    | opcode   |
|--------------|-------|-------|--------|-------|----------|
| 0000000      | 01000 | 01011 | 000    | 01011 | 0110011  |
