/* A Bison parser, made by GNU Bison 3.8.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30800

/* Bison version string.  */
#define YYBISON_VERSION "3.8"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 7 "/home/godcc/frontend/sysy.y"


#include <iostream>
#include <memory>
#include <string>
#include "ast.h"

// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::shared_ptr<Ast> &ast, const char *s);
using namespace std;


#line 85 "/home/godcc/frontend/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_RETURN = 3,                     /* RETURN  */
  YYSYMBOL_IDENT = 4,                      /* IDENT  */
  YYSYMBOL_LT = 5,                         /* LT  */
  YYSYMBOL_GT = 6,                         /* GT  */
  YYSYMBOL_EQ = 7,                         /* EQ  */
  YYSYMBOL_AND = 8,                        /* AND  */
  YYSYMBOL_OR = 9,                         /* OR  */
  YYSYMBOL_NE = 10,                        /* NE  */
  YYSYMBOL_LE = 11,                        /* LE  */
  YYSYMBOL_GE = 12,                        /* GE  */
  YYSYMBOL_CONST = 13,                     /* CONST  */
  YYSYMBOL_INT = 14,                       /* INT  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_BREAK = 18,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 19,                  /* CONTINUE  */
  YYSYMBOL_VOID = 20,                      /* VOID  */
  YYSYMBOL_INT_CONST = 21,                 /* INT_CONST  */
  YYSYMBOL_LOWER_THAN_ELSE = 22,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_23_ = 23,                       /* '('  */
  YYSYMBOL_24_ = 24,                       /* ')'  */
  YYSYMBOL_25_ = 25,                       /* ','  */
  YYSYMBOL_26_ = 26,                       /* '{'  */
  YYSYMBOL_27_ = 27,                       /* '}'  */
  YYSYMBOL_28_ = 28,                       /* ';'  */
  YYSYMBOL_29_ = 29,                       /* '='  */
  YYSYMBOL_30_ = 30,                       /* '['  */
  YYSYMBOL_31_ = 31,                       /* ']'  */
  YYSYMBOL_32_ = 32,                       /* ","  */
  YYSYMBOL_33_ = 33,                       /* '+'  */
  YYSYMBOL_34_ = 34,                       /* '-'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '/'  */
  YYSYMBOL_37_ = 37,                       /* '%'  */
  YYSYMBOL_38_ = 38,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_TranslationUnitAst = 40,        /* TranslationUnitAst  */
  YYSYMBOL_CompUnit = 41,                  /* CompUnit  */
  YYSYMBOL_CompUnitItem = 42,              /* CompUnitItem  */
  YYSYMBOL_FuncDef = 43,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 44,               /* FuncFParams  */
  YYSYMBOL_FuncFParamUp = 45,              /* FuncFParamUp  */
  YYSYMBOL_FuncFParamDef = 46,             /* FuncFParamDef  */
  YYSYMBOL_FuncType = 47,                  /* FuncType  */
  YYSYMBOL_Block = 48,                     /* Block  */
  YYSYMBOL_BlockItemUp = 49,               /* BlockItemUp  */
  YYSYMBOL_BlockItem = 50,                 /* BlockItem  */
  YYSYMBOL_Decl = 51,                      /* Decl  */
  YYSYMBOL_ConstDecl = 52,                 /* ConstDecl  */
  YYSYMBOL_ConstDefUp = 53,                /* ConstDefUp  */
  YYSYMBOL_ConstDef = 54,                  /* ConstDef  */
  YYSYMBOL_ArrayExpList = 55,              /* ArrayExpList  */
  YYSYMBOL_InitValList = 56,               /* InitValList  */
  YYSYMBOL_InitVal = 57,                   /* InitVal  */
  YYSYMBOL_VarDecl = 58,                   /* VarDecl  */
  YYSYMBOL_VarDefUp = 59,                  /* VarDefUp  */
  YYSYMBOL_VarDef = 60,                    /* VarDef  */
  YYSYMBOL_Identifier = 61,                /* Identifier  */
  YYSYMBOL_Stmt = 62,                      /* Stmt  */
  YYSYMBOL_Expr = 63,                      /* Expr  */
  YYSYMBOL_AddExpr = 64,                   /* AddExpr  */
  YYSYMBOL_RelExpr = 65,                   /* RelExpr  */
  YYSYMBOL_EqExpr = 66,                    /* EqExpr  */
  YYSYMBOL_AndExpr = 67,                   /* AndExpr  */
  YYSYMBOL_OrExpr = 68,                    /* OrExpr  */
  YYSYMBOL_MulExpr = 69,                   /* MulExpr  */
  YYSYMBOL_UnaryExp = 70,                  /* UnaryExp  */
  YYSYMBOL_FuncRParams = 71,               /* FuncRParams  */
  YYSYMBOL_FuncRParamUp = 72,              /* FuncRParamUp  */
  YYSYMBOL_PrimaryExpr = 73,               /* PrimaryExpr  */
  YYSYMBOL_LVal = 74,                      /* LVal  */
  YYSYMBOL_UnaryOp = 75,                   /* UnaryOp  */
  YYSYMBOL_Number = 76                     /* Number  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   203

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,     2,     2,    37,     2,     2,
      23,    24,    35,    33,    25,    34,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    28,
       2,    29,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,    27,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    69,    69,    83,    87,    94,    97,   114,   122,   132,
     139,   143,   150,   162,   167,   175,   184,   188,   194,   199,
     208,   213,   220,   228,   232,   238,   245,   253,   257,   263,
     268,   269,   276,   280,   288,   296,   300,   307,   312,   318,
     325,   336,   343,   349,   354,   360,   365,   371,   378,   387,
     397,   406,   411,   419,   427,   430,   433,   438,   441,   444,
     447,   450,   455,   458,   461,   466,   469,   475,   478,   483,
     486,   489,   492,   499,   505,   512,   518,   528,   535,   539,
     546,   552,   558,   567,   572,   582,   587,   592,   600
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "RETURN", "IDENT",
  "LT", "GT", "EQ", "AND", "OR", "NE", "LE", "GE", "CONST", "INT", "IF",
  "ELSE", "WHILE", "BREAK", "CONTINUE", "VOID", "INT_CONST",
  "LOWER_THAN_ELSE", "'('", "')'", "','", "'{'", "'}'", "';'", "'='",
  "'['", "']'", "\",\"", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'",
  "$accept", "TranslationUnitAst", "CompUnit", "CompUnitItem", "FuncDef",
  "FuncFParams", "FuncFParamUp", "FuncFParamDef", "FuncType", "Block",
  "BlockItemUp", "BlockItem", "Decl", "ConstDecl", "ConstDefUp",
  "ConstDef", "ArrayExpList", "InitValList", "InitVal", "VarDecl",
  "VarDefUp", "VarDef", "Identifier", "Stmt", "Expr", "AddExpr", "RelExpr",
  "EqExpr", "AndExpr", "OrExpr", "MulExpr", "UnaryExp", "FuncRParams",
  "FuncRParamUp", "PrimaryExpr", "LVal", "UnaryOp", "Number", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-138)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      57,    -3,  -138,  -138,    22,    57,  -138,  -138,    47,  -138,
    -138,  -138,    47,  -138,  -138,  -138,     2,  -138,    66,     8,
    -138,    52,  -138,    47,    -5,   144,   158,    89,    47,  -138,
     144,    91,  -138,   107,    47,    30,    54,    58,  -138,  -138,
     158,    71,  -138,  -138,  -138,  -138,   -15,  -138,   110,    20,
      13,    79,    82,    75,  -138,  -138,  -138,   158,  -138,    72,
     144,   158,  -138,  -138,   144,  -138,   112,  -138,    30,    92,
      98,  -138,  -138,    19,   164,    83,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,  -138,
    -138,  -138,   103,  -138,    24,   116,   124,   121,   126,  -138,
      47,  -138,    46,  -138,  -138,  -138,   130,   131,  -138,  -138,
    -138,   144,  -138,  -138,  -138,   139,   150,    75,    75,   110,
     110,   110,   110,    20,    20,    13,    79,  -138,  -138,  -138,
    -138,  -138,   141,   158,   158,  -138,  -138,  -138,  -138,  -138,
     158,  -138,  -138,   158,  -138,   156,   159,   161,  -138,   138,
     138,  -138,   168,  -138,   138,  -138
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    13,    14,     0,     2,     3,     5,     0,     6,
      20,    21,     0,     1,     4,    41,     0,    35,    37,     0,
      23,     0,    34,     0,     0,     0,     0,    38,     0,    22,
       0,     0,    36,    37,     0,     0,     0,     9,    10,    88,
       0,     0,    85,    86,    87,    39,    83,    29,    57,    62,
      65,    67,    53,    54,    69,    73,    82,     0,    81,     0,
       0,     0,    24,    26,     0,    12,     0,     8,     0,     0,
       0,    30,    32,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    74,
      27,    40,     0,    25,     0,     0,     0,     0,     0,    45,
       0,    46,     0,    16,    19,    18,     0,    82,     7,    11,
      80,     0,    31,    75,    78,     0,    77,    55,    56,    58,
      59,    60,    61,    63,    64,    66,    68,    70,    71,    72,
      28,    43,     0,     0,     0,    51,    52,    15,    17,    44,
       0,    33,    76,     0,    42,     0,     0,     0,    79,     0,
       0,    47,    48,    50,     0,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,  -138,   181,  -138,  -138,  -138,   125,   -63,   -25,
    -138,    88,   -60,  -138,  -138,   165,   -17,   -23,  -138,  -138,
    -138,   172,    -7,  -137,   -26,    21,    69,   115,   118,  -138,
      97,   -33,  -138,  -138,  -138,   -64,  -138,  -138
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,    36,    37,    38,     8,   101,
     102,   103,     9,    10,    19,    20,    27,    45,    73,    11,
      16,    17,    46,   105,    47,    48,    49,    50,    51,    52,
      53,    54,   115,   116,    55,    56,    57,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,    18,   107,   100,    31,    21,   104,    63,    74,    34,
      67,    12,   152,   153,    70,    26,    33,   155,    72,    35,
      82,    21,    13,    83,    89,    78,    79,    65,    15,    75,
      22,    80,    81,    28,    23,    92,    29,    91,   107,   100,
     106,    93,   104,   108,   111,    39,   112,    40,   114,    94,
      15,    15,   131,   127,   128,   129,    66,    42,    43,     1,
       2,    95,    44,    96,    97,    98,     3,    39,   132,    40,
       1,     2,    66,   137,    99,    15,   106,     3,    68,    42,
      43,    30,    26,    69,    44,   107,   107,    84,   141,    24,
     107,    85,    39,    33,    40,    25,    26,    41,    71,   119,
     120,   121,   122,    90,    42,    43,    34,   145,   146,    44,
      86,    87,    88,    61,   147,    94,    15,   148,    60,    61,
      64,    61,   110,   106,   106,     1,     2,    95,   106,    96,
      97,    98,     3,    39,   130,    40,    25,    26,    66,   133,
      99,    94,    15,    76,    77,    42,    43,   134,    15,   135,
      44,   123,   124,    95,   136,    96,    97,    98,   139,    39,
     140,    40,    15,   142,    66,    39,    99,    40,    15,   144,
      41,    42,    43,   117,   118,   143,    44,    42,    43,    39,
     149,    40,    44,   150,   154,    39,    14,    40,   113,   151,
     138,    42,    43,    62,   109,    32,    44,    42,    43,   125,
       0,     0,    44,   126
};

static const yytype_int16 yycheck[] =
{
      26,     8,    66,    66,    21,    12,    66,    30,    23,    14,
      35,    14,   149,   150,    40,    30,    23,   154,    41,    24,
       7,    28,     0,    10,    57,     5,     6,    34,     4,    46,
      28,    11,    12,    25,    32,    61,    28,    60,   102,   102,
      66,    64,   102,    68,    25,    21,    27,    23,    74,     3,
       4,     4,    28,    86,    87,    88,    26,    33,    34,    13,
      14,    15,    38,    17,    18,    19,    20,    21,    94,    23,
      13,    14,    26,    27,    28,     4,   102,    20,    24,    33,
      34,    29,    30,    25,    38,   149,   150,     8,   111,    23,
     154,     9,    21,   100,    23,    29,    30,    26,    27,    78,
      79,    80,    81,    31,    33,    34,    14,   133,   134,    38,
      35,    36,    37,    30,   140,     3,     4,   143,    29,    30,
      29,    30,    24,   149,   150,    13,    14,    15,   154,    17,
      18,    19,    20,    21,    31,    23,    29,    30,    26,    23,
      28,     3,     4,    33,    34,    33,    34,    23,     4,    28,
      38,    82,    83,    15,    28,    17,    18,    19,    28,    21,
      29,    23,     4,    24,    26,    21,    28,    23,     4,    28,
      26,    33,    34,    76,    77,    25,    38,    33,    34,    21,
      24,    23,    38,    24,    16,    21,     5,    23,    24,    28,
     102,    33,    34,    28,    69,    23,    38,    33,    34,    84,
      -1,    -1,    38,    85
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    13,    14,    20,    40,    41,    42,    43,    47,    51,
      52,    58,    14,     0,    42,     4,    59,    60,    61,    53,
      54,    61,    28,    32,    23,    29,    30,    55,    25,    28,
      29,    55,    60,    61,    14,    24,    44,    45,    46,    21,
      23,    26,    33,    34,    38,    56,    61,    63,    64,    65,
      66,    67,    68,    69,    70,    73,    74,    75,    76,    63,
      29,    30,    54,    56,    29,    61,    26,    48,    24,    25,
      63,    27,    56,    57,    23,    55,    33,    34,     5,     6,
      11,    12,     7,    10,     8,     9,    35,    36,    37,    70,
      31,    56,    63,    56,     3,    15,    17,    18,    19,    28,
      47,    48,    49,    50,    51,    62,    63,    74,    48,    46,
      24,    25,    27,    24,    63,    71,    72,    69,    69,    64,
      64,    64,    64,    65,    65,    66,    67,    70,    70,    70,
      31,    28,    63,    23,    23,    28,    28,    27,    50,    28,
      29,    56,    24,    25,    28,    63,    63,    63,    63,    24,
      24,    28,    62,    62,    16,    62
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    43,    43,    44,
      45,    45,    46,    47,    47,    48,    49,    49,    50,    50,
      51,    51,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    56,    57,    57,    58,    59,    59,    60,    60,    60,
      60,    61,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    63,    64,    64,    64,    65,    65,    65,
      65,    65,    66,    66,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    70,    70,    70,    70,    71,    72,    72,
      73,    73,    73,    74,    74,    75,    75,    75,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     6,     5,     1,
       1,     3,     2,     1,     1,     3,     1,     2,     1,     1,
       1,     1,     4,     1,     3,     4,     3,     3,     4,     1,
       2,     3,     1,     3,     3,     1,     3,     1,     2,     3,
       4,     1,     3,     2,     2,     1,     1,     4,     5,     7,
       5,     2,     2,     1,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     3,     3,     1,     2,     3,     4,     1,     1,     3,
       3,     1,     1,     1,     2,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (ast, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, std::shared_ptr<Ast> &ast)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (ast);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, std::shared_ptr<Ast> &ast)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, ast);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, std::shared_ptr<Ast> &ast)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, ast); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, std::shared_ptr<Ast> &ast)
{
  YY_USE (yyvaluep);
  YY_USE (ast);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (std::shared_ptr<Ast> &ast)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* TranslationUnitAst: CompUnit  */
#line 69 "/home/godcc/frontend/sysy.y"
         {
  auto trans  = new TranslationUnitAst();
  trans->comp_unit = shared_ptr<Ast>((yyvsp[0].ast_val));
  ast = shared_ptr<Ast>(trans);
 }
#line 1267 "/home/godcc/frontend/parser.cpp"
    break;

  case 3: /* CompUnit: CompUnitItem  */
#line 83 "/home/godcc/frontend/sysy.y"
             {
    auto compUnit = new CompUnitAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
    (yyval.ast_val) = compUnit;
}
#line 1276 "/home/godcc/frontend/parser.cpp"
    break;

  case 4: /* CompUnit: CompUnit CompUnitItem  */
#line 87 "/home/godcc/frontend/sysy.y"
                      {
	auto compUnit = new CompUnitAst(shared_ptr<Ast>((yyvsp[-1].ast_val)), shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = compUnit;
}
#line 1285 "/home/godcc/frontend/parser.cpp"
    break;

  case 5: /* CompUnitItem: FuncDef  */
#line 94 "/home/godcc/frontend/sysy.y"
        {
 	(yyval.ast_val) = (yyvsp[0].ast_val);
}
#line 1293 "/home/godcc/frontend/parser.cpp"
    break;

  case 6: /* CompUnitItem: Decl  */
#line 97 "/home/godcc/frontend/sysy.y"
     {
	(yyval.ast_val) = (yyvsp[0].ast_val);
}
#line 1301 "/home/godcc/frontend/parser.cpp"
    break;

  case 7: /* FuncDef: FuncType Identifier '(' FuncFParams ')' Block  */
#line 114 "/home/godcc/frontend/sysy.y"
                                                  {
  	auto funcDef = new FuncDefAst();
	funcDef->funcType = shared_ptr<Ast>((yyvsp[-5].ast_val));
	funcDef->ident = shared_ptr<Ast>((yyvsp[-4].ast_val));
	funcDef->funcParam = shared_ptr<Ast>((yyvsp[-2].ast_val));
	funcDef->block = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = funcDef;
  }
#line 1314 "/home/godcc/frontend/parser.cpp"
    break;

  case 8: /* FuncDef: FuncType Identifier '(' ')' Block  */
#line 122 "/home/godcc/frontend/sysy.y"
                                       {
     	auto funcDef = new FuncDefAst();
   	funcDef->funcType = shared_ptr<Ast>((yyvsp[-4].ast_val));
   	funcDef->ident = shared_ptr<Ast>((yyvsp[-3].ast_val));
   	funcDef->block = shared_ptr<Ast>((yyvsp[0].ast_val));
   	(yyval.ast_val) = funcDef;
     }
#line 1326 "/home/godcc/frontend/parser.cpp"
    break;

  case 9: /* FuncFParams: FuncFParamUp  */
#line 132 "/home/godcc/frontend/sysy.y"
             {
	auto funcFP = new FuncFParamAst();
	funcFP->params = FuncFParamAst::GetParamsFromFuncFParaUp(dynamic_cast<FuncFParamUpAst*>(shared_ptr<Ast>((yyvsp[0].ast_val)).get()));
	(yyval.ast_val) = funcFP;
}
#line 1336 "/home/godcc/frontend/parser.cpp"
    break;

  case 10: /* FuncFParamUp: FuncFParamDef  */
#line 139 "/home/godcc/frontend/sysy.y"
               {
	auto funcFPUp = new FuncFParamUpAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = funcFPUp;
}
#line 1345 "/home/godcc/frontend/parser.cpp"
    break;

  case 11: /* FuncFParamUp: FuncFParamUp ',' FuncFParamDef  */
#line 143 "/home/godcc/frontend/sysy.y"
                               {
	auto funcFPUp = new FuncFParamUpAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = funcFPUp;
}
#line 1354 "/home/godcc/frontend/parser.cpp"
    break;

  case 12: /* FuncFParamDef: INT Identifier  */
#line 150 "/home/godcc/frontend/sysy.y"
                {
	auto funcParaDef = new FuncFParamDefAst();
	funcParaDef->type = *((yyvsp[-1].str_val));
	funcParaDef->ident = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = funcParaDef;

}
#line 1366 "/home/godcc/frontend/parser.cpp"
    break;

  case 13: /* FuncType: INT  */
#line 162 "/home/godcc/frontend/sysy.y"
      {
    auto funcType = new FuncTypeAst();
    funcType->type = string("int");
    (yyval.ast_val) = funcType;
  }
#line 1376 "/home/godcc/frontend/parser.cpp"
    break;

  case 14: /* FuncType: VOID  */
#line 167 "/home/godcc/frontend/sysy.y"
      {
	auto funcType = new FuncTypeAst();
	funcType->type = string("void");
	(yyval.ast_val) = funcType;
}
#line 1386 "/home/godcc/frontend/parser.cpp"
    break;

  case 15: /* Block: '{' BlockItemUp '}'  */
#line 175 "/home/godcc/frontend/sysy.y"
                        {
    auto block = new BlockAst();
    auto blockItemUp = shared_ptr<Ast>((yyvsp[-1].ast_val));
    block->blockItems = BlockAst::GetFromBlockItemUp(dynamic_cast<BlockUpAst*>(blockItemUp.get()));
    (yyval.ast_val) = block;
  }
#line 1397 "/home/godcc/frontend/parser.cpp"
    break;

  case 16: /* BlockItemUp: BlockItem  */
#line 184 "/home/godcc/frontend/sysy.y"
           {
	auto blockItemUp = new BlockUpAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = blockItemUp;
 }
#line 1406 "/home/godcc/frontend/parser.cpp"
    break;

  case 17: /* BlockItemUp: BlockItemUp BlockItem  */
#line 188 "/home/godcc/frontend/sysy.y"
                       {
	auto blockItemUp = new BlockUpAst(shared_ptr<Ast>((yyvsp[-1].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = blockItemUp;
}
#line 1415 "/home/godcc/frontend/parser.cpp"
    break;

  case 18: /* BlockItem: Stmt  */
#line 194 "/home/godcc/frontend/sysy.y"
     {
	auto blockItem = new BlockItemAst();
	blockItem->item = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = blockItem;
}
#line 1425 "/home/godcc/frontend/parser.cpp"
    break;

  case 19: /* BlockItem: Decl  */
#line 199 "/home/godcc/frontend/sysy.y"
     {
	auto blockItem = new BlockItemAst();
	blockItem->item = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = blockItem;
}
#line 1435 "/home/godcc/frontend/parser.cpp"
    break;

  case 20: /* Decl: ConstDecl  */
#line 208 "/home/godcc/frontend/sysy.y"
          {
	auto decl = new DeclAst();
	decl->decl = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = decl;
}
#line 1445 "/home/godcc/frontend/parser.cpp"
    break;

  case 21: /* Decl: VarDecl  */
#line 213 "/home/godcc/frontend/sysy.y"
        {
	auto decl = new DeclAst();
	decl->decl = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = decl;
}
#line 1455 "/home/godcc/frontend/parser.cpp"
    break;

  case 22: /* ConstDecl: CONST INT ConstDefUp ';'  */
#line 220 "/home/godcc/frontend/sysy.y"
                         {
	auto constDecl = new ConstDeclAst();
	constDecl->constDefs=  ConstDeclAst::GetFromConstDefUpAst(dynamic_cast<ConstDefUpAst*>(shared_ptr<Ast>((yyvsp[-1].ast_val)).get()));
	constDecl->dataType = *((yyvsp[-2].str_val));
	(yyval.ast_val) = constDecl;
}
#line 1466 "/home/godcc/frontend/parser.cpp"
    break;

  case 23: /* ConstDefUp: ConstDef  */
#line 228 "/home/godcc/frontend/sysy.y"
         {
	auto constDeclUp = new ConstDefUpAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = constDeclUp;
}
#line 1475 "/home/godcc/frontend/parser.cpp"
    break;

  case 24: /* ConstDefUp: ConstDefUp ',' ConstDef  */
#line 232 "/home/godcc/frontend/sysy.y"
                        {
	auto constDeclUp = new ConstDefUpAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = constDeclUp;
}
#line 1484 "/home/godcc/frontend/parser.cpp"
    break;

  case 25: /* ConstDef: Identifier ArrayExpList '=' InitValList  */
#line 238 "/home/godcc/frontend/sysy.y"
                                        {
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>((yyvsp[-3].ast_val));
	constDef->array_expr_list = shared_ptr<Ast>((yyvsp[-2].ast_val));
	constDef->const_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = constDef;
}
#line 1496 "/home/godcc/frontend/parser.cpp"
    break;

  case 26: /* ConstDef: Identifier '=' InitValList  */
#line 245 "/home/godcc/frontend/sysy.y"
                           {
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>((yyvsp[-2].ast_val));
	constDef->const_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = constDef;
}
#line 1507 "/home/godcc/frontend/parser.cpp"
    break;

  case 27: /* ArrayExpList: '[' Expr ']'  */
#line 253 "/home/godcc/frontend/sysy.y"
              {
 	auto array_expr = new ArrayExprListAst(shared_ptr<Ast>((yyvsp[-1].ast_val)));
 	(yyval.ast_val) = array_expr;
}
#line 1516 "/home/godcc/frontend/parser.cpp"
    break;

  case 28: /* ArrayExpList: ArrayExpList '[' Expr ']'  */
#line 257 "/home/godcc/frontend/sysy.y"
                           {
	auto array_expr = new ArrayExprListAst(shared_ptr<Ast>((yyvsp[-3].ast_val)),shared_ptr<Ast>((yyvsp[-1].ast_val)));
 	(yyval.ast_val) = array_expr;
}
#line 1525 "/home/godcc/frontend/parser.cpp"
    break;

  case 29: /* InitValList: Expr  */
#line 263 "/home/godcc/frontend/sysy.y"
     {
	auto init_val_list = new InitValListAst();
	init_val_list->expr_init_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = init_val_list;
}
#line 1535 "/home/godcc/frontend/parser.cpp"
    break;

  case 30: /* InitValList: '{' '}'  */
#line 268 "/home/godcc/frontend/sysy.y"
         {}
#line 1541 "/home/godcc/frontend/parser.cpp"
    break;

  case 31: /* InitValList: '{' InitVal '}'  */
#line 269 "/home/godcc/frontend/sysy.y"
                {
	auto init_val_list = new InitValListAst();
	init_val_list->expr_init_val = shared_ptr<Ast>((yyvsp[-1].ast_val));
	(yyval.ast_val) = init_val_list;
}
#line 1551 "/home/godcc/frontend/parser.cpp"
    break;

  case 32: /* InitVal: InitValList  */
#line 276 "/home/godcc/frontend/sysy.y"
            {
	auto init_val = new InitValAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = init_val;
}
#line 1560 "/home/godcc/frontend/parser.cpp"
    break;

  case 33: /* InitVal: InitVal ',' InitValList  */
#line 280 "/home/godcc/frontend/sysy.y"
                        {
	auto init_val = new InitValAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = init_val;
}
#line 1569 "/home/godcc/frontend/parser.cpp"
    break;

  case 34: /* VarDecl: FuncType VarDefUp ';'  */
#line 288 "/home/godcc/frontend/sysy.y"
                      {
	auto varDecl = new VarDeclAst();
	varDecl->varDefs=  VarDeclAst::GetFromVarDefUpAst(dynamic_cast<VarDefUpAst*>(shared_ptr<Ast>((yyvsp[-1].ast_val)).get()));
	varDecl->dataType =  shared_ptr<Ast>((yyvsp[-2].ast_val));
	(yyval.ast_val) = varDecl;
}
#line 1580 "/home/godcc/frontend/parser.cpp"
    break;

  case 35: /* VarDefUp: VarDef  */
#line 296 "/home/godcc/frontend/sysy.y"
       {
	auto varDeclUp = new VarDefUpAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
        (yyval.ast_val) = varDeclUp;
}
#line 1589 "/home/godcc/frontend/parser.cpp"
    break;

  case 36: /* VarDefUp: VarDefUp "," VarDef  */
#line 300 "/home/godcc/frontend/sysy.y"
                     {
	auto varDeclUp = new VarDefUpAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
        (yyval.ast_val) = varDeclUp;
}
#line 1598 "/home/godcc/frontend/parser.cpp"
    break;

  case 37: /* VarDef: Identifier  */
#line 307 "/home/godcc/frontend/sysy.y"
           {
	auto varDef = new VarDefAst();
	varDef->ident = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = varDef;
}
#line 1608 "/home/godcc/frontend/parser.cpp"
    break;

  case 38: /* VarDef: Identifier ArrayExpList  */
#line 312 "/home/godcc/frontend/sysy.y"
                        {
	auto varDef = new VarDefAst();
	varDef->ident = shared_ptr<Ast>((yyvsp[-1].ast_val));
	varDef->array_expr_list = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = varDef;
}
#line 1619 "/home/godcc/frontend/parser.cpp"
    break;

  case 39: /* VarDef: Identifier '=' InitValList  */
#line 318 "/home/godcc/frontend/sysy.y"
                           {
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>((yyvsp[-2].ast_val));
	varDef->var_expr =  shared_ptr<Ast>((yyvsp[0].ast_val));
	varDef->is_expr = true;
	(yyval.ast_val) = varDef;
}
#line 1631 "/home/godcc/frontend/parser.cpp"
    break;

  case 40: /* VarDef: Identifier ArrayExpList '=' InitValList  */
#line 325 "/home/godcc/frontend/sysy.y"
                                        {
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>((yyvsp[-3].ast_val));
	varDef->array_expr_list = shared_ptr<Ast>((yyvsp[-2].ast_val));
	varDef->var_expr =  shared_ptr<Ast>((yyvsp[0].ast_val));
	varDef->is_expr = true;
	(yyval.ast_val) = varDef;
}
#line 1644 "/home/godcc/frontend/parser.cpp"
    break;

  case 41: /* Identifier: IDENT  */
#line 336 "/home/godcc/frontend/sysy.y"
      {
	auto identifier=  new IdentifierAst();
	identifier->name = *((yyvsp[0].str_val));
	(yyval.ast_val) = identifier;
}
#line 1654 "/home/godcc/frontend/parser.cpp"
    break;

  case 42: /* Stmt: RETURN Expr ';'  */
#line 343 "/home/godcc/frontend/sysy.y"
                  {
	auto stmt = new StmtAst();
	stmt->expr = shared_ptr<Ast>((yyvsp[-1].ast_val));
	stmt->type = StmtType::kReturn;
	(yyval.ast_val) = stmt;
}
#line 1665 "/home/godcc/frontend/parser.cpp"
    break;

  case 43: /* Stmt: RETURN ';'  */
#line 349 "/home/godcc/frontend/sysy.y"
            {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kReturn;
	(yyval.ast_val) = stmt;
}
#line 1675 "/home/godcc/frontend/parser.cpp"
    break;

  case 44: /* Stmt: Expr ';'  */
#line 354 "/home/godcc/frontend/sysy.y"
         {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kExpr;
	stmt->expr = shared_ptr<Ast>((yyvsp[-1].ast_val));
	(yyval.ast_val) = stmt;
}
#line 1686 "/home/godcc/frontend/parser.cpp"
    break;

  case 45: /* Stmt: ';'  */
#line 360 "/home/godcc/frontend/sysy.y"
    {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kExpr;
	(yyval.ast_val) = stmt;
}
#line 1696 "/home/godcc/frontend/parser.cpp"
    break;

  case 46: /* Stmt: Block  */
#line 365 "/home/godcc/frontend/sysy.y"
      {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kBlock;
	stmt->expr = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = stmt;
}
#line 1707 "/home/godcc/frontend/parser.cpp"
    break;

  case 47: /* Stmt: LVal '=' Expr ';'  */
#line 371 "/home/godcc/frontend/sysy.y"
                   {
	auto stmt = new StmtAst();
    	stmt->expr = shared_ptr<Ast>((yyvsp[-1].ast_val));
    	stmt->l_val =  shared_ptr<Ast>((yyvsp[-3].ast_val));
    	stmt->type = StmtType::kDecl;
    	(yyval.ast_val) = stmt;
 }
#line 1719 "/home/godcc/frontend/parser.cpp"
    break;

  case 48: /* Stmt: IF '(' Expr ')' Stmt  */
#line 378 "/home/godcc/frontend/sysy.y"
                                           {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kIf;
	auto ifStmt = new IfStmtAst();
	ifStmt->expr = shared_ptr<Ast>((yyvsp[-2].ast_val));
	ifStmt->stmt =  shared_ptr<Ast>((yyvsp[0].ast_val));
	stmt-> expr = shared_ptr<Ast>(ifStmt);
	(yyval.ast_val) = stmt;
}
#line 1733 "/home/godcc/frontend/parser.cpp"
    break;

  case 49: /* Stmt: IF '(' Expr ')' Stmt ELSE Stmt  */
#line 387 "/home/godcc/frontend/sysy.y"
                               {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kIf;
	auto ifStmt = new IfStmtAst();
	ifStmt->expr = shared_ptr<Ast>((yyvsp[-4].ast_val));
	ifStmt->stmt =  shared_ptr<Ast>((yyvsp[-2].ast_val));
	ifStmt->elseStmt = shared_ptr<Ast>((yyvsp[0].ast_val));
	stmt-> expr = shared_ptr<Ast>(ifStmt);
	(yyval.ast_val) = stmt;
}
#line 1748 "/home/godcc/frontend/parser.cpp"
    break;

  case 50: /* Stmt: WHILE '(' Expr ')' Stmt  */
#line 397 "/home/godcc/frontend/sysy.y"
                        {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kWhile;
	auto whileStmt = new WhileStmtAst();
	whileStmt->expr = shared_ptr<Ast>((yyvsp[-2].ast_val));
	whileStmt->stmt =  shared_ptr<Ast>((yyvsp[0].ast_val));
	stmt->expr = shared_ptr<Ast>(whileStmt);
	(yyval.ast_val) = stmt;
}
#line 1762 "/home/godcc/frontend/parser.cpp"
    break;

  case 51: /* Stmt: BREAK ';'  */
#line 406 "/home/godcc/frontend/sysy.y"
          {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kBreak;
	(yyval.ast_val) = stmt;
}
#line 1772 "/home/godcc/frontend/parser.cpp"
    break;

  case 52: /* Stmt: CONTINUE ';'  */
#line 411 "/home/godcc/frontend/sysy.y"
             {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kContinue;
	(yyval.ast_val) = stmt;
}
#line 1782 "/home/godcc/frontend/parser.cpp"
    break;

  case 53: /* Expr: OrExpr  */
#line 419 "/home/godcc/frontend/sysy.y"
           {
    auto Expr = new ExpAst();
    Expr->realExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
    (yyval.ast_val) = Expr;
  }
#line 1792 "/home/godcc/frontend/parser.cpp"
    break;

  case 54: /* AddExpr: MulExpr  */
#line 427 "/home/godcc/frontend/sysy.y"
         {
  (yyval.ast_val) = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAdd);
}
#line 1800 "/home/godcc/frontend/parser.cpp"
    break;

  case 55: /* AddExpr: AddExpr '+' MulExpr  */
#line 430 "/home/godcc/frontend/sysy.y"
                    {
  (yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAdd,"+");
}
#line 1808 "/home/godcc/frontend/parser.cpp"
    break;

  case 56: /* AddExpr: AddExpr '-' MulExpr  */
#line 433 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAdd,"-");
}
#line 1816 "/home/godcc/frontend/parser.cpp"
    break;

  case 57: /* RelExpr: AddExpr  */
#line 438 "/home/godcc/frontend/sysy.y"
        {
 (yyval.ast_val) = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel);
}
#line 1824 "/home/godcc/frontend/parser.cpp"
    break;

  case 58: /* RelExpr: RelExpr LT AddExpr  */
#line 441 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,"<");
}
#line 1832 "/home/godcc/frontend/parser.cpp"
    break;

  case 59: /* RelExpr: RelExpr GT AddExpr  */
#line 444 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,">");
}
#line 1840 "/home/godcc/frontend/parser.cpp"
    break;

  case 60: /* RelExpr: RelExpr LE AddExpr  */
#line 447 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,"<=");
}
#line 1848 "/home/godcc/frontend/parser.cpp"
    break;

  case 61: /* RelExpr: RelExpr GE AddExpr  */
#line 450 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,">=");
}
#line 1856 "/home/godcc/frontend/parser.cpp"
    break;

  case 62: /* EqExpr: RelExpr  */
#line 455 "/home/godcc/frontend/sysy.y"
         {
(yyval.ast_val) = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kEq);
}
#line 1864 "/home/godcc/frontend/parser.cpp"
    break;

  case 63: /* EqExpr: EqExpr EQ RelExpr  */
#line 458 "/home/godcc/frontend/sysy.y"
                  {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kEq,"==");
}
#line 1872 "/home/godcc/frontend/parser.cpp"
    break;

  case 64: /* EqExpr: EqExpr NE RelExpr  */
#line 461 "/home/godcc/frontend/sysy.y"
                  {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kEq,"!=");
}
#line 1880 "/home/godcc/frontend/parser.cpp"
    break;

  case 65: /* AndExpr: EqExpr  */
#line 466 "/home/godcc/frontend/sysy.y"
       {
(yyval.ast_val) = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAnd);
}
#line 1888 "/home/godcc/frontend/parser.cpp"
    break;

  case 66: /* AndExpr: AndExpr AND EqExpr  */
#line 469 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAnd,"&&");
}
#line 1896 "/home/godcc/frontend/parser.cpp"
    break;

  case 67: /* OrExpr: AndExpr  */
#line 475 "/home/godcc/frontend/sysy.y"
        {
(yyval.ast_val) = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kLor);
}
#line 1904 "/home/godcc/frontend/parser.cpp"
    break;

  case 68: /* OrExpr: OrExpr OR AndExpr  */
#line 478 "/home/godcc/frontend/sysy.y"
                  {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kLor,"||");
}
#line 1912 "/home/godcc/frontend/parser.cpp"
    break;

  case 69: /* MulExpr: UnaryExp  */
#line 483 "/home/godcc/frontend/sysy.y"
         {
  (yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul);
}
#line 1920 "/home/godcc/frontend/parser.cpp"
    break;

  case 70: /* MulExpr: MulExpr '*' UnaryExp  */
#line 486 "/home/godcc/frontend/sysy.y"
                     {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul,"*");
}
#line 1928 "/home/godcc/frontend/parser.cpp"
    break;

  case 71: /* MulExpr: MulExpr '/' UnaryExp  */
#line 489 "/home/godcc/frontend/sysy.y"
                     {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul,"/");
}
#line 1936 "/home/godcc/frontend/parser.cpp"
    break;

  case 72: /* MulExpr: MulExpr '%' UnaryExp  */
#line 492 "/home/godcc/frontend/sysy.y"
                     {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul,"%");
}
#line 1944 "/home/godcc/frontend/parser.cpp"
    break;

  case 73: /* UnaryExp: PrimaryExpr  */
#line 499 "/home/godcc/frontend/sysy.y"
                {
  	auto unaryExp = new UnaryExprAst();
  	unaryExp-> unaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
  	unaryExp->unaryType = UnaryType::kPrimary;
  	(yyval.ast_val) = unaryExp;
  }
#line 1955 "/home/godcc/frontend/parser.cpp"
    break;

  case 74: /* UnaryExp: UnaryOp UnaryExp  */
#line 505 "/home/godcc/frontend/sysy.y"
                   {
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>((yyvsp[-1].ast_val));
        unaryExp->unaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
	unaryExp->unaryType = UnaryType::kUnary;
	(yyval.ast_val) = unaryExp;
  }
#line 1967 "/home/godcc/frontend/parser.cpp"
    break;

  case 75: /* UnaryExp: Identifier '(' ')'  */
#line 512 "/home/godcc/frontend/sysy.y"
                    {
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>((yyvsp[-2].ast_val));
	unaryExp->unaryType = UnaryType::kCall;
	(yyval.ast_val) = unaryExp;
}
#line 1978 "/home/godcc/frontend/parser.cpp"
    break;

  case 76: /* UnaryExp: Identifier '(' FuncRParams ')'  */
#line 518 "/home/godcc/frontend/sysy.y"
                               {
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>((yyvsp[-3].ast_val));
        unaryExp->unaryExpr = shared_ptr<Ast>((yyvsp[-1].ast_val));
	unaryExp->unaryType = UnaryType::kCall;
	(yyval.ast_val) = unaryExp;
}
#line 1990 "/home/godcc/frontend/parser.cpp"
    break;

  case 77: /* FuncRParams: FuncRParamUp  */
#line 528 "/home/godcc/frontend/sysy.y"
             {
	auto funcRP = new FuncRParamAst();
	funcRP->params = FuncRParamAst::GetParamsFromFuncRParaUp(dynamic_cast<FuncRParamUpAst*>(shared_ptr<Ast>((yyvsp[0].ast_val)).get()));
	(yyval.ast_val) = funcRP;
}
#line 2000 "/home/godcc/frontend/parser.cpp"
    break;

  case 78: /* FuncRParamUp: Expr  */
#line 535 "/home/godcc/frontend/sysy.y"
     {
	auto funcRPUp = new FuncRParamUpAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = funcRPUp;
}
#line 2009 "/home/godcc/frontend/parser.cpp"
    break;

  case 79: /* FuncRParamUp: FuncRParamUp ',' Expr  */
#line 539 "/home/godcc/frontend/sysy.y"
                      {
	auto funcRPUp = new FuncRParamUpAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = funcRPUp;
}
#line 2018 "/home/godcc/frontend/parser.cpp"
    break;

  case 80: /* PrimaryExpr: '(' Expr ')'  */
#line 546 "/home/godcc/frontend/sysy.y"
                 {
  auto primaryAst = new PrimaryExprAst();
  primaryAst->primaryExpr = shared_ptr<Ast>((yyvsp[-1].ast_val));
  primaryAst->primaryType = PrimaryType::EXP;
  (yyval.ast_val) = primaryAst;
  }
#line 2029 "/home/godcc/frontend/parser.cpp"
    break;

  case 81: /* PrimaryExpr: Number  */
#line 552 "/home/godcc/frontend/sysy.y"
          {
  auto primaryAst = new PrimaryExprAst();
    primaryAst->primaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
    primaryAst->primaryType = PrimaryType::NUMBER;
    (yyval.ast_val) = primaryAst;
  }
#line 2040 "/home/godcc/frontend/parser.cpp"
    break;

  case 82: /* PrimaryExpr: LVal  */
#line 558 "/home/godcc/frontend/sysy.y"
       {
      auto primaryAst = new PrimaryExprAst();
      primaryAst->primaryType = PrimaryType::IDENTIFIER;
      primaryAst->primaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
      (yyval.ast_val) = primaryAst;
  }
#line 2051 "/home/godcc/frontend/parser.cpp"
    break;

  case 83: /* LVal: Identifier  */
#line 567 "/home/godcc/frontend/sysy.y"
           {
	auto lval = new LValAst();
	lval->l_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = lval;
}
#line 2061 "/home/godcc/frontend/parser.cpp"
    break;

  case 84: /* LVal: Identifier ArrayExpList  */
#line 572 "/home/godcc/frontend/sysy.y"
                         {
	auto lval = new LValAst();
	lval->l_val = shared_ptr<Ast>((yyvsp[-1].ast_val));
	lval->array_expr_list = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = lval;
}
#line 2072 "/home/godcc/frontend/parser.cpp"
    break;

  case 85: /* UnaryOp: '+'  */
#line 582 "/home/godcc/frontend/sysy.y"
       {
 auto unaryOpAst = new UnaryOpAst();
   unaryOpAst->op = "+";
   (yyval.ast_val) = unaryOpAst;
 }
#line 2082 "/home/godcc/frontend/parser.cpp"
    break;

  case 86: /* UnaryOp: '-'  */
#line 587 "/home/godcc/frontend/sysy.y"
       {
 auto unaryOpAst = new UnaryOpAst();
   unaryOpAst->op = "-";
   (yyval.ast_val) = unaryOpAst;
 }
#line 2092 "/home/godcc/frontend/parser.cpp"
    break;

  case 87: /* UnaryOp: '!'  */
#line 592 "/home/godcc/frontend/sysy.y"
       {
  auto unaryOpAst = new UnaryOpAst();
  unaryOpAst->op = "!";
  (yyval.ast_val) = unaryOpAst;
 }
#line 2102 "/home/godcc/frontend/parser.cpp"
    break;

  case 88: /* Number: INT_CONST  */
#line 600 "/home/godcc/frontend/sysy.y"
              {
  auto numberAst = new NumberAst();
  numberAst->value = ((yyvsp[0].int_val));
  (yyval.ast_val) = numberAst;
  }
#line 2112 "/home/godcc/frontend/parser.cpp"
    break;


#line 2116 "/home/godcc/frontend/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (ast, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, ast);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, ast);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (ast, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, ast);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 607 "/home/godcc/frontend/sysy.y"


// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
void yyerror(shared_ptr<Ast> &ast, const char *s) {
//  printf("%d:%d '%s'\n",yylloc.first_lien,yylloc.first_colunmn,s);
	printf("%s\n",s);
}
