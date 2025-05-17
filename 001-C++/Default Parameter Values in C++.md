
Default parameter values allow functions to be called with fewer arguments than specified in the prototype, with the missing arguments taking on predefined default values.

## Basic Syntax

```cpp
return_type function_name(parameter_type parameter_name = default_value);
```

Example:
```cpp
void printMessage(string msg = "Hello, World!") {
    cout << msg << endl;
}
```

## Key Rules and Characteristics

1. **Right-to-Left Assignment**
   - Default parameters must be specified from right to left
   - Once a parameter has a default value, all subsequent parameters must have defaults

   Valid:
   ```cpp
   void func(int a, int b = 5, int c = 10);
   ```
   
   Invalid:
   ```cpp
   void func(int a = 1, int b, int c = 10);  // Error
   ```

2. **Single Definition Rule**
   - Default arguments should be specified in the function declaration (typically in the header file)
   - If specified in both declaration and definition, the declaration takes precedence

3. **Evaluation Time**
   - Default arguments are evaluated at the time of the function call
   - They're not fixed at compile time (can use variables, but be careful with scope)

## Usage Examples

### Basic Usage
```cpp
void display(int x, int y = 20, int z = 30) {
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
}

int main() {
    display(10);        // x=10, y=20, z=30
    display(10, 40);    // x=10, y=40, z=30
    display(10, 40, 50);// x=10, y=40, z=50
}
```

### With Function Overloading
```cpp
void log(string message) { /*...*/ }
void log(string message, bool timestamp = false) { /*...*/ } // Overload with default

// log("error") - AMBIGUOUS! Both versions could match
```

## Important Considerations

1. **Virtual Functions**
   - Default parameters are statically bound (determined at compile time)
   - They don't behave polymorphically like virtual functions

   ```cpp
   class Base {
   public:
       virtual void print(int x = 10) { cout << "Base: " << x; }
   };
   
   class Derived : public Base {
   public:
       void print(int x = 20) override { cout << "Derived: " << x; }
   };
   
   int main() {
       Base* b = new Derived();
       b->print(); // Outputs "Derived: 10" (not 20)!
   }
   ```

2. **Pointers and References**
   - Default arguments are based on the static type of the object/pointer

3. **Templates**
   - Default template parameters follow similar rules but are specified differently

## Best Practices

1. Use default arguments to reduce the number of function overloads
2. Prefer default arguments over function overloading when the behavior is identical
3. Document default values in function comments
4. Avoid non-obvious default values that might confuse users
5. Be cautious when changing default values in library code (breaks binary compatibility)

Default parameters are a powerful feature that can make APIs more convenient to use, but they require careful design to avoid ambiguity and maintain clarity.