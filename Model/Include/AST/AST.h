#ifndef AST_H
#define AST_H
#include"../../Scope/scope.h"
#include"../../../Server/ControlBlock/controlblock.h"
#include "../Operations/Operations.h"

//#include"../../GeneralTypes/Types/Type/Type.h"

//Works with variables too
//Use only operators listed in unordered map, Can also use parentheses, Comma separated expressions, Ternar operator
//Do not cout << tree.calculate();
//cout << tree; will work now on
class AST {
public:
    AST(const std::string& expression); //Constructs Tree from given expression
    AST(const std::string& expression, std::vector<std::pair<double, std::string>>& args);//Passed vector will be filled with function call arguments' evaluated values
    operator double(); //Implicitly casts(returns) AST object to it's calculated value
    void levelOrderTraversal(); //Wrapper around private levelOrderTraversalHelper

private:
    struct Node { //Node is either number node, or operator node
        Node* left;
        Node* right;
        std::string val;
        int level;
        bool isOperator; //Is Node containing operator value
        Node(std::string value, bool isOp, int lvl) : left(nullptr), right(nullptr), val(value), isOperator(isOp), level(lvl)
        {}
    };

    void tokenize(const std::string& input); //Tokenizes string, dividing it into seprate tokens
    Node* rrotate(Node* node); //Right rotatation
    Node* LastCheck(Node* l); //Checks if there is need for rotations
    Node* resolve(std::vector<std::string> ::const_iterator start, std::vector<std::string> ::const_iterator end, std::vector<std::string>::const_iterator& reach, int level); //Here main resolving logic is written
    double calculate(Node* root); //Returns value of expression
    void levelOrderTraversalHelper(Node* root); //Prints the tree
    int getHeight(Node* root); //Returns height of given node
    void collectArgs(Node* node, std::vector<std::pair<double, std::string>>& args);//Collects function all arguments evaluated results
private:
    std::vector<std::string> tokens; //Contains tokens
    Node* root; //Root operator of expression
    std::unordered_map<std::string, int> power; //Contains all operators with their priorities
    Scope* scope;
    ControlBlock* cb;
};


#endif //AST_H
