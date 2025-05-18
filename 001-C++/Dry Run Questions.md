
### **Q1. What is the output?**

```cpp
#include <iostream>
class Base {
public:
    void display() { std::cout << "Base\n"; }
};

class Derived : public Base {
public:
    void display() { std::cout << "Derived\n"; }
};

int main() {
    Base* ptr = new Derived;
    ptr->display();
    return 0;
}
```

---

### **Q2. What is the output?**

```cpp
#include <iostream>
class Base {
public:
    virtual void show() { std::cout << "Base\n"; }
};

class Derived : public Base {
public:
    void show() override { std::cout << "Derived\n"; }
};

int main() {
    Derived d;
    Base& b = d;
    b.show();
    return 0;
}
```

---

### **Q3. What is the output and why?**

```cpp
#include <iostream>
class A {
public:
    A() { std::cout << "A "; }
    ~A() { std::cout << "~A "; }
};

class B : public A {
public:
    B() { std::cout << "B "; }
    ~B() { std::cout << "~B "; }
};

int main() {
    A* obj = new B;
    delete obj;
    return 0;
}
```

---

### **Q4. Why does this fail to compile?**

```cpp
#include <iostream>
template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(1, 2.5);
    return 0;
}
```

---

### **Q5. What is the output?**

```cpp
#include <iostream>
class Base {
public:
    virtual void foo() = 0;
};

class Derived : public Base {
public:
    void foo() override { std::cout << "Derived::foo\n"; }
};

int main() {
    // Base b; // Line A
    Derived d;
    Base* ptr = &d;
    ptr->foo();
    return 0;
}
```

---

### **Q6. Explain the output:**

```cpp
#include <iostream>
class A {
public:
    void func(int) { std::cout << "int\n"; }
    void func(double) { std::cout << "double\n"; }
};

class B : public A {
public:
    void func(char) { std::cout << "char\n"; }
};

int main() {
    B obj;
    obj.func(3.14);
    return 0;
}
```

---

### **Q7. What is the output?**

```cpp
#include <iostream>
#include <fstream>

int main() {
    std::ofstream file("data.txt");
    file << "Hello\n";
    file.close();

    std::ifstream read("data.txt");
    std::string word;
    read >> word;
    std::cout << word;
    return 0;
}
```

---

### **Q8. What is the output and why?**

```cpp
#include <iostream>
template<typename T>
void print(T a) {
    std::cout << "Template: " << a << "\n";
}

void print(int a) {
    std::cout << "Non-template: " << a << "\n";
}

int main() {
    print<>(10);    // Line A
    print(10);      // Line B
    return 0;
}
```

---

### **Q9. Does this compile? If not, why?**

```cpp
#include <iostream>
template<typename T>
void display(T a) {
    std::cout << a << '\n';
}

int main() {
    display("Hello" + 1);
    return 0;
}
```

---

### **Q10. What is the output?**

```cpp
#include <iostream>
class Base {
public:
    virtual void speak() { std::cout << "Base\n"; }
};

class Derived : public Base {
public:
    void speak() { std::cout << "Derived\n"; }
};

void callByValue(Base b) {
    b.speak();
}

int main() {
    Derived d;
    callByValue(d);
    return 0;
}
```

---

## ✅ **Answers & Concepts**

---

- **Q1 Answer**:
    
    - Output: `Base`
        
    - **Reason**: `display()` is non-virtual → early binding (compile-time).
        

---

- **Q2 Answer**:
    
    - Output: `Derived`
        
    - **Reason**: Virtual function → dynamic dispatch at runtime.
        

---

- **Q3 Answer**:
    
    - Output: `A B ~A`
        
    - **Reason**: Destructor in `Base` is **not virtual**, so `~B()` isn’t called → causes resource leaks in real apps.
        

---

- **Q4 Answer**:
    
    - **Fails to compile**
        
    - **Reason**: Template `add(T, T)` needs both args to be **same type**, but `1` is `int`, `2.5` is `double`. No deduction.
        

---

- **Q5 Answer**:
    
    - Output: `Derived::foo`
        
    - **Note**: Line A (if uncommented) would fail: cannot instantiate abstract class (`foo()` not implemented).
        

---

- **Q6 Answer**:
    
    - Output: **Compilation error**
        
    - **Reason**: `func(double)` is hidden in `B`. Only `func(char)` visible unless `using A::func;` added.
        

---

- **Q7 Answer**:
    
    - Output: `Hello`
        
    - **Reason**: `>>` stops at first whitespace, reads `"Hello"` only.
        

---

- **Q8 Answer**:
    
    - Output:
        
        ```
        Template: 10
        Non-template: 10
        ```
        
    - **Reason**:
        
        - Line A: Forces template version using `<>`.
            
        - Line B: Prefers non-template overload if exact match.
            

---

- **Q9 Answer**:
    
    - ✅ Compiles
        
    - **Output**: `ello`
        
    - **Reason**: `"Hello" + 1` returns pointer to 2nd char (`e`) → prints `"ello"`.
        

---

- **Q10 Answer**:
    
    - Output: `Base`
        
    - **Reason**: **Object slicing** occurs in `callByValue(Base)` → `Derived` info lost, base version called.
        

### **Q11. What is the output?**

```cpp
#include <iostream>
class A {
public:
    virtual void hello() const {
        std::cout << "A::hello\n";
    }
};

class B : public A {
public:
    void hello() {
        std::cout << "B::hello\n";
    }
};

int main() {
    const A* ptr = new B;
    ptr->hello();
    return 0;
}
```

---

### **Q12. What is the output?**

```cpp
#include <iostream>
template<typename T>
void func(T val) {
    std::cout << "Template\n";
}

void func(int val) {
    std::cout << "Non-template\n";
}

int main() {
    func<>(10);
    func(10);
    return 0;
}
```

---

### **Q13. What is the output?**

```cpp
#include <iostream>
template <typename T>
T square(T x) {
    return x * x;
}

int main() {
    std::cout << square(3.5f) << "\n";
    std::cout << square<>(2) << "\n";
    return 0;
}
```

---

### **Q14. What is the output?**

```cpp
#include <iostream>
class A {
public:
    A(int x = 0) { std::cout << "A(" << x << ")\n"; }
};

class B : virtual public A {
public:
    B() { std::cout << "B\n"; }
};

class C : virtual public A {
public:
    C() { std::cout << "C\n"; }
};

class D : public B, public C {
public:
    D() { std::cout << "D\n"; }
};

int main() {
    D obj;
    return 0;
}
```

---

### **Q15. What is the output?**

```cpp
#include <iostream>
class X {
public:
    X() { std::cout << "X\n"; }
    virtual ~X() { std::cout << "~X\n"; }
};

class Y : public X {
public:
    Y() { std::cout << "Y\n"; }
    ~Y() { std::cout << "~Y\n"; }
};

int main() {
    X* ptr = new Y;
    delete ptr;
    return 0;
}
```

---

### **Q16. What is the output?**

```cpp
#include <iostream>
template <typename T>
void show(T x) {
    std::cout << "Generic: " << x << "\n";
}

template <>
void show<int>(int x) {
    std::cout << "Specialized: " << x << "\n";
}

int main() {
    show(10);   // int
    show('A');  // char
    return 0;
}
```

---

### **Q17. What is the output?**

```cpp
#include <iostream>
#include <fstream>
int main() {
    std::ofstream file("test.txt");
    file << "C++\nTemplates\nFile\n";
    file.close();

    std::ifstream in("test.txt");
    std::string line;
    std::getline(in, line);
    std::cout << line;
    return 0;
}
```

---

### **Q18. What is the output?**

```cpp
#include <iostream>
class Base {
public:
    void fun() { std::cout << "Base\n"; }
};

class Derived : public Base {
public:
    void fun() { std::cout << "Derived\n"; }
};

void call(Base& b) {
    b.fun();
}

int main() {
    Derived d;
    call(d);
    return 0;
}
```

---

### **Q19. What is the output?**

```cpp
#include <iostream>
class Base {
public:
    Base() { std::cout << "Base\n"; }
};

class Derived1 : virtual public Base {
public:
    Derived1() { std::cout << "Derived1\n"; }
};

class Derived2 : virtual public Base {
public:
    Derived2() { std::cout << "Derived2\n"; }
};

class Final : public Derived1, public Derived2 {
public:
    Final() { std::cout << "Final\n"; }
};

int main() {
    Final obj;
    return 0;
}
```

---

### **Q20. Why does this fail?**

```cpp
#include <iostream>
template <typename T>
void printTwice(T a, T b) {
    std::cout << a << " " << b << "\n";
}

int main() {
    printTwice(5, "Hi");
    return 0;
}
```

---

## ✅ **Answers & Concepts**

---

- **Q11 Answer**: `A::hello`
    
    - `hello()` in `B` is not marked `const` → does not override → base version called due to const pointer.
        

---

- **Q12 Answer**:
    
    - Output:
        
        ```
        Template
        Non-template
        ```
        
    - Line 1: Explicit template version forced.
        
    - Line 2: Matches non-template perfectly.
        

---

- **Q13 Answer**:
    
    ```
    12.25
    4
    ```
    
    - `float` square evaluated.
        
    - Explicit template call on int.
        

---

- **Q14 Answer**:
    
    ```
    A(0)
    B
    C
    D
    ```
    
    - Virtual inheritance: only one `A` constructed, default arg used.
        

---

- **Q15 Answer**:
    
    ```
    X
    Y
    ~Y
    ~X
    ```
    
    - Destructors must be **virtual** to call `~Y`.
        

---

- **Q16 Answer**:
    
    ```
    Specialized: 10
    Generic: A
    ```
    
    - Template specialization for `int` only.
        

---

- **Q17 Answer**:
    
    ```
    C++
    ```
    
    - `getline()` reads the first line only.
        

---

- **Q18 Answer**:
    
    ```
    Base
    ```
    
    - Function is non-virtual → static binding → base version called.
        

---

- **Q19 Answer**:
    
    ```
    Base
    Derived1
    Derived2
    Final
    ```
    
    - Virtual inheritance prevents multiple `Base` constructor calls.
        

---

- **Q20 Answer**:
    
    - ❌ **Compilation Error**
        
    - Mismatched types: `int` and `const char*` → deduction fails for `T`.
        
