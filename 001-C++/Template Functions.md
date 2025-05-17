### >> Syntax of Template Functions

```cpp
template <typename T>
T functionName(T param1, T param2)
{
    // function logic
}
```

- `typename` and `class` are interchangeable in template declaration.
    
- `T` is a placeholder for a data type; replaced by actual type at compile time.
    

✅ **Example:**

```cpp
template <typename T>
T square(T x) {
    return x * x;
}
```

---

### >> How Template Functions Actually Work

- Templates enable **generic programming**: instead of writing the same function for different types, write one template.
    
- When a template function is invoked with a specific type, the compiler generates a **concrete function** by **replacing** `T` with the passed type.
    

🔍 **Example:**

```cpp
max<int>(1, 2);
// Compiler generates:
int max(int x, int y) {
    return (x < y) ? y : x;
}
```

💡 **Pro Tip**: This process is called **template instantiation**, and happens **at compile time**.

---

### >> 3 Ways to Call a Template Function

#### 1. **Explicitly specify the type**

```cpp
max<int>(1, 2);  // Template instantiation using int
```

- Compiler does **not perform type deduction**.
    
- All arguments must **match or be implicitly converted** to `int`.
    

#### 2. **Use empty angle brackets**

```cpp
max<>(1, 2);  // Template instantiation with automatic type deduction
```

- The compiler **deduces the type** from arguments.
    
- No consideration of non-template overloads.
    

#### 3. **Call without angle brackets**

```cpp
max(1, 2);
```

- Compiler:
    
    1. **Tries exact non-template matches first.**
        
    2. If none found, it performs template type deduction.
        

🧪 **Example:**

```cpp
template <typename T>
T max(T x, T y) {
    std::cout << "Template version\n";
    return (x < y) ? y : x;
}

int max(int x, int y) {
    std::cout << "Non-template version\n";
    return (x < y) ? y : x;
}

int main() {
    max<int>(1, 2);   // Template version
    max<>(1, 2);      // Template version (deduced)
    max(1, 2);        // Non-template version
}
```

---

### >> Errors When Using Templates (and Fix)

❌ **Problem**: Not all operations are defined for all types.

```cpp
template <typename T>
T addOne(T x) {
    return x + 1;
}
std::string hello = "Hello";
addOne(hello);  // ❌ Error: std::string + int not defined
```

✅ **Fix using template specialization**:

```cpp
template<>
std::string addOne<std::string>(std::string x) {
    return x + "1";
}
```

🧠 **Insight**: If an operator or function is **not defined** for a particular type, you'll get a **compilation error**, even if that function is not called during runtime.

---

### >> List: Conditions Where Template Deduction Fails

Compiler **cannot deduce template parameters** if:

1. **Arguments have mismatched types** without conversions.
    
    ```cpp
    template <typename T>
    void func(T a, T b);
    func(1, 1.2);  // ❌ T cannot be deduced to both int and double
    ```
    
2. **Argument is a non-deducible context**, e.g., return type only.
    
    ```cpp
    template <typename T>
    T create();  // ❌ T not deducible from arguments
    auto x = create();  // Error
    ```
    
3. **Function pointer or reference mismatch**
    
    ```cpp
    template <typename T>
    void func(T* ptr);
    int x;
    func(&x);   // OK
    func(x);    // ❌ Cannot deduce T* from int
    ```
    
4. **Overloaded functions passed as argument**
    
    ```cpp
    template <typename T>
    void call(T func);
    call(someOverloadedFunc);  // ❌ Ambiguity
    ```
    
#### **Does the compiler convert/cast parameters when calling template functions?**

#### ➤ **`max<int>(1, 2.0)`**

- ✅ Yes, **2.0 (double)** will be **converted to int**.
    
- Compiler generates `int max(int, int)` — both params cast to `int`.
    

#### ➤ **`max<>(1, 2.0)`**

- ❌ No, **template argument deduction fails**.
    
- Because one is `int`, the other is `double`, and **T can't be deduced** to a single type.
    
- **Compilation error**.
    

#### ➤ **`max(1, 2.0)`**

- 🔍 The compiler looks for a **non-template overload** first.
    
- If not found, **template deduction fails** (same reason as above: types don't match).
    
- **Compilation error**, unless an overloaded version like `template<typename T, typename U>` exists.
    

---

🧠 **Key Rule**:

- **Explicit type** (e.g., `max<int>`) → arguments are **cast to specified type**.
    
- **Implicit type deduction** (e.g., `max<>(...)`) → **no casting**, types must match.
    


### >> Multiple Typenames

- Allows use of **multiple independent** type parameters.
    

```cpp
template <typename T, typename U>
auto multiply(T a, U b) {
    return a * b;
}
```

- Use when function arguments may have **different types**.
    
- Use `auto` or trailing return type (`->`) in C++11+.
    

---

### >> Template Overloading

- Multiple versions of a function template (or mix of templates and non-templates) can **coexist**.
    

```cpp
template <typename T>
auto add(T x, T y) {
    return x + y;
}

template <typename T, typename U>
auto add(T x, U y) {
    return x + y;
}

template <typename T, typename U, typename V>
auto add(T x, U y, V z) {
    return x + y + z;
}
```

🧠 **Tip**: In case of ambiguity, C++ uses:

1. **Exact non-template match**
    
2. **Template with exact match**
    
3. **Template with conversions**
    

---

## 📘 Summary Table

|Concept|Description|
|---|---|
|`template<typename T>`|Declares a function template|
|Instantiation|Compiler generates type-specific function|
|Deduction failure|Compiler can't guess type from args|
|Overloading|Templates can be overloaded with types/arg counts|
|Specialization|Custom behavior for specific types|
|`auto` return type|Use with C++11+ to infer return from expressions|

---

## 🎓 Intermediate-Level Viva / Dry Run Questions

1. **Dry Run**: What is the output of this?
    
    ```cpp
    template<typename T>
    T identity(T x) { return x; }
    
    int identity(int x) { return x * 10; }
    
    std::cout << identity(5);
    ```
    
2. Why does this fail to compile?
    
    ```cpp
    template <typename T>
    void show(T x, T y);
    
    show(1, 2.0);
    ```
    
3. Explain what happens when both a template and a non-template function match the call. Which one is chosen?
    
4. Modify the following code to support `std::string` without causing compilation errors:
    
    ```cpp
    template <typename T>
    T addOne(T x) {
        return x + 1;
    }
    ```
    
5. What is the difference between `max<>(1, 2)` and `max(1, 2)` when both a template and non-template version exist?
    
6. How would you write a template function `combine(T x, U y)` that returns a `std::string` representation of both concatenated?
    
7. What happens if you try to instantiate a template function with a type that doesn’t support the operations inside it?
    
8. Explain with example: Can templates be overloaded based on number of arguments?
    
9. Describe a real-world scenario where template overloading is necessary.
    
