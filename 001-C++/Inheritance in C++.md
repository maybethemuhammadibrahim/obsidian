
### 🔹 1. Constructor Calling Order in Inheritance

#### ✅ **Single Inheritance**

```cpp
class Base {
public:
    Base() { cout << "Base Constructor\n"; }
};
class Derived : public Base {
public:
    Derived() { cout << "Derived Constructor\n"; }
};
```

🧠 **Order**: Base constructor → Derived constructor  
🧠 **Destructor Order**: Derived destructor → Base destructor

#### ✅ **Multilevel Inheritance**

```cpp
class A {
public:
    A() { cout << "A\n"; }
};
class B : public A {
public:
    B() { cout << "B\n"; }
};
class C : public B {
public:
    C() { cout << "C\n"; }
};
```

🧠 **Order**: A → B → C  
🧠 **Destructor Order**: C → B → A

#### ✅ **Multiple Inheritance**

```cpp
class A {
public:
    A() { cout << "A\n"; }
};
class B {
public:
    B() { cout << "B\n"; }
};
class C : public A, public B {
public:
    C() { cout << "C\n"; }
};
```

🧠 **Order**: A → B → C (order depends on declaration in `class C`)  
🧠 **Destructor Order**: C → B → A

#### ✅ **Hierarchical Inheritance**

```cpp
class Base {
public:
    Base() { cout << "Base\n"; }
};
class Derived1 : public Base {
public:
    Derived1() { cout << "Derived1\n"; }
};
class Derived2 : public Base {
public:
    Derived2() { cout << "Derived2\n"; }
};
```

🧠 **Order**: Base constructor runs for each derived class independently

#### ✅ **Hybrid Inheritance**

> Combination of two or more types of inheritance.

```cpp
class A { public: A() { cout << "A\n"; } };
class B : virtual public A { public: B() { cout << "B\n"; } };
class C : virtual public A { public: C() { cout << "C\n"; } };
class D : public B, public C { public: D() { cout << "D\n"; } };
```

🧠 **Order**: A → B → C → D  
🧠 `virtual` ensures A is called only once

---

### 🔹 2. Function Overriding and Shadowing

#### ✅ Example:

```cpp
class Parent {
public:
    void show() { cout << "Parent\n"; }
};
class Child : public Parent {
public:
    void show() { cout << "Child\n"; } // Shadows Parent::show()
};
```

#### 🧠 **Concept**:

- If a function with the same name exists in the derived class, it **shadows** the base version.
    
- Overload resolution occurs **only** in the scope of the derived class first.
    

#### ⚠️ Common Mistake:

```cpp
Child obj;
obj.show();        // "Child"
obj.Parent::show(); // Accesses base function explicitly
```

#### ✅ Calling Base Function via Pointer:

```cpp
Child obj;
Parent *ptr = &obj;
ptr->show(); // Calls Parent::show() unless it's virtual
```

---

### 🔹 3. Compile-time vs. Runtime Polymorphism

|Feature|Compile-Time|Run-Time|
|---|---|---|
|Resolved by|Compiler|Virtual Table (vtable)|
|Examples|Function overloading, templates|Virtual functions|
|Speed|Faster|Slower|
|Flexibility|Limited|High|

---

### 🔹 4. Virtual Functions

#### ✅ Key Rule:

- Must be called via **base class pointer/reference** to exhibit runtime behavior.
    
- Helps achieve **runtime polymorphism**.
    

```cpp
class Base {
public:
    virtual void greet() { cout << "Hello from Base\n"; }
};
class Derived : public Base {
public:
    void greet() override { cout << "Hello from Derived\n"; }
};
```

```cpp
Base* ptr = new Derived;
ptr->greet();  // Output: "Hello from Derived"
```

---

### 🔹 5. Pure Virtual Functions & Abstract Classes

```cpp
class Shape {
public:
    virtual void draw() = 0; // Pure virtual
};
```

- Any class containing a pure virtual function is **abstract**.
    
- Cannot create an object of an abstract class.
    

---

### 🔹 6. VTable (Virtual Table)

#### ✅ Definition:

A table used by the compiler to **resolve virtual functions at runtime**.

- Each class with virtual functions gets a **vtable**.
    
- Each object of such a class stores a pointer to this vtable.
    

#### ✅ Behavior:

```cpp
Base* ptr = new Derived;
ptr->greet(); // Looks up vtable to call Derived’s version
```

---

### 🔹 7. Diamond Problem & Virtual Inheritance

#### ❌ Problem:

```cpp
class A { public: void show() { cout << "A"; }};
class B : public A {};
class C : public A {};
class D : public B, public C {}; // Ambiguity! Two A's inherited
```

#### ✅ Solution: Virtual Inheritance

```cpp
class A { public: void show() { cout << "A"; }};
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {}; // Only one A now
```

🧠 **Virtual inheritance ensures only one copy** of A is passed to D.

---

## 🔸 Important Viva / Debug Questions

1. **What is the order of constructor and destructor calls in hybrid inheritance?**
    
2. **Can a base class pointer call a derived class function without virtual keyword?**
    
3. **What happens when both base and derived classes have functions with the same name but different signatures?**
    
4. **Is runtime polymorphism possible without using pointers or references?**
    
5. **How does the compiler resolve overloaded functions during inheritance?**
    
6. **How is ambiguity resolved in multiple inheritance when two base classes have same function names?**
    
7. **Why is virtual inheritance necessary and how does it affect constructor order?**
    
8. **Can an abstract class have non-virtual functions?**
    
9. **What if a derived class doesn’t override a pure virtual function?**
    
10. **How many vtables are created in case of multiple inheritance?**
    
11. **Why is the virtual keyword important in destructors for base classes?**
    
12. **What will happen if a virtual function is not overridden in derived class?**
    
13. **Can you instantiate a class with all pure virtual functions overridden privately?**
    

---

## 🔹 Key Takeaways

- **Constructor Order** is determined by inheritance chain (top-down); destructor is bottom-up.
    
- **Virtual functions** allow runtime decision-making; **vtable** is the backbone.
    
- Use `override` to signal intention to override and catch mismatches.
    
- **Shadowing ≠ Overriding**; pay attention to function signature.
    
- **Abstract classes** enforce a contract; cannot be instantiated.
    
- **Virtual inheritance** solves **diamond problem** by sharing base class.
    
## 🔸 Detailed Viva Q&A with Evaluation

---

### **1. What is the order of constructor and destructor calls in hybrid inheritance (assuming ambiguity is resolved using `virtual`)?**

📝 **Your Answer**: A → B → C → D. A is called once due to virtual inheritance.  
✅ **Verdict**: ✔️ **Correct**  
💡 **Explanation**: With virtual inheritance:

- `A` is constructed first (as it's virtually inherited).
    
- Then `B`, `C`, and finally `D`.
    
- This prevents duplicate `A` base calls.
    

---

### **2. Can a base class pointer call a derived class function without `virtual` keyword?**

📝 **Your Answer**: No, the base class function will be called.  
✅ **Verdict**: ✔️ **Correct**  
💡 **Explanation**: Without `virtual`, the compiler binds function calls **statically**, so the **base class version** is always called, even if the object is of the derived class.

---

### **3. What happens when both base and derived classes have functions with the same name but different signatures?**

📝 **Your Answer**: The derived class hides the base class version; only the derived version is searched.  
✅ **Verdict**: ✔️ **Correct**  
💡 **Explanation**: This is called **name hiding**. Even if the base class has overloaded versions, they're hidden unless brought into scope using:

```cpp
using Base::functionName;
```

---

### **4. Is runtime polymorphism possible without using pointers or references?**

📝 **Your Answer**: Not answered.  
❌ **Verdict**: ❌ **Incorrect**  
💡 **Correct Answer**: **No.** Runtime polymorphism requires the base class function to be called through a **pointer or reference**. Otherwise, it defaults to compile-time (static) binding.

---

### **5. How does the compiler resolve overloaded functions during inheritance?**

📝 **Your Answer**: It uses overload resolution based on function signature.  
✅ **Verdict**: ✔️ **Correct**  
💡 **Explanation**: The compiler looks at the function name and parameters and applies the most specific match available (starting from derived class, then base class if `using` is applied).

---

### **6. How is ambiguity resolved in multiple inheritance when two base classes have same function names?**

📝 **Your Answer**: Using scope resolution operator.  
✅ **Verdict**: ✔️ **Correct**  
💡 **Explanation**:

```cpp
obj.Base1::func();  // Resolves ambiguity explicitly
```

---

### **7. Why is virtual inheritance necessary and how does it affect constructor order?**

📝 **Your Answer**: It removes ambiguity; otherwise, error occurs.  
✅ **Verdict**: ✔️ **Correct**  
💡 **Explanation**: Without `virtual`, both paths bring their own copy of base class. With `virtual`, only one shared copy is created → resolves **diamond problem** and changes constructor order to construct the virtual base first.

---

### **8. Can an abstract class have non-virtual functions?**

📝 **Your Answer**: Yes, but no object can be made.  
✅ **Verdict**: ✔️ **Correct**  
💡 **Explanation**: Abstract class can contain both virtual and non-virtual functions. But **if it has at least one pure virtual function**, no object of it can be created.

---

### **9. What happens if a derived class doesn’t override a pure virtual function?**

📝 **Your Answer**: Error is thrown.  
✅ **Verdict**: ✔️ **Correct**  
💡 **Explanation**: The derived class also becomes **abstract** and can't be instantiated.

---

### **10. How many vtables are created in case of multiple inheritance?**

📝 **Your Answer**: One for each class.  
❌ **Verdict**: ❌ **Partially Incorrect**  
💡 **Correct Answer**: In **simple multiple inheritance**, each class with virtual functions has its **own vtable**.  
In complex inheritance like **virtual inheritance**, derived classes might use a **shared or combined vtable structure** depending on compiler implementation.

---

### **11. Why is the `virtual` keyword important in destructors for base classes?**

📝 **Your Answer**: Not answered.  
✅ **Correct Answer**: If a base class destructor is **not virtual**, then deleting a derived object via a base class pointer **causes undefined behavior** (base destructor is called, derived isn’t).

```cpp
virtual ~Base() {}
```

---

### **12. What will happen if a virtual function is not overridden in derived class?**

📝 **Your Answer**: The base version will be called.  
✅ **Verdict**: ✔️ **Correct**  
💡 **Explanation**: The function remains virtual, so if it's not overridden, the base class version is used during virtual dispatch.

---

### **13. Can you instantiate a class if it overrides all pure virtual functions privately?**

📝 **Your Answer**: Not answered.  
❌ **Verdict**: ❌ **Incorrect**  
💡 **Correct Answer**: **No.** Even if all pure virtual functions are overridden, if they are **private**, the derived class remains abstract for the compiler because the overridden functions aren't **accessible** for binding.
