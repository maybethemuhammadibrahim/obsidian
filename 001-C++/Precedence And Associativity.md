In C++, expressions with multiple operators are evaluated based on two key rules:
https://en.cppreference.com/w/cpp/language/operator_precedence

1. **Operator Precedence** (which operator comes first)
2. **Associativity** (when operators have the same precedence)

## How It Works:

### 1. Operator Precedence (Higher precedence evaluates first)
```cpp
int result = 2 + 3 * 4; 
// * has higher precedence than +, so evaluates to 2 + (3 * 4) = 14
// Not (2 + 3) * 4 = 20
```

### 2. Associativity (When precedence is equal)
```cpp
int x = 5 - 3 - 1; 
// - is left-associative, so (5 - 3) - 1 = 1
// Not 5 - (3 - 1) = 3

int y = a = b = c; 
// = is right-associative, so a = (b = c)
```

## Key Examples:

### Left-Associative Operators (evaluate left-to-right)
```cpp
cout << a << b << c;  // (((cout << a) << b) << c)
a + b + c;            // (a + b) + c
```

### Right-Associative Operators (evaluate right-to-left)
```cpp
x = y = z;            // x = (y = z)
*p++;                 // *(p++) not (*p)++
```

## Special Cases:

1. **Function Calls**: `f()()` is left-associative → `(f())()`
2. **Array Access**: `a[b][c]` is left-associative → `(a[b])[c]`
3. **Member Access**: `a->b->c` is left-associative → `(a->b)->c`

## Important Notes:

1. You cannot change an operator's associativity when overloading it
2. Parentheses `()` always override both precedence and associativity
3. The order of evaluation of operands is separate from precedence/associativity (except for `&&`, `||`, `?:`, and `,`)

