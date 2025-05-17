## **`<cstring>` (C String Functions)**  
### **1. `strcmp`**  
- **Params**: `const char* s1`, `const char* s2`  
- **Returns**: `int` (`0` if equal, `<0` if `s1 < s2`, `>0` if `s1 > s2`)  
- **Example**:  
  ```cpp
  if (strcmp("apple", "banana") < 0) { /* "apple" comes first */ }
  ```

### **2. `strncmp`**  
- **Params**: `const char* s1`, `const char* s2`, `size_t n`  
- **Returns**: `int` (compares first `n` chars)  
- **Example**:  
  ```cpp
  if (strncmp("apple", "appetite", 3) == 0) { /* first 3 chars match */ }
  ```

### **3. `strcat`**  
- **Params**: `char* dest`, `const char* src`  
- **Returns**: `char*` (pointer to `dest`)  
- **Warning**: No bounds checking!  
- **Example**:  
  ```cpp
  char dest[20] = "Hello";
  strcat(dest, " World");  // dest = "Hello World"
  ```

### **4. `strncat`**  
- **Params**: `char* dest`, `const char* src`, `size_t n`  
- **Returns**: `char*` (appends up to `n` chars)  
- **Example**:  
  ```cpp
  strncat(dest, "!!!", 2);  // Appends "!!"
  ```

### **5. `strcpy`**  
- **Params**: `char* dest`, `const char* src`  
- **Returns**: `char*` (pointer to `dest`)  
- **Warning**: Unsafe (no bounds checking)  
- **Example**:  
  ```cpp
  char dest[10];
  strcpy(dest, "Hi");  // dest = "Hi"
  ```

### **6. `strncpy`**  
- **Params**: `char* dest`, `const char* src`, `size_t n`  
- **Returns**: `char*` (copies up to `n` chars)  
- **Note**: May not null-terminate if `n` ≤ `strlen(src)`  
- **Example**:  
  ```cpp
  strncpy(dest, "Hello", sizeof(dest));  // Safer
  ```

### **7. `strlen`**  
- **Params**: `const char* s`  
- **Returns**: `size_t` (length excluding `'\0'`)  
- **Example**:  
  ```cpp
  int len = strlen("C++");  // len = 3
  ```

### **8. `strstr`**  
- **Params**: `const char* haystack`, `const char* needle`  
- **Returns**: `char*` (pointer to first match or `nullptr`)  
- **Example**:  
  ```cpp
  const char* p = strstr("C++ is fun", "is");  // p points to "is fun"
  ```

---

## **`<string>` (C++ String Utilities)**  
### **1. `std::string()`**  
- **Params**: (Multiple constructors, e.g., `string("text")`, `string(5, 'a')`)  
- **Returns**: `std::string` object  
- **Example**:  
  ```cpp
  std::string result =string(5, 'a');//returns aaaaaa
  ```

### **2. `to_string`**  
- **Params**: Numeric type (`int`, `float`, etc.)  
- **Returns**: `std::string`  
- **Example**:  
  ```cpp
  std::string num = std::to_string(42);  // "42"
  ```

### **3. `c_str()`**  
- **Params**: None (called on `std::string` object)  
- **Returns**: `const char*` (null-terminated C-string)  
- **Example**:  
  ```cpp
  std::string s = "C++";
  printf("%s", s.c_str());  // Pass to C functions
  ```

### **4.  `string::length()` 

Returns the number of characters in a `std::string` **excluding the null character (`\0`)**.

```cpp
size_t str.length() const noexcept;
```

### ⚠️ **Common Mistake**

- **Using `str.length()` for character arrays** — this only works for `std::string`, not C-style strings like `char[]`.
    

### 🔍 **Example**

```cpp
std::string s = "Hello";
std::cout << s.length(); // Output: 5
```

### 🧠 **Deep Note**

```cpp
std::string s = "abc\0def"; 
std::cout << s.length();  // Output: 7 — counts all characters stored in the object.
```

### **5.  `getline()` 

All three use the same overloaded functions:

```cpp
std::getline(std::istream&, std::string&);
std::getline(std::istream&, std::string&, char delim);
```

#### ✅ **Three ways to use `getline()`**

1. **With `std::cin` (keyboard input)**
    
```cpp
std::string s;
std::getline(std::cin, s);
```

2. **With `std::ifstream` (file input)**
    
```cpp
std::ifstream file("data.txt");
std::string line;
std::getline(file, line);
```

3. **With `std::istringstream` (in-memory string parsing)**
    
```cpp
std::istringstream ss("name,age");
std::string token;
std::getline(ss, token, ','); // token = "name"
```
