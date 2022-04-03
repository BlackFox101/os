#pragma once
#include <map>
#include <string>

class TokenStorage
{
public:
	using Token = std::string;
	using Info = std::string;

	TokenStorage()
	{
		m_tokens["and"] = "AND";
		m_tokens["auto"] = "AUTO";
		m_tokens["bool"] = "BOOL";
		m_tokens["break"] = "BREAK";
		m_tokens["case"] = "CASE";
		m_tokens["catch"] = "CATCH";
		m_tokens["char"] = "CHAR";
		m_tokens["class"] = "CLASS";
		m_tokens["const"] = "CONST";
		m_tokens["constexpr"] = "CONSTEXPR";
		m_tokens["continue"] = "CONTINUE";
		m_tokens["default"] = "DEFAULT";
		m_tokens["delete"] = "DELETE";
		m_tokens["do"] = "DO";
		m_tokens["double"] = "DOUBLE";
		m_tokens["dynamic_cast"] = "DYNAMIC_CAST";
		m_tokens["else"] = "ELSE";
		m_tokens["enum"] = "ENUM";
		m_tokens["explicit"] = "EXPLICIT";
		m_tokens["false"] = "FALSE";
		m_tokens["float"] = "FLOAT";
		m_tokens["for"] = "FOR";
		m_tokens["friend"] = "FRIEND";
		m_tokens["goto"] = "GOTO";
		m_tokens["if"] = "IF";
		m_tokens["inline"] = "INLINE";
		m_tokens["int"] = "INT";
		m_tokens["long"] = "LONG";
		m_tokens["mutable"] = "MUTABLE";
		m_tokens["namespace"] = "NAMESPACE";
		m_tokens["new"] = "NEW";
		m_tokens["noexcept"] = "NOEXCEPT";
		m_tokens["not"] = "NOT";
		m_tokens["nullptr"] = "NULLPTR";
		m_tokens["operator"] = "OPERATOR";
		m_tokens["or"] = "OR";
		m_tokens["private"] = "PRIVATE";
		m_tokens["protected"] = "PROTECTED";
		m_tokens["public"] = "PUBLIC";
		m_tokens["return"] = "RETURN";
		m_tokens["short"] = "SHORT";
		m_tokens["signed"] = "SIGNED";
		m_tokens["static"] = "STATIC";
		m_tokens["static_cast"] = "STATIC_CAST";
		m_tokens["struct"] = "STRUCT";
		m_tokens["switch"] = "SWITCH";
		m_tokens["template"] = "TEMPLATE";
		m_tokens["this"] = "THIS";
		m_tokens["throw"] = "THROW";
		m_tokens["true"] = "TRUE";
		m_tokens["try"] = "TRY";
		m_tokens["typename"] = "TYPENAME";
		m_tokens["unsigned"] = "UNSIGNED";
		m_tokens["using"] = "USING";
		m_tokens["virtual"] = "VIRTUAL";
		m_tokens["void"] = "VOID";
		m_tokens["while"] = "WHILE";
		m_tokens["xor"] = "XOR";
		m_tokens["override"] = "OVERRIDE";
		m_tokens["final"] = "FINAL";
		m_tokens["="] = "ASSIGN";
		m_tokens["+"] = "PLUS";
		m_tokens["-"] = "MINUS";
		m_tokens["*"] = "MULTIPLICATION";
		m_tokens["/"] = "DIVISIO";
		m_tokens[","] = "COMMA";
		m_tokens["."] = "DOT";
		m_tokens[":"] = "COLON";
		m_tokens[";"] = "SEMI_COLON";
		m_tokens["("] = "OPEN_PARENTHESIS";
		m_tokens[")"] = "CLOSE_PARENTHESIS";
		m_tokens["{"] = "OPEN_CURLY_BRACKET";
		m_tokens["}"] = "CLOSE_CURLY_BRACKET";
		m_tokens["["] = "OPEN_SQUARE_BRACKET";
		m_tokens["]"] = "CLOSE_SQUARE_BRACKET";
		m_tokens["||"] = "OR";
		m_tokens["&&"] = "AND";
		m_tokens["/*"] = "OPEN_BLOCK_COMMENT";
		m_tokens["*/"] = "CLOSE_BLOCK_COMMENT";
		m_tokens["<"] = "SIGN_LESS";
		m_tokens[">"] = "SIGN_MORE";
	}

	Info GetTokenData(const Token& token) const 
	{
		auto TokenIt = m_tokens.find(token);
		if (TokenIt != m_tokens.end())
		{
			return TokenIt->second;
		}
		
		if (isNumber(token))
		{
			return "NUMBER";
		}

		if (token[0] == '"' && token[token.length() - 1] == '"')
		{
			return "STRING";
		}

		return "IDENTIFIER";
	}

private:
	bool isNumber(Token token) const
	{
		return isdigit(token[0]);
	}

	std::map<Token, Info> m_tokens;
};

