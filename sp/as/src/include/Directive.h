#ifndef DIRECTIVE_H_
#define DIRECTIVE_H_

#include <string>
#include <vector>
#include <map>

#define ALIGN_AMOUNT 4
#define MAX_ALIGN_AMOUNT 1<<20

typedef void (*DirectiveFunctionPointer)(std::vector<std::string> directiv);

/**
 * @class Directive
 *
 * @brief Class used to handel direcives.
 *
 * @discussion Supported directives:
 *                 1) .public/.global/.glob <simbol>, ...  
 *                     - Makes the simbols visible to loader.
 *                     - Expect zero or more simbols,
 *                       of any section, separated by commas.
 *                 2) .extern <simbol>, ...
 *                     - Alows use of undefined simbols.
 *                     - Expect zero or more simbols,
 *                       of any section, separated by commas.
 *                 3) .char/.byte <expresion>, ...
 *                     - For each expression, emit a number that,
 *                       at run time, is the value of that expression. 
 *                     - Size of the number is trimed to one byte.
 *                     - Expect zero or more expressions,
 *                       of any section, separated by commas.
 *                 4) .word/.2byte <expresion>, ...
 *                     - For each expression, emit a number that,
 *                       at run time, is the value of that expression. 
 *                     - Size of the number is trimed to two byte.
 *                     - Expect zero or more expressions,
 *                       of any section, separated by commas.
 *                 5) .long/.4byte <expresion>, ...
 *                     - For each expression, emit a number that,
 *                       at run time, is the value of that expression. 
 *                     - Size of the number is trimed to four byte.
 *                     - Expect zero or more expressions,
 *                       of any section, separated by commas.
 *                 6) .align <align = 4>, <fill = 0>, <max = inf>
 *                     - Pad the location counter (in the current subsection)
 *                       to a particular storage boundary.
 *                     - The first expression (which must be absolute)
 *                       is the alignment required.
 *                     - The second expression (which must be absolute)
 *                       gives the fill value to be stored
 *                       in the padding bytes.
 *                       If it is omitted, the padding bytes are normally zero.
 *                     - The third expression (which must be absolute)
 *                       is the maximum number of bytes that should be skipped
 *                       by this alignment directive.
 *                       If doing the alignment would require
 *                       skipping more bytes than the specified maximum,
 *                       then the alignment is not done at all.
 *                       If it is omitted, any amount of bytes is skiped.
 *                 7) .skip/.space/.zero <size>, <fill>
 *                     - This directive emits size bytes,
 *                       each of value fill. 
 *                     - Both size and fill are absolute expressions.
 *                     - If the comma and fill are omitted,
 *                       fill is assumed to be zero.
 *                     - This is the same as `.space'. 
 *                 8) .end
 *                     - Marks the end of the assembly file.
 *                     - Assambler does not process anything
 *                       in the file past the .end directive.
 *                 9) .set/.equ <simbol>, <expresion>
 *                     - Set the value of symbol to expression.
 *                       This changes symbol's value and type
 *                       to conform to expression.
 *                       If symbol was flagged as external, it remains flagged
 *                     - You may .set a symbol many times
 *                       in the same assembly  provided that the values
 *                       given to the symbol are constants.
 *                 10) .ascii <string>, ...
 *                     - Expects zero or more string literals
 *                       separated by commas.
 *                     - It assembles each string,
 *                       with no automatic trailing zero byte,
 *                       into consecutive addresses. 
 *                 11) .asciz <string>, ...
 *                     - Expects zero or more string literals
 *                       separated by commas.
 *                     - It assembles each string,
 *                       with automatic trailing zero byte,
 *                       into consecutive addresses.
 */
struct Directive {
    /**
     * @brief Used to indicate whether .end directiv is found.
     */
    static bool endFound;

    /**
     * @brief Maps directiv name to apropriate function for first pass of as.
     */
    static std::map<std::string, DirectiveFunctionPointer> functionForFirstPass;

    /**
     * @brief Maps directiv name to apropriate function for secons pass of as.
     */
    static std::map<std::string, DirectiveFunctionPointer> functionForSecondPass;
    
    /**
     * @brief Checks if directive is supported.
     *
     * @param name The directive name.
     * @return Returns true if directiv is supported, dalse othervise.
     */
    static bool isNameValid(std::string name);
    
    /**
     * @brief Function that does nothing
     *
     * @discussion Used when directiv shouldn't do anything.
     *
     * @param directiv The directiv
     */
    static void emptyFunction(std::vector<std::string> directiv) {}
};

#endif /* DIRECTIVE_H_ */

