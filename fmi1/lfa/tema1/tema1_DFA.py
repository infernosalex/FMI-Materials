# Scânteie Alexandru-Ioan, grupa 151, python 3.12

import sys
import os
from sty import * # For colored text : pip install sty

def create_DFA():
    return {
        'states': set(), # Q
        'sigma': set(), # Σ
        'transitions': {}, # δ
        'start_state': None, # q0
        'final_states': set(), # F
        'strings': []
    }

def add_state(DFA, state, flags):
    DFA['states'].add(state)
    
    if "S" in flags:
        # Start state is unique
        if DFA['start_state'] is not None:
            raise ValueError("Multiple start states specified")
        DFA['start_state'] = state
    
    if "F" in flags:
        DFA['final_states'].add(state)

def add_sigma(DFA, symbol):
    DFA['sigma'].add(symbol)

def add_transition(DFA, from_state, symbol, to_state):
    # Check if the from state exists
    if from_state not in DFA['states']:
        raise ValueError(f"State {from_state} not in states list")
    
    # Check if the final states exist
    if to_state not in DFA['states']:
        raise ValueError(f"State {to_state} not in states list")
    
    # Check if the symbol is in the alphabet
    if symbol not in DFA['sigma']:
        raise ValueError(f"Symbol {symbol} not in sigma")

    if (from_state, symbol) not in DFA['transitions']:
        DFA['transitions'][(from_state, symbol)] = []
    
    # Tuple key: (from_state, symbol) -> list of to_states 
    DFA['transitions'][(from_state, symbol)].append(to_state)

def is_valid(DFA):
    if not DFA['states']:
        return False, "No states defined"
    
    if not DFA['start_state']:
        return False, "No start state defined"
    
    if not DFA['sigma']:
        return False, "No symbols defined"
    
    # Check if the transitions have length 1, if not, it's NFA
    for transition in DFA['transitions'].values():
        if len(transition) != 1:
            return False, "Transitions have more than 1 to state, this is NFA"
    
    return True, "DFA is valid"

def parse_appendix(file_path):
    DFA = create_DFA()
    current_section = None
    
    with open(file_path, 'r') as file:
        for line in file:
            # print(line.strip())
            if '#' in line:
                line = line[:line.index('#')]
            line = line.strip()
            # print(line)
            if not line:
                continue
            # print(line)

            # Select section
            if line == "States:":
                current_section = "States"
                continue
            elif line == "Sigma:":
                current_section = "Sigma"
                continue
            elif line == "Transitions:":
                current_section = "Transitions"
                continue
            elif line == "Strings:":
                current_section = "Strings"
                continue
            elif line == "End":
                current_section = None
                continue
            
            # Process line based on current section
            if current_section == "States":
                parts = line.split(',')
                state_name = parts[0]
                # Flags are just from the start and final states
                flags = parts[1:] if len(parts) > 1 else []
                add_state(DFA, state_name, flags)
            
            elif current_section == "Sigma":
                add_sigma(DFA, line)
            
            elif current_section == "Transitions":
                parts = line.split(',')
                if len(parts) == 3:
                    from_state, symbol, to_state = parts
                    add_transition(DFA, from_state, symbol, to_state)
                else:
                    raise ValueError("Invalid transition format")
            # For subtask 2
            elif current_section == "Strings":
                DFA['strings'].append(line)
    return DFA

def word_accepted(DFA, w):
    q = DFA['start_state']
    for lit in w:
        transition = DFA['transitions'].get((q, lit)) 
        if transition is None:
            return False
        q = transition[0]  
        #print(q)
    return q in DFA['final_states']

def main():
    # python3 tema1_DFA.py subtask1 task1
    # python3 tema1_DFA.py subtask2 task2
    print("Usage: python3 tema1_DFA.py subtask1 task1 or python3 tema1_DFA.py subtask2 task2")
    try:
        if sys.argv[1] == "subtask1":
            print()
            print(fg.yellow + "Subtask 1".center(100) + rs.all)
            print("-"*100)
            # Subtask 1
            # Open all files in the directory task1 and check if the appendixes are valid
            files = [f for f in os.listdir(sys.argv[2]) if os.path.isfile(os.path.join(sys.argv[2], f))]
            # print(files)
            for file in files:
                DFA = parse_appendix(os.path.join(sys.argv[2], file))
                ok, message = is_valid(DFA)
                if not ok:
                    print(fg.red + "File", file, "is not a DFA, error:", message + rs.all)
                else:
                    print(fg.green + "File", file, "is a DFA" + rs.all)
                print("-"*100)

        elif sys.argv[1] == "subtask2":
            print()
            print(fg.yellow + "Subtask 2".center(100) + rs.all)
            print("-"*100)
            # Subtask 2
            # Open all files in the directory task2 and check if the appendixes are valid and if the strings are accepted by the DFA
            files = [f for f in os.listdir(sys.argv[2]) if os.path.isfile(os.path.join(sys.argv[2], f))]
            # print(files)
            for file in files:
                DFA = parse_appendix(os.path.join(sys.argv[2], file))
                # print(DFA['strings'])
                for w in DFA['strings']:
                    if word_accepted(DFA, w):
                        print(fg.green + "File", file, "word", w, "is accepted" + rs.all)
                    else:
                        print(fg.red + "File", file, "word", w, "is not accepted" + rs.all)
                print("-"*100)
        else:
            print("Invalid subtask")
            sys.exit(1)
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
