### **Object Slicing in C++ (with Example)**  
**Object slicing** occurs when a **derived class object** is assigned to a **base class object**, causing the **derived class-specific attributes/methods to be "sliced off"**. Only the base class part is copied, losing polymorphism.  

---

#### **Example: Object Slicing**  
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    int x;
    Base(int x) : x(x) {}
    virtual void show() { cout << "Base x = " << x << endl; }
};

class Derived : public Base {
public:
    int y;
    Derived(int x, int y) : Base(x), y(y) {}
    void show() override { cout << "Derived x = " << x << ", y = " << y << endl; }
};

void print(Base obj) {  // Accepts Base by value (slicing happens here)
    obj.show();
}

int main() {
    Derived d(10, 20);
    print(d);  // Slices Derived part, only Base is copied!
    return 0;
}
```

**Output:**  
```
Base x = 10  // Lost Derived::y and Derived::show()!
```

---

### **Why It Happens**  
1. **Pass-by-value**: When a `Derived` object is passed to a function expecting a `Base` object, only the `Base` part is copied.  
2. **No Polymorphism**: The `virtual` function is resolved based on the **static type** (`Base`), not the dynamic type (`Derived`).  

---

### **How to Prevent Slicing**  
1. **Pass by reference**:  
   ```cpp
   void print(Base& obj) { obj.show(); }  // Output: Derived x = 10, y = 20
   ```  
2. **Pass by pointer**:  
   ```cpp
   void print(Base* obj) { obj->show(); }  // Output: Derived x = 10, y = 20
   ```  
3. **Use `std::reference_wrapper` or smart pointers**.  

---

### **Key Takeaways**  
✅ **Slicing occurs** when copying a derived object into a base object.  
✅ **Polymorphism is lost** in sliced objects.  
✅ **Fix by passing references/pointers** to preserve the derived class's full identity.  

**Real-world analogy**: Photocopying only the first page of a multi-page document (losing the rest).