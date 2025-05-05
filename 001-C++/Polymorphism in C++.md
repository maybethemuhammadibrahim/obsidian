
- The ability of different objects to respond differently to the **same function call**.
    
- Comes in two major types:
    
    1. **Compile-Time Polymorphism (Early Binding)**
        
    2. **Runtime Polymorphism (Late Binding)**
        

---

## 🔷 Compile-Time Polymorphism (Early Binding)

### 1. **Function Overloading**

- Multiple functions with the same name but different parameters (signature, number, or order).
    
- The compiler chooses the best match during compilation.
    

```cpp
void print(int x);
void print(double x);
void print(int x, int y);
```

➡️ The compiler resolves which one to call based on the passed arguments.

---

### 2. **Constructor Overloading**

- A class can have multiple constructors with different parameters.
    

```cpp
class Test {
public:
    Test() {}
    Test(int x) {}
    Test(int x, int y) {}
};
```

---

### 3. **Const and Non-Const Overload**

- A **const** member function can be overloaded with a **non-const** version.
    

```cpp
class Demo {
public:
    void print() {
        cout << "Non-const version\n";
    }
    void print() const {
        cout << "Const version\n";
    }
};

void test() {
    Demo d1;
    const Demo d2;
    d1.print();  // calls non-const
    d2.print();  // calls const
}
```

📌 _Compiler chooses based on whether the object is const or not._

---

## 🔷 Runtime Polymorphism (Late Binding)

### ✅ Requires:

- Inheritance
    
- **Same function name and signature** in base and derived class
    
- **Virtual** keyword in base class
    

---

### 1. **Function Overriding**

- Derived class function overrides base class function if the signature matches.
    
- **Object type** (not pointer/reference type) determines which version runs.
    
- **Shadowing** occurs even if function signatures differ → can lead to error if expected base version is missing in derived.
    

#### 🔍 Shadowing Example:

```cpp
class Base {
public:
    void print() {
        cout << "Base print\n";
    }
};

class Derived : public Base {
public:
    void print() {
        cout << "Derived print\n";
    }
};

int main() {
    Derived d;
    d.print();        // Derived print
    d.Base::print();  // Base print
}
```

#### ✅ Accessing shadowed functions:

- Using `::` → `Base::function();`
    
- Using base pointer:
    

```cpp
Base* ptr = &d;
ptr->print();  // Calls Base::print unless it's virtual
```

---

### 2. **Virtual Functions**

- Used to achieve runtime polymorphism via base class pointers/references.
    
- Helps call **most-derived** function even if the object is accessed through base class.
    

```cpp
class Base {
public:
    virtual void show() {
        cout << "Base\n";
    }
};

class Derived : public Base {
public:
    void show() override {
        cout << "Derived\n";
    }
};

int main() {
    Base* ptr = new Derived();
    ptr->show();  // Derived
}
```

---

### ❌ Never call virtual functions inside constructors or destructors

- They won't behave polymorphically; only base class versions will be called.
    

---

### 🔁 Virtual Functions with Collection of Objects

✔️ Helps treat different derived objects uniformly.

#### Example:

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Employee {
    private:
        string first_name;
        string last_name;
    public:
        Employee(string fname, string lname): first_name(fname), last_name(lname) {}
        string get_full_name() {
            return first_name + " " + last_name;
        }
        virtual void print_wage() {
            cout << "The employee's wage structure is not declared yet" << endl;
        }
        virtual ~Employee() {}
};

class HourlyEmployee: public Employee {
    private:
        double hourly_wage;
    public:
        HourlyEmployee(string fname, string lname, double wage_per_hour): Employee(fname, lname), hourly_wage(wage_per_hour) {}
        void print_wage() override {
            cout << "The hourly wage of " << get_full_name() << " is " << hourly_wage << endl;
        }
};

class RegularEmployee: public Employee {
    private:
        double monthly_wage;
    public:
        RegularEmployee(string fname, string lname, double wage_per_month): Employee(fname, lname), monthly_wage(wage_per_month) {}
        void print_wage() override {
            cout << "The monthly wage of " << get_full_name() << " is " << monthly_wage << endl;
        }
};

int main() {
    vector<Employee*> employees {
        new HourlyEmployee("John", "Doe", 13.5),
        new RegularEmployee("Jane", "Smith", 3000.7)
    };
    for(Employee* employee: employees) {
        employee->print_wage();
    }
    return 0;
}
```

🛑 **Why is `virtual` destructor important?**

When deleting a derived class object using a base class pointer (e.g., `delete basePtr;`), **only the base class destructor is called** if the destructor isn't virtual.  
This leads to **resource leaks** because the derived class's destructor (which may release dynamic memory) is never executed.

✅ Marking the base class destructor `virtual` ensures that the **destructor chain is properly followed** — from most-derived to base — and all resources are correctly freed.

---

### 3. **Pure Virtual Functions and Abstract Classes**

- Declared by: `virtual void function() = 0;`
    
- Makes the class **abstract**: cannot instantiate directly.
    
- Forces derived classes to implement the function.
    

```cpp
class Shape {
public:
    virtual void draw() = 0;  // pure virtual
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle\n";
    }
};
```

---

## 🔁 Virtual Tables (vtable) and Runtime Resolution

### ✅ What is a vtable?

A **vtable (virtual table)** is an array of pointers to virtual functions. Every class that has at least one virtual function has its own vtable.

✅ **What is a vptr (virtual pointer)?**

Every object of a class with virtual functions contains a hidden pointer called **vptr**, which points to the class’s vtable.


➕ **Object Memory Layout (Conceptual)**:

 ```cpp
 class Base {
     virtual void show();  // vtable entry
     int data;             // object data
 };
 ```
 
 - The layout in memory (conceptually) looks like:>     
     ```
     [ vptr ] → [ vtable: show() → Base::show() ]
     [ data ]
    ```
   
➕ When a virtual function is called through a pointer/reference, the compiler generates code that:
> 
> - Follows the vptr
>     
> - Indexes into the vtable
>     
> - Calls the correct function based on the runtime type of the object

	📌 **Virtual calls disable inlining** unless the compiler can statically deduce the object's type.
	
---

## ⚠️ Virtual Inheritance and the Diamond Problem

✅ **What is the Diamond Problem?**

It arises in **multiple inheritance** when two derived classes inherit from the same base class, and another class inherits from both of them.

Example:

```cpp
class A {
public:
    virtual void greet() {}
};

class B : public A {};
class C : public A {};
class D : public B, public C {};
```

❌ Ambiguity: Class `D` has **two instances** of `A`.  
→ Calling `greet()` on a `D` object is ambiguous.

✅ **Solution: Virtual Inheritance**

Use `virtual` keyword when inheriting from base:

```cpp
class B : virtual public A {};
class C : virtual public A {};
```

➕ Now class `D` has **only one shared instance** of `A`, removing ambiguity and memory duplication.

🔁 The compiler ensures that `A`'s subobject is **shared**, and vtable is managed correctly.

✅ This is **crucial** when `A` has **virtual functions**, as each virtual base should only appear once in the final object layout to preserve consistent vtable behavior.

---
## 🔷 Polymorphism Rules Recap

| Feature                   | Compile Time | Runtime             |
| ------------------------- | ------------ | ------------------- |
| Function Overloading      | ✅ Yes        | ❌ No                |
| Constructor Overloading   | ✅ Yes        | ❌ No                |
| Operator Overloading      | ✅ Yes (Skip) | ❌ No                |
| Function Overriding       | ❌ No         | ✅ Yes (via virtual) |
| Const/Non-Const Overloads | ✅ Yes        | ❌ No                |
| Templates                 | ✅ Yes        | ❌ No                |

---

## ❓ Beginner-Trick Viva Questions (With Explanations)

### Q1: Can you overload a function based only on return type?

**❌ No.** The compiler needs parameter differences to resolve ambiguity.

---

### Q2: Can a `const` object call a non-const function?

**❌ No.** It will result in a compilation error.

---

### Q3: Does virtual function resolution work without a pointer or reference?

**❌ No.** It only works when calling through a pointer/reference.

---

### Q4: Can an abstract class have non-pure functions?

**✅ Yes.** An abstract class can have both pure and regular functions.

---

### Q5: How many vtables are created in a class hierarchy?

**🧠 One per class.**

---

### Q6: Why can't we call virtual functions in constructors?

**🚫 Because during construction, the vptr still points to the base class vtable.**

---

### Q7: What happens if you don't override a pure virtual function?

**⚠️ The derived class also becomes abstract and cannot be instantiated.**

---

Let me know if you'd like an extra **visual diagram of vtable working**, or if you want to include **polymorphism + inheritance interview sheet**, or quiz-style Q/A for testing your concepts.