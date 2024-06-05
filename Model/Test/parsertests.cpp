//Name
//void runTests() {
//    // Test cases
//    std::string functionString;
//    std::string functionName;

//    // Test 1: Basic function declaration
//    functionString = "void foo(int a, int b);";
//    functionName = extractFunctionName(functionString);
//    std::cout << "Test 1: " << (functionName == "foo" ? "Passed" : "Failed") << std::endl;

//    // Test 2: Function with template parameters
//    functionString = "std::vector<int> bar();";
//    functionName = extractFunctionName(functionString);
//    std::cout << "Test 2: " << (functionName == "bar" ? "Passed" : "Failed") << std::endl;

//    // Test 3: Function with multiple words in return type and name
//    functionString = "const char* get_result_string();";
//    functionName = extractFunctionName(functionString);
//    std::cout << "Test 3: " << (functionName == "get_result_string" ? "Passed" : "Failed") << std::endl;

//    // Test 4: Function with comments
//    functionString = "// This is a comment\nint compute();";
//    functionName = extractFunctionName(functionString);
//    std::cout << "Test 4: " << (functionName == "compute" ? "Passed" : "Failed") << std::endl;

//    // Test 5: Function with comments and multiline declaration
//    functionString = "/* This is a\n   multiline comment */\ndouble calculate_average();";
//    functionName = extractFunctionName(functionString);
//    std::cout << "Test 5: " << (functionName == "calculate_average" ? "Passed" : "Failed") << std::endl;

//    // Test 6: Function with whitespace before and after the function name
//    functionString = "  int   perform_operation ();";
//    functionName = extractFunctionName(functionString);
//    std::cout << "Test 6: " << (functionName == "perform_operation" ? "Passed" : "Failed") << std::endl;

//    // Test 7: Function with parameters
//    functionString = "void process_data(int x, double y);";
//    functionName = extractFunctionName(functionString);
//    std::cout << "Test 7: " << (functionName == "process_data" ? "Passed" : "Failed") << std::endl;

//    // Test 8: Function with no return type
//    functionString = "print_message(const std::string& msg);";
//    functionName = extractFunctionName(functionString);
//    std::cout << "Test 8: " << (functionName == "print_message" ? "Passed" : "Failed") << std::endl;

//    // Test 9: Function with no parameters
//    functionString = "void display_result();";
//    functionName = extractFunctionName(functionString);
//    std::cout << "Test 9: " << (functionName == "display_result" ? "Passed" : "Failed") << std::endl;
//}
// Agrs

//void runTests() {
//    // Test cases
//    std::string functionString;
//    std::string arguments;

//    // Test 1: Basic function declaration with arguments
//    functionString = "void foo(int a, double b);";
//    arguments = extractArguments(functionString);
//    std::cout << "Test 1: " << (arguments == "int a, double b" ? "Passed" : "Failed") << std::endl;

//    // Test 2: Function with no arguments
//    functionString = "int bar();";
//    arguments = extractArguments(functionString);
//    std::cout << "Test 2: " << (arguments == "" ? "Passed" : "Failed") << std::endl;

//    // Test 3: Function with arguments and whitespace
//    functionString = "void baz(   int   x  ,   double   y   );";
//    arguments = extractArguments(functionString);
//    std::cout << "Test 3: " << (arguments == "int   x  ,   double   y" ? "Passed" : "Failed") << std::endl;

//    // Test 4: Function with comments inside arguments
//    functionString = "float qux(/* Comment */ int x /* Another comment */, double y);";
//    arguments = extractArguments(functionString);
//    std::cout << "Test 4: " << (arguments == "/* Comment */ int x /* Another comment */, double y" ? "Passed" : "Failed") << std::endl;

//    // Test 5: Function with default argument values
//    functionString = "void quux(int x = 10, double y = 3.14);";
//    arguments = extractArguments(functionString);
//    std::cout << "Test 5: " << (arguments == "int x = 10, double y = 3.14" ? "Passed" : "Failed") << std::endl;

//    // Test 6: Function with complex argument types
//    functionString = "void quuz(int* ptr, const char& c, float arr[], std::string* str);";
//    arguments = extractArguments(functionString);
//    std::cout << "Test 6: " << (arguments == "int* ptr, const char& c, float arr[], std::string* str" ? "Passed" : "Failed") << std::endl;

//    // Test 7: Function with ellipsis indicating a variable number of arguments
//    functionString = "void variadic(int a, ...);";
//    arguments = extractArguments(functionString);
//    std::cout << "Test 7: " << (arguments == "int a, ..." ? "Passed" : "Failed") << std::endl;
//}
// Return Type

//void runTests() {
//    // Test cases
//    std::string functionString;
//    std::string returnType;

//    // Test 1: Basic void return type
//    functionString = "void foo(int a, int b, std::string);";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 1: " << (returnType == "void" ? "Passed" : "Failed") << std::endl;

//    // Test 2: Int return type
//    functionString = "int bar();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 2: " << (returnType == "int" ? "Passed" : "Failed") << std::endl;

//    // Test 3: Double return type
//    functionString = "double baz();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 3: " << (returnType == "double" ? "Passed" : "Failed") << std::endl;

//    // Test 4: Return type with multiple words
//    functionString = "std::vector<int> qux();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 4: " << (returnType == "std::vector<int>" ? "Passed" : "Failed") << std::endl;

//    // Test 5: Return type with digits and underscores
//    functionString = "MyStruct_123 xyz();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 5: " << (returnType == "MyStruct_123" ? "Passed" : "Failed") << std::endl;

//    // Test 6: Function with leading whitespace
//    functionString = "   bool abc();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 6: " << (returnType == "bool" ? "Passed" : "Failed") << std::endl;

//    // Test 7: Function with trailing whitespace
//    functionString = "void def();    ";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 7: " << (returnType == "void" ? "Passed" : "Failed") << std::endl;

//    // Test 8: Function spread across multiple lines
//    functionString = "int\nghi\n(\n);\n";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 8: " << (returnType == "int" ? "Passed" : "Failed") << std::endl;

//    // Test 9: Function with comments
//    functionString = "// This is a comment\nfloat jkl();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 9: " << (returnType == "float" ? "Passed" : "Failed") << std::endl;

//    // Test 10: Function with template parameters
//    functionString = "std::map<int, double> mno();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 10: " << (returnType == "std::map<int, double>" ? "Passed" : "Failed") << std::endl;

//    // Test 11: Function with pointer return type
//    functionString = "char* pqr();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 11: " << (returnType == "char*" ? "Passed" : "Failed") << std::endl;

//    // Test 12: Function with reference return type
//    functionString = "const std::string& stu();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 12: " << (returnType == "const std::string&" ? "Passed" : "Failed") << std::endl;

//    // Test 13: Function with const return type
//    functionString = "const int vwx();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 13: " << (returnType == "const int" ? "Passed" : "Failed") << std::endl;

//    // Test 14: Function with volatile return type
//    functionString = "volatile long yz();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 14: " << (returnType == "volatile long" ? "Passed" : "Failed") << std::endl;

//    // Test 15: Function with const volatile return type
//    functionString = "const volatile float aaa();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 15: " << (returnType == "const volatile float" ? "Passed" : "Failed") << std::endl;

//    // Test 16: Function with no return type (implicit int)
//    functionString = "bar();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 16: " << (returnType == "" ? "Passed" : "Failed") << std::endl;

//    // Test 17: Function with invalid syntax
//    functionString = "invalid_syntax();";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 17: " << (returnType == "" ? "Passed" : "Failed") << std::endl;

//    // Test 18: Function with incomplete parameters
//    functionString = "void incomplete_params(int a, );";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 18: " << (returnType == "void" ? "Passed" : "Failed") << std::endl;

//    // Test 19: Function with no semicolon at the end
//    functionString = "void no_semicolon()";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 19: " << (returnType == "" ? "Passed" : "Failed") << std::endl;

//    // Test 20: Empty input string
//    functionString = "";
//    returnType = extractReturnType(functionString);
//    std::cout << "Test 20: " << (returnType == "" ? "Passed" : "Failed") << std::endl;
//}
