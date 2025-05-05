### 🔹 Rules

1. Most existing C++ operators can be overloaded.
    
2. **Cannot overload**: `?:`, `sizeof`, `::`, `.`, `.*`, `typeid`, cast operators.
    
3. You cannot create new operators or rename existing ones.(e.g **)
    
4. At least **one operand must be a user-defined type**.
    
5. You **cannot change** the number of operands an operator takes.
    

---

## 🔸 Commonly Overloaded Operators

|Operator|Description|Typical Use|
|---|---|---|
|`+`|Addition|Math, String Concatenation|
|`-`|Subtraction|Math|
|`*`|Multiplication|Math, Scalar Product|
|`/`|Division|Math|
|`==`|Equality|Comparisons|
|`!=`|Inequality|Comparisons|
|`<`, `>`|Less than, greater than|Comparisons|
|`<=`, `>=`|Less/greater than or equal|Comparisons|
|`++`|Increment (Prefix/Postfix)|Iteration, Counters|
|`--`|Decrement (Prefix/Postfix)|Iteration, Counters|
|`<<`, `>>`|Stream Insertion/Extraction|I/O|
|`=`|Assignment|Deep copy|
|`!`, `&&`, `||`|

---

## 🔸 Different Ways to Overload Operators

A general rule:

- **Unary operators** → member functions.
    
- **Binary operators** → friend/non-member functions (if left-hand operand is not the object itself).
    

---

### ✅ 1. Member Function Overloading

**Syntax**:

```cpp
returnType operatorOP(arguments) const {
    // ...
}
```

**Commonly used for**:

- Unary operators: `++`, `--`, `-`, `!`
    
- Binary when left-hand side is the object: `+`, `-`, `*`, etc.
    

#### Example: Overloading `+` for object + int

```cpp
class Cents {
private:
    int m_cents;
public:
    Cents(int cents) : m_cents{ cents } {}
    Cents operator+(int value) const {
        return Cents{ m_cents + value };
    }
    int getCents() const { return m_cents; }
};
```

#### Example: Prefix and Postfix `++` (With Explanation Included)
```cpp
#include <iostream>
using namespace std;

class Check
{
private:
    int i;

public:
    Check() : i(0) {}

    Check operator++()
    {
        Check temp;
        temp.i = ++i;

        return temp;
    }
    Check operator++(int)
    {
        Check temp;

        temp.i = i++;

        return temp;
    }

    void Display()
    {
        cout << "i = " << i << endl;
    }
};

int main()
{
    Check obj, obj1;
    obj.Display();
    obj1.Display();

    obj1 = obj++;
    

    obj.Display();
    obj1.Display();

    return 0;
}
```

```cpp
#include <iostream>

class Mango {
private:
    float price;

public:
    Mango(float p) : price(p) {}

    // Getter function to access price (needed since it's private)
    float getPrice() const { return price; }

    // Setter function to modify price
    void setPrice(float p) { price = p; }

    // Friend declarations for global operator overloading
    friend Mango& operator--(Mango& m);       // Prefix --
    friend Mango operator--(Mango& m, int);   // Postfix --
};

// Prefix -- (returns modified object by reference)
Mango& operator--(Mango& m) {
    m.setPrice(m.getPrice() - 100);
    return m;
}

// Postfix -- (returns old value by value)
Mango operator--(Mango& m, int) {
    Mango temp = m;          // Save original state
    m.setPrice(m.getPrice() - 100);  // Modify the object
    return temp;            // Return original state
}

int main() {
    Mango mango(500.0f);

    // Test prefix --
    std::cout << "Original price: " << mango.getPrice() << "\n";
    Mango newMango = --mango;
    std::cout << "After prefix --: " << mango.getPrice() << "\n";
    std::cout << "Returned value: " << newMango.getPrice() << "\n\n";

    // Test postfix --
    mango.setPrice(500.0f);  // Reset price
    std::cout << "Original price: " << mango.getPrice() << "\n";
    Mango oldMango = mango--;
    std::cout << "After postfix --: " << mango.getPrice() << "\n";
    std::cout << "Returned value: " << oldMango.getPrice() << "\n";

    return 0;
}
```
## 🔸 Prefix vs Postfix Recap

|Aspect|Prefix (`++x`)|Postfix (`x++`)|
|---|---|---|
|Syntax|`operator++()`|`operator++(int)`|
|Return Type|Usually reference|Usually by value|
|Efficiency|More efficient|Less efficient (creates temp)|
|Code Reuse|Base logic|Often calls prefix logic|

---

### ✅ 2. Friend Function Overloading

**Syntax**:

```cpp
friend returnType operatorOP(const ClassName& lhs, const ClassName& rhs);
```

**Commonly used for**:

- Binary operators: `+`, `-`, `==`, `!=`, `<`, `>`
    
- Stream I/O operators `<<` and `>>`
    

#### Example: Overloading `+` (Cents + Cents)

```cpp
friend Cents operator+(const Cents& c1, const Cents& c2){
  // use the Cents constructor and operator+(int, int)
  // we can access m_cents directly because this is a friend function
  return { c1.m_cents + c2.m_cents };
}
```

#### Example: Stream Insertion/Extraction

```cpp
friend ostream& operator<<(ostream& output, const Distance& D){ 
         output << "F : " << D.feet << " I : " << D.inches;
         return output;            
      }
friend istream& operator>>(istream& input, Distance& D){ 
         input >> D.feet >> D.inches;
         return input;            
      }
```

#### Example: Comparison Operators (`==`, `!=`, `<`, `>`, `<=`, `>=`)

```cpp
friend bool operator==(const Cents& c1, const Cents& c2);
friend bool operator!=(const Cents& c1, const Cents& c2);
```

##### A simple program to compare two objects
```cpp
#include <iostream>

class Cents
{
private:
    int m_cents;

public:
    Cents(int cents)
        : m_cents{ cents }
    {}

    friend bool operator== (const Cents& c1, const Cents& c2) { return c1.m_cents == c2.m_cents; }
    friend bool operator!= (const Cents& c1, const Cents& c2) { return !(operator==(c1, c2)); }

    friend bool operator< (const Cents& c1, const Cents& c2) { return c1.m_cents < c2.m_cents; }
    friend bool operator> (const Cents& c1, const Cents& c2) { return operator<(c2, c1); }

    friend bool operator<= (const Cents& c1, const Cents& c2) { return !(operator>(c1, c2)); }
    friend bool operator>= (const Cents& c1, const Cents& c2) { return !(operator<(c1, c2)); }

};

int main()
{
    Cents dime{ 10 };
    Cents nickel{ 5 };

    if (nickel > dime)
        std::cout << "a nickel is greater than a dime.\n";
    if (nickel >= dime)
        std::cout << "a nickel is greater than or equal to a dime.\n";
    if (nickel < dime)
        std::cout << "a dime is greater than a nickel.\n";
    if (nickel <= dime)
        std::cout << "a dime is greater than or equal to a nickel.\n";
    if (nickel == dime)
        std::cout << "a dime is equal to a nickel.\n";
    if (nickel != dime)
        std::cout << "a dime is not equal to a nickel.\n";

    return 0;
}
```
---

### ✅ 3. Normal (Non-member, Non-friend) Function Overloading
Normally used with appropriate getters/setters
**Syntax**:

```cpp
returnType operatorOP(const ClassName& lhs, const ClassName& rhs) {
    return ClassName{ lhs.getValue() OP rhs.getValue() };
}
```

**Used when:**

- You can implement the operation using **public getters/setters**.
    
- Useful when **direct access to private members isn't needed**.
    

#### Example:

```cpp
Cents operator+(const Cents& c1, const Cents& c2) {
    return Cents{ c1.getCents() + c2.getCents() };
}
```

---

### ✅ 4. Logical Operator Overloading (`!`, `&&`, `||`)

**Use case**: Custom objects representing boolean conditions, logic handling.

#### Example: Overload `!`

```cpp
class Flag {
    bool active;
public:
    Flag(bool a) : active(a) {}
    bool operator!() const {
        return !active;
    }
};
```

#### Note:

- Overloading `&&` and `||` **does not preserve short-circuiting**.  
    Example:
    

```cpp
Flag operator&&(const Flag& f1, const Flag& f2) {
    return Flag(f1.getState() && f2.getState());
}
```

📌 Logical operators are often used in state-checking classes (e.g., resource handles, status wrappers).

---

## ✅ Key Takeaways

- Unary ops → Prefer member functions
    
- Binary ops → Use friend if lhs is not the object
    
- Comparison & stream ops → Best done as friend
    
- Logical operators can be overloaded, but **short-circuiting is lost**
    
