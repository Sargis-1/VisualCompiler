#include "AST.h"
#include"../../Scope/scope.h"

//Use only operators listed in unordered map, except for ternar operator, Can also use parentheses, Comma separated expressions
//Works with variables too
AST::AST(const std::string& expression) : scope(Scope::getScope()), cb(ControlBlock::getControlBlock())
{
    tokenize(expression);//Tokenizes expression
    power = {    //Sets operators and their priorities
        {"*", 10},
        {"/", 10},
        {"%", 10},
        {"+", 9},
        {"-", 9},
        {"<<", 8},
        {">>", 8},
        {"<", 7},
        {">", 7},
        {"<=", 7},
        {">=", 7},
        {"==", 6},
        {"!=", 6},
        {"&", 5},
        {"^", 4},
        {"|", 3},
        {"&&", 2},
        {"||", 1},
        {":", 0},
        {"?", -1},
        {",", -2}
    };

    auto reach = tokens.cbegin();
    root = resolve(tokens.begin(), tokens.end(), reach, 0);//Constructs the tree from given expression

}

AST::AST(const std::string &expression, std::vector<std::pair<double, std::string>>& args) : scope(Scope::getScope()), cb(ControlBlock::getControlBlock())
{
    tokenize(expression);//Tokenizes expression
    power = {   //Sets operators and their priorities
        {"*", 10},
        {"/", 10},
        {"%", 10},
        {"+", 9},
        {"-", 9},
        {"<<", 8},
        {">>", 8},
        {"<", 7},
        {">", 7},
        {"<=", 7},
        {">=", 7},
        {"==", 6},
        {"!=", 6},
        {"&", 5},
        {"^", 4},
        {"|", 3},
        {"&&", 2},
        {"||", 1},
        {":", 0},
        {"?", -1},
        {",", -2}
    };


    if(expression.size() == 2 && expression[0] == '(' && expression[1] == ')'){
        return;
    }

    auto reach = tokens.cbegin();
    root = resolve(tokens.begin(), tokens.end(), reach, 0);
    collectArgs(root, args);//Collects function call arguments and pushes them into args}
    //std::cout << "1111" << std::endl;
}

AST::operator double()
{
    double result = calculate(root);
    if (result == std::numeric_limits<double>::max()) {//if max value returned means something gone wrong
        std::cout << "Something went wrong" << std::endl;
    }
    return result;
}

double AST::calculate(Node* root)
{
    //Recursively calculates value of expression
    if (!root) {
        return 0.0;
    }

    if (isdigit(root -> val[0]) || isdigit(root->val[1])) {
        if(std::find(root -> val.begin(), root -> val.end(), '.') != root -> val.end()){//floating point number
            return std::stod(root -> val);
        }else{
            return std::stoi(root -> val);
        }
    }else if(root -> val[0] == '\'' && root -> val.back() == '\''){//is temporary char
        Operations charCase;
        return std::stoi(charCase.char_cast_to_int(root ->val));
    }else if(power.find(root -> val) == power.end() && root -> val != "(" && root -> val != ")"){//add char variable case
        std::string variableValue = scope -> getValueByName(root -> val).first;
        if(variableValue.empty()){
            Operations expr(root -> val);
            auto value = expr.getResultAndVariable_type().first;
            variableValue = value;
        }

        if(std::find(variableValue.begin(), variableValue.end(), '.') != variableValue.end()){//floating point number
            return std::stod(variableValue);
        }else{
            return std::stoi(variableValue);
        }

    }

    if (root -> val == "+") {
        return calculate(root -> left) + calculate(root -> right);
    } else if (root -> val == "*") {
        return calculate(root -> left) * calculate(root -> right);
    } else if (root -> val == "/") {
        auto leftval =  calculate(root->left);
        auto rightval = calculate(root->right);
        std::string left = std::to_string(leftval);
        std::string right = std::to_string(rightval);
        if(std::find(left.begin(), left.end(), '.') == left.end() || std::find(right.begin(), right.end(), '.') == right.end() ){//variable is floating point number
            if (rightval != 0)
                return static_cast<double>(leftval) / static_cast<double>(rightval);
            else {
                std::cout << "Integer division by zero" << std::endl;
                return std::numeric_limits<double>::max();
            }
        }else{//intergal case
            if (rightval != 0)
                return static_cast<int>(leftval) / static_cast<int>(rightval);
            else {
                std::cout << "Integer division by zero" << std::endl;
                return std::numeric_limits<double>::max();
            }
        }
    } else if (root -> val == "%") {
        double rightval = calculate(root -> right);
        if (rightval != 0) {
            return static_cast<int>(calculate(root -> left)) % static_cast<int>(rightval);
        } else {
            std::cout << "Integer division by zero" << std::endl;
            return std::numeric_limits<double>::max();
        }
    } else if (root -> val == "-") {
        return calculate(root -> left) - calculate(root -> right);
    } else if (root -> val == "<<") {
        return static_cast<int>(calculate(root -> left)) << static_cast<int>(calculate(root -> right));
    } else if (root -> val == ">>") {
        return static_cast<int>(calculate(root -> left)) >> static_cast<int>(calculate(root -> right));
    } else if (root -> val == "&") {
        return static_cast<int>(calculate(root -> left)) & static_cast<int>(calculate(root -> right));
    } else if (root -> val == "^") {
        return static_cast<int>(calculate(root -> left)) ^ static_cast<int>(calculate(root -> right));
    } else if (root -> val == "|") {
        return static_cast<int>(calculate(root -> left)) | static_cast<int>(calculate(root -> right));
    } else if (root -> val == "&&") {
        return calculate(root -> left) && calculate(root -> right);
    } else if (root -> val == "||") {
        return calculate(root -> left) || calculate(root -> right);
    } else if (root -> val == "==") {
        return calculate(root -> left) == calculate(root -> right);
    } else if (root -> val == "!=") {
        return calculate(root -> left) != calculate(root -> right);
    } else if (root -> val == "<") {
        return calculate(root -> left) < calculate(root -> right);
    } else if (root -> val == "<=") {
        return calculate(root -> left) <= calculate(root -> right);
    } else if (root -> val == ">=") {
        return calculate(root -> left) >= calculate(root -> right);
    } else if (root -> val == ">") {
        return calculate(root -> left) > calculate(root -> right);
    } else if (root -> val == "?") {
        if (calculate(root -> left) != 0) {
            return root -> right && root -> right -> left ? calculate(root -> right -> left) : std::numeric_limits<double>::max();
        } else {
            return root -> right && root -> right -> right ? calculate(root -> right -> right) : std::numeric_limits<double>::max();
        }
    } else if (root -> val == ">") {
        return calculate(root -> left) > calculate(root -> right);
    }else if (root->val == ",") {
        double previous = calculate(root->left);//First calculate expression before comma
        return  calculate(root->right);//then calculate and return last expression i.e. after comma
    }
    else {
        std::cout << "Using unsupported operator" << std::endl;
    }
    return std::numeric_limits<double>::max();
}

void AST::levelOrderTraversalHelper(Node* root)
{
    if (!root) {
        return;
    }

    std::string block = "     ";
    std::queue<Node*> q;//Queue is used to print tree level by level
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size(); // Number of nodes at the current level
        int height = 0;
        // Process all nodes at the current level
        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            if (!current) {
                //std::cout << block << block;
                q.pop();
                continue;
            }

            if (i == 0) {
                height = getHeight(current);
                std::string space;
                while (height + 1) {
                    space += block;
                    --height;
                }

            }

            if (i != 0) {
                if (current && current -> isOperator) {
                    //std::cout << " , " << calculate(current);
                }
            }

            q.push(current -> left);
            q.push(current -> right);
            q.pop();
        }
       // std::cout << std::endl << std::endl; // Move to the next line after processing a level
    }
}

int AST::getHeight(Node* root)
{
    if (!root) {
        return 0;
    }

    return std::max(getHeight(root -> left), getHeight(root -> right)) + 1;
}

void AST::collectArgs(Node *node, std::vector<std::pair<double, std::string>>& args)
{
    if(!node){
        return;
    }

    if (node->val != ",") {//First met operator which is not comma, is the first argument, calculate it and return
        if(!node -> left && !node -> right && !isdigit(node -> val[0]) && !((node -> val[0] == '-' || node -> val[0] == '+') && isdigit(node -> val[1]))
            && power.find(node->val) == power.end()){//if is not digit or operator
            auto status = scope -> getValueByName(node -> val);
            if(status.first.size() > 0){//is variable
                args.push_back(std::make_pair(std::stod(status.first), status.second));
            }else if(node -> val[0] == '\'' && node -> val.back() == '\''){
                Operations charCase;
                std::string castedVal = charCase.char_cast_to_int(node -> val);
                args.push_back(std::make_pair(std::stoi(castedVal), ""));
            }else{//if is increment or decrement or other operation
                Operations op(node -> val);
                auto valofop = op.getResultAndVariable_type();
                args.push_back(std::make_pair(std::stod(valofop.first), valofop.second));
            }
        }else{
            args.push_back({calculate(node), ""});//If is operator or digit
        }
        return;
    }

    collectArgs(node -> left, args);

    if(node -> right){
        if(!node->right->left && !node->right->right && !isdigit((node->right->val)[0]) && !((node -> val[0] == '-' || node -> val[0] == '+') && isdigit(node -> val[1]))
            && power.find(node->right->val) == power.end()){
            auto status = scope->getValueByName(node -> right -> val);
            if(status.first.size() > 0){//is variable
                args.push_back(std::make_pair(std::stod(status.first), status.second));
            }else if(node -> right -> val[0] == '\'' && node -> right -> val.back() == '\''){//is temporary char
                Operations charCase;
                std::string castedVal = charCase.char_cast_to_int(node -> right -> val);
                args.push_back(std::make_pair(std::stoi(castedVal), ""));
            }else{//if is increment or decrement or other operation
                Operations op(node -> right -> val);
                auto valofop = op.getResultAndVariable_type();
                args.push_back(std::make_pair(std::stod(valofop.first), valofop.second));
            }
        }else{
            args.push_back({calculate(node->right), ""});
        }
    }
}

void AST::levelOrderTraversal()
{
    levelOrderTraversalHelper(root);
}

void AST::tokenize(const std::string& input)
{
    if(input.front() == '(' && input.back() == ')' && input.size() < 4){ //(2), (x) case
        tokens.push_back("(");
        tokens.push_back(input.substr(1, input.size() - 2));
        tokens.push_back(")");
        return;
    }

    std::stringstream iss(input);
    std::string token;

    //Tokenizes and separates every parentheses, comma's and numbers
    while (iss >> token)
    {
        if (token.size() == 1) {
            tokens.push_back(token);
        }
        else {
            if (token[0] == '(') {
                bool found = false;//In this case (((7,      there is ',' in the end
                if (token[token.size() - 1] == ',') {
                    token.pop_back();
                    found = true;//mark as true to indicate that the case above is met
                }

                int i = 0;
                while (token[i] == '(') {//while there is '(' push them as separate tokens
                    tokens.push_back("(");
                    ++i;
                }
                //After pushing parentheses, the number or variable name is left only
                tokens.push_back(token.substr(i));//Push variable or number

                if(found){
                    tokens.push_back(",");//push ',', if it was in the end of original token
                }
            }
            else {//token dosen't start with '('
                if (token[token.size() - 1] == ')') {//If there is ')' in the end
                    //Same logic as above
                    int i = token.size() - 1;
                    std::vector<std::string> tmp;
                    while (token[i] == ')') {
                        tmp.push_back(")");
                        token.pop_back();
                        --i;
                    }

                    tokens.push_back(token);

                    for (const std::string& str : tmp) {
                        tokens.push_back(str);
                    }

                }
                else if (token[token.size() - 1] == ',') {//if there is comma in the end "8," or "9))))," cases
                    token.pop_back();//pop the comma in the end
                    if (token[token.size() - 1] == ')') {
                        int i = token.size() - 1;
                        std::vector<std::string> tmp;
                        while (token[i] == ')') {
                            tmp.push_back(")");
                            token.pop_back();
                            --i;
                        }

                        tokens.push_back(token);

                        for (const std::string& str : tmp) {
                            tokens.push_back(str);
                        }
                    }
                    else {
                        tokens.push_back(token);//
                    }

                    tokens.push_back(",");//push ',', if it was in the end of original token
                }
                else {
                    tokens.push_back(token);//standalone number or variable
                }
            }
        }

    }

    // std::cout << "Tokens " << std::endl;
    // for(const auto& elem : tokens){
    //     std::cout << elem << " ";
    // }
}

AST::Node* AST::rrotate(Node* node)
{
    if (node) {
        Node* y = node -> left;
        Node* l2 = y -> right;
        y -> right = nullptr;
        node -> left = l2;
        y -> right = node;
        return y;
    }
    return nullptr;
}

AST::Node* AST::LastCheck(Node* l)
{
    //Both if's check if current op has higher priority if its left, and if True rotates subtrees
    if (l && l -> left && l -> isOperator && l -> left -> isOperator && power[l -> val] > power[l -> left->val] && (l -> level >= l -> left -> level)) {
        Node* root = rrotate(l);

        if (l && l -> left && l -> isOperator && l -> left -> isOperator && power[l -> val] > power[l -> left->val] && (l -> level >= l -> left -> level)) {
            root -> right = rrotate(l);
        }

        return root;
    }

    return nullptr;
}

AST::Node* AST::resolve(std::vector<std::string>::const_iterator start, std::vector<std::string>::const_iterator end, std::vector<std::string>::const_iterator& reach, int level)
{
    Node* op = nullptr;
    Node* l = nullptr;
    Node* r = nullptr;
    Node* ternarRoot = nullptr;
    Node* LastTernar = nullptr;
    Node* lastOp = nullptr;

    if (start == end - 1) {
        return new Node(*start, 0, level);
    }

    if(tokens.size() == 3 && tokens.front() == "(" && tokens.back() == ")"){
        return new Node(*(++start), 0, level);
    }

    //Basic expression case like: 5 * 7
    if (std::distance(start, end) == 3) {
        l = new Node(*start, 0, level);
        op = new Node(*(start + 1), 0, level);
        r = new Node(*(start + 2), 0, level);
        op->left = l;
        op->right = r;
        reach = start + 2;
        return op;
    }

    std::cout << std::endl;
    for (auto& it = start; it != end; ++it) {
        if ((isdigit((*it)[0]) || isdigit((*it)[1])) || (power.find(*it) == power.end() && *it != "(" && *it != ")")){
            auto pos = std::find((*it).begin(), (*it).end(), '(');
            std::string func;
            //std::cout << "*it = " << *it << std::endl;
            if(pos != (*it).end()){
                while(*it != ")"){
                    if(power.find(*it) != power.end()){
                        func += " ";
                    }
                    func += *it;
                    if(power.find(*it) != power.end()){
                        func += " ";
                    }
                    ++it;
                }
                func += ")";
                func = cb -> processString(func);
            }

            if (!l) {
                if(func.size() != 0){
                    l = new Node(func, false, level);
                }else{
                    l = new Node(*it, false, level);
                }
            } else {
                if(func.size() != 0){
                    r = new Node(func, false, level);
                }else{
                    r = new Node(*it, false, level);
                }

                if (op) {
                    op -> right = r;
                }
            }
        } else {
            Node* newop = new Node(*it, true, level); //If current token is operator

            if (newop -> val == "(") {
                if (op && !op->left) {
                    op -> left = l;
                }

                if (op) {
                    op -> right = resolve(++it, end, reach, level + 1);
                } else {
                    l = resolve(++it, end, reach, level + 1);
                }

                if (reach > it) {
                    it = reach;
                }

                if (!op) {
                    op = l;
                } else {
                    l = op;
                    r = nullptr;
                }

                continue;
            } else if (newop -> val == ")") {
                reach = it;
                if (l && !op -> left) {
                    op -> left = l;
                }

                if (r && !op -> right) {
                    op -> right = r;
                }

                break;
            }

            if (ternarRoot && newop->val == "?") {
                if (lastOp -> val != "?" && lastOp -> val != ":" && getHeight(LastTernar) <= getHeight(lastOp)) {//To avoid cases where newop is not fully intergrated in tree
                    lastOp -> left = LastTernar -> right;//make it part of the tree, i.e left operand of newop must become right node of Last met ternar
                    Node* lr = LastCheck(lastOp);//Rotate if needed
                    if (lr){//if rotate needed
                        LastTernar -> right = lr;
                    }else{//if not
                        LastTernar -> right = lastOp;
                    }
                    r = nullptr;
                }

                Node* start = LastTernar;
                Node* newopsleft = start -> right;
                start -> right = newop;
                newop -> left = newopsleft;
                if (!op -> left){
                    op -> left = l;
                }

                r = nullptr;
                l = newop;
                op = newop;
                LastTernar = newop;
                continue;
            }


            if (ternarRoot && newop -> val == ":") {
                if (lastOp -> val != "?" && lastOp -> val != ":" && getHeight(LastTernar) <= getHeight(lastOp)) {//To avoid cases where newop is not fully intergrated in tree
                    lastOp -> left = LastTernar -> right;
                    Node* lr = LastCheck(lastOp);
                    if (lr){
                        LastTernar -> right = lr;
                    }else{
                        LastTernar -> right = lastOp;
                    }
                    r = nullptr;
                }


                if (l && l -> left && l -> isOperator && l -> left -> isOperator && power[l -> val] > power[l -> left -> val] &&
                    (l -> level >= l -> left -> level) && l -> val != ":" ) {
                    l = LastCheck(l);
                    op = l;
                }


                Node* start = ternarRoot;//Starting from root find the '?' with no ':' as right node
                Node* koracharcakan = nullptr;//assign the '?' with no ':' in the right to this pointer
                while (start && start -> right && start -> right -> right) {//
                    if (start -> val == "?" && start -> right -> val != ":"){
                        koracharcakan = start;//Keep last '?' that satisfies our condition
                    }
                    start = start -> right;//Go to right while not found
                }

                if (start -> val == "?" && start -> right->val != ":"){//check the same for last met node
                    koracharcakan = start;
                }

                if (!koracharcakan){//if this was left nullptr, assign it to the start
                    koracharcakan = start;
                }

                Node* iffalse = koracharcakan -> right;
                koracharcakan -> right = newop;
                newop -> left = iffalse;

                if (!op -> left){
                    op -> left = l;
                }

                r = nullptr;
                l = newop;
                op = newop;
                LastTernar = newop;
                continue;
            }

            if (l && r && !r -> isOperator && !l -> isOperator) {//l and r are numbers or variables
                op -> left = l;
                newop -> left = op;
                r = nullptr;
                l = newop;
                op = newop;
            } else if (l && l -> isOperator) {//l is operator
                if (op && op -> left -> isOperator && (power[op -> val] > power[op -> left -> val])
                    && (op -> level >= op -> left -> level) && op -> val != "?" && op -> val != ":") {//Rotate if needed if they are operators of the same level
                    newop -> left = rrotate(l);
                    Node* lr = newop -> left -> right;
                    if (lr && lr -> left && lr -> isOperator && lr -> left -> isOperator && power[lr -> val] > power[lr -> left -> val] && (lr -> level >= lr -> left -> level)) {
                        newop -> left -> right = rrotate(lr);
                    }
                } else {
                    newop -> left = l;
                }

                l = newop;
                op = newop;
            } else {
                op = newop;
            }

            if (!ternarRoot && op->val == "?") {
                ternarRoot = op;
                LastTernar = op;
            }

            if(newop->val != "?" || newop->val != ":"){
                lastOp = newop;
            }
        }
    }

    if (ternarRoot) {//if ternar operator was met return the tree with ternar root
        if (lastOp->left && lastOp->left->val == ":") {
            lastOp->left = LastTernar->right;
            Node* lr = LastCheck(lastOp);
            if (lr){
                LastTernar->right = lr;
            }else{
                LastTernar->right = lastOp;
            }
            r = nullptr;
        }

        return ternarRoot;
    }

    Node* root = nullptr;
    if (l && r && !r -> isOperator && !l -> isOperator) {//l and r are numbers or variables
        op -> left = l;
    }

    if(op && op->left->isOperator && (power[op->val] > power[op->left->val]) && (op->level >= op->left->level)){
        root = LastCheck(op);
    }

    if (!root){
        root = op;
    }

    return  root;
}
