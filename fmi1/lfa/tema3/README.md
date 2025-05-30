# Context-Free Grammar
## Grammar Definition

The main CFG implemented is:
```
S → aSb | ε
```
This grammar generates the language: **L(G) = {a^n b^n | n ≥ 0}**

## Tasks Implemented

### Task 1: Define a CFG (15 points)
- ✅ Programmatic representation of the CFG
- ✅ Clear definition of non-terminals, terminals, start symbol, and production rules

### Task 2: String Generator (25 points)
- ✅ Random string generation from the CFG
- ✅ Generates up to 10 strings
- ✅ Limits string length to at most 10 characters
- ✅ Uses recursive derivation with depth limits to prevent infinite loops

### Task 3: Derivation (25 points)
- ✅ Shows complete derivation steps for target strings
- ✅ Uses leftmost derivation approach
- ✅ Recursive implementation with backtracking
- ✅ Clear step-by-step output format

### Task 4: Membership Tester (25 points)
- ✅ Recognizer function that returns True/False
- ✅ Works correctly for strings up to length 12
- ✅ Two implementations:
  - Direct approach (optimized for this specific grammar)
  - General approach using derivation (works for any CFG)

### Task 5: Bonus - aⁿbⁿcⁿ (+20 bonus points)
- ✅ Recognizer for the language {aⁿbⁿcⁿ | n ≥ 1}
- ✅ Explanation of why this language is NOT context-free
- ✅ Uses pumping lemma proof in the explanation

## How to Run

```bash
python3 cfg.py
```

## Requirements

- Python 3.6+
- No external libraries required (uses only standard library)

## File Structure
```
.
├── cfg.py      # Main implementation
├── README.md            # This documentation file
└── Assignment__3___Limbaje_Formale_și_Automate.pdf  # Original assignment
```