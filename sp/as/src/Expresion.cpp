#include "Expresion.h"

const char * expressionToParse;

char peek() {
	return expressionToParse[0];
}

char get() {
	return *expressionToParse++;
}

char back() {
	return *expressionToParse--;
}

char peekInfront() {
	return expressionToParse[1];
}

Value expression();

Value number() {
	long long base = 10;
	if(peek() == '0') {
		get(); // '0'
		if(peek() == 'x' || peek() == 'X') {
			get(); // 'x' || 'X'
			base = 16;
		} else if(peek() == 'b' || peek() == 'B') {
			get(); // 'b' || 'B'
			base = 2;
		} else if(peek() >= '0' && peek() <= '7') {
			base = 8;
		} else {
			return 0;
		}
	}

	long long result = get() - '0';
	while ((base == 10 && isdigit(peek())) ||
	       (base == 16 && (isdigit(peek()) || (peek()>='a' && peek()<='f') || (peek()>='A' && peek()<='F'))) ||
	       (base == 8 && (peek()>='0' && peek()<='7')) ||
	       (base == 2 && (peek()>='0' && peek()<='1'))) {
		result = base*result + get() - '0';
	}

	return Value(result);
}

Value simbol() {
	std::string simbol = "";
	while (isalpha(peek()) || peek() == '.') {
		simbol += get();
	}

	for(long long i=0; i<simbolTabel.size(); i++) {
		if(simbol.compare(simbolTabel[i].name) == 0) {
			return Value(simbolTabel[i]);
		}
	}

	// simbol not found
	return Value(Simbol(simbol, 0, 0, false, true));
}

Value word() {
	long long base = 256;

	long long result = get();
	while (isalpha(peek())) {
		result = base*result + get();
	}

	return Value(result);
}

Value factor() {
	if (isdigit(peek())) {
		return number();
	} else if (isalpha(peek()) || peek() == '.') {
		return simbol();
	} else if (peek() == '\'') {
		get(); // '''
		Value result = word();
		if(peek() == '\''){
			get(); // '''
		}
		return result;
	} else if (peek() == '(') {
		get(); // '('
		Value result = expression();
		get(); // ')'
		return result;
	} else if (peek() == '-') {
		get(); // '-'
		Value result = factor();
		result.updateForNegation();
		return result;
	} else if (peek() == '~') {
		get(); // '~'
		Value result = factor();
		result.updateForComplementation();
		return result;
	}

	return 0; // error
}

Value termHighestPrecedence() {
	Value result = factor();

	while ((peek() == '*') || (peek() == '/') || (peek() == '%') ||
	       (peek() == '>' && peekInfront() == '>') ||
	       (peek() == '<' && peekInfront() == '<')) {
		if (peek() == '*') {
			get(); // '*'
			result.updateForMultiplication(factor());
		} else if (peek() == '/') {
			get(); // '/'
			result.updateForDivision(factor());
		} else if (peek() == '%') {
			get(); // '%'
			result.updateForRemainder(factor());
		} else if (peek() == '>') {
			get(); // '>'
			get(); // '>'
			result.updateForShiftRight(factor());
		} else if (peek() == '<') {
			get(); // '<'
			get(); // '<'
			result.updateForShiftLeft(factor());
		}
	}

	return result;
}

Value termIntermediatePrecedence() {
	Value result = termHighestPrecedence();

	while ((peek() == '^') ||
	       (peek() == '|' && peekInfront() != '|') ||
	       (peek() == '&' && peekInfront() != '&')) {
		if (peek() == '|') {
			get(); // '|'
			result.updateForBitwiseInclusiveOr(termHighestPrecedence());
		} else if (peek() == '&') {
			get(); // '&'
			result.updateForBitwiseAnd(termHighestPrecedence());
		} else if (peek() == '^') {
			get(); // '^'
			result.updateForBitwiseExclusiveOr(termHighestPrecedence());
		}
	}

	return result;
}

Value termLowPrecedence() {
	Value result = termIntermediatePrecedence();

	while ((peek() == '+') || (peek() == '-') ||
	       (peek() == '=' && peekInfront() == '=') ||
	       (peek() == '!' && peekInfront() == '=') ||
	       (peek() == '>' && peekInfront() == '=') ||
	       (peek() == '<' && peekInfront() == '=') ||
	       (peek() == '>' && peekInfront() != '>') ||
	       (peek() == '<' && peekInfront() != '<')) {
		if (peek() == '+') {
			get(); // '+'
			result.updateForAdditionWith(termIntermediatePrecedence());
		} else if (peek() == '-') {
			get(); // '-'
			result.updateForSubstactionWith(termIntermediatePrecedence());
		} else if (peek() == '=' && peekInfront() == '=') {
			get(); // '='
			get(); // '='
			result.updateForIsEqualTo(termIntermediatePrecedence());
		} else if (peek() == '!' && peekInfront() == '=') {
			get(); // '!'
			get(); // '='
			result.updateForIsNotEqualTo(termIntermediatePrecedence());
		} else if (peek() == '>' && peekInfront() == '=') {
			get(); // '>'
			get(); // '='
			result.updateForIsGreaterThanOrEqualTo(termIntermediatePrecedence());
		} else if (peek() == '<' && peekInfront() == '=') {
			get(); // '<'
			get(); // '='
			result.updateForIsLessThanOrEqualTo(termIntermediatePrecedence());
		} else if (peek() == '>' && peekInfront() != '>') {
			get(); // '>'
			result.updateForIsGreaterThanOrEqualTo(termIntermediatePrecedence());
		} else if (peek() == '<' && peekInfront() != '<') {
			get(); // '<'
			result.updateForIsLessThan(termIntermediatePrecedence());
		}
	}

	return result;
}

Value expression() {
	Value result = termLowPrecedence();

	while ((peek() == '|' && peekInfront() == '|') ||
	       (peek() == '&' && peekInfront() == '&')) {
		if (peek() == '|' && peekInfront() == '|') {
			result.updateForLogicalOr(termLowPrecedence());
		} else if (peek() == '&' && peekInfront() == '&') {
			result.updateForLogicalAnd(termLowPrecedence());
		}
	}

	return result;
}

Value Expresion::evaluate() {
	expressionToParse = expresion.c_str();

	Value result = expression();

	return result;
}

