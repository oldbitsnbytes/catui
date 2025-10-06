{
    .t      = cat::lang::type::LineComment,
    .s      = cat::lang::type::LineComment,
    .m      = cat::lang::mnemonic::LineComment,
    .name   = {"LineComment"},
    .d      = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::LineComment },
    .properties  = { .V = 0 }
},
{
    .t      = cat::lang::type::BlocComment,
    .s      = cat::lang::type::BlocComment,
    .m      = cat::lang::mnemonic::BeginComment,
    .name   = {"BlocComment"},
    .d      = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::CommentBegin },
    .properties  = { .V = 01 }
},
{
    .t      = cat::lang::type::BlocComment,
    .s      = cat::lang::type::BlocComment,
    .m      = cat::lang::mnemonic::EndComment,
    .name   = {"LineComment"},
    .d      = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::CommentEnd },
    .properties  = { .V = 1 }
},
{
    .t      = cat::lang::type::Binary,
    .s      = cat::lang::type::Operator|cat::lang::type::Binary,
    .m      = cat::lang::mnemonic::LeftShift,
    .name   = {"LeftShift"},
    .d      = cat::lang::operand::Shift,
    .cursor = {.begin = cat::lang::lexeme::LeftShift },
    .properties  = { .V = 1 }
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword|cat::lang::type::Number|cat::lang::type::Const,
    .m     = cat::lang::mnemonic::Null,
    .name  = "Null",
    .d     = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Null },
    .properties = { .V = 1 }
},
{
    .t  = cat::lang::type::Prefix,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m     = cat::lang::mnemonic::UnShadow,
    .name  = "Unshadow",
    .d     = cat::lang::operand::Scope,
    .cursor = {.begin = cat::lang::lexeme::Unshadow},
    .properties = { .V = 1 }
},
{
    .t = cat::lang::type::OpenPair,
    .s = cat::lang::type::Binary|cat::lang::type::Operator|cat::lang::type::OpenPair|cat::lang::type::Punctuation,
    .m     = cat::lang::mnemonic::OpenAbsOp, // |< x+1 >|;
    //                               ~~
    //                               ^
    .name  = "OpenAbsOp",
    .d     = cat::lang::operand::Pair,
    .cursor   = {.begin = cat::lang::lexeme::AbsBegin },
    .properties = { .V = 1 }
},
{
    .t = cat::lang::type::ClosePair,
    .s = cat::lang::type::Binary|cat::lang::type::Operator|cat::lang::type::OpenPair|cat::lang::type::Punctuation,
    .m     = cat::lang::mnemonic::CloseAbsOp, // |< x+1 >|;
    //                                       ~~
    //                                       ^
    .name  = "CloseAbsOp",
    .d     = cat::lang::operand::Pair,
    .cursor   = {.begin = cat::lang::lexeme::AbsEnd },
    .properties = { .V = 1 }
},
{
    .t = cat::lang::type::Binary,
    .s = cat::lang::type::Binary|cat::lang::type::Operator,
    .m     = cat::lang::mnemonic::Radical,
    .name  = "Radical",
    .d     = cat::lang::operand::Exponent,
    .cursor   = {.begin = cat::lang::lexeme::Radical },
    .properties = { .V = 1 }
},
{
    .t = cat::lang::type::Binary,
    .s = cat::lang::type::Binary|cat::lang::type::Operator,
    .m     = cat::lang::mnemonic::Exponent,
    .name    = "Exponent",
    .d     = cat::lang::operand::Exponent,
    .cursor   = {.begin = cat::lang::lexeme::Exponent },
    .properties = { .V = 1 }
},
{
    .t = cat::lang::type::Binary,
    .s = cat::lang::type::Binary|cat::lang::type::Operator,
    .m     = cat::lang::mnemonic::RightShift,
    .name  = "RightShift",
    .d     = cat::lang::operand::Shift,
    .cursor   = {.begin = cat::lang::lexeme::RightShift },
    .properties = { .V = 1 }
},
{
    .t = cat::lang::type::Binary,
    .s = cat::lang::type::Binary|cat::lang::type::Operator,
    .m     = cat::lang::mnemonic::BinaryXor,
    .name  = "BinaryXor",
    .d     = cat::lang::operand::Bits,
    .cursor   = {.begin = cat::lang::lexeme::Xor },
    .properties = { .V = 1 }
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Unary,
    .m     = cat::lang::mnemonic::Deref,
    .name  = "Deref",
    .d     = cat::lang::operand::Deref,
    .cursor   = {.begin = cat::lang::lexeme::Deref },
    .properties = { .V = 1 }
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m     = cat::lang::mnemonic::Deref,
    .name  = "DerefUtf",
    .d     = cat::lang::operand::Bits,
    .cursor   = {.begin = "➪" },
    .properties = { .V = 1 }
},
{
    .t = cat::lang::type::Unary,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m     = cat::lang::mnemonic::Decr,
    .name  = "Decr",
    .d     = cat::lang::operand::Unary,
    .cursor   = {.begin = cat::lang::lexeme::Decr },
    .properties = { .V = 1 }
},
{
    .t  = cat::lang::type::Unary,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m     = cat::lang::mnemonic::Incr,
    .name  = "Incr",
    .d     = cat::lang::operand::Unary,
    .cursor   = {.begin = cat::lang::lexeme::Incr },
    .properties = { .V = 1 }
},
{
    .t  = cat::lang::type::Assign,
    .s   = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Assign,
    .m     = cat::lang::mnemonic::AssignAdd,
    .name  = "AssignAdd",
    .d     = cat::lang::operand::Assign,
    .cursor   = {.begin = cat::lang::lexeme::AssignAdd},
    .properties = {.V=1}
},
{
    .t   = cat::lang::type::Assign,
    .s    = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Assign,
    .m      = cat::lang::mnemonic::AssignMul,
    .name  = "AssignMul",
    .d      = cat::lang::operand::Assign,
    .cursor    = {.begin = cat::lang::lexeme::AssignMul},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Assign,
    .s    = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Assign,
    .m      = cat::lang::mnemonic::AssignDiv,
    .name  = "AssignDiv",
    .d      = cat::lang::operand::Assign,
    .cursor    = {.begin = cat::lang::lexeme::AssignDiv},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Assign,
    .s    = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Assign,
    .m      = cat::lang::mnemonic::AssignMod,
    .name  = "AssignMod",
    .d      = cat::lang::operand::Assign,
    .cursor    = {.begin = cat::lang::lexeme::AssignMod},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Assign,
    .s    = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Assign,
    .m      = cat::lang::mnemonic::AssignOr,
    .name  = "AssignOr",
    .d      = cat::lang::operand::Assign,
    .cursor    = {.begin = cat::lang::lexeme::AssignOr},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Assign,
    .s    = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Assign,
    .m      = cat::lang::mnemonic::AssignXor,
    .name  = "AssignXor",
    .d      = cat::lang::operand::Assign,
    .cursor    = {.begin = cat::lang::lexeme::AssignXor},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Assign,
    .s    = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Assign,
    .m      = cat::lang::mnemonic::AssignC1,
    .name  = "AssignC1",
    .d      = cat::lang::operand::Assign,
    .cursor    = {.begin = cat::lang::lexeme::AssignC1},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Assign,
    .s    = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Assign,
    .m      = cat::lang::mnemonic::AssignLeftShift,
    .name  = "AssignLeftShift",
    .d      = cat::lang::operand::Assign,
    .cursor    = {.begin = cat::lang::lexeme::AssignLShift},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Assign,
    .s    = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Assign,
    .m      = cat::lang::mnemonic::AssignRightShift,
    .name  = "AssignRightShift",
    .d      = cat::lang::operand::Assign,
    .cursor    = {.begin = cat::lang::lexeme::AssignRShift},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Bool,
    .m      = cat::lang::mnemonic::GreaterEq,
    .name  = "GreaterEq",
    .d      = cat::lang::operand::Equality,
    .cursor    = {.begin = cat::lang::lexeme::GreaterEqual},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Bool,
    .m      = cat::lang::mnemonic::Equal,
    .name  = "Equal",
    .d      = cat::lang::operand::Equality,
    .cursor    = {.begin = cat::lang::lexeme::Equal},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Bool,
    .m      = cat::lang::mnemonic::NotEqual,
    .name  = "NotEqual",
    .d      = cat::lang::operand::Equality,
    .cursor    = {.begin = cat::lang::lexeme::NotEqual},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Bool,
    .m      = cat::lang::mnemonic::NotEqual,
    .name  = "NotEqualAlt",
    .d      = cat::lang::operand::Equality,
    .cursor    = {.begin = lang::lexeme::NotEqualAlt},
    .properties  = {.V = 1}
},

{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary,
    .m      = cat::lang::mnemonic::Add,
    .name  = "Addition",
    .d      = cat::lang::operand::Addition,
    .cursor    = {.begin = cat::lang::lexeme::Addition},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary,
    .m      = cat::lang::mnemonic::Sub,
    .name  = "Subtract",
    .d      = cat::lang::operand::Addition,
    .cursor    = {.begin = cat::lang::lexeme::Sub},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary,
    .m      = cat::lang::mnemonic::Mul,
    .name  = "Multiply",
    .d      = cat::lang::operand::Product,
    .cursor    = {.begin = cat::lang::lexeme::Multiply},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::LineComment,
    .s    = cat::lang::type::LineComment|cat::lang::type::Operator,
    .m      = cat::lang::mnemonic::CommentCpp,
    .name  = "CommentCpp",
    .d      = cat::lang::operand::Noop_,
    .cursor    = {.begin = cat::lang::lexeme::CommentCpp},
    .properties  = {.V = 0}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary,
    .m      = cat::lang::mnemonic::Modulo,
    .name  = "Modulo",
    .d      = cat::lang::operand::Product,
    .cursor    = {.begin = cat::lang::lexeme::Modulo},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Bool,
    .m      = cat::lang::mnemonic::LessThan,
    .name  = "LessThan",
    .d      = cat::lang::operand::Equality,
    .cursor    = {.begin = cat::lang::lexeme::LessThan},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Bool,
    .m      = cat::lang::mnemonic::GreaterThan,
    .name  = "GreaterThan",
    .d      = cat::lang::operand::Equality,
    .cursor    = {.begin = cat::lang::lexeme::GreaterThan},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Assign,
    .s    = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Assign,
    .m      = cat::lang::mnemonic::Assign,
    .name  = "Assign",
    .d      = cat::lang::operand::Assign,
    .cursor    = {.begin = cat::lang::lexeme::Assign},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary,
    .m      = cat::lang::mnemonic::BinaryAnd,
    .name  = "BinaryAnd",
    .d      = cat::lang::operand::Bits,
    .cursor    = {.begin = cat::lang::lexeme::BinaryAnd},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary,
    .m      = cat::lang::mnemonic::BinaryOr,
    .name  = "BinaryOr",
    .d      = cat::lang::operand::Bits,
    .cursor    = {.begin = cat::lang::lexeme::BinaryOr},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Prefix,
    .s    = cat::lang::type::Unary|cat::lang::type::Operator|cat::lang::type::Prefix,
    .m      = cat::lang::mnemonic::C2, // Tow's complement
    .name  = "TwoComplement",
    .d      = cat::lang::operand::Prefix,
    .cursor    = {.begin = cat::lang::lexeme::C2},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Prefix,
    .s    = cat::lang::type::Unary|cat::lang::type::Operator|cat::lang::type::Prefix,
    .m      = cat::lang::mnemonic::C1, // Tow's complement
    .name  = "OneComplement",
    .d      = cat::lang::operand::Prefix,
    .cursor    = {.begin = cat::lang::lexeme::C1},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Unary,
    .s    = cat::lang::type::Unary|cat::lang::type::Operator|cat::lang::type::Prefix,
    .m      = cat::lang::mnemonic::BinaryNot, // Tow's complement
    .name  = "BinaryNot",
    .d      = cat::lang::operand::Prefix,
    .cursor    = {.begin = cat::lang::lexeme::Not},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Bool,
    .m      = cat::lang::mnemonic::LogicalAnd, // Tow's complement
    .name  = "LogicalAnd",
    .d      = cat::lang::operand::Bool_and,
    .cursor    = {.begin = cat::lang::lexeme::BoolAnd},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::Binary,
    .s    = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Bool,
    .m      = cat::lang::mnemonic::LogicalOr, // Tow's complement
    .name  = "LogicalOr",
    .d      = cat::lang::operand::Bool_or,
    .cursor    = {.begin = cat::lang::lexeme::BoolOr},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::OpenPair,
    .s    = cat::lang::type::Operator|cat::lang::type::Punctuation|cat::lang::type::OpenPair,
    .m      = cat::lang::mnemonic::OpenPar, // Tow's complement
    .name  = "OpenPar",
    .d      = cat::lang::operand::Pair,
    .cursor    = {.begin = cat::lang::lexeme::OpenPar},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::ClosePair,
    .s    = cat::lang::type::Operator|cat::lang::type::Punctuation|cat::lang::type::ClosePair,
    .m      = cat::lang::mnemonic::ClosePar, // Tow's complement
    .name  = "ClosePar",
    .d      = cat::lang::operand::Pair,
    .cursor    = {.begin = cat::lang::lexeme::ClosePar},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::OpenPair,
    .s    = cat::lang::type::Operator|cat::lang::type::Punctuation|cat::lang::type::OpenPair,
    .m      = cat::lang::mnemonic::OpenIndex, // Tow's complement
    .name  = "OpenIndex",
    .d      = cat::lang::operand::Pair,
    .cursor    = {.begin = cat::lang::lexeme::OpenIndex},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::ClosePair,
    .s    = cat::lang::type::Operator|cat::lang::type::Punctuation|cat::lang::type::ClosePair,
    .m      = cat::lang::mnemonic::CloseIndex, // Tow's complement
    .name  = "CloseIndex",
    .d      = cat::lang::operand::Pair,
    .cursor    = {.begin = cat::lang::lexeme::CloseIndex},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::OpenPair,
    .s    = cat::lang::type::Operator|cat::lang::type::Punctuation|cat::lang::type::OpenPair,
    .m      = cat::lang::mnemonic::OpenBrace, // Tow's complement
    .name  = "OpenBrace",
    .d      = cat::lang::operand::Pair,
    .cursor    = {.begin = cat::lang::lexeme::BraceBegin},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::ClosePair,
    .s    = cat::lang::type::Operator|cat::lang::type::Punctuation|cat::lang::type::ClosePair,
    .m      = cat::lang::mnemonic::CloseBrace, // Tow's complement
    .name  = "CloseBrace",
    .d      = cat::lang::operand::Pair,
    .cursor    = {.begin = cat::lang::lexeme::BraceEnd},
    .properties  = {.V = 1}
},
{
    .t   = cat::lang::type::BlocComment,
    .s    = cat::lang::type::BlocComment|cat::lang::type::Operator,
    .m      = cat::lang::mnemonic::BeginComment, // Tow's complement
    .name  = "BeginBlocComment",
    .d      = cat::lang::operand::Noop_,
    .cursor    = {.begin = cat::lang::lexeme::CommentBegin},
    .properties  = {.V = 0}
},
{
    .t   = cat::lang::type::BlocComment,
    .s    = cat::lang::type::BlocComment|cat::lang::type::Operator,
    .m      = cat::lang::mnemonic::EndComment, // Tow's complement
    .name  = "EndBlocComment",
    .d      = cat::lang::operand::Noop_,
    .cursor    = {.begin = cat::lang::lexeme::CommentEnd},
    .properties  = {.V = 0}
},
{
    .t = cat::lang::type::Binary,
    .s = cat::lang::type::Operator|cat::lang::type::Binary,
    .m = cat::lang::mnemonic::Div,
    .name  = "Division",
    .d = cat::lang::operand::Product,
    .cursor = {.begin = cat::lang::lexeme::Division},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Punctuation,
    .s = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Punctuation,
    .m = cat::lang::mnemonic::Comma,
    .name  = "Comma",
    .d = cat::lang::operand::Comma,
    .cursor = {.begin = cat::lang::lexeme::Comma},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Punctuation,
    .s = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Punctuation,
    .m = cat::lang::mnemonic::Scope,
    .name  = "Scope",
    .d = cat::lang::operand::Scope,
    .cursor = {.begin = cat::lang::lexeme::Scope},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Punctuation,
    .s = cat::lang::type::Punctuation,
    .m = cat::lang::mnemonic::Semicolon,
    .name  = "SemiColon",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::Semicolon},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Punctuation,
    .s = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Punctuation,
    .m = cat::lang::mnemonic::Colon,
    .name  = "Colon",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::Colon},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Binary,
    .s = cat::lang::type::Operator|cat::lang::type::Binary|cat::lang::type::Punctuation,
    .m = cat::lang::mnemonic::Range,
    .name  = "Range",
    .d = cat::lang::operand::Scope,
    .cursor = {.begin = cat::lang::lexeme::Range},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Postfix,
    .s = cat::lang::type::Unary|cat::lang::type::Postfix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Factorial,
    .name  = "Factorial",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Factorial},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Sign|cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Positive,
    .name  = "Positive",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Positive},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Sign|cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Negative,
    .name  = "Negative",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Negative},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Text,
    .s = cat::lang::type::Text|cat::lang::type::Leaf|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::SQuote,
    .name  = "SingleQuote",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::SQuote},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Text,
    .s = cat::lang::type::Text|cat::lang::type::Leaf|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::DQuote,
    .name  = "DoubleQuote",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::DQuote},
    .properties{.V=1}
},

{
    .t = cat::lang::type::Keyword,
    .s =  cat::lang::type::Keyword|cat::lang::type::Type,
    .m = cat::lang::mnemonic::Procedure,
    .name  = "Procedure",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Procedure},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword|cat::lang::type::Type,
    .m = cat::lang::mnemonic::Function,
    .name  = "Function",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Function},
    .properties{.V=1}
},



{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Binary,
    .m = cat::lang::mnemonic::Ternary,
    .name  = "Ternary",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Ternary},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Hash,
    .name  = "Hash",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Hash},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Eos,
    .name  = "EosMark",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Eos},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Punctuation,
    .s = cat::lang::type::Punctuation|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Dot,
    .name  = "Dot",
    .d = cat::lang::operand::Scope,
    .cursor = {.begin = cat::lang::lexeme::Dot},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Return,
    .name  = "Return",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Return},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::If,
    .name  = "If",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::If},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Number,
    .s = cat::lang::type::Number|cat::lang::type::Leaf|cat::lang::type::Float|cat::lang::type::Keyword|cat::lang::type::Const|cat::lang::type::Literal,
    .m = cat::lang::mnemonic::Pi,
    .name  = "Pi",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Pi},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Number,
    .s = cat::lang::type::Number|cat::lang::type::Leaf|cat::lang::type::Float|cat::lang::type::Keyword|cat::lang::type::Const|cat::lang::type::Literal,
    .m = cat::lang::mnemonic::Pi,
    .name  = "PiUtf",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = "π"},
    .properties{.V=1,.U=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::Number|cat::lang::type::Unary|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Number,
    .name  = "Number",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Number},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::U8|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Type,
    .m = cat::lang::mnemonic::U8,
    .name  = "U8",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::U8},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::U16|cat::lang::type::Unary|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Type|cat::lang::type::Type,
    .m = cat::lang::mnemonic::U16,
    .name  = "U16",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::U16},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::U32|cat::lang::type::Unary|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Type,
    .m = cat::lang::mnemonic::U32,
    .name  = "U32",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::U32},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::U64|cat::lang::type::Unary|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Type,
    .m = cat::lang::mnemonic::U64,
    .name  = "U64",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::U64},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::I8|cat::lang::type::Unary|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Type,
    .m = cat::lang::mnemonic::I8,
    .name  = "I8",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::I8},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::I16|cat::lang::type::Unary|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Type,
    .m = cat::lang::mnemonic::I16,
    .name  = "I16",
    .d = cat::lang::operand::Identifier, .cursor = {.begin = cat::lang::lexeme::I16},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::I32|cat::lang::type::Unary|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Type,
    .m = cat::lang::mnemonic::I32,
    .name  = "I32",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::I32},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::I64|cat::lang::type::Unary|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Type,
    .m = cat::lang::mnemonic::I64,
    .name  = "I64",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::I64},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::Float|cat::lang::type::Unary|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Type,
    .m = cat::lang::mnemonic::Float,
    .name  = "Float",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Float},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Type,
    .s = cat::lang::type::Text|cat::lang::type::Unary|cat::lang::type::Keyword|cat::lang::type::Prefix|cat::lang::type::Operator|cat::lang::type::Type,
    .m = cat::lang::mnemonic::String,
    .name  = "String",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::String},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Then,
    .name  = "Then",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Then},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Else,
    .name  = "Else",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Else},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword|cat::lang::type::Const,
    .m = cat::lang::mnemonic::Const,
    .name  = "Const",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Const},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Include,
    .name  = "Include",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Include},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Amu,
    .name  = "Amu",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Amu},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Address,
    .name  = "AddressOf",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Address},.properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Prime,
    .name  = "Prime",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Prime},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Do,
    .name  = "Do",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::Do},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::While,
    .name  = "While",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::While},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::For,
    .name  = "For",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::For},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Until,
    .name  = "Until",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::Until},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Repeat,
    .name  = "Repeat",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::Repeat},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Switch,
    .name  = "Switch",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::Switch},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Case,
    .name  = "Case",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::Case},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Type,
    .name  = "Type",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::Type},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Leaf|cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Hex,
    .m = cat::lang::mnemonic::LowHex,
    .name  = "LowHex",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::LowHex},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Leaf|cat::lang::type::Keyword|cat::lang::type::Operator|cat::lang::type::Hex,
    .m = cat::lang::mnemonic::UpHex,
    .name  = "UpHex",
    .d = cat::lang::operand::Noop_,
    .cursor = {.begin = cat::lang::lexeme::UpHex},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Cosinus,
    .name  = "Cosinus",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Cosinus},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Keyword|cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::ArcCosinus,
    .name  = "ArcCosinus",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::ArcCosinus},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Keyword|cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Tangent,
    .name  = "Tangent",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Tangent},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Keyword|cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::ArcTangent,
    .name  = "ArcTangent",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::ArcTangent},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Keyword|cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::Sinus,
    .name  = "Sinus",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::Sinus},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Prefix,
    .s = cat::lang::type::Keyword|cat::lang::type::Unary|cat::lang::type::Prefix|cat::lang::type::Operator,
    .m = cat::lang::mnemonic::ArcSinus,
    .name  = "ArcSinus",
    .d = cat::lang::operand::Unary,
    .cursor = {.begin = cat::lang::lexeme::ArcSinus},
    .properties{.V=1}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Object,
    .name  = "Object",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Object},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::Static,
    .name  = "Static",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::Static},
    .properties{.V=0}
},
{
    .t = cat::lang::type::Keyword,
    .s = cat::lang::type::Keyword,
    .m = cat::lang::mnemonic::This,
    .name  = "This",
    .d = cat::lang::operand::Identifier,
    .cursor = {.begin = cat::lang::lexeme::This},
    .properties{.V=1}
},{
      .t = cat::lang::type::Type,
      .s = cat::lang::type::Keyword|cat::lang::type::Void,
      .m = cat::lang::mnemonic::This,
      .name  = "Void",
      .d = cat::lang::operand::Identifier,
      .cursor = {.begin = cat::lang::lexeme::Void},
      .properties{.V=0}
  }
