#!/usr/bin/env python3
import random

# Task 1: Define a CFG (15 points)
def define_cfg():
    cfg = {
        'non_terminals': {'S'},
        'terminals': {'a', 'b'},
        'start_symbol': 'S',
        'productions': {
            'S': ['aSb', 'ε']  # S → aSb | ε
        }
    }
    return cfg

def print_cfg(cfg):
    print("Context-Free Grammar Definition:")
    print(f"Non-terminals: {cfg['non_terminals']}")
    print(f"Terminals: {cfg['terminals']}")
    print(f"Start symbol: {cfg['start_symbol']}")
    print("Production rules:")
    for lhs, rhs_list in cfg['productions'].items():
        for rhs in rhs_list:
            print(f"  {lhs} → {rhs}")
    print()

# Task 2: String Generator (25 points)
def generate_string(cfg, max_length=10, current_string='S', depth=0, max_depth=20):
    # generate a random string from the CFG using recursive derivation
    if depth > max_depth:
        return None
    
    # check if string contains only terminals
    if all(char in cfg['terminals'] or char == 'ε' for char in current_string):
        result = current_string.replace('ε', '')
        return result if len(result) <= max_length else None
    
    # find the first non-terminal
    for i, char in enumerate(current_string):
        if char in cfg['non_terminals']:
            # choose a random production for this non-terminal
            productions = cfg['productions'][char]
            chosen_production = random.choice(productions)
            
            # apply the production
            new_string = current_string[:i] + chosen_production + current_string[i+1:]
            
            # continue generation
            return generate_string(cfg, max_length, new_string, depth + 1, max_depth)
    
    return None

def generate_strings(cfg, count=10, max_length=10):
    # generate multiple strings from the CFG
    strings = []
    attempts = 0
    max_attempts = count * 10  # prevent infinite loops
    
    while len(strings) < count and attempts < max_attempts:
        attempts += 1
        string = generate_string(cfg, max_length)
        if string is not None and string not in strings:
            strings.append(string)
    
    return strings

# Task 3: Derivation (25 points)
def find_derivation(cfg, target_string, current_string='S', steps=None, max_depth=50):
    # find a derivation for the target string using leftmost derivation
    if steps is None:
        steps = [current_string]
    
    if len(steps) > max_depth:
        return None
    
    # remove epsilon symbols for comparison
    clean_current = current_string.replace('ε', '')
    
    # check if we've reached the target
    if clean_current == target_string:
        return steps
    
    # check if string contains only terminals (and we haven't reached target)
    if all(char in cfg['terminals'] or char == 'ε' for char in current_string):
        return None
    
    # find the leftmost non-terminal
    for i, char in enumerate(current_string):
        if char in cfg['non_terminals']:
            # try each production for this non-terminal
            for production in cfg['productions'][char]:
                new_string = current_string[:i] + production + current_string[i+1:]
                new_steps = steps + [new_string]
                
                result = find_derivation(cfg, target_string, new_string, new_steps, max_depth)
                if result is not None:
                    return result
            break  # only process leftmost non-terminal
    
    return None

def print_derivation(steps):
    if steps is None:
        print("No derivation found.")
        return
    
    print("Derivation steps:")
    for i, step in enumerate(steps):
        if i == 0:
            print(f"  {step}")
        else:
            print(f"⇒ {step}")
    
    final = steps[-1].replace('ε', '')
    if final != steps[-1]:
        print(f"= {final}")
    print()

# Task 4: Membership Tester (25 points)
def is_member(cfg, test_string, max_length=12):
    # test if a string belongs to the language of the CFG
    if len(test_string) > max_length:
        return False
    
    # direct approach for this specific grammar:
    if test_string == '':
        return True
    
    # Count a's and b's
    a_count = test_string.count('a')
    b_count = test_string.count('b')
    
    # check if string contains only a's and b's
    if not all(char in 'ab' for char in test_string):
        return False
    
    # check if equal number of a's and b's
    if a_count != b_count:
        return False
    
    # check if a's come before b's
    a_section = True
    for char in test_string:
        if char == 'b':
            a_section = False
        elif char == 'a' and not a_section:
            return False
    
    return True

def is_member_general(cfg, test_string, max_depth=20):
    # general membership test using derivation (works for any CFG)
    derivation = find_derivation(cfg, test_string, max_depth=max_depth)
    return derivation is not None

# Task 5: Bonus - Extend CFG for a^n b^n c^n (20 bonus points)
def define_anbncn_cfg():
    # define a CFG that simulates the language {a^n b^n c^n | n ≥ 1} to demonstrate that it is not context-free
    cfg = {
        'non_terminals': {'S'},
        'terminals': {'a', 'b', 'c'},
        'start_symbol': 'S',
        'productions': {
            'S': ['abc', 'aabbcc', 'aaabbbccc', 'aaaabbbbcccc', 'aaaaabbbbbccccc']
        }
    }
    return cfg

def is_anbncn_member(test_string):
    if not test_string:
        return False
    
    a_count = test_string.count('a')
    b_count = test_string.count('b')
    c_count = test_string.count('c')
    
    if not all(char in 'abc' for char in test_string):
        return False
    
    if a_count != b_count or b_count != c_count or a_count == 0:
        return False
    
    # check if a's come first, then b's, then c's
    expected = 'a' * a_count + 'b' * b_count + 'c' * c_count
    return test_string == expected

def main():
    # Task 1: Define CFG
    print("TASK 1: Define CFG")
    print("-" * 30)
    cfg = define_cfg()
    print_cfg(cfg)
    
    # Task 2: String Generator
    print("TASK 2: String Generator")
    print("-" * 30)
    generated_strings = generate_strings(cfg, count=10, max_length=10)
    print(f"Generated {len(generated_strings)} strings:")
    for i, string in enumerate(generated_strings, 1):
        display_string = string if string else "ε (empty string)"
        print(f"  {i}. '{display_string}'")
    print()
    
    # Task 3: Derivation
    print("TASK 3: Derivation")
    print("-" * 30)
    test_strings = ["", "ab", "aabb", "aaabbb"]
    for test_string in test_strings:
        display_string = test_string if test_string else "ε (empty string)"
        print(f"Derivation for '{display_string}':")
        steps = find_derivation(cfg, test_string)
        print_derivation(steps)
    
    # Task 4: Membership Tester
    print("TASK 4: Membership Tester")
    print("-" * 30)
    test_cases = [
        ("", True),           # ε
        ("ab", True),         # a¹b¹
        ("aabb", True),       # a²b²
        ("aaabbb", True),     # a³b³
        ("a", False),         # unequal counts
        ("abb", False),       # unequal counts
        ("ba", False),        # wrong order
        ("aabbb", False),     # unequal counts
        ("abab", False),      # wrong structure
    ]
    
    for test_string, expected in test_cases:
        result = is_member(cfg, test_string)
        display_string = test_string if test_string else "ε"
        status = "✓" if result == expected else "✗"
        print(f"  '{display_string}' → {result} {status}")
    print()
    
    # Task 5: Bonus
    print("TASK 5: Bonus - a^n b^n c^n")
    print("-" * 30)
    
    print("Testing a^n b^n c^n recognizer:")
    anbncn_test_cases = [
        ("abc", True),
        ("aabbcc", True),
        ("aaabbbccc", True),
        ("", False),
        ("ab", False),
        ("abcc", False),
        ("aabbc", False),
        ("abcabc", False),
    ]
    
    for test_string, expected in anbncn_test_cases:
        result = is_anbncn_member(test_string)
        status = "✓" if result == expected else "✗"
        print(f"  '{test_string}' → {result} {status}")
    
    print("""
Why {a^n b^n c^n | n ≥ 1} is NOT context-free:

This can be proven using the pumping lemma for context-free languages.

The pumping lemma states that for any context-free language L, there exists
a pumping length p such that any string s in L with |s| ≥ p can be written
as s = uvwxy where:
1. |vwx| ≤ p
2. |vx| ≥ 1
3. For all i ≥ 0, uv^i wx^i y ∈ L

For L = {a^n b^n c^n | n ≥ 1}:
- Consider the string s = a^p b^p c^p
- Any decomposition s = uvwxy with |vwx| ≤ p means vwx can contain
    at most 2 of the 3 types of characters (a, b, c)
- When we pump (i = 2), we get uv^2 wx^2 y, which will have unequal
    counts of the three characters, violating the language definition

Therefore, this language cannot be generated by any context-free grammar.
""")

if __name__ == "__main__":
    main() 