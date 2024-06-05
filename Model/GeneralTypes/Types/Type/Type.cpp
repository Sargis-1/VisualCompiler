#include "Type.h"

// Type::Type()
// {
//     castTable = {
//                 {"int", &Type::intCast},
//                 {"signed int", &Type::intCast},
//                 {"long", &Type::intCast},
//                 {"long int",  &Type::intCast},
//                 {"signed long int",  &Type::intCast},

//                 {"char", &Type::charCast},
//                 {"float", &Type::floatCast},
//                 {"double", &Type::doubleCast},
//                 {"bool", &Type::boolCast},
//                 {"char", &Type::charCast},
//                 {"short", &Type::shortCast}
//     };
// }

// std::string Type::callToAst(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     std::string result;
//     if(tokens[1] == "+=") {
//         result = operator +=(expr);
//      //   AST ob(SC -> getValueByName(tokens[0]).first + "+" + SC -> getValueByName(tokens[2]).first);
//     } else if (tokens[1] == "-=") {
//         result = operator -=(expr);
//     } else if (tokens[1] == "*=") {
//          result = operator *=(expr);
//     } else if (tokens[1] == "/=") {
//          result = operator /=(expr);
//     } else if (tokens[1] == "%=") {
//         result = operator %=(expr);
//     } else if (tokens[1] == "|=") {
//         result = operator |=(expr);
//     } else if (tokens[1] == "&=") {
//         result = operator &=(expr);
//     } else if (tokens[1] == "^=") {
//         result = operator ^=(expr);
//     } else if (tokens[1] == "<<=") {
//         result = operator <<=(expr);
//     } else if (tokens[1] == ">>=") {
//         result = operator >>=(expr);
//     } // call to operator= also must be from here
//     //result = operator=(expr);
//    return result;
// }

// static std::string Type::plusOne(std::string num)
// {
//     bool negative = false; // Flag to indicate if the number is negative
//     std::vector<int> digits; // Vector to store individual digits of the number

//     // Check if the number is negative
//     if (num[0] == '-' ) {
//         negative = true;
//         num = num.substr(1); // Remove the negative sign
//     }
//     // Convert string digits to integer and store them in 'digits'
//     for (int i = 0; i < num.size(); ++i) {
//         digits.push_back(static_cast<int>(num[i]) - 48);
//     }
//     // Handle cases based on the position of the decimal point
//     if (start_index == 0) {
//         digits.insert(digits.begin(), 0); // Insert '0' before decimal if it's at the beginning // .0253 -> 0.0253, astart_index = 0
//     } else if (start_index == std::string::npos) {
//         start_index = digits.size() - 1; // Decimal not found, set start_index to the last digit // 256 -> start_index = 2
//     } else {
//         --start_index; // Move start_index before the decimal point // 2563.36 -> start_index = 3
//     }

//     // Count the number of '9's and '0's before or including the decimal point
//     int count_of_nines = 0;
//     int count_of_zeros = 0;
//     for (int i = 0; i <= start_index; ++i) {
//         if(digits[i] == 9){
//             ++count_of_nines;
//         } else if (digits[i] == 0) {
//             ++count_of_zeros;
//         }
//     }

//     // Remove trailing zeros after the decimal point
//     if (num.find('.') != std::string::npos) {
//         while(digits.back() == 0) {
//             digits.pop_back();
//         }
//     }

//     // Increment the number based on its sign and position of '9's and '0's
//     if (!negative) {
//         if (count_of_nines == start_index + 1) { // All digits are '9's //99999.3 -> 00000.3
//             for(int i = 0; i <= start_index; ++i) {
//                 digits[i] = 0;
//             }
//             digits.insert(digits.begin(), 1); // Insert '1' at the beginning // 00000.3 -> 100000.3
//         } else if (digits[start_index] == 9) { // Handle cases when start_index is 9 //150099.9 -> 150100.9
//             int i = start_index;
//             for(; i >= 0 && digits[i] == 9; --i) {
//                 digits[i] = 0;
//             }
//             digits[i] += 1;
//         } else {
//             digits[start_index] += 1; // Increment digit at start_index // 153.7 -> 154.7
//         }
//     } else {  // Number is negative
//         if (count_of_zeros == start_index + 1) { // All digits before the decimal are '0's //0000.03650
//             digits.erase(digits.begin(), digits.begin() + start_index); // 0.03560
//             digits[0] = 1; // Set first digit to '1'  // 1.03560
//             start_index = 0;
//         } else if (count_of_zeros == start_index) { // Increment the last non-zero digit before decimal // 100.2563 -> start_index = 2 count_of_zeroes = 2
//             int i = start_index;
//             for (; digits[i] == 0 && i > 0; --i) {  // 099.2563
//                 digits[i] = 9;
//             }
//             digits[i] -= 1;
//             if (digits.size() != 1 && digits.front() == 0) { // Remove leading zeros //99.2563
//                 digits.erase(digits.begin());
//             }
//         } else if (digits[start_index] == 0) { // Increment digit at start_index // 15600.3 -> 15599.3
//             int tmp = start_index;
//             while(digits[tmp] == 0) {
//                 digits[tmp] = 9;
//                 --tmp;
//             }
//             digits[tmp] -= 1;
//         } else {
//             digits[start_index] -= 1; // Decrement digit at start_index // 154.3 -> 153.3
//         }
//     }
//     // Remove trailing '.' if present
//     if (digits.back() == -2) { // -2 corresponds to '.'
//         digits.pop_back();
//     }
//         return num;
//     }
    // for (char c : num) {
    //     if (c == '-' && !found_digit) {
    //         isNegative = true;
    //     } else if (std::isdigit(c)) {
    //         integer_value = integer_value * 10 + (c - '0');
    //         found_digit = true;
    //     }
    //
    // }
    // if (isNegative) {
    //     integer_value = -integer_value;
    // }
    //return std::to_string(integer_value);
//}

/*std::string Type::charCast(std::string num)
{
    char char_value = 0;
    std::istringstream iss(num);
    long double number;
    iss >> number;
    if (number < 0) {
        return "Garbage";
    }
    if (number < 33) {
        std::map<int, std::string> ascii_nums = { // char t = 7; in ui -> '\a'
            {0, "NULL"}, {1, "SOH"}, {2, "STX"}, {3, "ETX"}, {4, "EOT"}, {5, "ENQ"},
            {6, "ACK"}, {7, "'\\a'"}, {8, "'\\b'"}, {9, "'\\t'"}, {10, "'\\n'"},
            {11, "'\\v'"}, {12, "'\\f'"}, {13, "'\\r'"}, {14, "SO"}, {15, "SI"},
            {16, "DLE"}, {17, "DC1"}, {18, "DC2"}, {19, "DC3"}, {20, "DC4"}, {21, "NAK"},
            {22, "SYN"}, {23, "ETB"}, {24, "CAN"}, {25, "EM"}, {26, "SUB"}, {27, "ESC"},
            {28, "FS"}, {29, "GS"}, {30, "RS"}, {31, "US"}, {32, " "}
        };

        auto it = ascii_nums.find(number);
        if (it != ascii_nums.end()) {
            num = it -> second;
        }
    } else {
        char_value = static_cast<char>(number);
        num = "'" + std::string(1, char_value) + "'";
    }
   return num;
}

std::string Type::floatCast(std::string num)
{
    return num;
}

std::string Type::doubleCast(std::string val)
{
    std::string ret_val = "";

    if (!std::isdigit(val.back()) && std::isdigit(val.front())){ //for double d = 12f , ul, l, .f, u
        if (val[val.size() - 2] == 'u' && val.back() == 'l'){
            val.pop_back();
            val.pop_back();
        } else if (val[val.size() - 2] == 'U' && val.back() == 'L'){
            val.pop_back();
            val.pop_back();
        } else if (val[val.size() - 2] == '.' && val.back() == 'f'){
            val.pop_back();
            val.pop_back();
        } else if (val[val.size() - 2] == 'L' && val.back() == 'L') {
            val.pop_back();
            val.pop_back();
            if (val.back() == 'U'){
                val.pop_back();
            }
        } else if (val[val.size() - 2] == 'l' && val.back() == 'l') {
            val.pop_back();
            val.pop_back();
            if (val.back() == 'u'){
                val.pop_back();
            }
        } else {
            switch (val.back()) {
                case 'f':
                case 'F':
                case 'l':
                case 'L':
                case 'u':
                case 'U':
                    val.pop_back();
            }
        }
    }
    if (std::isdigit(val[0]) && (val.find('e') != std::string::npos || val.find('E') != std::string::npos))  //for double d = 12e2
    {
        std::ostringstream oss; //creating buffer object to get the correct form of the value
        double d;
        try {
            d = std::stod(val);
            oss << d;
            ret_val = oss.str();
        } catch(std::out_of_range) {
            try{
                long double ld = std::stold(val);
                d = ld;
                oss << d;
                ret_val = oss.str();
            } catch (std::out_of_range) {
                ret_val = "inf";
            }
        }
    }
    bool neg = false;
    if(val == "" || val == name) //double x{}  val = "" or double d = d
    {
        return "0";
    }
    if(val.find("++") != std::string::npos || val.find("--") != std::string::npos || val.find('!') != std::string::npos) // double d = x++
    {
        ret_val = resolveOperation(val);
    }

    if(val[0] == '-' || val[0] == '+') // double x = -789;
    {
        int i = 0;
        while(val[i] == '-' || val[i] == '+' || val[i] == '(') //for +-+-+-+-+-+-+-+-5;
        {
            if (val[i] == '(') {
                ++i;
                continue;
            }
            if(val[i] == '-'){
                neg = !neg;
            }
            ++i;
        }
        val.erase(0, i);
    }
    if (val[0] == '0'){ //for double d = 00000.33;
        int i = 0;
        while(val[i] == '0')
        {
            ++i;
        }
        val = val.erase(0,i);
    }
    if (val[0] == '.'){ //for double d = .3;
        val = '0' + val;
    }
    if (std::isdigit(val[0]))
    {
        std::ostringstream oss; //creating buffer object to get the correct form of the value
        double d;
        try {
            d = std::stod(val);
            oss << d;
            ret_val = oss.str();
        } catch(std::out_of_range& e) {
            long double ld = std::stold(val);
            d = ld;
            oss << d;
            ret_val = oss.str();
        }
    }
    else if (val == "true")
    {
        ret_val = "1";
    }
    else if (val == "false")
    {
        ret_val = "0";
    }
    else if (val.front() == '\'' && val.back() == '\'')// val = 'a'  val = '\0'
    {
        val.erase(0, 1);                                 // Erase the first character (')
        val.erase(val.length() - 1);                    // Erase the last character (')
        if(val.size() == 1)
        {
            short tmp = static_cast<short>(val[0]);
            ret_val = std::to_string(tmp);
        }
        else if(val.size() == 2)// '\t' '\n' and more than one symbol in char arent handled
        {
            if(val[1] == 'n')  ret_val = "10";
            if(val[1] == 't')  ret_val = "9";
            if(val[1] == 'b')   ret_val = "8";
            if(val[1] == 'r')   ret_val = "13";
            if(val[1] == 'v')  ret_val = "11";
            if(val[1] == 'f')  ret_val = "12";
            if(val[1] == 'a')  ret_val = "7";
            if(val[1] == '\\')  ret_val = "92";
            if(val[1] == '?')  ret_val = "63";
            if(val[1] == '\'')  ret_val = "39";
            if(val[1] == '\"')  ret_val = "34";
            if(val[1] == '0')  ret_val = "0";
        }
        else if (val[1] == 'x'){ //for double d = '\x7a'; hexical numbers
            if (std::isdigit(val[2]) || ('a' <= val[2] && 'f' >= val[2]) || ('A' <= val[2] && 'F' >= val[2])){
                std::string hexVal = "";
                for(int i = 2; std::isdigit(val[i]) || ('a' <= val[i] && 'f' >= val[i]) || ('A' <= val[i] && 'F' >= val[i]); ++i)
                {
                    hexVal += val[i];
                }
                int tmp = std::stoi(hexVal, nullptr, 16);
                if (tmp >= 0 && tmp <= 127){
                    ret_val = std::to_string(tmp);
                } else if (tmp >127 && tmp <256){
                    tmp -= 256;
                    ret_val = std::to_string(tmp);
                }
            }
        }
        else if (std::isdigit(val[1]) && (val[1] >=48 && val[1] <=55)){ //for double d = '\21';  octal numbers
            std::string octVal = "";
            for(int i = 1; std::isdigit(val[i]) && (val[i] >=48 && val[i] <=55); ++i)
            {
                octVal += val[i];
            }
            int tmp = std::stoi(octVal, nullptr, 8);
            if (tmp >= 0 && tmp <= 127){
                ret_val = std::to_string(tmp);
             }
             else if (tmp >127 && tmp <256){
                tmp -= 256;
                ret_val = std::to_string(tmp);
             }
        }
    } else {
       ret_val = doubleCast(SC -> getValueByName(val).first);
    }

    if (neg) {
        ret_val = "-" + ret_val;
    }
    if (ret_val.find('.') != std::string::npos){ //for 5.00000 -> 5
        while(ret_val.back() == '0'){
            ret_val.pop_back();
        }
    }
    return ret_val;
}

std::string Type::boolCast(std::string num)
{
    std::string ret_val = "";

    if (!std::isdigit(val.back()) && std::isdigit(val.front())){ //for double d = 12f , ul, l, .f, u
        if (val[val.size() - 2] == 'u' && val.back() == 'l'){
            val.pop_back();
            val.pop_back();
        } else if (val[val.size() - 2] == 'U' && val.back() == 'L'){
            val.pop_back();
            val.pop_back();
        } else if (val[val.size() - 2] == '.' && val.back() == 'f'){
            val.pop_back();
            val.pop_back();
        } else if (val[val.size() - 2] == 'L' && val.back() == 'L') {
            val.pop_back();
            val.pop_back();
            if (val.back() == 'U'){
                val.pop_back();
            }
        } else if (val[val.size() - 2] == 'l' && val.back() == 'l') {
            val.pop_back();
            val.pop_back();
            if (val.back() == 'u'){
                val.pop_back();
            }
        } else {
            switch (val.back()) {
                case 'f':
                case 'F':
                case 'l':
                case 'L':
                case 'u':
                case 'U':
                    val.pop_back();
            }
        }
    }
    if (std::isdigit(val[0]) && (val.find('e') != std::string::npos || val.find('E') != std::string::npos))  //for double d = 12e2
    {
        std::ostringstream oss; //creating buffer object to get the correct form of the value
        double d;
        try {
            d = std::stod(val);
            oss << d;
            ret_val = oss.str();
        } catch(std::out_of_range) {
            try{
                long double ld = std::stold(val);
                d = ld;
                oss << d;
                ret_val = oss.str();
            } catch (std::out_of_range) {
                ret_val = "inf";
            }
        }
    }
    bool neg = false;
    if(val == "" || val == name) //double x{}  val = "" or double d = d
    {
        return "0";
    }
    if(val.find("++") != std::string::npos || val.find("--") != std::string::npos || val.find('!') != std::string::npos) // double d = x++
    {
        ret_val = resolveOperation(val);
    }

    if(val[0] == '-' || val[0] == '+') // double x = -789;
    {
        int i = 0;
        while(val[i] == '-' || val[i] == '+' || val[i] == '(') //for +-+-+-+-+-+-+-+-5;
        {
            if (val[i] == '(') {
                ++i;
                continue;
            }
            if(val[i] == '-'){
                neg = !neg;
            }
            ++i;
        }
        val.erase(0, i);
    }
    if (val[0] == '0'){ //for double d = 00000.33;
        int i = 0;
        while(val[i] == '0')
        {
            ++i;
        }
        val = val.erase(0,i);
    }
    if (val[0] == '.'){ //for double d = .3;
        val = '0' + val;
    }
    if (std::isdigit(val[0]))
    {
        std::ostringstream oss; //creating buffer object to get the correct form of the value
        double d;
        try {
            d = std::stod(val);
            oss << d;
            ret_val = oss.str();
        } catch(std::out_of_range& e) {
            long double ld = std::stold(val);
            d = ld;
            oss << d;
            ret_val = oss.str();
        }
    }
    else if (val == "true")
    {
        ret_val = "1";
    }
    else if (val == "false")
    {
        ret_val = "0";
    }
    else if (val.front() == '\'' && val.back() == '\'')// val = 'a'  val = '\0'
    {
        val.erase(0, 1);                                 // Erase the first character (')
        val.erase(val.length() - 1);                    // Erase the last character (')
        if(val.size() == 1)
        {
            short tmp = static_cast<short>(val[0]);
            ret_val = std::to_string(tmp);
        }
        else if(val.size() == 2)// '\t' '\n' and more than one symbol in char arent handled
        {
            if(val[1] == 'n')  ret_val = "10";
            if(val[1] == 't')  ret_val = "9";
            if(val[1] == 'b')   ret_val = "8";
            if(val[1] == 'r')   ret_val = "13";
            if(val[1] == 'v')  ret_val = "11";
            if(val[1] == 'f')  ret_val = "12";
            if(val[1] == 'a')  ret_val = "7";
            if(val[1] == '\\')  ret_val = "92";
            if(val[1] == '?')  ret_val = "63";
            if(val[1] == '\'')  ret_val = "39";
            if(val[1] == '\"')  ret_val = "34";
            if(val[1] == '0')  ret_val = "0";
        }
        else if (val[1] == 'x'){ //for double d = '\x7a'; hexical numbers
            if (std::isdigit(val[2]) || ('a' <= val[2] && 'f' >= val[2]) || ('A' <= val[2] && 'F' >= val[2])){
                std::string hexVal = "";
                for(int i = 2; std::isdigit(val[i]) || ('a' <= val[i] && 'f' >= val[i]) || ('A' <= val[i] && 'F' >= val[i]); ++i)
                {
                    hexVal += val[i];
                }
                int tmp = std::stoi(hexVal, nullptr, 16);
                if (tmp >= 0 && tmp <= 127){
                    ret_val = std::to_string(tmp);
                } else if (tmp >127 && tmp <256){
                    tmp -= 256;
                    ret_val = std::to_string(tmp);
                }
            }
        }
        else if (std::isdigit(val[1]) && (val[1] >=48 && val[1] <=55)){ //for double d = '\21';  octal numbers
            std::string octVal = "";
            for(int i = 1; std::isdigit(val[i]) && (val[i] >=48 && val[i] <=55); ++i)
            {
                octVal += val[i];
            }
            int tmp = std::stoi(octVal, nullptr, 8);
            if (tmp >= 0 && tmp <= 127){
                ret_val = std::to_string(tmp);
             }
             else if (tmp >127 && tmp <256){
                tmp -= 256;
                ret_val = std::to_string(tmp);
             }
        }
    } else {
       ret_val = doubleCast(SC -> getValueByName(val).first);
    }

    if (neg) {
        ret_val = "-" + ret_val;
    }
    if (ret_val.find('.') != std::string::npos){ //for 5.00000 -> 5
        while(ret_val.back() == '0'){
            ret_val.pop_back();
        }
    }
    return ret_val;
}*/

//     // Remove leading zeros
//     if (digits.front() == 0) {
//         int index = 0;
//         while(digits[index] == 0 && index < digits.size()) {
//             ++index;
//         }
//         digits.erase(digits.begin(), digits.begin() + index);
//         if(digits.empty()) {
//             digits.push_back(0); // If digits become empty, set it to '0'
//         }
//     }

//     // Add back the negative sign if the number was originally negative
//     if (negative) {
//         digits.insert(digits.begin(), '-');
//     }

//     // Convert vector of digits back to string representation
//     num.clear();
//     for (int i = 0; i < digits.size(); ++i) {
//         if (digits[i] == 45) {
//             num += '-'; // Add negative sign
//         } else if (digits[i] == -2) {
//             num += '.'; // Add decimal point
//         } else {
//             num += static_cast<char>(digits[i] + 48); // Convert integer to ASCII
//         }
//     }

//     // Handle special cases for the final output
//     if (num == "-") {
//         num = "0"; // If the result is just a negative sign, set it to '0'
//     } else if (num == "-0") {
//         num = num.substr(1); // Remove negative sign if result is "-0"
//     } else if (num.find("-.") != std::string::npos) {
//         num = num.substr(1); // Remove negative sign if result starts with "-."
//         num.insert(num.begin(), '0'); // Insert '0' before '.'
//     }

//     // Return the final result
//     return num;
// }

// static std::string Type::char_cast_to_int(std::string str)
// {
//     if (str[0] == '\'') {
//         if (str[1] == '\\') {
//             if (str[2] == 'a') {
//                 str = "7";
//             } else if (str[2] == 'b') {
//                 str = "8";
//             } else if (str[2] == 't') {
//                 str = "9";
//             } else if (str[2] == 'n') {
//                 str = "10";
//             } else if (str[2] == 'v') {
//                 str = "11";
//             } else if (str[2] == 'f') {
//                 str = "12";
//             } else if (str[2] == 'r') {
//                 str = "13";
//             } else if (str[2] == '\"') {
//                 str = "34";
//             } else if (str[2] == '\'') {
//                 str = "39";
//             } else if (str[2] == '\?') {
//                 str = "63";
//             } else if (str[2] == '\\') {
//                 str = "92";
//             } else if (str[2] == 'x') { //'\xFF' -> -1
//                str = str.substr(3);
//                str.pop_back();
//                int x = std::stoi(str, 0, 16);
//                if (x >= 128) {
//                    x = 256 - x;
//                    str += '-';
//                }
//                str += std::to_string(x);
//             } else if (std::isdigit(str[2])) { // '\101' -> 65
//                str = str.substr(2);
//                str.pop_back();
//                int x = std::stoi(str, 0, 8);
//                if (x > 127) {
//                    x = 256 - x;
//                    str += '-';
//                }
//                str += std::to_string(x);
//            }
//         } else {
//             int x = static_cast<int>(str[1]);
//             str = std::to_string(x);
//         }
//     }
//     return str;
// }

// static std::string Type::intCast(std::string num)
// {
//     int integer_value = 0;
//     bool isNegative = false;
//     if (num == "inf" || num == "nan"){
//         integer_value = -2147483648;
//     } else if (num.find('e') != std::string::npos || num.find('.') != std::string::npos) {
//         std::istringstream iss(num);
//         long double floating_point_number;
//         iss >> floating_point_number;
//         if (floating_point_number > INT_MAX) {
//             integer_value = INT_MAX;
//         } else {
//             integer_value = static_cast<int>(floating_point_number);
//         }
//     } else if (num.find('\'') != std::string::npos) {
//         return char_cast_to_int(num);
//     } else {
//         for (char c : num) {
//             if (c == '-') {
//                 isNegative = true;
//             }
//             if (std::isdigit(c)) {
//                 integer_value = integer_value * 10 + (c - '0');
//             }
//             // else if (found_digit) {
//             //     //in case sees 'ull', 'u' etc.
//             //     break;
//             // }
//         }
//         if (isNegative) {
//             integer_value = -integer_value;
//         }
//     }
//     //need to handle cases like
//     // double x = infinty();
//     // int k = x; -> x = int_min
//     // int h = infinty(); -> x = int_max

//     // bool found_digit = false;
//     // bool isNegative = false;
// //     if (num.find('e') != std::string::npos) {
// //         try {
// //             num = std::to_string(std::stold(num));
// //         } catch (std::out_of_range& e) {
// //              if(num[0] == '-') {
// //                 num =  std::to_string(INT_MIN);
// //             } else {
// //                 num = std::to_string(INT_MAX);
// //             }
// //             return num;
// //         }
// //     }
// //     if (num.find('.') != std::string::npos) {
// //         num  = num.substr(0, num.find('.'));
// //         try {
// //             num = std::to_string(std::stoi(num));
// //         } catch (std::out_of_range& e) {
// //             if(num[0] == '-') {
// //                 num =  std::to_string(INT_MIN);
// //             } else {
// //                 num = std::to_string(INT_MAX);
// //             }
// //         }
// //         return num;
// //     }
//     // for (char c : num) {
//     //     if (c == '-' && !found_digit) {
//     //         isNegative = true;
//     //     } else if (std::isdigit(c)) {
//     //         integer_value = integer_value * 10 + (c - '0');
//     //         found_digit = true;
//     //     }
//     //
//     // }
//     // if (isNegative) {
//     //     integer_value = -integer_value;
//     // }
//     return std::to_string(integer_value);
// }

// static std::string Type::charCast(std::string num)
// {
//     char char_value = 0;
//     std::istringstream iss(num);
//     long double number;
//     iss >> number;
//     if (number < 0) {  // harcnel
//         return "Garbage";

//     }
//     if (number < 33) {

//         std::map<int, std::string> ascii_nums = { // char t = 7; in ui -> '\a'
//             {0, "NULL"}, {1, "SOH"}, {2, "STX"}, {3, "ETX"}, {4, "EOT"}, {5, "ENQ"},
//             {6, "ACK"}, {7, "'\\a'"}, {8, "'\\b'"}, {9, "'\\t'"}, {10, "'\\n'"},
//             {11, "'\\v'"}, {12, "'\\f'"}, {13, "'\\r'"}, {14, "SO"}, {15, "SI"},
//             {16, "DLE"}, {17, "DC1"}, {18, "DC2"}, {19, "DC3"}, {20, "DC4"}, {21, "NAK"},
//             {22, "SYN"}, {23, "ETB"}, {24, "CAN"}, {25, "EM"}, {26, "SUB"}, {27, "ESC"},
//             {28, "FS"}, {29, "GS"}, {30, "RS"}, {31, "US"}, {32, " "}
//         };

//         auto it = ascii_nums.find(number);
//         if (it != ascii_nums.end()) {
//             num = it -> second;
//         }
//     } else {
//         char_value = static_cast<char>(number);
//         num = "'" + std::string(1, char_value) + "'";
//     }
//    return num;
// }

// static std::string Type::floatCast(std::string num)
// {
//     return num;
// }

// static std::string Type::doubleCast(std::string num)
// {
//     return num;
// }

// static std::string Type::boolCast(std::string num)
// {
//     bool result = 0;
//     std::istringstream iss(num);
//     iss >> result;
//     return std::to_string(result);
// }

// static std::string Type::shortCast(std::string num)
// {
//     short short_value = 0;
//     bool isNegative = false;
//     if (num == "inf" ){
//         short_value = 0;
//     } else if (num.find('e') != std::string::npos || num.find('.') != std::string::npos) {
//         if (num.back() == 'f') {
//             num.pop_back();
//         }

// <<<<<<< Updated upstream
// std::string Type::postfixIncrement(std::string var_name)
/*
{
    bool type_contains_char = false;
    std::string type_of_var = SC -> getValueByName(var_name).second;
    std::string value;
    if (type_of_var.find("char") != std::string::npos) {
        //if type contains char get its value from type_info
        type_contains_char = true;
        std::vector<std::string> tokens = Tokenizing(type_of_var);
        value = tokens[tokens.size() - 1];
        type_of_var = "";
        for (int i = 0; i < tokens.size() - 1; ++i) {
            type_of_var +=tokens[i];
        }
    } else if (type_of_var.find("float") != std::string::npos || type_of_var.find("double") != std::string::npos) {
        value = std::to_string(std::stold(SC -> getValueByName(var_name).first));
    } else {
        value  = SC -> getValueByName(var_name).first;
    }
    //story temporary value of a variable to return it
    std::string temp_value = value;

    // value = ; //somewhere on ui, needed to be resolved, eg usingned char 48
    value = plusOne(value);     //add value by one
    value = (this->*Type::castTable[type_of_var])(value);

    //when type of the variable contains char store it in a buffer and read from it as a character
    if (type_contains_char) {
//        std::string char_value;
//        std::ostringstream oss;
//        oss << static_cast<char>(std::stoi(value));
//        char_value = oss.str();

//        //set value like 'A'
//        SC -> setValueByName(var_name, '\'' + char_value + '\'');
        //change the value stored with type_info // "char 65" -> "char 66"
        SC -> changeType(var_name,  type_of_var + " " + temp_value);
    } else {
        SC -> setValueByName(var_name, value);
    }
    //return the initial value
    return temp_value;*/
//         std::istringstream iss(num);
//         long double floating_point_number;
//         iss >> floating_point_number;
//         if (floating_point_number > SHRT_MAX) {
//             short_value = SHRT_MAX;
//         } else {
//             short_value = static_cast<short>(floating_point_number);
//         }
//     } else {
//         for (char c : num) {
//             if (c == '-') {
//                 isNegative = true;
//             }
//             if (std::isdigit(c)) {
//                 short_value = short_value * 10 + (c - '0');
//             }
//         }
//         if (isNegative) {
//             short_value = -short_value;
//         }
//     }
//    return std::to_string(short_value);
// }

// static std::string Type::resolveOperation(std::string expr)
// {
//     std::string result;
//     std::string operation; // ++, !, ~
//     int index = 0;
//     while (expr[index] == '+' || expr[index] == '-' || expr[index] == '!' || expr[index] == '~') {
//         operation += expr[index++];
//     }
//     if (operation == "!") {
//         result = logicalNot(expr.substr(index));
//     } else if (operation == "~") {
//         result = bitwiseNot(expr.substr(index));
//     } else if (operation == "++") {
//         result = prefixIncrement(expr.substr(index));
//     } else if (operation == "--") {
//         result = prefixDecrement(expr.substr(index));
//     } else if (operation == ""){ // op == ""
//         if (expr[expr.size() - 1] == '+') {
//             result = postfixIncrement(expr.substr(0, expr.size() - 2));
//         } else {
//             result = postfixDecrement(expr.substr(0, expr.size() - 2));
//         }
//     } else {
//        // result = callToAst(expr); //x += y, x += ++y
//     }
//     return result;
// }

// std::string Type::operator +=(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     // x += y
//     tokens[1] = " + ";
//     expr = "";
//     for(int i = 0; i < tokens.size(); ++i) {
//         expr += " " + tokens[i];
//     }
//     AST ob(expr);
//     return std::to_string(static_cast<double>(ob));
// }

// std::string Type::operator -=(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     // x -= y
//     tokens[1] = " - ";
//     expr = "";
//     for(int i = 0; i < tokens.size(); ++i) {
//         expr += " " + tokens[i];
//     }
//     AST ob(expr);
//     return std::to_string(static_cast<double>(ob));
// }

// std::string Type::operator *=(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     // x *= y
//     tokens[1] = " * ";
//     expr = "";
//     for(int i = 0; i < tokens.size(); ++i) {
//         expr += " " + tokens[i];
//     }
//     AST ob(expr);
//     return std::to_string(static_cast<double>(ob));
// }

// std::string Type::operator /=(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     // x /= y
//     tokens[1] = " / ";
//     expr = "";
//     for(int i = 0; i < tokens.size(); ++i) {
//         expr += " " + tokens[i];
//     }
//     AST ob(expr);
//     return std::to_string(static_cast<double>(ob));
// }

// std::string Type::operator %=(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     // x %= y
//     tokens[1] = " % ";
//     expr = "";
//     for(int i = 0; i < tokens.size(); ++i) {
//         expr += " " + tokens[i];
//     }
//     AST ob(expr);
//     return std::to_string(static_cast<double>(ob));
// }

// std::string Type::operator &=(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     // x &= y
//     tokens[1] = " & ";
//     expr = "";
//     for(int i = 0; i < tokens.size(); ++i) {
//         expr += " " + tokens[i];
//     }
//     AST ob(expr);
//     return std::to_string(static_cast<double>(ob));
// }

// std::string Type::operator ^=(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     // x ^= y
//     tokens[1] = " ^ ";
//     expr = "";
//     for(int i = 0; i < tokens.size(); ++i) {
//         expr += " " + tokens[i];
//     }
//     AST ob(expr);
//     return std::to_string(static_cast<double>(ob));
// }

// std::string Type::operator |=(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     // x |= y
//     tokens[1] = " | ";
//     expr = "";
//     for(int i = 0; i < tokens.size(); ++i) {
//         expr += " " + tokens[i];
//     }
//     AST ob(expr);
//     return std::to_string(static_cast<double>(ob));
// }

// std::string Type::operator <<=(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     // x <<= y
//     tokens[1] = " << ";
//     expr = "";
//     for(int i = 0; i < tokens.size(); ++i) {
//         expr += " " + tokens[i];
//     }
//     AST ob(expr);
//     return std::to_string(static_cast<double>(ob));
// }

// std::string Type::operator >>=(std::string expr)
// {
//     std::vector<std::string> tokens = Tokenizing(expr);
//     // x >>= y
//     tokens[1] = " >> ";
//     expr = "";
//     for(int i = 0; i < tokens.size(); ++i) {
//         expr += " " + tokens[i];
//     }
//     AST ob(expr);
//     return std::to_string(static_cast<double>(ob));
// }

// static std::string Type::logicalNot(std::string var_name)
// {
//     //logica operations doesn't work with floating_point numbers
//     std::string type = SC -> getValueByName(var_name).second;
//     std::string value = SC -> getValueByName(var_name).first;
//     double result;
//     try {
//         result = std::stold(value);
//         if (result) {
//             result = 0;
//         } else {
//             result = 1;
//         }
//     } catch (std::invalid_argument& e) {
//         if (value == "'\0'") {
//             result = 1;
//         } else {
//             result = 0;
//         }
//     }
//     // catch (std::out_of_range& e) {

//     // }
//     return std::to_string(result);
// }

// static std::string Type::bitwiseNot(std::string var_name)
// {
//      //double and float numbers aren't considered
//     std::string type = SC -> getValueByName(var_name).second;
//     std::string value = SC -> getValueByName(var_name).first;
//     int result;
//     if (type.find("unsigned") != std::string::npos) {
//         // must support also unsigned versions, it will have another implementation
//     } else {
//         if(type.find("char") != std::string::npos) {
//             std::vector<std::string> tokens = Tokenizing(type);
//             std::cout << "here is it; "<< std::endl;
//             result = std::stoll(tokens[tokens.size() - 1]);
//         } else {
//             if (std::isdigit(var_name[0])) {
//                 result = std::stoi(value);
//             } else {
//                 result = std::stoi(SC -> getValueByName(var_name).first);
//             }
//         }
//     }
//     return std::to_string(~result);
// }

// static std::string Type::postfixIncrement(std::string var_name)
// {
//     bool type_contains_char = false;
//     std::string type_of_var = SC -> getValueByName(var_name).second;
//     std::string value;

//     if (type_of_var.find("char") != std::string::npos) {
//         //if type contains char get its value from type_info
//         type_contains_char = true;
//         std::vector<std::string> tokens = Tokenizing(type_of_var);
//         value = tokens[tokens.size() - 1];
//         type_of_var = "";
//         for (int i = 0; i < tokens.size() - 1; ++i) {
//             type_of_var +=tokens[i];
//         }
//     } else if (type_of_var.find("float") != std::string::npos || type_of_var.find("double") != std::string::npos) {
//         value = std::to_string(std::stold(SC -> getValueByName(var_name).first));
//     } else {
//         value  = SC -> getValueByName(var_name).first;
//     }
//     //store temporary value of a variable to return it
//     std::string tmp_value = value;
//     value = plusOne(value);     //add value by one
//     std::string tmp_value_for_char = value;  //store added value in a string to add it to type_info
//     value = (this->*Type::castTable[type_of_var])(value);
//     if (type_contains_char) {
//         SC -> changeType(var_name, type_of_var + " " + tmp_value_for_char);
//     }
//     SC -> setValueByName(var_name, value);
//     return tmp_value;
// }

// static std::string Type::prefixDecrement(std::string expr)
// {
//     return expr;
// }

// static std::string Type::prefixIncrement(std::string var_name)
// {
//     bool type_contains_char = false;
//     std::string type_of_var = SC -> getValueByName(var_name).second;
//     std::string value;

//     if (type_of_var.find("char") != std::string::npos) {
//         //if type contains char get its value from type_info
//         type_contains_char = true;
//         std::vector<std::string> tokens = Tokenizing(type_of_var);
//         value = tokens[tokens.size() - 1];
//         type_of_var = "";
//         for (int i = 0; i < tokens.size() - 1; ++i) {
//             type_of_var +=tokens[i];
//         }
//     } else if (type_of_var.find("float") != std::string::npos || type.find("double") != std::string::npos) {
//         value = std::to_string(std::stold(SC -> getValueByName(var_name).first));
//     } else {
//         value  = SC -> getValueByName(var_name).first;
//     }

//     // value = ; //somewhere on ui, needed to be resolved, eg usingned char 48
//     value = plusOne(value); //add value by one

//     std::string tmp_value_for_char;
//     if(type_contains_char) {
//         tmp_value_for_char = value;
//     }
//     value = (this->*Type::castTable[type_of_var])(value);

//     if (type_contains_char) {
//         SC -> changeType(var_name, type_of_var + " " + tmp_value_for_char);
//     }
//     SC -> setValueByName(var_name, value);

//     //return changed value
//     if(type_contains_char) {
//         return tmp_value_for_char;
//     }
//     return value;
// }

// static std::string Type::postfixDecrement(std::string expr)
// {
//     return expr;
// }

Type::~Type()
{

}
