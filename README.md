# LinkList (C++ Template)

A simple **Doubly Linked List** implemented in C++ template.  
Supports memory management (RAM/PSRAM), adding by value or pointer, and flexible usage.

---

## Features
- ✅ Template-based (store any data type)
- ✅ Select memory source: `RAM` or `PSRAM`
- ✅ Add members by **value copy** (`Add(T)`) or **pointer reference** (`Add(T*)`)
- ✅ Optional member limit (`limit_member`)
- ✅ Access via `operator[]` (with nullptr check)
- ✅ Iterate with `Find` using lambda
- ✅ Remove by index and clear all members
- ✅ Compact memory structure (`#pragma pack(push,1)`)

---

## Quick Example

```cpp
#include "LinkList.h"

int main() {
    // Create list of int in RAM
    LinkList<int> xs(MemorySource::RAM, /*limit*/ 10);

    xs.Add(10);        // Add by value copy
    int v = 99;
    xs.Add(&v);        // Add by pointer reference (user-managed)

    // Access element (unsafe if nullptr)
    if (auto p = xs[0]) {
        // *p = 123; // modify stored value
    }

    // Iterate with Find
    xs.Find([](int* item, size_t i){
        if (item) {
            // printf("[%zu] = %d\n", i, *item);
        }
    });

    // Remove first element
    xs.Remove(0);

    // Clear all
    xs.Clear();
}
```

---

## Choosing Memory Source
```cpp
LinkList<MyType> a;                        // Default = RAM
LinkList<MyType> b(MemorySource::PSRAM);   // Use PSRAM
```

> Internally, `Allocator()` currently calls `calloc` for both RAM/PSRAM.  
> You can modify to use platform-specific allocators (e.g., `ps_calloc`).

---

## Adding Members
### 1) By Value Copy
```cpp
MyType value{...};
xs.Add(value);  // Allocates new memory and copies value
```

### 2) By Pointer Reference
```cpp
MyType* p = get_external_ptr();
xs.Add(p);      // Stores pointer directly (not copied)
```

> In pointer mode, `bit_user_manage_address` flag prevents auto-free.  
> You must manage the pointer's lifetime manually.

---

## Access with `operator[]`
```cpp
if (auto p = xs[5]) {
    // use *p safely
}
```
⚠️ Always check for `nullptr` before dereferencing.

---

## Iteration with Find
```cpp
xs.Find([](MyType* item, size_t index){
    if (!item) return;
    if (*item == 100) {
        // Do something
    }
});
```

---

## Remove & Clear
```cpp
xs.Remove(3); // Remove index 3
xs.Clear();   // Free all nodes
```

---

## Status Information
```cpp
size_t n = xs.Count();      // current member count
size_t sz = xs.Size();      // approx memory size
```

---

## Safety Tips
- Always check `nullptr` from `operator[]`
- When using `Add(T*)`, ensure pointer remains valid
- Use `limit_member` to restrict size if needed
- Adjust `ARCH_16Bit / ARCH_32Bit` macros for your platform

---

## Limitations
- `operator[]` is O(n) traversal (not random access like `std::vector`)
- No STL-style iterators yet (can be added later)
- PSRAM currently uses same `calloc` as RAM (adapt for your platform)

---

## Example Lifecycle

```cpp
LinkList<int> xs(MemorySource::RAM, 5);

for (int i = 0; i < 5; ++i) xs.Add(i * 10);

xs.Find([](int* p, size_t i){
    if (p) printf("[%zu] = %d\n", i, *p);
});

xs.Remove(2);   // remove index 2
xs.Clear();     // free all
```

---

## File Structure
```
LinkList.h   // Single header-only file
```

---

## License
Choose any license (e.g., MIT) to include with your project.
