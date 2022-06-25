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
#line 8 "/home/godcc/frontend/sysy.y"

#include <iostream>
#include <memory>
#include <string>
#include "ast.h"

//#include "ast_to_ir.h" //用于编译器求值


#define YYLOCATION_PRINT location_print //打印位置信息
// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::shared_ptr<Ast> &ast, const char *s);
using namespace std;

#line 87 "/home/godcc/frontend/parser.cpp"

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
  YYSYMBOL_FOR = 21,                       /* FOR  */
  YYSYMBOL_DEC = 22,                       /* DEC  */
  YYSYMBOL_INC = 23,                       /* INC  */
  YYSYMBOL_INT_CONST = 24,                 /* INT_CONST  */
  YYSYMBOL_LOWER_THAN_ELSE = 25,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_ = 28,                       /* ','  */
  YYSYMBOL_29_ = 29,                       /* '['  */
  YYSYMBOL_30_ = 30,                       /* ']'  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_32_ = 32,                       /* '}'  */
  YYSYMBOL_33_ = 33,                       /* ';'  */
  YYSYMBOL_34_ = 34,                       /* '='  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_39_ = 39,                       /* '%'  */
  YYSYMBOL_40_ = 40,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_TranslationUnitAst = 42,        /* TranslationUnitAst  */
  YYSYMBOL_CompUnit = 43,                  /* CompUnit  */
  YYSYMBOL_CompUnitItem = 44,              /* CompUnitItem  */
  YYSYMBOL_FuncDef = 45,                   /* FuncDef  */
  YYSYMBOL_FuncFParamList = 46,            /* FuncFParamList  */
  YYSYMBOL_FuncFParam = 47,                /* FuncFParam  */
  YYSYMBOL_FuncType = 48,                  /* FuncType  */
  YYSYMBOL_Block = 49,                     /* Block  */
  YYSYMBOL_BlockItemList = 50,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 51,                 /* BlockItem  */
  YYSYMBOL_Decl = 52,                      /* Decl  */
  YYSYMBOL_ConstDecl = 53,                 /* ConstDecl  */
  YYSYMBOL_ConstDefList = 54,              /* ConstDefList  */
  YYSYMBOL_ConstDef = 55,                  /* ConstDef  */
  YYSYMBOL_ArrayExpList = 56,              /* ArrayExpList  */
  YYSYMBOL_InitValList = 57,               /* InitValList  */
  YYSYMBOL_InitVal = 58,                   /* InitVal  */
  YYSYMBOL_VarDecl = 59,                   /* VarDecl  */
  YYSYMBOL_VarDefList = 60,                /* VarDefList  */
  YYSYMBOL_VarDef = 61,                    /* VarDef  */
  YYSYMBOL_Identifier = 62,                /* Identifier  */
  YYSYMBOL_Stmt = 63,                      /* Stmt  */
  YYSYMBOL_Expr = 64,                      /* Expr  */
  YYSYMBOL_AddExpr = 65,                   /* AddExpr  */
  YYSYMBOL_RelExpr = 66,                   /* RelExpr  */
  YYSYMBOL_EqExpr = 67,                    /* EqExpr  */
  YYSYMBOL_AndExpr = 68,                   /* AndExpr  */
  YYSYMBOL_OrExpr = 69,                    /* OrExpr  */
  YYSYMBOL_MulExpr = 70,                   /* MulExpr  */
  YYSYMBOL_UnaryExp = 71,                  /* UnaryExp  */
  YYSYMBOL_PostfixExp = 72,                /* PostfixExp  */
  YYSYMBOL_FuncRParamList = 73,            /* FuncRParamList  */
  YYSYMBOL_PrimaryExpr = 74,               /* PrimaryExpr  */
  YYSYMBOL_LVal = 75,                      /* LVal  */
  YYSYMBOL_UnaryOp = 76,                   /* UnaryOp  */
  YYSYMBOL_Number = 77                     /* Number  */
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   329

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  182

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   280


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
       2,     2,     2,    40,     2,     2,     2,    39,     2,     2,
      26,    27,    37,    35,    28,    36,     2,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
       2,    34,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    29,     2,    30,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    74,    74,    90,    96,   105,   108,   125,   135,   148,
     154,   163,   172,   181,   191,   207,   214,   224,   231,   240,
     246,   254,   261,   272,   279,   288,   298,   304,   312,   321,
     331,   337,   345,   352,   358,   367,   373,   383,   393,   399,
     408,   415,   423,   431,   443,   454,   462,   469,   477,   484,
     492,   501,   514,   528,   541,   548,   555,   571,   585,   601,
     618,   628,   634,   640,   649,   655,   661,   667,   673,   681,
     687,   693,   701,   707,   716,   722,   730,   736,   742,   748,
     758,   766,   775,   785,   795,   803,   814,   822,   830,   842,
     848,   857,   871,   879,   890,   897,   909,   916,   923,   933
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
  "ELSE", "WHILE", "BREAK", "CONTINUE", "VOID", "FOR", "DEC", "INC",
  "INT_CONST", "LOWER_THAN_ELSE", "'('", "')'", "','", "'['", "']'", "'{'",
  "'}'", "';'", "'='", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "$accept",
  "TranslationUnitAst", "CompUnit", "CompUnitItem", "FuncDef",
  "FuncFParamList", "FuncFParam", "FuncType", "Block", "BlockItemList",
  "BlockItem", "Decl", "ConstDecl", "ConstDefList", "ConstDef",
  "ArrayExpList", "InitValList", "InitVal", "VarDecl", "VarDefList",
  "VarDef", "Identifier", "Stmt", "Expr", "AddExpr", "RelExpr", "EqExpr",
  "AndExpr", "OrExpr", "MulExpr", "UnaryExp", "PostfixExp",
  "FuncRParamList", "PrimaryExpr", "LVal", "UnaryOp", "Number", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-91)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       7,    26,   -91,   -91,    15,     7,   -91,   -91,    19,   -91,
     -91,   -91,    19,   -91,   -91,   -91,    -9,   -91,   -12,    37,
     -91,    85,    19,   -91,    -2,   289,    68,   101,    19,   -91,
      68,   102,   -91,   108,     0,    51,   -91,    19,   289,   289,
     -91,   289,   -91,   -91,   -91,    16,    14,    62,   115,    95,
      56,    76,   237,   -91,   100,   -91,   -91,   289,   -91,    31,
     -91,   -91,   289,    68,   -91,   -91,    68,   130,   -91,     0,
      26,    58,   -91,   -91,    79,   223,    60,   -91,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   -91,   -91,   -91,   -91,   -91,    49,    86,   -91,   -91,
     208,    98,   120,   122,   131,   153,   -91,   -91,    19,   -91,
     154,   -91,   -91,   -91,   155,   157,   -91,   -91,   247,    60,
     -91,   -91,   -91,   111,   237,   237,    62,    62,    62,    62,
     115,   115,    95,    56,   -91,   -91,   -91,    68,   -91,   -91,
     -91,   170,   289,   289,   -91,   -91,   178,   -91,   -91,   -91,
     289,   179,   -91,   289,   -91,   -91,   180,   183,   202,   202,
     182,    60,   -91,   202,   202,   262,   268,   -91,   200,   -91,
     202,   195,   202,   209,   202,   -91,   202,   -91,   202,   -91,
     -91,   -91
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    15,    16,     0,     2,     3,     5,     0,     6,
      23,    24,     0,     1,     4,    44,     0,    38,    40,     0,
      26,     0,     0,    37,     0,     0,     0,    41,     0,    25,
       0,     0,    39,    40,     0,     0,     9,     0,     0,     0,
      99,     0,    96,    97,    98,    94,     0,    64,    69,    72,
      74,    60,    61,    76,    80,    86,    93,     0,    92,     0,
      42,    32,     0,     0,    27,    29,     0,     0,     8,     0,
       0,    11,    82,    83,     0,     0,    95,    30,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    87,    88,    81,    33,    35,     0,     0,    43,    28,
       0,     0,     0,     0,     0,     0,    18,    48,     0,    49,
       0,    19,    22,    21,     0,    93,     7,    10,     0,    14,
      91,    84,    89,     0,    62,    63,    65,    66,    67,    68,
      70,    71,    73,    75,    77,    78,    79,     0,    34,    31,
      46,     0,     0,     0,    54,    55,     0,    17,    20,    47,
       0,    12,    85,     0,    36,    45,     0,     0,     0,     0,
       0,    13,    90,     0,     0,     0,     0,    50,    51,    53,
       0,     0,     0,     0,     0,    59,     0,    57,     0,    52,
      58,    56
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -91,   -91,   -91,   224,   -91,   -91,   169,     6,   -21,   -91,
     146,   -59,   -91,   -91,   212,   -19,   -27,   -91,   114,   -91,
     235,    21,   -90,   -25,   172,    75,   175,   177,   -91,   105,
     -29,   -91,   -91,   -91,   -63,   -91,   -91
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,    35,    36,   108,   109,   110,
     111,     9,    10,    19,    20,    27,    60,    96,    11,    16,
      17,    45,   113,   114,    47,    48,    49,    50,    51,    52,
      53,    54,   123,    55,    56,    57,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      46,    61,    31,    65,   115,    61,     8,    12,   112,    72,
      73,     8,     2,    68,    24,    13,    74,    25,     3,    22,
       1,     2,    26,    15,    23,    34,    76,     3,    93,    18,
      37,    67,    95,    21,    61,    15,    98,    97,    61,    99,
       2,    61,    75,    33,    77,    25,     3,   115,   116,    21,
     122,   112,   119,    38,    39,    40,   159,    41,    71,   134,
     135,   136,    59,    94,    86,    28,    42,    43,   165,   166,
      29,    44,    15,   168,   169,   141,    37,   137,    69,    70,
     175,   138,   177,   115,   179,    87,   180,   118,   181,    62,
      38,    39,    40,    46,    41,   115,   115,    78,    79,    59,
     115,   115,    84,    42,    43,    85,   120,   115,    44,   115,
     154,   115,    61,   115,    25,   115,   139,   156,   157,    30,
      80,    81,    91,    92,   142,   160,    82,    83,   162,    33,
      62,    62,   161,   100,    15,    63,    66,    25,   152,   153,
     171,   173,    26,     1,     2,   101,   143,   102,   103,   104,
       3,   105,    38,    39,    40,   144,    41,   100,    15,   130,
     131,    67,   106,   107,   145,    42,    43,     1,     2,   101,
      44,   102,   103,   104,     3,   105,    38,    39,    40,   146,
      41,   100,    15,   124,   125,    67,   147,   107,   149,    42,
      43,   150,     2,   101,    44,   102,   103,   104,     3,   105,
      38,    39,    40,   155,    41,   100,    15,   163,    25,    67,
     164,   107,    15,    42,    43,   167,   174,   101,    44,   102,
     103,   104,   176,   105,    38,    39,    40,    15,    41,    14,
      38,    39,    40,    67,    41,   107,   178,    42,    43,   117,
      64,   140,    44,    42,    43,    38,    39,    40,    44,    41,
     121,    15,   126,   127,   128,   129,   148,    32,    42,    43,
     158,   132,     0,    44,   133,     0,    15,     0,     0,    38,
      39,    40,    15,    41,    88,    89,    90,   151,     0,     0,
       0,     0,    42,    43,    38,    39,    40,    44,    41,   170,
      38,    39,    40,    15,    41,   172,     0,    42,    43,     0,
       0,     0,    44,    42,    43,     0,     0,     0,    44,     0,
       0,    38,    39,    40,     0,    41,     0,     0,     0,     0,
       0,     0,     0,     0,    42,    43,     0,     0,     0,    44
};

static const yytype_int16 yycheck[] =
{
      25,    26,    21,    30,    67,    30,     0,     1,    67,    38,
      39,     5,    14,    34,    26,     0,    41,    29,    20,    28,
      13,    14,    34,     4,    33,    27,    45,    20,    57,     8,
      24,    31,    59,    12,    59,     4,    63,    62,    63,    66,
      14,    66,    26,    22,    30,    29,    20,   110,    69,    28,
      75,   110,    71,    22,    23,    24,   146,    26,    37,    88,
      89,    90,    31,    32,     8,    28,    35,    36,   158,   159,
      33,    40,     4,   163,   164,   100,    70,    28,    27,    28,
     170,    32,   172,   146,   174,     9,   176,    29,   178,    29,
      22,    23,    24,   118,    26,   158,   159,    35,    36,    31,
     163,   164,     7,    35,    36,    10,    27,   170,    40,   172,
     137,   174,   137,   176,    29,   178,    30,   142,   143,    34,
       5,     6,    22,    23,    26,   150,    11,    12,   153,   108,
      29,    29,   151,     3,     4,    34,    34,    29,    27,    28,
     165,   166,    34,    13,    14,    15,    26,    17,    18,    19,
      20,    21,    22,    23,    24,    33,    26,     3,     4,    84,
      85,    31,    32,    33,    33,    35,    36,    13,    14,    15,
      40,    17,    18,    19,    20,    21,    22,    23,    24,    26,
      26,     3,     4,    78,    79,    31,    32,    33,    33,    35,
      36,    34,    14,    15,    40,    17,    18,    19,    20,    21,
      22,    23,    24,    33,    26,     3,     4,    27,    29,    31,
      27,    33,     4,    35,    36,    33,    16,    15,    40,    17,
      18,    19,    27,    21,    22,    23,    24,     4,    26,     5,
      22,    23,    24,    31,    26,    33,    27,    35,    36,    70,
      28,    33,    40,    35,    36,    22,    23,    24,    40,    26,
      27,     4,    80,    81,    82,    83,   110,    22,    35,    36,
     146,    86,    -1,    40,    87,    -1,     4,    -1,    -1,    22,
      23,    24,     4,    26,    37,    38,    39,    30,    -1,    -1,
      -1,    -1,    35,    36,    22,    23,    24,    40,    26,    27,
      22,    23,    24,     4,    26,    27,    -1,    35,    36,    -1,
      -1,    -1,    40,    35,    36,    -1,    -1,    -1,    40,    -1,
      -1,    22,    23,    24,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    13,    14,    20,    42,    43,    44,    45,    48,    52,
      53,    59,    48,     0,    44,     4,    60,    61,    62,    54,
      55,    62,    28,    33,    26,    29,    34,    56,    28,    33,
      34,    56,    61,    62,    27,    46,    47,    48,    22,    23,
      24,    26,    35,    36,    40,    62,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    74,    75,    76,    77,    31,
      57,    64,    29,    34,    55,    57,    34,    31,    49,    27,
      28,    62,    71,    71,    64,    26,    56,    30,    35,    36,
       5,     6,    11,    12,     7,    10,     8,     9,    37,    38,
      39,    22,    23,    71,    32,    57,    58,    64,    57,    57,
       3,    15,    17,    18,    19,    21,    32,    33,    48,    49,
      50,    51,    52,    63,    64,    75,    49,    47,    29,    56,
      27,    27,    64,    73,    70,    70,    65,    65,    65,    65,
      66,    66,    67,    68,    71,    71,    71,    28,    32,    30,
      33,    64,    26,    26,    33,    33,    26,    32,    51,    33,
      34,    30,    27,    28,    57,    33,    64,    64,    59,    63,
      64,    56,    64,    27,    27,    63,    63,    33,    63,    63,
      27,    64,    27,    64,    16,    63,    27,    63,    27,    63,
      63,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    45,    45,    46,
      46,    47,    47,    47,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    53,    54,    54,    55,    55,
      56,    56,    57,    57,    57,    58,    58,    59,    60,    60,
      61,    61,    61,    61,    62,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      64,    65,    65,    65,    66,    66,    66,    66,    66,    67,
      67,    67,    68,    68,    69,    69,    70,    70,    70,    70,
      71,    71,    71,    71,    71,    71,    72,    72,    72,    73,
      73,    74,    74,    74,    75,    75,    76,    76,    76,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     6,     5,     1,
       3,     2,     4,     5,     3,     1,     1,     3,     2,     1,
       2,     1,     1,     1,     1,     4,     1,     3,     4,     3,
       3,     4,     1,     2,     3,     1,     3,     3,     1,     3,
       1,     2,     3,     4,     1,     3,     2,     2,     1,     1,
       4,     5,     7,     5,     2,     2,     7,     6,     7,     6,
       1,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     3,     3,
       1,     2,     2,     2,     3,     4,     1,     2,     2,     1,
       3,     3,     1,     1,     1,     2,     1,     1,     1,     1
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, std::shared_ptr<Ast> &ast)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, std::shared_ptr<Ast> &ast)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, ast);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, ast); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, std::shared_ptr<Ast> &ast)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* TranslationUnitAst: CompUnit  */
#line 74 "/home/godcc/frontend/sysy.y"
         {
  auto trans  = new TranslationUnitAst();
  trans->comp_unit = shared_ptr<Ast>((yyvsp[0].ast_val));
  trans->line = (yyloc).first_line;
  trans->column = (yyloc).first_column;
  ast = shared_ptr<Ast>(trans);
 }
#line 1425 "/home/godcc/frontend/parser.cpp"
    break;

  case 3: /* CompUnit: CompUnitItem  */
#line 90 "/home/godcc/frontend/sysy.y"
             {
    auto compUnit = new CompUnitAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
      compUnit->line = (yyloc).first_line;
      compUnit->column = (yyloc).first_column;
    (yyval.ast_val) = compUnit;
}
#line 1436 "/home/godcc/frontend/parser.cpp"
    break;

  case 4: /* CompUnit: CompUnit CompUnitItem  */
#line 96 "/home/godcc/frontend/sysy.y"
                      {
	auto compUnit = new CompUnitAst(shared_ptr<Ast>((yyvsp[-1].ast_val)), shared_ptr<Ast>((yyvsp[0].ast_val)));
	compUnit->line = (yyloc).first_line;
        compUnit->column = (yyloc).first_column;
	(yyval.ast_val) = compUnit;
}
#line 1447 "/home/godcc/frontend/parser.cpp"
    break;

  case 5: /* CompUnitItem: FuncDef  */
#line 105 "/home/godcc/frontend/sysy.y"
        {
 	(yyval.ast_val) = (yyvsp[0].ast_val);
}
#line 1455 "/home/godcc/frontend/parser.cpp"
    break;

  case 6: /* CompUnitItem: Decl  */
#line 108 "/home/godcc/frontend/sysy.y"
     {
	(yyval.ast_val) = (yyvsp[0].ast_val);
}
#line 1463 "/home/godcc/frontend/parser.cpp"
    break;

  case 7: /* FuncDef: FuncType Identifier '(' FuncFParamList ')' Block  */
#line 125 "/home/godcc/frontend/sysy.y"
                                                     {
  	auto funcDef = new FuncDefAst();
	funcDef->funcType = shared_ptr<Ast>((yyvsp[-5].ast_val));
	funcDef->ident = shared_ptr<Ast>((yyvsp[-4].ast_val));
	funcDef->funcParamList = shared_ptr<Ast>((yyvsp[-2].ast_val));
	funcDef->block = shared_ptr<Ast>((yyvsp[0].ast_val));
 	funcDef->line = (yyloc).first_line;
      	funcDef->column = (yyloc).first_column;
	(yyval.ast_val) = funcDef;
  }
#line 1478 "/home/godcc/frontend/parser.cpp"
    break;

  case 8: /* FuncDef: FuncType Identifier '(' ')' Block  */
#line 135 "/home/godcc/frontend/sysy.y"
                                       {
     	auto funcDef = new FuncDefAst();
   	funcDef->funcType = shared_ptr<Ast>((yyvsp[-4].ast_val));
   	funcDef->ident = shared_ptr<Ast>((yyvsp[-3].ast_val));
   	funcDef->block = shared_ptr<Ast>((yyvsp[0].ast_val));
   	funcDef->line = (yyloc).first_line;
	funcDef->column = (yyloc).first_column;
   	(yyval.ast_val) = funcDef;
     }
#line 1492 "/home/godcc/frontend/parser.cpp"
    break;

  case 9: /* FuncFParamList: FuncFParam  */
#line 148 "/home/godcc/frontend/sysy.y"
            {
	auto func_fpl = new FuncFParamListAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	func_fpl->line = (yyloc).first_line;
	func_fpl->column = (yyloc).first_column;
	(yyval.ast_val) = func_fpl;
}
#line 1503 "/home/godcc/frontend/parser.cpp"
    break;

  case 10: /* FuncFParamList: FuncFParamList ',' FuncFParam  */
#line 154 "/home/godcc/frontend/sysy.y"
                              {
	auto func_fpl = new FuncFParamListAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	func_fpl->line = (yyloc).first_line;
	func_fpl->column = (yyloc).first_column;
	(yyval.ast_val) = func_fpl;
}
#line 1514 "/home/godcc/frontend/parser.cpp"
    break;

  case 11: /* FuncFParam: FuncType Identifier  */
#line 163 "/home/godcc/frontend/sysy.y"
                     {
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>((yyvsp[-1].ast_val));
	funcParaDef->ident = shared_ptr<Ast>((yyvsp[0].ast_val));
	funcParaDef->first_no_dim = false;
	funcParaDef->line = (yyloc).first_line;
	funcParaDef->column = (yyloc).first_column;
	(yyval.ast_val) = funcParaDef;
}
#line 1528 "/home/godcc/frontend/parser.cpp"
    break;

  case 12: /* FuncFParam: FuncType Identifier '[' ']'  */
#line 172 "/home/godcc/frontend/sysy.y"
                             {
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>((yyvsp[-3].ast_val));
	funcParaDef->ident = shared_ptr<Ast>((yyvsp[-2].ast_val));
	funcParaDef->first_no_dim = true;
	funcParaDef->line = (yyloc).first_line;
	funcParaDef->column = (yyloc).first_column;
	(yyval.ast_val) = funcParaDef;
}
#line 1542 "/home/godcc/frontend/parser.cpp"
    break;

  case 13: /* FuncFParam: FuncType Identifier '[' ']' ArrayExpList  */
#line 181 "/home/godcc/frontend/sysy.y"
                                         {
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>((yyvsp[-4].ast_val));
	funcParaDef->ident = shared_ptr<Ast>((yyvsp[-3].ast_val));
	funcParaDef->first_no_dim = true;
	funcParaDef->array_expr_list = shared_ptr<Ast>((yyvsp[0].ast_val));
	funcParaDef->line = (yyloc).first_line;
	funcParaDef->column = (yyloc).first_column;
	(yyval.ast_val) = funcParaDef;
}
#line 1557 "/home/godcc/frontend/parser.cpp"
    break;

  case 14: /* FuncFParam: FuncType Identifier ArrayExpList  */
#line 191 "/home/godcc/frontend/sysy.y"
                                  {
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>((yyvsp[-2].ast_val));
	funcParaDef->ident = shared_ptr<Ast>((yyvsp[-1].ast_val));
	funcParaDef->first_no_dim = false;
	funcParaDef->array_expr_list = shared_ptr<Ast>((yyvsp[0].ast_val));
	funcParaDef->line = (yyloc).first_line;
	funcParaDef->column = (yyloc).first_column;
	(yyval.ast_val) = funcParaDef;
}
#line 1572 "/home/godcc/frontend/parser.cpp"
    break;

  case 15: /* FuncType: INT  */
#line 207 "/home/godcc/frontend/sysy.y"
      {
    auto funcType = new FuncTypeAst();
    funcType->type = "int";
	funcType->line = (yyloc).first_line;
	funcType->column = (yyloc).first_column;
    (yyval.ast_val) = funcType;
  }
#line 1584 "/home/godcc/frontend/parser.cpp"
    break;

  case 16: /* FuncType: VOID  */
#line 214 "/home/godcc/frontend/sysy.y"
      {
	auto funcType = new FuncTypeAst();
	funcType->type = "void";
	funcType->line = (yyloc).first_line;
	funcType->column = (yyloc).first_column;
	(yyval.ast_val) = funcType;
}
#line 1596 "/home/godcc/frontend/parser.cpp"
    break;

  case 17: /* Block: '{' BlockItemList '}'  */
#line 224 "/home/godcc/frontend/sysy.y"
                          {
	auto block = new BlockAst();
	block-> block_item_list= shared_ptr<Ast>((yyvsp[-1].ast_val));
	block->line = (yyloc).first_line;
	block->column = (yyloc).first_column;
	(yyval.ast_val) = block;
  }
#line 1608 "/home/godcc/frontend/parser.cpp"
    break;

  case 18: /* Block: '{' '}'  */
#line 231 "/home/godcc/frontend/sysy.y"
           {
	auto block = new BlockAst();
	block->line = (yyloc).first_line;
	block->column = (yyloc).first_column;
	(yyval.ast_val) = block;
  }
#line 1619 "/home/godcc/frontend/parser.cpp"
    break;

  case 19: /* BlockItemList: BlockItem  */
#line 240 "/home/godcc/frontend/sysy.y"
           {
	auto blockItemUp = new BlockItemListAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	blockItemUp->line = (yyloc).first_line;
	blockItemUp->column = (yyloc).first_column;
	(yyval.ast_val) = blockItemUp;
 }
#line 1630 "/home/godcc/frontend/parser.cpp"
    break;

  case 20: /* BlockItemList: BlockItemList BlockItem  */
#line 246 "/home/godcc/frontend/sysy.y"
                         {
	auto blockItemUp = new BlockItemListAst(shared_ptr<Ast>((yyvsp[-1].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	blockItemUp->line = (yyloc).first_line;
	blockItemUp->column = (yyloc).first_column;
	(yyval.ast_val) = blockItemUp;
}
#line 1641 "/home/godcc/frontend/parser.cpp"
    break;

  case 21: /* BlockItem: Stmt  */
#line 254 "/home/godcc/frontend/sysy.y"
     {
	auto blockItem = new BlockItemAst();
	blockItem->item = shared_ptr<Ast>((yyvsp[0].ast_val));
		blockItem->line = (yyloc).first_line;
        	blockItem->column = (yyloc).first_column;
	(yyval.ast_val) = blockItem;
}
#line 1653 "/home/godcc/frontend/parser.cpp"
    break;

  case 22: /* BlockItem: Decl  */
#line 261 "/home/godcc/frontend/sysy.y"
     {
	auto blockItem = new BlockItemAst();
	blockItem->item = shared_ptr<Ast>((yyvsp[0].ast_val));
		blockItem->line = (yyloc).first_line;
		blockItem->column = (yyloc).first_column;
	(yyval.ast_val) = blockItem;
}
#line 1665 "/home/godcc/frontend/parser.cpp"
    break;

  case 23: /* Decl: ConstDecl  */
#line 272 "/home/godcc/frontend/sysy.y"
          {
	auto decl = new DeclAst();
	decl->decl = shared_ptr<Ast>((yyvsp[0].ast_val));
	decl->line = (yyloc).first_line;
	decl->column = (yyloc).first_column;
	(yyval.ast_val) = decl;
}
#line 1677 "/home/godcc/frontend/parser.cpp"
    break;

  case 24: /* Decl: VarDecl  */
#line 279 "/home/godcc/frontend/sysy.y"
        {
	auto decl = new DeclAst();
	decl->decl = shared_ptr<Ast>((yyvsp[0].ast_val));
		decl->line = (yyloc).first_line;
        	decl->column = (yyloc).first_column;
	(yyval.ast_val) = decl;
}
#line 1689 "/home/godcc/frontend/parser.cpp"
    break;

  case 25: /* ConstDecl: CONST FuncType ConstDefList ';'  */
#line 288 "/home/godcc/frontend/sysy.y"
                                {
	auto constDecl = new ConstDeclAst();
	constDecl->const_def_list= shared_ptr<Ast>((yyvsp[-1].ast_val));
	constDecl->data_type = shared_ptr<Ast>((yyvsp[-2].ast_val));
	constDecl->line = (yyloc).first_line;
	constDecl->column = (yyloc).first_column;
	(yyval.ast_val) = constDecl;
}
#line 1702 "/home/godcc/frontend/parser.cpp"
    break;

  case 26: /* ConstDefList: ConstDef  */
#line 298 "/home/godcc/frontend/sysy.y"
         {
	auto constDeclUp = new ConstDefListAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	constDeclUp->line = (yyloc).first_line;
	constDeclUp->column = (yyloc).first_column;
	(yyval.ast_val) = constDeclUp;
}
#line 1713 "/home/godcc/frontend/parser.cpp"
    break;

  case 27: /* ConstDefList: ConstDefList ',' ConstDef  */
#line 304 "/home/godcc/frontend/sysy.y"
                          {
	auto constDeclUp = new ConstDefListAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
		constDeclUp->line = (yyloc).first_line;
        	constDeclUp->column = (yyloc).first_column;
	(yyval.ast_val) = constDeclUp;
}
#line 1724 "/home/godcc/frontend/parser.cpp"
    break;

  case 28: /* ConstDef: Identifier ArrayExpList '=' InitValList  */
#line 312 "/home/godcc/frontend/sysy.y"
                                        {
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>((yyvsp[-3].ast_val));
	constDef->array_expr_list = shared_ptr<Ast>((yyvsp[-2].ast_val));
	constDef->const_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	constDef->line = (yyloc).first_line;
	constDef->column = (yyloc).first_column;
	(yyval.ast_val) = constDef;
}
#line 1738 "/home/godcc/frontend/parser.cpp"
    break;

  case 29: /* ConstDef: Identifier '=' InitValList  */
#line 321 "/home/godcc/frontend/sysy.y"
                           {
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>((yyvsp[-2].ast_val));
	constDef->const_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	constDef->line = (yyloc).first_line;
	constDef->column = (yyloc).first_column;
	(yyval.ast_val) = constDef;
}
#line 1751 "/home/godcc/frontend/parser.cpp"
    break;

  case 30: /* ArrayExpList: '[' Expr ']'  */
#line 331 "/home/godcc/frontend/sysy.y"
              {
 	auto array_expr = new ArrayExprListAst(shared_ptr<Ast>((yyvsp[-1].ast_val)));
 	array_expr->line = (yyloc).first_line;
	array_expr->column = (yyloc).first_column;
 	(yyval.ast_val) = array_expr;
}
#line 1762 "/home/godcc/frontend/parser.cpp"
    break;

  case 31: /* ArrayExpList: ArrayExpList '[' Expr ']'  */
#line 337 "/home/godcc/frontend/sysy.y"
                           {
	auto array_expr = new ArrayExprListAst(shared_ptr<Ast>((yyvsp[-3].ast_val)),shared_ptr<Ast>((yyvsp[-1].ast_val)));
	 	array_expr->line = (yyloc).first_line;
        	array_expr->column = (yyloc).first_column;
 	(yyval.ast_val) = array_expr;
}
#line 1773 "/home/godcc/frontend/parser.cpp"
    break;

  case 32: /* InitValList: Expr  */
#line 345 "/home/godcc/frontend/sysy.y"
     {
	auto init_val_list = new InitValListAst();
	init_val_list->expr_init_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	init_val_list->line = (yyloc).first_line;
	init_val_list->column = (yyloc).first_column;
	(yyval.ast_val) = init_val_list;
}
#line 1785 "/home/godcc/frontend/parser.cpp"
    break;

  case 33: /* InitValList: '{' '}'  */
#line 352 "/home/godcc/frontend/sysy.y"
         {
	auto init_val_list = new InitValListAst();
	init_val_list->line = (yyloc).first_line;
	init_val_list->column = (yyloc).first_column;
	(yyval.ast_val) = init_val_list;
}
#line 1796 "/home/godcc/frontend/parser.cpp"
    break;

  case 34: /* InitValList: '{' InitVal '}'  */
#line 358 "/home/godcc/frontend/sysy.y"
                {
	auto init_val_list = new InitValListAst();
	init_val_list->expr_init_val = shared_ptr<Ast>((yyvsp[-1].ast_val));
	init_val_list->line = (yyloc).first_line;
	init_val_list->column = (yyloc).first_column;
	(yyval.ast_val) = init_val_list;
}
#line 1808 "/home/godcc/frontend/parser.cpp"
    break;

  case 35: /* InitVal: InitValList  */
#line 367 "/home/godcc/frontend/sysy.y"
            {
	auto init_val = new InitValAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	init_val->line = (yyloc).first_line;
	init_val->column = (yyloc).first_column;
	(yyval.ast_val) = init_val;
}
#line 1819 "/home/godcc/frontend/parser.cpp"
    break;

  case 36: /* InitVal: InitVal ',' InitValList  */
#line 373 "/home/godcc/frontend/sysy.y"
                        {
	auto init_val = new InitValAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	init_val->line = (yyloc).first_line;
	init_val->column = (yyloc).first_column;
	(yyval.ast_val) = init_val;
}
#line 1830 "/home/godcc/frontend/parser.cpp"
    break;

  case 37: /* VarDecl: FuncType VarDefList ';'  */
#line 383 "/home/godcc/frontend/sysy.y"
                        {
	auto varDecl = new VarDeclAst();
	varDecl->var_def_list = shared_ptr<Ast>((yyvsp[-1].ast_val));
	varDecl->dataType =  shared_ptr<Ast>((yyvsp[-2].ast_val));
		varDecl->line = (yyloc).first_line;
        	varDecl->column = (yyloc).first_column;
	(yyval.ast_val) = varDecl;
}
#line 1843 "/home/godcc/frontend/parser.cpp"
    break;

  case 38: /* VarDefList: VarDef  */
#line 393 "/home/godcc/frontend/sysy.y"
       {
	auto varDeclUp = new VarDefListAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	varDeclUp->line = (yyloc).first_line;
	varDeclUp->column = (yyloc).first_column;
        (yyval.ast_val) = varDeclUp;
}
#line 1854 "/home/godcc/frontend/parser.cpp"
    break;

  case 39: /* VarDefList: VarDefList ',' VarDef  */
#line 399 "/home/godcc/frontend/sysy.y"
                       {
	auto varDeclUp = new VarDefListAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	varDeclUp->line = (yyloc).first_line;
	varDeclUp->column = (yyloc).first_column;
        (yyval.ast_val) = varDeclUp;
}
#line 1865 "/home/godcc/frontend/parser.cpp"
    break;

  case 40: /* VarDef: Identifier  */
#line 408 "/home/godcc/frontend/sysy.y"
           {
	auto varDef = new VarDefAst();
	varDef->ident = shared_ptr<Ast>((yyvsp[0].ast_val));
		varDef->line = (yyloc).first_line;
        	varDef->column = (yyloc).first_column;
	(yyval.ast_val) = varDef;
}
#line 1877 "/home/godcc/frontend/parser.cpp"
    break;

  case 41: /* VarDef: Identifier ArrayExpList  */
#line 415 "/home/godcc/frontend/sysy.y"
                        {
	auto varDef = new VarDefAst();
	varDef->ident = shared_ptr<Ast>((yyvsp[-1].ast_val));
	varDef->array_expr_list = shared_ptr<Ast>((yyvsp[0].ast_val));
	varDef->line = (yyloc).first_line;
	varDef->column = (yyloc).first_column;
	(yyval.ast_val) = varDef;
}
#line 1890 "/home/godcc/frontend/parser.cpp"
    break;

  case 42: /* VarDef: Identifier '=' InitValList  */
#line 423 "/home/godcc/frontend/sysy.y"
                           {
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>((yyvsp[-2].ast_val));
	varDef->var_expr =  shared_ptr<Ast>((yyvsp[0].ast_val));
	varDef->line = (yyloc).first_line;
	varDef->column = (yyloc).first_column;
	(yyval.ast_val) = varDef;
}
#line 1903 "/home/godcc/frontend/parser.cpp"
    break;

  case 43: /* VarDef: Identifier ArrayExpList '=' InitValList  */
#line 431 "/home/godcc/frontend/sysy.y"
                                        {
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>((yyvsp[-3].ast_val));
	varDef->array_expr_list = shared_ptr<Ast>((yyvsp[-2].ast_val));
	varDef->var_expr =  shared_ptr<Ast>((yyvsp[0].ast_val));
	varDef->line = (yyloc).first_line;
	varDef->column = (yyloc).first_column;
	(yyval.ast_val) = varDef;
}
#line 1917 "/home/godcc/frontend/parser.cpp"
    break;

  case 44: /* Identifier: IDENT  */
#line 443 "/home/godcc/frontend/sysy.y"
      {
	auto identifier=  new IdentifierAst();
	identifier->name = ((yyvsp[0].str_val))->c_str();
	identifier->line = (yyloc).first_line;
	identifier->column = (yyloc).first_column;
	(yyval.ast_val) = identifier;
}
#line 1929 "/home/godcc/frontend/parser.cpp"
    break;

  case 45: /* Stmt: RETURN Expr ';'  */
#line 454 "/home/godcc/frontend/sysy.y"
                  {
	auto stmt = new StmtAst();
	stmt->expr = shared_ptr<Ast>((yyvsp[-1].ast_val));
	stmt->type = StmtType::kReturn;
	stmt->line = (yyloc).first_line;
	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 1942 "/home/godcc/frontend/parser.cpp"
    break;

  case 46: /* Stmt: RETURN ';'  */
#line 462 "/home/godcc/frontend/sysy.y"
            {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kReturn;
	stmt->line = (yyloc).first_line;
	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 1954 "/home/godcc/frontend/parser.cpp"
    break;

  case 47: /* Stmt: Expr ';'  */
#line 469 "/home/godcc/frontend/sysy.y"
         {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kExpr;
	stmt->expr = shared_ptr<Ast>((yyvsp[-1].ast_val));
		stmt->line = (yyloc).first_line;
        	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 1967 "/home/godcc/frontend/parser.cpp"
    break;

  case 48: /* Stmt: ';'  */
#line 477 "/home/godcc/frontend/sysy.y"
    {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kExpr;
		stmt->line = (yyloc).first_line;
        	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 1979 "/home/godcc/frontend/parser.cpp"
    break;

  case 49: /* Stmt: Block  */
#line 484 "/home/godcc/frontend/sysy.y"
      {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kBlock;
	stmt->expr = shared_ptr<Ast>((yyvsp[0].ast_val));
		stmt->line = (yyloc).first_line;
        	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 1992 "/home/godcc/frontend/parser.cpp"
    break;

  case 50: /* Stmt: LVal '=' Expr ';'  */
#line 492 "/home/godcc/frontend/sysy.y"
                   {
	auto stmt = new StmtAst();
    	stmt->expr = shared_ptr<Ast>((yyvsp[-1].ast_val));
    	stmt->l_val =  shared_ptr<Ast>((yyvsp[-3].ast_val));
    	stmt->type = StmtType::kAssign;
    		stmt->line = (yyloc).first_line;
        	stmt->column = (yyloc).first_column;
    	(yyval.ast_val) = stmt;
 }
#line 2006 "/home/godcc/frontend/parser.cpp"
    break;

  case 51: /* Stmt: IF '(' Expr ')' Stmt  */
#line 501 "/home/godcc/frontend/sysy.y"
                                           {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kIf;
	auto ifStmt = new IfStmtAst();
	ifStmt->line = (yyloc).first_line;
	ifStmt->column = (yyloc).first_column;
	ifStmt->expr = shared_ptr<Ast>((yyvsp[-2].ast_val));
	ifStmt->stmt =  shared_ptr<Ast>((yyvsp[0].ast_val));
	stmt-> expr = shared_ptr<Ast>(ifStmt);
	stmt->line = (yyloc).first_line;
	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 2024 "/home/godcc/frontend/parser.cpp"
    break;

  case 52: /* Stmt: IF '(' Expr ')' Stmt ELSE Stmt  */
#line 514 "/home/godcc/frontend/sysy.y"
                               {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kIf;
	auto ifStmt = new IfStmtAst();
	ifStmt->line = (yyloc).first_line;
	ifStmt->column = (yyloc).first_column;
	ifStmt->expr = shared_ptr<Ast>((yyvsp[-4].ast_val));
	ifStmt->stmt =  shared_ptr<Ast>((yyvsp[-2].ast_val));
	ifStmt->elseStmt = shared_ptr<Ast>((yyvsp[0].ast_val));
	stmt-> expr = shared_ptr<Ast>(ifStmt);
		stmt->line = (yyloc).first_line;
        	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 2043 "/home/godcc/frontend/parser.cpp"
    break;

  case 53: /* Stmt: WHILE '(' Expr ')' Stmt  */
#line 528 "/home/godcc/frontend/sysy.y"
                        {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kWhile;
	auto whileStmt = new WhileStmtAst();
	whileStmt->expr = shared_ptr<Ast>((yyvsp[-2].ast_val));
	whileStmt->stmt =  shared_ptr<Ast>((yyvsp[0].ast_val));
	whileStmt->line = (yyloc).first_line;
	whileStmt->column = (yyloc).first_column;
	stmt->expr = shared_ptr<Ast>(whileStmt);
	stmt->line = (yyloc).first_line;
	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 2061 "/home/godcc/frontend/parser.cpp"
    break;

  case 54: /* Stmt: BREAK ';'  */
#line 541 "/home/godcc/frontend/sysy.y"
          {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kBreak;
		stmt->line = (yyloc).first_line;
        	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 2073 "/home/godcc/frontend/parser.cpp"
    break;

  case 55: /* Stmt: CONTINUE ';'  */
#line 548 "/home/godcc/frontend/sysy.y"
             {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kContinue;
		stmt->line = (yyloc).first_line;
        	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 2085 "/home/godcc/frontend/parser.cpp"
    break;

  case 56: /* Stmt: FOR '(' Stmt Stmt Expr ')' Stmt  */
#line 555 "/home/godcc/frontend/sysy.y"
                                   {
	printf("FOR\n");
	auto stmt = new StmtAst();
	stmt->type = StmtType::kFor;
	auto forStmt = new ForStmtAst();
	forStmt->expr1 = shared_ptr<Ast>((yyvsp[-4].ast_val));
	forStmt->expr2 = shared_ptr<Ast>((yyvsp[-3].ast_val));
	forStmt->expr3 = shared_ptr<Ast>((yyvsp[-2].ast_val));
	forStmt->stmt =  shared_ptr<Ast>((yyvsp[0].ast_val));
	forStmt->line = (yyloc).first_line;
	forStmt->column = (yyloc).first_column;
	stmt->expr = shared_ptr<Ast>(forStmt);
	stmt->line = (yyloc).first_line;
	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 2106 "/home/godcc/frontend/parser.cpp"
    break;

  case 57: /* Stmt: FOR '(' Stmt Stmt ')' Stmt  */
#line 571 "/home/godcc/frontend/sysy.y"
                              {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kFor;
	auto forStmt = new ForStmtAst();
	forStmt->expr1 = shared_ptr<Ast>((yyvsp[-3].ast_val));
	forStmt->expr2 = shared_ptr<Ast>((yyvsp[-2].ast_val));
	forStmt->stmt =  shared_ptr<Ast>((yyvsp[0].ast_val));
	forStmt->line = (yyloc).first_line;
	forStmt->column = (yyloc).first_column;
	stmt->expr = shared_ptr<Ast>(forStmt);
	stmt->line = (yyloc).first_line;
	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 2125 "/home/godcc/frontend/parser.cpp"
    break;

  case 58: /* Stmt: FOR '(' VarDecl Stmt Expr ')' Stmt  */
#line 585 "/home/godcc/frontend/sysy.y"
                                      {
	printf("FOR\n");
	auto stmt = new StmtAst();
	stmt->type = StmtType::kFor;
	auto forStmt = new ForStmtAst();
	forStmt->expr1 = shared_ptr<Ast>((yyvsp[-4].ast_val));
	forStmt->expr2 = shared_ptr<Ast>((yyvsp[-3].ast_val));
	forStmt->expr3 = shared_ptr<Ast>((yyvsp[-2].ast_val));
	forStmt->stmt =  shared_ptr<Ast>((yyvsp[0].ast_val));
	forStmt->line = (yyloc).first_line;
	forStmt->column = (yyloc).first_column;
	stmt->expr = shared_ptr<Ast>(forStmt);
	stmt->line = (yyloc).first_line;
	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 2146 "/home/godcc/frontend/parser.cpp"
    break;

  case 59: /* Stmt: FOR '(' VarDecl Stmt ')' Stmt  */
#line 601 "/home/godcc/frontend/sysy.y"
                                 {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kFor;
	auto forStmt = new ForStmtAst();
	forStmt->expr1 = shared_ptr<Ast>((yyvsp[-3].ast_val));
	forStmt->expr2 = shared_ptr<Ast>((yyvsp[-2].ast_val));
	forStmt->stmt =  shared_ptr<Ast>((yyvsp[0].ast_val));
	forStmt->line = (yyloc).first_line;
	forStmt->column = (yyloc).first_column;
	stmt->expr = shared_ptr<Ast>(forStmt);
	stmt->line = (yyloc).first_line;
	stmt->column = (yyloc).first_column;
	(yyval.ast_val) = stmt;
}
#line 2165 "/home/godcc/frontend/parser.cpp"
    break;

  case 60: /* Expr: OrExpr  */
#line 618 "/home/godcc/frontend/sysy.y"
           {
    auto Expr = new ExpAst();
    Expr->realExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
	Expr->line = (yyloc).first_line;
	Expr->column = (yyloc).first_column;
    (yyval.ast_val) = Expr;
  }
#line 2177 "/home/godcc/frontend/parser.cpp"
    break;

  case 61: /* AddExpr: MulExpr  */
#line 628 "/home/godcc/frontend/sysy.y"
         {
  auto binary = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAdd);
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2188 "/home/godcc/frontend/parser.cpp"
    break;

  case 62: /* AddExpr: AddExpr '+' MulExpr  */
#line 634 "/home/godcc/frontend/sysy.y"
                    {
  auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAdd,"+");
  binary->line = (yyloc).first_line;
  binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2199 "/home/godcc/frontend/parser.cpp"
    break;

  case 63: /* AddExpr: AddExpr '-' MulExpr  */
#line 640 "/home/godcc/frontend/sysy.y"
                    {

  auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAdd,"-");
  binary->line = (yyloc).first_line;
  binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2211 "/home/godcc/frontend/parser.cpp"
    break;

  case 64: /* RelExpr: AddExpr  */
#line 649 "/home/godcc/frontend/sysy.y"
        {
 auto binary = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel);
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2222 "/home/godcc/frontend/parser.cpp"
    break;

  case 65: /* RelExpr: RelExpr LT AddExpr  */
#line 655 "/home/godcc/frontend/sysy.y"
                    {
auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,"<");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2233 "/home/godcc/frontend/parser.cpp"
    break;

  case 66: /* RelExpr: RelExpr GT AddExpr  */
#line 661 "/home/godcc/frontend/sysy.y"
                    {
auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,">");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2244 "/home/godcc/frontend/parser.cpp"
    break;

  case 67: /* RelExpr: RelExpr LE AddExpr  */
#line 667 "/home/godcc/frontend/sysy.y"
                    {
auto binary =  new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,"<=");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2255 "/home/godcc/frontend/parser.cpp"
    break;

  case 68: /* RelExpr: RelExpr GE AddExpr  */
#line 673 "/home/godcc/frontend/sysy.y"
                    {
auto binary= new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,">=");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2266 "/home/godcc/frontend/parser.cpp"
    break;

  case 69: /* EqExpr: RelExpr  */
#line 681 "/home/godcc/frontend/sysy.y"
         {
auto binary = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kEq);
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2277 "/home/godcc/frontend/parser.cpp"
    break;

  case 70: /* EqExpr: EqExpr EQ RelExpr  */
#line 687 "/home/godcc/frontend/sysy.y"
                  {
auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kEq,"==");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2288 "/home/godcc/frontend/parser.cpp"
    break;

  case 71: /* EqExpr: EqExpr NE RelExpr  */
#line 693 "/home/godcc/frontend/sysy.y"
                  {
auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kEq,"!=");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2299 "/home/godcc/frontend/parser.cpp"
    break;

  case 72: /* AndExpr: EqExpr  */
#line 701 "/home/godcc/frontend/sysy.y"
       {
auto binary = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAnd);
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2310 "/home/godcc/frontend/parser.cpp"
    break;

  case 73: /* AndExpr: AndExpr AND EqExpr  */
#line 707 "/home/godcc/frontend/sysy.y"
                    {
auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAnd,"&&");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2321 "/home/godcc/frontend/parser.cpp"
    break;

  case 74: /* OrExpr: AndExpr  */
#line 716 "/home/godcc/frontend/sysy.y"
        {
auto binary = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kLor);
	binary->line = (yyloc).first_line;
	binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2332 "/home/godcc/frontend/parser.cpp"
    break;

  case 75: /* OrExpr: OrExpr OR AndExpr  */
#line 722 "/home/godcc/frontend/sysy.y"
                  {
auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kLor,"||");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2343 "/home/godcc/frontend/parser.cpp"
    break;

  case 76: /* MulExpr: UnaryExp  */
#line 730 "/home/godcc/frontend/sysy.y"
         {
  auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul);
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2354 "/home/godcc/frontend/parser.cpp"
    break;

  case 77: /* MulExpr: MulExpr '*' UnaryExp  */
#line 736 "/home/godcc/frontend/sysy.y"
                     {
auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul,"*");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2365 "/home/godcc/frontend/parser.cpp"
    break;

  case 78: /* MulExpr: MulExpr '/' UnaryExp  */
#line 742 "/home/godcc/frontend/sysy.y"
                     {
auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul,"/");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2376 "/home/godcc/frontend/parser.cpp"
    break;

  case 79: /* MulExpr: MulExpr '%' UnaryExp  */
#line 748 "/home/godcc/frontend/sysy.y"
                     {
auto binary = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul,"%");
  binary->line = (yyloc).first_line;
binary->column = (yyloc).first_column;
  (yyval.ast_val) = binary;
}
#line 2387 "/home/godcc/frontend/parser.cpp"
    break;

  case 80: /* UnaryExp: PostfixExp  */
#line 758 "/home/godcc/frontend/sysy.y"
               {
  	auto unaryExp = new UnaryExprAst();
  	unaryExp-> unaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
  	unaryExp->unaryType = UnaryType::kPostfix;
  	unaryExp->line = (yyloc).first_line;
        unaryExp->column = (yyloc).first_column;
  	(yyval.ast_val) = unaryExp;
  }
#line 2400 "/home/godcc/frontend/parser.cpp"
    break;

  case 81: /* UnaryExp: UnaryOp UnaryExp  */
#line 766 "/home/godcc/frontend/sysy.y"
                   {
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>((yyvsp[-1].ast_val));
        unaryExp->unaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
	unaryExp->unaryType = UnaryType::kUnary;
  	unaryExp->line = (yyloc).first_line;
	unaryExp->column = (yyloc).first_column;
	(yyval.ast_val) = unaryExp;
  }
#line 2414 "/home/godcc/frontend/parser.cpp"
    break;

  case 82: /* UnaryExp: DEC UnaryExp  */
#line 775 "/home/godcc/frontend/sysy.y"
               {
  	auto unaryExp = new UnaryExprAst();
  	unaryExp->unaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
  	auto unaryOpAst = new UnaryOpAst("--");
  	unaryExp->unaryOp = shared_ptr<Ast>(unaryOpAst);
  	unaryExp->unaryType = UnaryType::kUnary;
  	unaryExp->line = (yyloc).first_line;
	unaryExp->column = (yyloc).first_column;
  	(yyval.ast_val) = unaryExp;
  }
#line 2429 "/home/godcc/frontend/parser.cpp"
    break;

  case 83: /* UnaryExp: INC UnaryExp  */
#line 785 "/home/godcc/frontend/sysy.y"
               {
  	auto unaryExp = new UnaryExprAst();
  	unaryExp->unaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
  	auto unaryOpAst = new UnaryOpAst("++");
	unaryExp->unaryOp = shared_ptr<Ast>(unaryOpAst);
  	unaryExp->unaryType = UnaryType::kUnary;
  	unaryExp->line = (yyloc).first_line;
	unaryExp->column = (yyloc).first_column;
	(yyval.ast_val) = unaryExp;
}
#line 2444 "/home/godcc/frontend/parser.cpp"
    break;

  case 84: /* UnaryExp: Identifier '(' ')'  */
#line 795 "/home/godcc/frontend/sysy.y"
                    {
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>((yyvsp[-2].ast_val));
	unaryExp->unaryType = UnaryType::kCall;
	  unaryExp->line = (yyloc).first_line;
	unaryExp->column = (yyloc).first_column;
	(yyval.ast_val) = unaryExp;
}
#line 2457 "/home/godcc/frontend/parser.cpp"
    break;

  case 85: /* UnaryExp: Identifier '(' FuncRParamList ')'  */
#line 803 "/home/godcc/frontend/sysy.y"
                                  {
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>((yyvsp[-3].ast_val));
    	unaryExp->unaryExpr = shared_ptr<Ast>((yyvsp[-1].ast_val));
	unaryExp->unaryType = UnaryType::kCall;
	  unaryExp->line = (yyloc).first_line;
	unaryExp->column = (yyloc).first_column;
	(yyval.ast_val) = unaryExp;
}
#line 2471 "/home/godcc/frontend/parser.cpp"
    break;

  case 86: /* PostfixExp: PrimaryExpr  */
#line 814 "/home/godcc/frontend/sysy.y"
                      {
	auto postfixExp = new PostfixExprAst();
	postfixExp->postfixExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
	postfixExp->postfixType = PostfixType::kPrimary;
	 postfixExp->line = (yyloc).first_line;
	postfixExp->column = (yyloc).first_column;
	(yyval.ast_val) = postfixExp;
}
#line 2484 "/home/godcc/frontend/parser.cpp"
    break;

  case 87: /* PostfixExp: PostfixExp DEC  */
#line 822 "/home/godcc/frontend/sysy.y"
                {
	auto postfixExp = new PostfixExprAst();
	postfixExp->postfixExpr = shared_ptr<Ast>((yyvsp[-1].ast_val));
	postfixExp->postfixType = PostfixType::kBDec;
	  postfixExp->line = (yyloc).first_line;
	postfixExp->column = (yyloc).first_column;
	(yyval.ast_val) = postfixExp;
}
#line 2497 "/home/godcc/frontend/parser.cpp"
    break;

  case 88: /* PostfixExp: PostfixExp INC  */
#line 830 "/home/godcc/frontend/sysy.y"
                {
	auto postfixExp = new PostfixExprAst();
	postfixExp->postfixExpr = shared_ptr<Ast>((yyvsp[-1].ast_val));
	postfixExp->postfixType = PostfixType::kBInc;
        postfixExp->line = (yyloc).first_line;
	postfixExp->column = (yyloc).first_column;
	(yyval.ast_val) = postfixExp;
}
#line 2510 "/home/godcc/frontend/parser.cpp"
    break;

  case 89: /* FuncRParamList: Expr  */
#line 842 "/home/godcc/frontend/sysy.y"
     {
	auto funcRPUp = new FuncRParamListAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	  	  funcRPUp->line = (yyloc).first_line;
                funcRPUp->column = (yyloc).first_column;
	(yyval.ast_val) = funcRPUp;
}
#line 2521 "/home/godcc/frontend/parser.cpp"
    break;

  case 90: /* FuncRParamList: FuncRParamList ',' Expr  */
#line 848 "/home/godcc/frontend/sysy.y"
                        {
	auto funcRPUp = new FuncRParamListAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	  funcRPUp->line = (yyloc).first_line;
	funcRPUp->column = (yyloc).first_column;
	(yyval.ast_val) = funcRPUp;
}
#line 2532 "/home/godcc/frontend/parser.cpp"
    break;

  case 91: /* PrimaryExpr: '(' Expr ')'  */
#line 857 "/home/godcc/frontend/sysy.y"
                 {
  auto primaryAst = new PrimaryExprAst();
  primaryAst->primaryExpr = shared_ptr<Ast>((yyvsp[-1].ast_val));
  primaryAst->primaryType = PrimaryType::EXP;
  primaryAst->line = (yyloc).first_line;
  primaryAst->column = (yyloc).first_column;
  auto expr = dynamic_cast<ExpAst*>((yyvsp[-1].ast_val));
  //编译器求值
  if(expr->have_value){
  	primaryAst->have_value = true;
  	primaryAst->value = expr->value;
  }
  (yyval.ast_val) = primaryAst;
  }
#line 2551 "/home/godcc/frontend/parser.cpp"
    break;

  case 92: /* PrimaryExpr: Number  */
#line 871 "/home/godcc/frontend/sysy.y"
          {
  auto primaryAst = new PrimaryExprAst();
    primaryAst->primaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
    primaryAst->primaryType = PrimaryType::NUMBER;
      primaryAst->line = (yyloc).first_line;
   primaryAst->column = (yyloc).first_column;
    (yyval.ast_val) = primaryAst;
  }
#line 2564 "/home/godcc/frontend/parser.cpp"
    break;

  case 93: /* PrimaryExpr: LVal  */
#line 879 "/home/godcc/frontend/sysy.y"
       {
      auto primaryAst = new PrimaryExprAst();
      primaryAst->primaryType = PrimaryType::IDENTIFIER;
      primaryAst->primaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
        primaryAst->line = (yyloc).first_line;
      	  primaryAst->column = (yyloc).first_column;
      (yyval.ast_val) = primaryAst;
  }
#line 2577 "/home/godcc/frontend/parser.cpp"
    break;

  case 94: /* LVal: Identifier  */
#line 890 "/home/godcc/frontend/sysy.y"
           {
	auto lval = new LValAst();
	lval->l_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	  lval->line = (yyloc).first_line;
	  lval->column = (yyloc).first_column;
	(yyval.ast_val) = lval;
}
#line 2589 "/home/godcc/frontend/parser.cpp"
    break;

  case 95: /* LVal: Identifier ArrayExpList  */
#line 897 "/home/godcc/frontend/sysy.y"
                         {
	auto lval = new LValAst();
	lval->l_val = shared_ptr<Ast>((yyvsp[-1].ast_val));
	lval->array_expr_list = shared_ptr<Ast>((yyvsp[0].ast_val));
	  lval->line = (yyloc).first_line;
	  lval->column = (yyloc).first_column;
	(yyval.ast_val) = lval;
}
#line 2602 "/home/godcc/frontend/parser.cpp"
    break;

  case 96: /* UnaryOp: '+'  */
#line 909 "/home/godcc/frontend/sysy.y"
       {
 auto unaryOpAst = new UnaryOpAst();
   unaryOpAst->op = "+";
   unaryOpAst->line = (yyloc).first_line;
   unaryOpAst->column = (yyloc).first_column;
   (yyval.ast_val) = unaryOpAst;
 }
#line 2614 "/home/godcc/frontend/parser.cpp"
    break;

  case 97: /* UnaryOp: '-'  */
#line 916 "/home/godcc/frontend/sysy.y"
       {
 auto unaryOpAst = new UnaryOpAst();
   unaryOpAst->op = "-";
   unaryOpAst->line = (yyloc).first_line;
   unaryOpAst->column = (yyloc).first_column;
   (yyval.ast_val) = unaryOpAst;
 }
#line 2626 "/home/godcc/frontend/parser.cpp"
    break;

  case 98: /* UnaryOp: '!'  */
#line 923 "/home/godcc/frontend/sysy.y"
       {
  auto unaryOpAst = new UnaryOpAst();
  unaryOpAst->op = "!";
  unaryOpAst->line = (yyloc).first_line;
  unaryOpAst->column = (yyloc).first_column;
  (yyval.ast_val) = unaryOpAst;
 }
#line 2638 "/home/godcc/frontend/parser.cpp"
    break;

  case 99: /* Number: INT_CONST  */
#line 933 "/home/godcc/frontend/sysy.y"
              {
  auto numberAst = new NumberAst();
  numberAst->value = ((yyvsp[0].int_val));
  numberAst->line = (yyloc).first_line;
  numberAst->column = (yyloc).first_column;
  (yyval.ast_val) = numberAst;
  }
#line 2650 "/home/godcc/frontend/parser.cpp"
    break;


#line 2654 "/home/godcc/frontend/parser.cpp"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, ast);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, ast);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc, ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, ast);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 942 "/home/godcc/frontend/sysy.y"


// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
void yyerror(shared_ptr<Ast> &ast, const char *s) {
  	printf("[ERROR] address:%d:%d '%s'\n",yylloc.first_line,yylloc.first_column,s);
}
