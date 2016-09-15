#include <algorithm>

#include "Expresion.h"
#include "ProcessString.h"
#include "CreateVector.h"
#include "Error.h"
#include "Log.h"

#define ERROR_PREFIX "Invalid expresion: "

#define END_TOKEN "!end!"

std::vector<std::string> tokens;

std::string peek() {
    if(tokens[0] != END_TOKEN) {
        setErrorColumToBeginingOfString(tokens[0]);
    }

    return tokens[0];
}

std::string get() {
    if(tokens.size() == 0) {
        ERROR("expected more arguments");
    }

    std::string result = tokens[0];

    tokens.erase(tokens.begin());

    if(result != END_TOKEN) {
        setErrorColumToBeginingOfString(result);
    }

    return result;
}

Argument expression();

Argument word(std::string word) {
    long long base = 256;

    long long result = 0;
    for (int i=1; i<word.length() && word[i]!='\'' && word[i]!='"'; i++) {
        result = base*result + word[i];
    }

    return Argument(result);
}

bool isWord(std::string word) {
    return word[0] == '\'' || word[0] == '"';
}

Argument factor() {
    std::string argument = get();

    if (isIntager(argument)) {
        return Argument(toIntager(argument));
    } else if (Simbol::withName(argument) != -1) {
        return Argument(Simbol::tabel[Simbol::withName(argument)]);
    } else if (isWord(argument)) {
        return word(argument);
    } else if (argument == "(") {
        Argument result = expression();
        
        std::string bracket = get();
        if(bracket != ")") {
            ERROR("expected '", BOLD(")"), "' before '", BOLD(bracket), "'");
        }

        return result;
    } else if (argument == "-") {
        return factor().updateForNegation();
    } else if (argument == "~") {
        return factor().updateForComplementation();
    } else if(argument != END_TOKEN){
        ERROR("argument '", BOLD(argument), 
              "' was not declared in this scope");
    }

    return 0;
}

Argument termHighestPrecedence() {
    Argument result = factor();

    std::vector<std::string> highestPrecedenceOperators =
        createVector<std::string>("*")("/")("%")(">>")("<<");

    while (contains(highestPrecedenceOperators, peek())){
        std::string operand = get();

        if (operand == "*") {
            result *= factor();
        } else if (operand == "/") {
            result /= factor();
        } else if (operand == "%") {
            result %= factor();
        } else if (operand == ">>") {
            result >>= factor();
        } else if (operand == "<<") {
            result <<= factor();
        }
    }

    return result;
}

Argument termIntermediatePrecedence() {
    Argument result = termHighestPrecedence();

    std::vector<std::string> intermediatePrecedenceOperators =
        createVector<std::string>("&")("|")("^");

    while (contains(intermediatePrecedenceOperators, peek())){
        std::string operand = get();

        if (operand == "&") {
            result &= termHighestPrecedence();
        } else if (operand == "|") {
            result |= termHighestPrecedence();
        } else if (operand == "^") {
            result ^= termHighestPrecedence();
        }
    }

    return result;
}

Argument termLowPrecedence() {
    Argument result = termIntermediatePrecedence();

    std::vector<std::string> lowPrecedenceOperators =
        createVector<std::string>("+")("-")("==")("!=")("<=")(">=")("<")(">");

    while (contains(lowPrecedenceOperators, peek())){
        std::string operand = get();

        if (operand == "+") {
            result += termIntermediatePrecedence();
        } else if (operand == "-") {
            result -= termIntermediatePrecedence();
        } else if (operand == "==") {
            result = result == termIntermediatePrecedence();
        } else if (operand == "!=") {
            result = result != termIntermediatePrecedence();
        } else if (operand == "<=") {
            result = result <= termIntermediatePrecedence();
        } else if (operand == ">=") {
            result = result >= termIntermediatePrecedence();
        } else if (operand == "<") {
            result = result < termIntermediatePrecedence();
        } else if (operand == ">") {
            result = result > termIntermediatePrecedence();
        }
    }

    return result;
}

Argument expression() {
    Argument result = termLowPrecedence();

    std::vector<std::string> lowestPrecedenceOperators =
        createVector<std::string>("&&")("||");

    while (contains(lowestPrecedenceOperators, peek())){
        std::string operand = get();

        if (operand == "&&") {
            result = result && termLowPrecedence();
        } else if (operand == "||") {
            result = result || termLowPrecedence();
        }
    }

    return result;
}

void splitStringIntoTokens(std::string s) {
    tokens.clear();

    std::string complexOperators("><!=|&"), simpleOperators("()+-*/%^~");
    std::string token("");
    bool inOperator = false;

    for(int i = 0; i < s.length(); i++) {
        if(isspace(s[i])) {
            continue;
        }

        if(token != "" && contains(simpleOperators, token)) {
            tokens.push_back(token);
            token = "";
        } else if(token != "" && contains(complexOperators, token[0])) {
            inOperator = true;
        } else {
            inOperator = false;
        }

        if((contains(simpleOperators, s[i])) ||
           (!contains(complexOperators, s[i]) && inOperator) ||
           (contains(complexOperators, s[i]) && !inOperator)) {
            if(token != "") {
                tokens.push_back(token);
            }

            token = "";
        }

        token += s[i];
    }

    if(token != "") {
        tokens.push_back(token);
    }

    tokens.push_back(END_TOKEN);
}

Argument Expresion::evaluate() {
    splitStringIntoTokens(expresion);

    Argument result = expression();

    if(peek() != END_TOKEN) {
        ERROR("too many arguments");
    } else {
        LOG(expresion ," = ", result.value);
    }

    return result;
}

Argument expresion(std::string s) {
    Expresion exp(s);

    return exp.evaluate();
}

