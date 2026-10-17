# Test Suite Failure Report (`run_tests.pl all`)

This document catalogs all issues encountered across the 62 tests in `tests/`.
Out of **62 total tests**:
- **30 tests** successfully generate C++ code (`.cpp`).
- **32 tests** fail during AST parsing / translation in `json2verif.exe`.

Below is the categorized breakdown with the exact error signatures, affected tests, root causes in the codebase, and suggested fixes.

---

## Issue Cluster 1: `Error in key value` (14 Tests)

### Failing Tests:
- `tests/chapter_5/section_5_1/test_5_1_1.json`
- `tests/chapter_5/section_5_1/test_5_1_10.json`
- `tests/chapter_5/section_5_1/test_5_1_12.json`
- `tests/chapter_5/section_5_1/test_5_1_13.json`
- `tests/chapter_5/section_5_1/test_5_1_14.json`
- `tests/chapter_5/section_5_1/test_5_1_15.json`
- `tests/chapter_5/section_5_1/test_5_1_18.json`
- `tests/chapter_5/section_5_1/test_5_1_2.json`
- `tests/chapter_5/section_5_1/test_5_1_3.json`
- `tests/chapter_5/section_5_1/test_5_1_4.json`
- `tests/chapter_5/section_5_1/test_5_1_5.json`
- `tests/chapter_5/section_5_1/test_5_1_7.json`
- `tests/chapter_5/section_5_1/test_5_1_8.json`
- `tests/chapter_5/section_5_1/test_5_1_9.json`

### Error Output:
```text
Error in key value
```

### Root Cause:
Triggered inside `json2map_cpp/json2map.cpp` (around line 147–170). The JSON parser encounters an unhandled JSON value type or key structure when populating `प्रकरणसूची` (the AST map variant `std::variant<शब्दाङ्कनक्शा, शब्दशब्दनक्शा, ...>`).
- Often caused by an unexpected primitive type in the JSON (e.g., boolean `true`/`false`, null, or unquoted numeric/nested array inside an object).

---

## Issue Cluster 2: `Error in array datatype in JSON value` (6 Tests)

### Failing Tests:
- `tests/chapter_3/section_3_5/test_3_5_1.json`
- `tests/chapter_4/section_4_10/test_4_10_2.json`
- `tests/chapter_4/section_4_9/test_4_9_1.json`
- `tests/chapter_4/section_4_9/test_4_9_2.json`
- `tests/chapter_4/section_4_9/test_4_9_3.json`
- `tests/chapter_4/section_4_9/test_4_9_4.json`

### Error Output:
```text
Error in array datatype in JSON value
```

### Root Cause:
Inside `json2map_cpp/json2map.cpp` (lines 173–210), when parsing a JSON array `[...]`:
The code expects arrays to either be:
- List of integers (`अङ्कसूची`), OR
- List of strings (`शब्दसूची`).
If the array contains **mixed types**, **nested arrays** (multi-dimensional arrays like in `test_3_5_1`), or **nested JSON objects**, it falls into the `else` branch and terminates with `Error in array datatype in JSON value`.

---

## Issue Cluster 3: `Error in JSON in seperation of key and values` (4 Tests)

### Failing Tests:
- `tests/chapter_4/section_4_2/test_4_2_1.json`
- `tests/chapter_4/section_4_2/test_4_2_2.json`
- `tests/chapter_4/section_4_3/test_4_3_1.json`
- `tests/chapter_4/section_4_3/test_4_3_2.json`

### Error Output:
```text
Error in JSON in seperation of key and values
```

### Root Cause:
Inside `json2map_cpp/json2map.cpp` during line-by-line or object decomposition. The parser expects key-value separators (colons/brackets) to strictly match a specific syntax. When comments, unexpected whitespace, or complex nested blocks occur, the separation check fails.

---

## Issue Cluster 4: Postfix Expression Parsing Errors (5 Tests)

### Failing Tests & Errors:
1. `tests/chapter_5/section_5_1/test_5_1_21.json`
   ```text
   Error in postfix expression c 113 U- =
   ```
   **Cause**: Unary minus operator (`U-`) is not recognized in the postfix evaluation stack in `json2cpp_cpp/convertjson2cpp.cpp` (`पश्चव्यञ्जकरूपान्तरणम्`).

2. `tests/chapter_5/section_5_1/test_5_1_22.json`
   ```text
   Error in postfix expression b 113 U- =
   ```
   **Cause**: Same unary minus operator (`U-`) unhandled.

3. `tests/chapter_7/section_7_1/test_7_1_1_2.json`
   ```text
   Error in postfix expression a b 7 0 : [part-select] =
   ```
   **Cause**: Part-select range operator (`:`) in postfix expression stack.

4. `tests/chapter_7/section_7_1/test_7_1_1_3.json`
   ```text
   Error in postfix expression a b [index] c =
   ```
   **Cause**: Array indexing / bit-select operator unhandled in expression stack.

5. `tests/chapter_9/section_9_1/test_9_1_2.json`
   ```text
   Error in postfix expression a #10 b =
   ```
   **Cause**: Delay token `#10` inside postfix assignment expression.

---

## Issue Cluster 5: `Error from soochakaparyanta` (2 Tests)

### Failing Tests:
- `tests/chapter_7/section_7_1/test_7_1_1_1.json`
- `tests/chapter_7/section_7_1/test_7_1_1_4.json`

### Error Output:
```text
Error from soochakaparyanta
```

### Root Cause:
Inside `json2map_cpp/json2map.cpp` function `सूचकपर्यन्तसञ्चरणम्` (*pointer traversal*). When traversing the index stack (`std::stack<int>`), it looks for a child container/map in `शब्दपिण्डनक्शा`, but the expected index does not exist or points to a non-existent child node.

---

## Issue Cluster 6: `std::regex_error` (1 Test)

### Failing Test:
- `tests/chapter_3/section_3_9/test_3_9_1.json`

### Error Output:
```text
terminate called after throwing an instance of 'std::regex_error'
```

### Root Cause:
Inside expression or statement matching regex (e.g. `check_expr.cpp` or `get_correct_key`), an unescaped character (such as `[`, `]`, `(`, `)`, or `\`) is passed into a `std::regex` constructor from the parsed JSON tokens.

---

## Summary Table

| Category | Count | Primary Affected Source File |
| :--- | :--- | :--- |
| **Unhandled JSON key value format** | 14 | `json2map_cpp/json2map.cpp` |
| **Nested/multidimensional array datatypes** | 6 | `json2map_cpp/json2map.cpp` |
| **Key/value separation in JSON parser** | 4 | `json2map_cpp/json2map.cpp` |
| **Postfix operators (`U-`, `:`, indexing, delays)** | 5 | `json2cpp_cpp/convertjson2cpp.cpp` / `check_expr.cpp` |
| **AST Tree Traversal (`सूचकपर्यन्तसञ्चरणम्`)** | 2 | `json2map_cpp/json2map.cpp` |
| **Regex syntax exception (`std::regex_error`)** | 1 | `check_expr.cpp` / `json2verif.cpp` |
| **Total Failures** | **32** | |
