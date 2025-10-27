#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Size of Data Type

Problem Statement:
Given a string representing a C++ data type 
("int", "char", "float", "double", "bool"), 
return the size of that data type in bytes.

Return -1 if the data type is unknown.

-----------------------------------------------------------
Example:
Input: "int"
Output: 4 (bytes, may vary by system)

Input: "bool"
Output: 1 (byte)

===========================================================
*/

/*-----------------------------------------------------------
Approach: Map string to sizeof operator in C++
💡 Idea:
- Compare input string with known data types.
- Return the result of sizeof() operator for matched type.
- Handle unknown types by returning -1.

🧩 Algorithm:
1. Compare input string against "int", "char", "float", "double", "bool".
2. Return sizeof corresponding type if found.
3. Output error and return -1 if not recognized.

⏱ Time Complexity: O(1) for fixed comparisons  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
int sizeofdatatype(string datatype) {
    if (datatype == "int") {
        return sizeof(int);
    } else if (datatype == "char") {
        return sizeof(char);
    } else if (datatype == "float") {
        return sizeof(float);
    } else if (datatype == "double") {
        return sizeof(double);
    } else if (datatype == "bool") {
        return sizeof(bool);
    } else {
        cout << "Unknown datatype" << endl;
        return -1;
    }
}

/*-----------------------------------------------------------
Main function: Demonstrate the sizeofdatatype function
-----------------------------------------------------------*/
int main() {
    cout << "Size of int: " << sizeofdatatype("int") << " bytes" << endl;
    cout << "Size of char: " << sizeofdatatype("char") << " bytes" << endl;
    cout << "Size of float: " << sizeofdatatype("float") << " bytes" << endl;
    cout << "Size of double: " << sizeofdatatype("double") << " bytes" << endl;
    cout << "Size of bool: " << sizeofdatatype("bool") << " bytes" << endl;
    cout << "Size of long: " << sizeofdatatype("long") << " bytes" << endl; // Unknown datatype example

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach:
       - Direct comparison of strings to known types.
       - Use sizeof operator to determine sizes.
       - O(1) time and space complexity due to fixed inputs.
    -----------------------------------------------------------
    */
    return 0;
}
