## 🧭 Roadmap to Build a Shift-and-Add Multiplier in Logisim

---

### ✅ **Phase 1: Prerequisites (Foundational Logic)**

Make sure you're fully confident in:

1. **Binary Addition**
    
    - Understand how carry works (0+1=1, 1+1=0 with carry etc.)
        
    - 2’s complement for negative numbers
        
2. **Half Adder and Full Adder**
    
    - Know how to build them using logic gates
        
    - Connect full adders to make an **8-bit adder**
        
    - You’ve already done this — ✅
        
3. **Binary Shifting**
    
    - Learn how **left shifting** multiplies a number by 2
        
    - Get comfortable with shifting circuits using **wires and splitters**
        
4. **Basic Registers and Flip-Flops**
    
    - Learn how to **store values temporarily**
        
    - Useful for holding intermediate results like partial product and accumulator
        

---

### 🚧 **Phase 2: Learn and Build Components for Multiplier**

Now build these small pieces first:

#### 1. **AND Gate Matrix (Partial Product Generator)**

- Every bit of **multiplicand** ANDed with each bit of **multiplier**
    
- For an 8×8 multiplier: 64 AND gates
    
- Only needed in **Array Multiplier**, but useful to understand
    

✅ But for Shift-and-Add, this is optional — you mainly need a basic **AND for multiplier bit check**

#### 2. **Shift Register / Left Shift Circuit**

- Create a circuit that **left shifts the multiplicand** by 1 every cycle
    
- Can also shift the result (accumulator) if needed
    

#### 3. **Control Logic (Very Basic FSM-style thinking)**

- Check current bit of multiplier (LSB)
    
    - If it's 1: **add** multiplicand to result
        
    - If it's 0: **skip**
        
- **Shift** multiplicand left
    
- **Shift** multiplier right
    
- Loop for 8 times
    

---

### 🏗 Phase 3: Build the Shift-and-Add Multiplier in Logisim

Break it into these components:

|Block|Role|
|---|---|
|**A (Multiplicand)**|Stored in a register|
|**B (Multiplier)**|Bits are checked one-by-one|
|**Accumulator (Result)**|Stores the running result|
|**Control**|Coordinates loop (you can use a clock or step manually)|
|**Adder**|Your 8-bit adder (already made)|

You’ll need:

- 1x 8-bit adder
    
- 1x register for multiplicand
    
- 1x register for multiplier
    
- 1x result register
    
- Control mechanism to:
    
    - Check LSB of multiplier
        
    - Add if needed
        
    - Shift both registers accordingly
        

---

### 🔄 Phase 4: Testing & Iterating

1. Use **switches** for 8-bit A and B
    
2. Use **probes** for output
    
3. Test small values (e.g., 3 × 2 = 6)
    
4. Then try negative numbers using 2’s complement
    

---

### 🧠 Optional Learning (After Basic Version)

|Concept|Why Learn It|
|---|---|
|**Booth’s Algorithm**|Smarter signed multiplication|
|**Control Unit FSM**|For auto-sequencing steps|
|**Signed Overflow Handling**|To check if the result is too large|
|**Clocking and Timing**|For real-time control (using pulses)|

---

## ✅ Summary: Your Learning Steps

1. ✔️ Binary addition & 2’s complement
    
2. ✔️ Full adder chain (already done)
    
3. ✔️ Understand binary shifting
    
4. 🔄 Practice building shift and store circuits (registers)
    
5. 🔁 Learn how to check bits (ANDing multiplier LSB)
    
6. 🧠 Understand the algorithm: check → add → shift → repeat
    
7. 🛠️ Build it in Logisim using switches and probes
    
8. 🧪 Test with both positive and negative numbers
    

---

Whenever you're ready, I can give you a **step-by-step flowchart or pseudo-algorithm** for the multiplier, or help build individual pieces (like the shift circuit or control logic). Just say the word!