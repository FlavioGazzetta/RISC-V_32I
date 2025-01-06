# RV32I Processor Coursework  

**Flavio Gazzetta**  

---
---

## Overview  

This project involved designing and implementing a RISC-V RV32I processor in both single-cycle and pipelined architectures. My contributions spanned from creating individual components to debugging and integrating them into functional CPUs. Below, I outline my contributions and the components developed for each architecture.

- [RV32I Processor Coursework](#rv32i-processor-coursework)
  - [Overview](#overview)
  - [Single Cycle CPU](#single-cycle-cpu)
  - [Single Cycle - Added or edited Components](#single-cycle---added-or-edited-components)
    - [Program Counter](#program-counter)
      - [Block Diagrams](#block-diagrams)
        - [Links to Module](#links-to-module)
      - [Most Relevant Commits](#most-relevant-commits)
    - [ALU](#alu)
      - [Block Diagram](#block-diagram)
      - [Link to Module](#link-to-module)
      - [Most Relevant Commits](#most-relevant-commits-1)
    - [RegFile](#regfile)
      - [Link to Module](#link-to-module-1)
      - [Most Relevant Commits](#most-relevant-commits-2)
    - [DataMemory](#datamemory)
      - [Link to Module](#link-to-module-2)
      - [Most Relevant Commits](#most-relevant-commits-3)
  - [Pipeline](#pipeline)
    - [Without hazard unit](#without-hazard-unit)
    - [With hazard unit](#with-hazard-unit)
  - [Pipeline CPU - Added or Edited Components](#pipeline-cpu---added-or-edited-components)
    - [Pipeline Registers](#pipeline-registers)
      - [Links to Modules](#links-to-modules)
      - [Most Relevant Commits](#most-relevant-commits-4)
    - [PC Register](#pc-register)
      - [Links to Modules](#links-to-modules-1)
      - [Most Relevant Commits](#most-relevant-commits-5)
    - [Control Unit](#control-unit)
        - [main Decoder main changes](#main-decoder-main-changes)
        - [ALU Decoder main changes](#alu-decoder-main-changes)
      - [Links to Modules](#links-to-modules-2)
      - [Most Relevant Commits](#most-relevant-commits-6)
    - [ALU \& Branch Unit](#alu--branch-unit)
      - [Links to Modules](#links-to-modules-3)
      - [Most Relevant Commits](#most-relevant-commits-7)
    - [Hazard Unit and Mux](#hazard-unit-and-mux)
      - [Links to Modules](#links-to-modules-4)
      - [Most Relevant Commits](#most-relevant-commits-8)
    - [JALR Mux](#jalr-mux)
      - [Links to Modules](#links-to-modules-5)
      - [Most Relevant Commits](#most-relevant-commits-9)
    - [PCMux Select](#pcmux-select)
      - [Links to Modules](#links-to-modules-6)
      - [Most Relevant Commits](#most-relevant-commits-10)
  - [Testing \& Results](#testing--results)
        - [Pipeline 5 tests](#pipeline-5-tests)
  - [Debugging Strategies](#debugging-strategies)
  - [Personal Reflection](#personal-reflection)
  - [potential improvements](#potential-improvements)
  - [Additional Comments](#additional-comments)


---
---

## Single Cycle CPU

[Jump to Relevant Single Cycle commits](#Single_Cycle-Added_or_edited_Components)

When considering the single cycle CPU, my work on it consisted of making, debugging and editing various components starting with some from Lab 4 and augmenting them in order to better fit to the more advanced CPU. Strarting with the program counter ([PC Register](rtl/pcReg.sv) and [PC Mux](rtl/pcMux.sv)) where at first I focused on trying to apply compartmentalisation and separated the add4 component with the counter itself, however, I later decided to combine the 2 into a single component allowing for simplification in debugging and in the top file. 
<img src="Pipeline/images/SC_PC.png" width="650" height="350" alt="SC_PC"> 
After that I worked on the [alu](rtl/alu.sv) where I innitially started with a 4-bit version allowing for a large range of instructions, later deciding to shrink it down to 3 bits given that this would still keep the main operations and allowed for a lot of simplification (this would then be changed back to 4 bits in the pipeline).
<img src="Pipeline/images/SC_ALU.png" width="650" height="350" alt="SC_ALU">
I then spent some time making the [register file](Pipeline/rtl/regfile.sv), which turned out to be a lot simpler than expected. A issue that I at first had with this component was that I was convinced I need a .mem file to store values which eventually I noticed not to be the case. 
<img src="Pipeline/images/SC_Register_file.png" width="650" height="350" alt="SC_Reg">
The last single-cycle component which I made very significant changes to was the [Data Memory](rtl/dataMemory.sv), which on the second attempt I got to both work and select between a byte, half word and word size.
<img src="Pipeline/images/SC_Data_Memory.png" width="650" height="350" alt="SC_Dmem">

---

---
---

<a name="Single_Cycle-Added_or_edited_Components"></a>

## Single Cycle - Added or edited Components

---

### Program Counter

The pcReg module implements a program counter (PC) register with increment and update logic:

Increment Logic:

```systemverilog
Copy code
always_comb begin
    incPC = pc + OFFSET;
end
```
This block continuously calculates the incremented PC (incPC) by adding the fixed OFFSET (in my case 4) to the current pc. It uses combinational logic to ensure incPC updates immediately whenever pc changes.

PC Update Logic:

```systemverilog
Copy code
always_ff @ (posedge clk)
    if (rst)
        pc <= 32'hBFC00000;
    else
        pc <= nextPC;
```

This block updates the pc on the positive edge of the clock. If the reset (rst) signal is active, pc is initialized to 32'hBFC00000, a common boot address. Otherwise, pc is updated to the value of nextPC, supporting jumps or branch instructions.

#### Block Diagrams

Program Counter:

<img src="Pipeline/images/ISSIE_PC.png" width="750" height="250" alt="debugging with GTK wave">

PC Register:

<img src="Pipeline/images/ISSIE_PCReg.png" width="750" height="350" alt="debugging with GTK wave">

PCMux:

<img src="Pipeline/images/ISSIE_PCMux.png" width="750" height="350" alt="debugging with GTK wave">

##### Links to Module  

[pcReg.sv](rtl/pcReg.sv)

[pcMux.sv](rtl/pcMux.sv)

#### Most Relevant Commits

1) [first version of counter](https://github.com/opnuub/Lab4/commit/66f45f5c08d823b52e3ff4d20c09211cb3410bed)

2) [first version of counter](https://github.com/opnuub/Lab4/commit/66f45f5c08d823b52e3ff4d20c09211cb3410bed)

3) [changed PCreg and top to include combinational logic inside of PC](https://github.com/opnuub/Lab4/commit/602bbcf9fe90792f2bb1aef4e45129d38d9b2730)

---

### ALU

The alu module implements an Arithmetic Logic Unit (ALU) that performs various operations based on a control signal (aluControl):

Operation Logic:

```systemverilog
always_comb begin
    case (aluControl)
        3'b000: aluResult = srcA + srcB;                         // Addition
        3'b001: aluResult = srcA - srcB;                         // Subtraction
        3'b010: aluResult = srcA & srcB;                         // Bitwise AND
        3'b011: aluResult = srcA | srcB;                         // Bitwise OR
        3'b100: aluResult = srcB;                                // Load Upper Immediate (lui)
        3'b101: aluResult = ($signed(srcA) < $signed(srcB)) ? 32'b1 : 32'b0;  // Set Less Than (signed)
        3'b110: aluResult = srcA << srcB[4:0];                   // Logical Left Shift
        3'b111: aluResult = srcA >> srcB[4:0];                   // Logical Right Shift
    endcase
end
```
This block uses a case statement to determine the ALU operation based on the 3-bit control signal aluControl. It calculates the result (aluResult) as follows:
3'b000 and 3'b001 perform addition and subtraction.
3'b010 and 3'b011 perform bitwise operations (AND and OR).
3'b100 simply outputs srcB, representing a "Load Upper Immediate" operation.
3'b101 compares the signed values of srcA and srcB and sets aluResult to 1 if srcA < srcB, otherwise 0.
3'b110 and 3'b111 perform logical shifts left and right, using the lower 5 bits of srcB to specify the shift amount.
Purpose:

#### Block Diagram

<img src="Pipeline/images/Block_DIagram_SC_ALU.png" width="1150" height="550" alt="ISSIE SC_ALU">

#### Link to Module  

[Single cycle alu.sv](rtl/alu.sv)

#### Most Relevant Commits

1) [added ALU version 1](https://github.com/opnuub/iac-riscv-cw-16/commit/fc9c426b4c8af0576de1129055d2b3582990d3de)

2) [Added mux connecting to ALU](https://github.com/opnuub/iac-riscv-cw-16/commit/56752057c5c8f5cf7abfee144f58caf270d2d0e9)

3) [updates to ALU including signed and unsigned smaller than](https://github.com/opnuub/iac-riscv-cw-16/commit/29db9d2eeab6de3a390bccd528c7f5b89459afd2)

4) [added unchanged SrcB to allow for lui](https://github.com/opnuub/iac-riscv-cw-16/commit/4e4d1629e8dce89d05d143472dde3d0a2a077e4e)

5) [changed ALU back to 3 bits](https://github.com/opnuub/iac-riscv-cw-16/commit/5a6290178d83b32d25e95a0dfc2205948b976b7c)

---

### RegFile

This module provides essential register file functionality for a CPU:

Reads: Outputs the values of two registers (rs1 and rs2) as operands for computations.
```verilog
always_comb begin
        ALUop1 = rom_array[rs1]; // Read first operand
        regOp2 = rom_array[rs2]; // Read second operand
end
```

Writes: Updates a specified register (rd) with a value (ALUout) if RegWrite is enabled. Also Continuously updates a0 to reflect the value of register x10, used for the 5 cpu tests.
```systemverilog
always_ff @(posedge clk) begin
        if (RegWrite && rd != 5'd0)
            rom_array[rd] <= ALUout;  // Write to register
        a0 <= rom_array[5'd10];
end
```

#### Link to Module 

[Single cycle regFile.sv](rtl/regFile.sv)

#### Most Relevant Commits

1) [Added RegFile version 1](https://github.com/opnuub/iac-riscv-cw-16/commit/deb3dc83c7be3d490ad1d975ee7e690f2ce03e91)

this was later changed by cole during implementation

---

### DataMemory

The dataMemory module implements a memory unit for reading and writing data in a CPU, with support for byte-addressable memory and variable data sizes.

Memory Initialization:

```systemverilog
logic [7:0] memory [2**ADDR_WIDTH-1:0];

initial begin
    $readmemh("../tb/data.hex", memory, 17'h10000);
end
```
The memory array represents a byte-addressable memory space with 2^17 locations, each 8 bits wide.
At startup, memory is initialized with data from an external file (data.hex), starting at address 0x10000.

the reason why it is 2^17 bits is because the memory is allocated in the following way:

<img src="Pipeline/images/Memory_allocation.png" width="250" height="450" alt="Memory">


Write Logic:

```systemverilog
always_ff @(posedge clk) begin
    if (MemWrite) begin
        case (SizeCtr)
            3'b010: begin
                memory[ALUResult]     <= WriteData[7:0];
                memory[ALUResult+1]   <= WriteData[15:8];
                memory[ALUResult+2]   <= WriteData[23:16];
                memory[ALUResult+3]   <= WriteData[31:24];
            end
            3'b001: begin
                memory[ALUResult]     <= WriteData[7:0];
                memory[ALUResult+1]   <= WriteData[15:8];
            end
            3'b000: begin
                memory[ALUResult]     <= WriteData[7:0];
            end
            default: ;
        endcase
    end
end
```
Writes occur on the positive edge of the clock when MemWrite is active.
The SizeCtr signal determines the size of the write:
3'b010: Writes a full word (32 bits) across 4 memory locations.
3'b001: Writes a halfword (16 bits) across 2 locations.
3'b000: Writes a single byte (8 bits).
The memory address is specified by ALUResult.
Read Logic:

```systemverilog
always_comb begin
    case (SizeCtr)
        3'b010: begin
            ReadData = {memory[ALUResult+3], memory[ALUResult+2], memory[ALUResult+1], memory[ALUResult]};
        end
        3'b001: begin
            ReadData = {{16{memory[ALUResult+1][7]}}, memory[ALUResult+1], memory[ALUResult]};
        end
        3'b000: begin
            ReadData = {{24{memory[ALUResult][7]}}, memory[ALUResult]};
        end
        3'b100: begin
            ReadData = {24'b0, memory[ALUResult]};
        end
        3'b101: begin
            ReadData = {16'b0, memory[ALUResult+1], memory[ALUResult]};
        end
        default: ReadData = 32'b0;
    endcase
end
```
The always_comb block reads data based on the SizeCtr signal:
3'b010: Reads a full word (32 bits) from 4 memory locations.
3'b001: Reads a halfword (16 bits) with sign extension from 2 locations.
3'b000: Reads a single byte (8 bits) with sign extension.
3'b100 and 3'b101: Perform unsigned reads of 1 byte and 2 bytes, respectively.
Sign extension fills higher bits with the most significant bit of the data if signed, or with zeros if unsigned.

#### Link to Module

[Single cycle dataMemory.sv](rtl/dataMemory.sv)

#### Most Relevant Commits

1) [Data memory](https://github.com/opnuub/iac-riscv-cw-16/commit/ddabfb75227940ec05f503a63af4c198829b5f99)

---
---

## Pipeline

[Jump to Relevant Pipeline commits](#Pipeline-Added_or_Edited_Components)

### Without hazard unit

<img src="Pipeline/images/no_hazard_pipeline.png" width="950" height="550" alt="Pipeline 5 stages passed">

For the Pipeline CPU I made various changes both to separate the stages Fetch, Decode, Execute, Memory and WriteBack, and to various components in order to adjust them to these stages. First of all I added 4 regsters to separate the stages [Fetch -> Decode](Pipeline/rtl/PRegFetch.sv), [Decode -> Execute](Pipeline/rtl/PRegDecode.sv), [Execute -> Memory](Pipeline/rtl/PRegExecute.sv), [Memory -> WriteBack](Pipeline/rtl/PRegMemory.sv). Initially these only took the inputs from one stage and passed them to the next after a clock tick, at first here I thought it would be a good idea to give these registers a memory, but later I decide to make them act like 32-bit flip flops. After having made these I edited the [control unit](Pipeline/rtl/controlUnit.sv) (specifically making changes in the [aluDecoder.sv](Pipeline/rtl/aluDecoder.sv) and the [mainDecoder.sv](Pipeline/rtl/mainDecoder.sv)) and added outputs including JumpD to decide when I would Jump, BranchD to decide when I would Branch, I then used the component [PCMuxSelect](Pipeline/rtl/mainDecoder.sv) to AND the zeroE output of the [Branch Unit](Pipeline/rtl/branchUnit.sv) with JumpE (JumpD output after passing through the Decode -> Execute stage), and then OR'ed the output of this AND gate with BranchE. I removed the PCsrc Output and then changed my ResultSrc output from 1 to 2 bits, this is because I wanted the [result Mux](Pipeline/rtl/resultMux.sv) (register in the in the writeback stage of the alu) to select between 3 values (where I made the 4th input be a default 00 as this would never be used). The reason for now using a 4 input mux was that i combined 2 muxes from the single-cycle stage (resultMux and JumpMux) to better follow the schematic given to us and to keep everything as compact as possible. I also changed ALUControl from 3 to 4 bits, this change was made in order to allow the [alu](Pipeline/rtl/alu.sv) and [Branch Unit](Pipeline/rtl/branchUnit.sv) to act separately, as with 3 bits their operations would overlap in the same stage and lead to errors. Hence, due to this change in ALUControl I changed the bit allocation in the [Branch Unit](Pipeline/rtl/branchUnit.sv) and [alu](Pipeline/rtl/alu.sv) (adding a 1 as MSB for the [Branch Unit](Pipeline/rtl/branchUnit.sv) and a 0 for the [alu](Pipeline/rtl/alu.sv)). I also added a Jalrsrc output to act as a select bit for a [Jalr Mux](Pipeline/rtl/JalrMux.sv) located in the execute stage which would select between the last program counter value or the last register1 value to be passed into the [extend PC component](Pipeline/rtl/extendPC.sv) component which would add the immediate value in the execute stage with the value passed on by the [Jalr Mux](Pipeline/rtl/JalrMux.sv), with the ouput of this component being the other input in the [PC Register](Pipeline/rtl/pcReg.sv). 

<a name="Hazard_Unit_description"></a>

### With hazard unit 

<img src="Pipeline/images/Full_Pipeline_CPU.png" width="850" height="550" alt="Pipeline 5 stages passed">

Of course, even with all these changes (and other minor ones) the cpu could still not pass any of the 5 tests given to us, this was because I was yet to add the [Hazard Unit](Pipeline/rtl/HazardUnit.sv) and related [HazardMux'es](Pipeline/rtl/HazardMux.sv). I made the [Hazard Unit](Pipeline/rtl/HazardUnit.sv) able to perform 3 different types of actions: Flushing (uses outputs FlushD and FlushE to set all the outputs of the [Fetch -> Decode](Pipeline/rtl/PRegFetch.sv) and [Decode -> Execute](Pipeline/rtl/PRegDecode.sv) registers to 0), Stalling (uses the ouput stall to prevent the values in the [PC Register](Pipeline/rtl/pcReg.sv) and [Fetch -> Decode](Pipeline/rtl/PRegFetch.sv) registers to pass on to the next ones) and Forwarding (uses the ouputs ForwardAE and ForwardBE to select between the value of register1 and register2 ouputs of the [register file](Pipeline/rtl/regfile.sv) in the execute stage, the value of the aluresult in the memory stage and the value of the result which is in the writeback stage and ). In my HazardUnit code, forwarding, stalling, and flushing are implemented to resolve hazards as follows:

Forwarding resolves data hazards by bypassing results from later stages (Memory or Writeback) to the Execute stage. For Source A (ForwardAE), the logic is as follows:

```systemverilog
if (RegWriteM && (destReg_m != 0) && (destReg_m == Rs1E)) begin
    ForwardAE = 2'b10;  // Forward from Memory stage
end else if (RegWriteW && (destReg_w != 0) && (destReg_w == Rs1E)) begin
    ForwardAE = 2'b01;  // Forward from Writeback stage
end else begin
    ForwardAE = 2'b00;  // No forwarding
end
```

Similarly, ForwardBE handles forwarding for Source B by checking Rs2E. This ensures the [alu](Pipeline/rtl/alu.sv) in the Execute stage receives up-to-date data directly from the pipeline. Stalling resolves load-use hazards, where an instruction requires data from a load still in the Memory stage. If a load instruction in the Execute stage (memoryRead_e) has a destination register (RdE) that matches either source register in the Decode stage (Rs1D or Rs2D), the pipeline is stalled as follows:
```systemverilog
if (memoryRead_e && ((RdE == Rs1D) || (RdE == Rs2D))) begin
    stall = 1'b1;
end else begin
    stall = 1'b0;
end
```
When stall is asserted, the Fetch and Decode stages are frozen, and the Execute stage is cleared using:
```systemverilog
if (stall) begin
    FlushE = 1'b1;  // Clear Execute stage to avoid incorrect operation
end
```
Flushing resolves control hazards (e.g., branches or jumps) by discarding incorrect instructions fetched after a mispredicted branch or jump. If a branch condition (zero_hazard) or jump (jump_hazard) is detected, flushing is applied as follows:
```systemverilog
if (zero_hazard || jump_hazard) begin
    FlushD = 1'b1;  // Clear Decode stage
    FlushE = 1'b1;  // Clear Execute stage
end
```
This ensures any incorrectly fetched instructions are removed. 

In order to implement flush and stall I also changed the registers between [Fetch -> Decode](Pipeline/rtl/PRegFetch.sv) and [Decode -> Execute](Pipeline/rtl/PRegDecode.sv), only allowing the values to pass from Fetch to Decode when stall = 0 is high and making all outputs of <= 0 when FlushD and FlushE respectivley.

---

<a name="Pipeline-Added_or_Edited_Components"></a>

## Pipeline CPU - Added or Edited Components

---

### Pipeline Registers

1) PRegFetch
Purpose: Transfers instruction and program counter values from Fetch (F) to Decode (D).
Key Behavior:
```systemverilog
if (rst || Flush) begin
    Outputs_D <= 0;
end else if (!stall) begin
    Outputs_D <= Inputs_F;
end
```
2) PRegDecode
Purpose: Passes register values, immediate data, and control signals from Decode (D) to Execute (E).
Key Behavior:
```systemverilog
if (rst || Flush) begin
    Outputs_E <= 0;
end else begin
    Outputs_E <= Inputs_D;
end
```
3) PRegExecute
Purpose: Transfers ALU results, write data, and control signals from Execute (E) to Memory (M).
Key Behavior:
```systemverilog
if (rst) begin
    Outputs_M <= 0;
end else begin
    Outputs_M <= Inputs_E;
end
```
4) PRegMemory
Purpose: Transfers memory results and control signals from Memory (M) to Write-back (W).
Key Behavior:
```systemverilog
if (rst) begin
    Outputs_W <= 0;
end else begin
    Outputs_W <= Inputs_M;
end
```

#### Links to Modules

[Pipeline PRegFetch.sv](Pipeline/rtl/PRegFetch.sv)

[Pipeline PRegDecode.sv](Pipeline/rtl/PRegDecode.sv)

[Pipeline PRegExecute.sv](Pipeline/rtl/PRegExecute.sv)

[Pipeline PRegMemory.sv](Pipeline/rtl/PRegMemory.sv)

#### Most Relevant Commits

1) [Improved Pipeline Registers](https://github.com/opnuub/iac-riscv-cw-16/commit/72aea873a82f6d3353513419fee9e28bb456142d)

---

### PC Register

Only change from single cycle to be noted is that now the pc value would only update if stall is low.

#### Links to Modules

[Pipeline pcReg.sv](Pipeline/rtl/pcReg.sv)

#### Most Relevant Commits

1) [added stall input and logic to PC Register](https://github.com/opnuub/iac-riscv-cw-16/commit/e0d78c7d70b8c6f9d52549edf97012f398580148#diff-4a14945f50d25a4a73dbddafd3a27787d927da7f30fc6a6f8f0f3b4974b420f2)

---

### Control Unit

##### main Decoder main changes

Added sizeSrc for Load/Store Instructions
Specifies the size of data (byte, halfword, word) based on funct3.

```systemverilog

output  logic [2:0] sizeSrc; // Size control for load/store instructions

case (funct3)
    3'b000: sizeSrc = 3'b000; // Byte
    3'b001: sizeSrc = 3'b001; // Halfword
    3'b010: sizeSrc = 3'b010; // Word
endcase
```
Expanded resultSrc to 2 Bits
Allows distinction between ALU (00), memory (01), and PC (10) results.

```systemverilog
output  logic [1:0] resultSrc; // Expanded to 2 bits
```
Added Separate Branch Signal
Differentiates branch determination from pcSrc.

```systemverilog
output logic Branch; // Indicates branch instruction
```

Branch = 1; // Set for branch instructions
Explicit Handling for funct3 in Load/Store
Decodes funct3 for load/store size control.

```systemverilog
case (funct3)
    3'b000: sizeSrc = 3'b000; // Load Byte
    3'b001: sizeSrc = 3'b001; // Load Halfword
    3'b010: sizeSrc = 3'b010; // Load Word
endcase
```

##### ALU Decoder main changes

Increased the width of aluControl to 4 bits for additional operations.
```systemverilog
// Original:
output  logic [2:0] aluControl;

// New:
output  logic [3:0] aluControl;
```

Added explicit handling for branch operations (aluOp = 2'b01).
```systemverilog
2'b01: begin
    case (funct3)
        3'b000: aluControl = 4'b1000; // beq
        3'b001: aluControl = 4'b1001; // bne
        3'b100: aluControl = 4'b1100; // blt
        3'b101: aluControl = 4'b1101; // bge
        3'b110: aluControl = 4'b1110; // bltu
        3'b111: aluControl = 4'b1111; // bgeu
        default: aluControl = 4'b0000; // Default to add
    endcase
end
```
Expanded the set of ALU operations, including li, xor, and additional R-type instructions.

```systemverilog
2'b10: begin
    case (funct3)
        3'b000: aluControl = (opfunct7 == 2'b11) ? 4'b0001 : 4'b0000; // sub/add
        3'b001: aluControl = 4'b0110; // sll
        3'b010: aluControl = 4'b0101; // slt
        3'b011: aluControl = 4'b0100; // li
        3'b100: aluControl = 4'b0010; // xor
        3'b101: aluControl = 4'b0111; // srl
        3'b110: aluControl = 4'b0011; // or
        3'b111: aluControl = 4'b0010; // and
        default: aluControl = 4'b0000; // Default to add
    endcase
end
```

#### Links to Modules

[Pipeline controlUnit.sv](Pipeline/rtl/controlUnit.sv)

[Pipeline aluDecoder.sv](Pipeline/rtl/aluDecoder.sv)

[Pipeline mainDecoder.sv](Pipeline/rtl/mainDecoder.sv)

#### Most Relevant Commits

1) [Improved Pipeline Registers](https://github.com/opnuub/iac-riscv-cw-16/commit/72aea873a82f6d3353513419fee9e28bb456142d)

---

### ALU & Branch Unit

The change I made here was that I made the inputs of ALUControl for the alu and for the branch unit 4 bits instead of 3, this was in order to avoid overlapping of instructions between alu and branch unit.

#### Links to Modules

[Pipeline alu.sv](Pipeline/rtl/alu.sv)

[Pipeline branchUnit.sv](Pipeline/rtl/branchUnit.sv)

#### Most Relevant Commits

1) [ALU and Branch Unit back to 4 bits](https://github.com/opnuub/iac-riscv-cw-16/commit/85c43cbd421743b3bdd7a0dee47591ee72d02baa)

---

### Hazard Unit and Mux

The Hazard Unit is responsible of making sure to perform forwarding, stalling and flushing. The description of both this and its relevant muxes can be found [above](#Hazard_Unit_description).

#### Links to Modules

[Pipeline HazardUnit.sv](Pipeline/rtl/HazardUnit.sv)

[Pipeline HazardMux.sv](Pipeline/rtl/HazardMux.sv)

#### Most Relevant Commits

1) [Initial completion of Hazard Unit](https://github.com/opnuub/iac-riscv-cw-16/commit/e0d78c7d70b8c6f9d52549edf97012f398580148)


2) [Completed Hazard Unit and Hazard Muxes For integration ](https://github.com/opnuub/iac-riscv-cw-16/commit/d50856a378adf044793459dd35e9c20bbe420e27#diff-f2270990438d4fe624dded4421d87faf3af562e371a59e28e0ed97eccde2a080)

---

### JALR Mux

The role of this mux is to select between the value of PCe (program counter in execute stage) and RD1E (register 1 output in execute stage) to be added with the immediate value and become one of the inputs of the pcMux.

#### Links to Modules

[Pipeline JalrMux.sv](Pipeline/rtl/JalrMux.sv)

#### Most Relevant Commits

1) [Implementation of Jalr instruction using a separate mux to pass test 4](https://github.com/opnuub/iac-riscv-cw-16/commit/aa623c2f9ed204c58805c8cf299f0bddc0a6dc05)

---

### PCMux Select

This component took three 1-bit inputs (JumpE, BranchE and zero) and performe boolean operations (JumpE | (BranchE & zero)) on them to decide wether or not a branch/jump operation should be performed.

#### Links to Modules

[Pipeline PCMuxSelect.sv](Pipeline/rtl/PCMuxSelect.sv)

#### Most Relevant Commits

1) [added PCMuxSelect](https://github.com/opnuub/iac-riscv-cw-16/commit/8b46618a579c4afabefadc15f6fbddc0e15df24d)

---

After having added all these features and having done a lot of debugging I tested the 5 cpu tests and got the following results:

## Testing & Results

##### Pipeline 5 tests

<img src="Pipeline/images/Pipelined_all_5_tests_pass_proof.png" width="550" height="550" alt="Pipeline 5 stages passed">
 
---
---

## Debugging Strategies

During my time working on the project, I found that a very large percentage of the workload was dedicated to finding and fixing errors. For this, I found two very useful strategies: displaying outputs and displaying signals on GTKWave. Displaying outputs was the first strategy I used, as it allowed for an instant and simple visualization of various signals. Its advantage was that it was really easy to set up, enabling the display of input, output, and intermediate signals.

<img src="Pipeline/images/Display_output.png" width="650" height="450" alt="debugging with displays">

However, this strategy had a significant limitation: the terminal had a limit on the amount of information it could display at once. This led me to switch to GTKWave, which turned out to be an almost perfect solution. It allowed me to visualize a large number of signals simultaneously, with the minor drawback that these signals had to be outputs of the top file. This required the slightly tedious process of temporarily making each signal an output. Ultimately, though, it provided a very straightforward debugging process without any limitations.

the simulation from GTKWave looked like this (image from debugging test 5 errors in pipeline)

<img src="Pipeline/images/GTKWave.png" width="1150" height="450" alt="debugging with GTK wave">

---
---

## Personal Reflection

Every moment I spent working on this project has shown me how much of a profoundly rewarding experience this has been, one that reminded me of why I chose to pursue EIE in the first place. Despite the challenges, endless debugging sessions and a cascade of errors, I found myself fixated on the light at the end of the tunnel. Every step forward, no matter how small, reinforced my determination.

The joy of overcoming those hurdles and seeing a system I meticulously designed come to life is unparalleled. From crafting the ALU, Register File, Program Counter, and Data Memory for the single-cycle CPU to designing, editing, and integrating components into a fully functional five-stage pipelined CPU, this project tested my technical and problem-solving skills like never before.

In the end, the satisfaction of completing something so well-structured and functionally robust has reaffirmed my passion for engineering. It’s moments like these that make the challenges worthwhile and strengthen my belief that this path is where I belong.

---

## potential improvements

When thinking about potential improvements to this CPU the things that come to mind are:
- I could have added more intructions, such as arithmetic shifts and much more. 
- Another interesting feature would have been Dynamic Branch Prediction:
- Introducing out-of-order execution to allow instructions to be executed as resources become available would have sped up the compile time by a lot, rather than strictly in program order.

---

## Additional Comments 

I’d like to thank my teammates Michael, Cole, and Soon Yung for their incredible teamwork throughout this project. I believe we all worked exceptionally well together, combining our strengths and supporting one another to achieve something truly impressive. It’s been an absolute pleasure collaborating with them!
