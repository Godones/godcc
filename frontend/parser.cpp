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
  YYSYMBOL_26_ = 26,                       /* '['  */
  YYSYMBOL_27_ = 27,                       /* ']'  */
  YYSYMBOL_28_ = 28,                       /* '{'  */
  YYSYMBOL_29_ = 29,                       /* '}'  */
  YYSYMBOL_30_ = 30,                       /* ';'  */
  YYSYMBOL_31_ = 31,                       /* '='  */
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
  YYSYMBOL_FuncFParamList = 44,            /* FuncFParamList  */
  YYSYMBOL_FuncFParam = 45,                /* FuncFParam  */
  YYSYMBOL_FuncType = 46,                  /* FuncType  */
  YYSYMBOL_Block = 47,                     /* Block  */
  YYSYMBOL_BlockItemList = 48,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 49,                 /* BlockItem  */
  YYSYMBOL_Decl = 50,                      /* Decl  */
  YYSYMBOL_ConstDecl = 51,                 /* ConstDecl  */
  YYSYMBOL_ConstDefList = 52,              /* ConstDefList  */
  YYSYMBOL_ConstDef = 53,                  /* ConstDef  */
  YYSYMBOL_ArrayExpList = 54,              /* ArrayExpList  */
  YYSYMBOL_InitValList = 55,               /* InitValList  */
  YYSYMBOL_InitVal = 56,                   /* InitVal  */
  YYSYMBOL_VarDecl = 57,                   /* VarDecl  */
  YYSYMBOL_VarDefList = 58,                /* VarDefList  */
  YYSYMBOL_VarDef = 59,                    /* VarDef  */
  YYSYMBOL_Identifier = 60,                /* Identifier  */
  YYSYMBOL_Stmt = 61,                      /* Stmt  */
  YYSYMBOL_Expr = 62,                      /* Expr  */
  YYSYMBOL_AddExpr = 63,                   /* AddExpr  */
  YYSYMBOL_RelExpr = 64,                   /* RelExpr  */
  YYSYMBOL_EqExpr = 65,                    /* EqExpr  */
  YYSYMBOL_AndExpr = 66,                   /* AndExpr  */
  YYSYMBOL_OrExpr = 67,                    /* OrExpr  */
  YYSYMBOL_MulExpr = 68,                   /* MulExpr  */
  YYSYMBOL_UnaryExp = 69,                  /* UnaryExp  */
  YYSYMBOL_FuncRParamList = 70,            /* FuncRParamList  */
  YYSYMBOL_PrimaryExpr = 71,               /* PrimaryExpr  */
  YYSYMBOL_LVal = 72,                      /* LVal  */
  YYSYMBOL_UnaryOp = 73,                   /* UnaryOp  */
  YYSYMBOL_Number = 74                     /* Number  */
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
#define YYLAST   224

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

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
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
       2,    31,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    26,     2,    27,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,     2,    29,     2,     2,     2,     2,
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
       0,    70,    70,    84,    88,    95,    98,   115,   123,   134,
     138,   145,   152,   159,   167,   181,   186,   194,   202,   206,
     212,   217,   226,   231,   238,   246,   250,   256,   263,   271,
     275,   281,   286,   290,   297,   301,   309,   317,   321,   328,
     333,   339,   345,   355,   362,   368,   373,   379,   384,   390,
     397,   406,   416,   425,   430,   438,   446,   449,   452,   457,
     460,   463,   466,   469,   474,   477,   480,   485,   488,   494,
     497,   502,   505,   508,   511,   518,   524,   531,   537,   548,
     552,   559,   565,   571,   580,   585,   595,   600,   605,   613
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
  "LOWER_THAN_ELSE", "'('", "')'", "','", "'['", "']'", "'{'", "'}'",
  "';'", "'='", "\",\"", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'",
  "$accept", "TranslationUnitAst", "CompUnit", "CompUnitItem", "FuncDef",
  "FuncFParamList", "FuncFParam", "FuncType", "Block", "BlockItemList",
  "BlockItem", "Decl", "ConstDecl", "ConstDefList", "ConstDef",
  "ArrayExpList", "InitValList", "InitVal", "VarDecl", "VarDefList",
  "VarDef", "Identifier", "Stmt", "Expr", "AddExpr", "RelExpr", "EqExpr",
  "AndExpr", "OrExpr", "MulExpr", "UnaryExp", "FuncRParamList",
  "PrimaryExpr", "LVal", "UnaryOp", "Number", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-72)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      11,    -5,   -72,   -72,    58,    11,   -72,   -72,    25,   -72,
     -72,   -72,    25,   -72,   -72,   -72,   -11,   -72,   -13,    31,
     -72,    20,   -72,    25,    -8,    91,    29,    48,    25,   -72,
      29,    62,   -72,    63,    43,    53,   -72,    25,   -72,    91,
     -72,   -72,   -72,    -6,    38,    77,    32,    92,    89,    98,
     187,   -72,   -72,   -72,    91,   -72,    26,   -72,   -72,    91,
      29,   -72,   -72,    29,   141,   -72,    43,    -5,    75,   104,
      49,    87,   -72,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,   -72,   -72,   -72,    61,
     108,   -72,   -72,   169,   107,   118,   113,   116,   -72,    25,
     -72,   119,   -72,   -72,   -72,   120,   132,   -72,   -72,   183,
      87,   -72,   -72,   -72,    95,   187,   187,    77,    77,    77,
      77,    32,    32,    92,    89,   -72,   -72,   -72,    29,   -72,
     -72,   -72,   121,    91,    91,   -72,   -72,   -72,   -72,   -72,
      91,   139,   -72,    91,   -72,   -72,   144,   146,   142,    87,
     -72,   163,   163,   -72,   167,   -72,   163,   -72
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    15,    16,     0,     2,     3,     5,     0,     6,
      22,    23,     0,     1,     4,    43,     0,    37,    39,     0,
      25,     0,    36,     0,     0,     0,     0,    40,     0,    24,
       0,     0,    38,    39,     0,     0,     9,     0,    89,     0,
      86,    87,    88,    84,     0,    59,    64,    67,    69,    55,
      56,    71,    75,    83,     0,    82,     0,    41,    31,     0,
       0,    26,    28,     0,     0,     8,     0,     0,    11,     0,
       0,    85,    29,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,    32,    34,     0,
       0,    42,    27,     0,     0,     0,     0,     0,    47,     0,
      48,     0,    18,    21,    20,     0,    83,     7,    10,     0,
      14,    81,    77,    79,     0,    57,    58,    60,    61,    62,
      63,    65,    66,    68,    70,    72,    73,    74,     0,    33,
      30,    45,     0,     0,     0,    53,    54,    17,    19,    46,
       0,    12,    78,     0,    35,    44,     0,     0,     0,    13,
      80,     0,     0,    49,    50,    52,     0,    51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   180,   -72,   -72,   122,     2,   -26,   -72,
      93,   -59,   -72,   -72,   160,   -20,   -28,   -72,   -72,   -72,
     172,    -1,   -71,   -25,   136,    37,   117,   123,   -72,   103,
      21,   -72,   -72,   -60,   -72,   -72
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,    35,    36,     8,   100,   101,
     102,     9,    10,    19,    20,    27,    57,    89,    11,    16,
      17,    43,   104,    58,    45,    46,    47,    48,    49,    50,
      51,   114,    52,    53,    54,    55
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      44,    31,    62,    12,   106,   103,     2,    18,    65,     2,
      24,    21,     3,    25,    69,     3,    34,    70,    26,    22,
      25,    23,    33,    71,     1,     2,    37,    21,    88,    15,
      15,     3,    91,    15,    90,    92,    68,    75,    76,   105,
     107,   106,   103,    77,    78,   113,    25,    38,   110,    39,
      38,    30,    39,    15,    56,    87,    28,    56,    13,    40,
      41,    29,    40,    41,    42,    72,    99,    42,   132,    37,
      38,    64,    39,   112,    59,    86,   105,    66,    67,    60,
     154,   155,    40,    41,    44,   157,   128,    42,    59,    25,
     129,   106,   106,    63,    26,    15,   106,    81,    33,    79,
     144,   109,    80,    99,   125,   126,   127,    82,   146,   147,
      73,    74,    38,    59,    39,   148,   121,   122,   150,   142,
     143,   149,    93,    15,    40,    41,   105,   105,   111,    42,
     133,   105,     1,     2,    94,   130,    95,    96,    97,     3,
      38,   134,    39,   135,    93,    15,   136,    64,   137,    98,
     139,   145,    40,    41,     1,     2,    94,    42,    95,    96,
      97,     3,    38,   140,    39,    25,    93,    15,   151,    64,
     152,    98,   153,    15,    40,    41,   115,   116,    94,    42,
      95,    96,    97,   156,    38,    14,    39,    15,    61,   108,
      38,    64,    39,    98,   138,    32,    40,    41,   123,   131,
       0,    42,    40,    41,    38,   124,    39,    42,     0,     0,
     141,   117,   118,   119,   120,     0,    40,    41,     0,     0,
       0,    42,    83,    84,    85
};

static const yytype_int16 yycheck[] =
{
      25,    21,    30,     1,    64,    64,    14,     8,    34,    14,
      23,    12,    20,    26,    39,    20,    24,    23,    31,    30,
      26,    32,    23,    43,    13,    14,    24,    28,    56,     4,
       4,    20,    60,     4,    59,    63,    37,     5,     6,    64,
      66,   101,   101,    11,    12,    70,    26,    21,    68,    23,
      21,    31,    23,     4,    28,    29,    25,    28,     0,    33,
      34,    30,    33,    34,    38,    27,    64,    38,    93,    67,
      21,    28,    23,    24,    26,    54,   101,    24,    25,    31,
     151,   152,    33,    34,   109,   156,    25,    38,    26,    26,
      29,   151,   152,    31,    31,     4,   156,     8,    99,     7,
     128,    26,    10,   101,    83,    84,    85,     9,   133,   134,
      33,    34,    21,    26,    23,   140,    79,    80,   143,    24,
      25,   141,     3,     4,    33,    34,   151,   152,    24,    38,
      23,   156,    13,    14,    15,    27,    17,    18,    19,    20,
      21,    23,    23,    30,     3,     4,    30,    28,    29,    30,
      30,    30,    33,    34,    13,    14,    15,    38,    17,    18,
      19,    20,    21,    31,    23,    26,     3,     4,    24,    28,
      24,    30,    30,     4,    33,    34,    73,    74,    15,    38,
      17,    18,    19,    16,    21,     5,    23,     4,    28,    67,
      21,    28,    23,    30,   101,    23,    33,    34,    81,    30,
      -1,    38,    33,    34,    21,    82,    23,    38,    -1,    -1,
      27,    75,    76,    77,    78,    -1,    33,    34,    -1,    -1,
      -1,    38,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    13,    14,    20,    40,    41,    42,    43,    46,    50,
      51,    57,    46,     0,    42,     4,    58,    59,    60,    52,
      53,    60,    30,    32,    23,    26,    31,    54,    25,    30,
      31,    54,    59,    60,    24,    44,    45,    46,    21,    23,
      33,    34,    38,    60,    62,    63,    64,    65,    66,    67,
      68,    69,    71,    72,    73,    74,    28,    55,    62,    26,
      31,    53,    55,    31,    28,    47,    24,    25,    60,    62,
      23,    54,    27,    33,    34,     5,     6,    11,    12,     7,
      10,     8,     9,    35,    36,    37,    69,    29,    55,    56,
      62,    55,    55,     3,    15,    17,    18,    19,    30,    46,
      47,    48,    49,    50,    61,    62,    72,    47,    45,    26,
      54,    24,    24,    62,    70,    68,    68,    63,    63,    63,
      63,    64,    64,    65,    66,    69,    69,    69,    25,    29,
      27,    30,    62,    23,    23,    30,    30,    29,    49,    30,
      31,    27,    24,    25,    55,    30,    62,    62,    62,    54,
      62,    24,    24,    30,    61,    61,    16,    61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    43,    43,    44,
      44,    45,    45,    45,    45,    46,    46,    47,    48,    48,
      49,    49,    50,    50,    51,    52,    52,    53,    53,    54,
      54,    55,    55,    55,    56,    56,    57,    58,    58,    59,
      59,    59,    59,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    62,    63,    63,    63,    64,
      64,    64,    64,    64,    65,    65,    65,    66,    66,    67,
      67,    68,    68,    68,    68,    69,    69,    69,    69,    70,
      70,    71,    71,    71,    72,    72,    73,    73,    73,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     6,     5,     1,
       3,     2,     4,     5,     3,     1,     1,     3,     1,     2,
       1,     1,     1,     1,     4,     1,     3,     4,     3,     3,
       4,     1,     2,     3,     1,     3,     3,     1,     3,     1,
       2,     3,     4,     1,     3,     2,     2,     1,     1,     4,
       5,     7,     5,     2,     2,     1,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     3,     3,     1,     2,     3,     4,     1,
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
#line 70 "/home/godcc/frontend/sysy.y"
         {
  auto trans  = new TranslationUnitAst();
  trans->comp_unit = shared_ptr<Ast>((yyvsp[0].ast_val));
  ast = shared_ptr<Ast>(trans);
 }
#line 1269 "/home/godcc/frontend/parser.cpp"
    break;

  case 3: /* CompUnit: CompUnitItem  */
#line 84 "/home/godcc/frontend/sysy.y"
             {
    auto compUnit = new CompUnitAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
    (yyval.ast_val) = compUnit;
}
#line 1278 "/home/godcc/frontend/parser.cpp"
    break;

  case 4: /* CompUnit: CompUnit CompUnitItem  */
#line 88 "/home/godcc/frontend/sysy.y"
                      {
	auto compUnit = new CompUnitAst(shared_ptr<Ast>((yyvsp[-1].ast_val)), shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = compUnit;
}
#line 1287 "/home/godcc/frontend/parser.cpp"
    break;

  case 5: /* CompUnitItem: FuncDef  */
#line 95 "/home/godcc/frontend/sysy.y"
        {
 	(yyval.ast_val) = (yyvsp[0].ast_val);
}
#line 1295 "/home/godcc/frontend/parser.cpp"
    break;

  case 6: /* CompUnitItem: Decl  */
#line 98 "/home/godcc/frontend/sysy.y"
     {
	(yyval.ast_val) = (yyvsp[0].ast_val);
}
#line 1303 "/home/godcc/frontend/parser.cpp"
    break;

  case 7: /* FuncDef: FuncType Identifier '(' FuncFParamList ')' Block  */
#line 115 "/home/godcc/frontend/sysy.y"
                                                     {
  	auto funcDef = new FuncDefAst();
	funcDef->funcType = shared_ptr<Ast>((yyvsp[-5].ast_val));
	funcDef->ident = shared_ptr<Ast>((yyvsp[-4].ast_val));
	funcDef->funcParamList = shared_ptr<Ast>((yyvsp[-2].ast_val));
	funcDef->block = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = funcDef;
  }
#line 1316 "/home/godcc/frontend/parser.cpp"
    break;

  case 8: /* FuncDef: FuncType Identifier '(' ')' Block  */
#line 123 "/home/godcc/frontend/sysy.y"
                                       {
     	auto funcDef = new FuncDefAst();
   	funcDef->funcType = shared_ptr<Ast>((yyvsp[-4].ast_val));
   	funcDef->ident = shared_ptr<Ast>((yyvsp[-3].ast_val));
   	funcDef->block = shared_ptr<Ast>((yyvsp[0].ast_val));
   	(yyval.ast_val) = funcDef;
     }
#line 1328 "/home/godcc/frontend/parser.cpp"
    break;

  case 9: /* FuncFParamList: FuncFParam  */
#line 134 "/home/godcc/frontend/sysy.y"
            {
	auto func_fpl = new FuncFParamListAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = func_fpl;
}
#line 1337 "/home/godcc/frontend/parser.cpp"
    break;

  case 10: /* FuncFParamList: FuncFParamList ',' FuncFParam  */
#line 138 "/home/godcc/frontend/sysy.y"
                              {
	auto func_fpl = new FuncFParamListAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = func_fpl;
}
#line 1346 "/home/godcc/frontend/parser.cpp"
    break;

  case 11: /* FuncFParam: FuncType Identifier  */
#line 145 "/home/godcc/frontend/sysy.y"
                     {
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>((yyvsp[-1].ast_val));
	funcParaDef->ident = shared_ptr<Ast>((yyvsp[0].ast_val));
	funcParaDef->first_no_dim = false;
	(yyval.ast_val) = funcParaDef;
}
#line 1358 "/home/godcc/frontend/parser.cpp"
    break;

  case 12: /* FuncFParam: FuncType Identifier '[' ']'  */
#line 152 "/home/godcc/frontend/sysy.y"
                             {
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>((yyvsp[-3].ast_val));
	funcParaDef->ident = shared_ptr<Ast>((yyvsp[-2].ast_val));
	funcParaDef->first_no_dim = true;
	(yyval.ast_val) = funcParaDef;
}
#line 1370 "/home/godcc/frontend/parser.cpp"
    break;

  case 13: /* FuncFParam: FuncType Identifier '[' ']' ArrayExpList  */
#line 159 "/home/godcc/frontend/sysy.y"
                                         {
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>((yyvsp[-4].ast_val));
	funcParaDef->ident = shared_ptr<Ast>((yyvsp[-3].ast_val));
	funcParaDef->first_no_dim = true;
	funcParaDef->array_expr_list = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = funcParaDef;
}
#line 1383 "/home/godcc/frontend/parser.cpp"
    break;

  case 14: /* FuncFParam: FuncType Identifier ArrayExpList  */
#line 167 "/home/godcc/frontend/sysy.y"
                                  {
	auto funcParaDef = new FuncFParamAst();
	funcParaDef->funcType = shared_ptr<Ast>((yyvsp[-2].ast_val));
	funcParaDef->ident = shared_ptr<Ast>((yyvsp[-1].ast_val));
	funcParaDef->first_no_dim = false;
	funcParaDef->array_expr_list = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = funcParaDef;
}
#line 1396 "/home/godcc/frontend/parser.cpp"
    break;

  case 15: /* FuncType: INT  */
#line 181 "/home/godcc/frontend/sysy.y"
      {
    auto funcType = new FuncTypeAst();
    funcType->type = "int";
    (yyval.ast_val) = funcType;
  }
#line 1406 "/home/godcc/frontend/parser.cpp"
    break;

  case 16: /* FuncType: VOID  */
#line 186 "/home/godcc/frontend/sysy.y"
      {
	auto funcType = new FuncTypeAst();
	funcType->type = "void";
	(yyval.ast_val) = funcType;
}
#line 1416 "/home/godcc/frontend/parser.cpp"
    break;

  case 17: /* Block: '{' BlockItemList '}'  */
#line 194 "/home/godcc/frontend/sysy.y"
                          {
	auto block = new BlockAst();
	block-> block_item_list= shared_ptr<Ast>((yyvsp[-1].ast_val));
	(yyval.ast_val) = block;
  }
#line 1426 "/home/godcc/frontend/parser.cpp"
    break;

  case 18: /* BlockItemList: BlockItem  */
#line 202 "/home/godcc/frontend/sysy.y"
           {
	auto blockItemUp = new BlockItemListAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = blockItemUp;
 }
#line 1435 "/home/godcc/frontend/parser.cpp"
    break;

  case 19: /* BlockItemList: BlockItemList BlockItem  */
#line 206 "/home/godcc/frontend/sysy.y"
                         {
	auto blockItemUp = new BlockItemListAst(shared_ptr<Ast>((yyvsp[-1].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = blockItemUp;
}
#line 1444 "/home/godcc/frontend/parser.cpp"
    break;

  case 20: /* BlockItem: Stmt  */
#line 212 "/home/godcc/frontend/sysy.y"
     {
	auto blockItem = new BlockItemAst();
	blockItem->item = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = blockItem;
}
#line 1454 "/home/godcc/frontend/parser.cpp"
    break;

  case 21: /* BlockItem: Decl  */
#line 217 "/home/godcc/frontend/sysy.y"
     {
	auto blockItem = new BlockItemAst();
	blockItem->item = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = blockItem;
}
#line 1464 "/home/godcc/frontend/parser.cpp"
    break;

  case 22: /* Decl: ConstDecl  */
#line 226 "/home/godcc/frontend/sysy.y"
          {
	auto decl = new DeclAst();
	decl->decl = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = decl;
}
#line 1474 "/home/godcc/frontend/parser.cpp"
    break;

  case 23: /* Decl: VarDecl  */
#line 231 "/home/godcc/frontend/sysy.y"
        {
	auto decl = new DeclAst();
	decl->decl = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = decl;
}
#line 1484 "/home/godcc/frontend/parser.cpp"
    break;

  case 24: /* ConstDecl: CONST FuncType ConstDefList ';'  */
#line 238 "/home/godcc/frontend/sysy.y"
                                {
	auto constDecl = new ConstDeclAst();
	constDecl->const_def_list= shared_ptr<Ast>((yyvsp[-1].ast_val));
	constDecl->data_type = shared_ptr<Ast>((yyvsp[-2].ast_val));
	(yyval.ast_val) = constDecl;
}
#line 1495 "/home/godcc/frontend/parser.cpp"
    break;

  case 25: /* ConstDefList: ConstDef  */
#line 246 "/home/godcc/frontend/sysy.y"
         {
	auto constDeclUp = new ConstDefListAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = constDeclUp;
}
#line 1504 "/home/godcc/frontend/parser.cpp"
    break;

  case 26: /* ConstDefList: ConstDefList ',' ConstDef  */
#line 250 "/home/godcc/frontend/sysy.y"
                          {
	auto constDeclUp = new ConstDefListAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = constDeclUp;
}
#line 1513 "/home/godcc/frontend/parser.cpp"
    break;

  case 27: /* ConstDef: Identifier ArrayExpList '=' InitValList  */
#line 256 "/home/godcc/frontend/sysy.y"
                                        {
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>((yyvsp[-3].ast_val));
	constDef->array_expr_list = shared_ptr<Ast>((yyvsp[-2].ast_val));
	constDef->const_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = constDef;
}
#line 1525 "/home/godcc/frontend/parser.cpp"
    break;

  case 28: /* ConstDef: Identifier '=' InitValList  */
#line 263 "/home/godcc/frontend/sysy.y"
                           {
	auto constDef = new ConstDefAst();
	constDef->ident = shared_ptr<Ast>((yyvsp[-2].ast_val));
	constDef->const_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = constDef;
}
#line 1536 "/home/godcc/frontend/parser.cpp"
    break;

  case 29: /* ArrayExpList: '[' Expr ']'  */
#line 271 "/home/godcc/frontend/sysy.y"
              {
 	auto array_expr = new ArrayExprListAst(shared_ptr<Ast>((yyvsp[-1].ast_val)));
 	(yyval.ast_val) = array_expr;
}
#line 1545 "/home/godcc/frontend/parser.cpp"
    break;

  case 30: /* ArrayExpList: ArrayExpList '[' Expr ']'  */
#line 275 "/home/godcc/frontend/sysy.y"
                           {
	auto array_expr = new ArrayExprListAst(shared_ptr<Ast>((yyvsp[-3].ast_val)),shared_ptr<Ast>((yyvsp[-1].ast_val)));
 	(yyval.ast_val) = array_expr;
}
#line 1554 "/home/godcc/frontend/parser.cpp"
    break;

  case 31: /* InitValList: Expr  */
#line 281 "/home/godcc/frontend/sysy.y"
     {
	auto init_val_list = new InitValListAst();
	init_val_list->expr_init_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = init_val_list;
}
#line 1564 "/home/godcc/frontend/parser.cpp"
    break;

  case 32: /* InitValList: '{' '}'  */
#line 286 "/home/godcc/frontend/sysy.y"
         {
	auto init_val_list = new InitValListAst();
	(yyval.ast_val) = init_val_list;
}
#line 1573 "/home/godcc/frontend/parser.cpp"
    break;

  case 33: /* InitValList: '{' InitVal '}'  */
#line 290 "/home/godcc/frontend/sysy.y"
                {
	auto init_val_list = new InitValListAst();
	init_val_list->expr_init_val = shared_ptr<Ast>((yyvsp[-1].ast_val));
	(yyval.ast_val) = init_val_list;
}
#line 1583 "/home/godcc/frontend/parser.cpp"
    break;

  case 34: /* InitVal: InitValList  */
#line 297 "/home/godcc/frontend/sysy.y"
            {
	auto init_val = new InitValAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = init_val;
}
#line 1592 "/home/godcc/frontend/parser.cpp"
    break;

  case 35: /* InitVal: InitVal ',' InitValList  */
#line 301 "/home/godcc/frontend/sysy.y"
                        {
	auto init_val = new InitValAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = init_val;
}
#line 1601 "/home/godcc/frontend/parser.cpp"
    break;

  case 36: /* VarDecl: FuncType VarDefList ';'  */
#line 309 "/home/godcc/frontend/sysy.y"
                        {
	auto varDecl = new VarDeclAst();
	varDecl->var_def_list = shared_ptr<Ast>((yyvsp[-1].ast_val));
	varDecl->dataType =  shared_ptr<Ast>((yyvsp[-2].ast_val));
	(yyval.ast_val) = varDecl;
}
#line 1612 "/home/godcc/frontend/parser.cpp"
    break;

  case 37: /* VarDefList: VarDef  */
#line 317 "/home/godcc/frontend/sysy.y"
       {
	auto varDeclUp = new VarDefListAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
        (yyval.ast_val) = varDeclUp;
}
#line 1621 "/home/godcc/frontend/parser.cpp"
    break;

  case 38: /* VarDefList: VarDefList "," VarDef  */
#line 321 "/home/godcc/frontend/sysy.y"
                       {
	auto varDeclUp = new VarDefListAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
        (yyval.ast_val) = varDeclUp;
}
#line 1630 "/home/godcc/frontend/parser.cpp"
    break;

  case 39: /* VarDef: Identifier  */
#line 328 "/home/godcc/frontend/sysy.y"
           {
	auto varDef = new VarDefAst();
	varDef->ident = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = varDef;
}
#line 1640 "/home/godcc/frontend/parser.cpp"
    break;

  case 40: /* VarDef: Identifier ArrayExpList  */
#line 333 "/home/godcc/frontend/sysy.y"
                        {
	auto varDef = new VarDefAst();
	varDef->ident = shared_ptr<Ast>((yyvsp[-1].ast_val));
	varDef->array_expr_list = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = varDef;
}
#line 1651 "/home/godcc/frontend/parser.cpp"
    break;

  case 41: /* VarDef: Identifier '=' InitValList  */
#line 339 "/home/godcc/frontend/sysy.y"
                           {
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>((yyvsp[-2].ast_val));
	varDef->var_expr =  shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = varDef;
}
#line 1662 "/home/godcc/frontend/parser.cpp"
    break;

  case 42: /* VarDef: Identifier ArrayExpList '=' InitValList  */
#line 345 "/home/godcc/frontend/sysy.y"
                                        {
	auto varDef = new VarDefAst();
	varDef->ident =  shared_ptr<Ast>((yyvsp[-3].ast_val));
	varDef->array_expr_list = shared_ptr<Ast>((yyvsp[-2].ast_val));
	varDef->var_expr =  shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = varDef;
}
#line 1674 "/home/godcc/frontend/parser.cpp"
    break;

  case 43: /* Identifier: IDENT  */
#line 355 "/home/godcc/frontend/sysy.y"
      {
	auto identifier=  new IdentifierAst();
	identifier->name = ((yyvsp[0].str_val))->c_str();
	(yyval.ast_val) = identifier;
}
#line 1684 "/home/godcc/frontend/parser.cpp"
    break;

  case 44: /* Stmt: RETURN Expr ';'  */
#line 362 "/home/godcc/frontend/sysy.y"
                  {
	auto stmt = new StmtAst();
	stmt->expr = shared_ptr<Ast>((yyvsp[-1].ast_val));
	stmt->type = StmtType::kReturn;
	(yyval.ast_val) = stmt;
}
#line 1695 "/home/godcc/frontend/parser.cpp"
    break;

  case 45: /* Stmt: RETURN ';'  */
#line 368 "/home/godcc/frontend/sysy.y"
            {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kReturn;
	(yyval.ast_val) = stmt;
}
#line 1705 "/home/godcc/frontend/parser.cpp"
    break;

  case 46: /* Stmt: Expr ';'  */
#line 373 "/home/godcc/frontend/sysy.y"
         {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kExpr;
	stmt->expr = shared_ptr<Ast>((yyvsp[-1].ast_val));
	(yyval.ast_val) = stmt;
}
#line 1716 "/home/godcc/frontend/parser.cpp"
    break;

  case 47: /* Stmt: ';'  */
#line 379 "/home/godcc/frontend/sysy.y"
    {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kExpr;
	(yyval.ast_val) = stmt;
}
#line 1726 "/home/godcc/frontend/parser.cpp"
    break;

  case 48: /* Stmt: Block  */
#line 384 "/home/godcc/frontend/sysy.y"
      {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kBlock;
	stmt->expr = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = stmt;
}
#line 1737 "/home/godcc/frontend/parser.cpp"
    break;

  case 49: /* Stmt: LVal '=' Expr ';'  */
#line 390 "/home/godcc/frontend/sysy.y"
                   {
	auto stmt = new StmtAst();
    	stmt->expr = shared_ptr<Ast>((yyvsp[-1].ast_val));
    	stmt->l_val =  shared_ptr<Ast>((yyvsp[-3].ast_val));
    	stmt->type = StmtType::kAssign;
    	(yyval.ast_val) = stmt;
 }
#line 1749 "/home/godcc/frontend/parser.cpp"
    break;

  case 50: /* Stmt: IF '(' Expr ')' Stmt  */
#line 397 "/home/godcc/frontend/sysy.y"
                                           {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kIf;
	auto ifStmt = new IfStmtAst();
	ifStmt->expr = shared_ptr<Ast>((yyvsp[-2].ast_val));
	ifStmt->stmt =  shared_ptr<Ast>((yyvsp[0].ast_val));
	stmt-> expr = shared_ptr<Ast>(ifStmt);
	(yyval.ast_val) = stmt;
}
#line 1763 "/home/godcc/frontend/parser.cpp"
    break;

  case 51: /* Stmt: IF '(' Expr ')' Stmt ELSE Stmt  */
#line 406 "/home/godcc/frontend/sysy.y"
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
#line 1778 "/home/godcc/frontend/parser.cpp"
    break;

  case 52: /* Stmt: WHILE '(' Expr ')' Stmt  */
#line 416 "/home/godcc/frontend/sysy.y"
                        {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kWhile;
	auto whileStmt = new WhileStmtAst();
	whileStmt->expr = shared_ptr<Ast>((yyvsp[-2].ast_val));
	whileStmt->stmt =  shared_ptr<Ast>((yyvsp[0].ast_val));
	stmt->expr = shared_ptr<Ast>(whileStmt);
	(yyval.ast_val) = stmt;
}
#line 1792 "/home/godcc/frontend/parser.cpp"
    break;

  case 53: /* Stmt: BREAK ';'  */
#line 425 "/home/godcc/frontend/sysy.y"
          {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kBreak;
	(yyval.ast_val) = stmt;
}
#line 1802 "/home/godcc/frontend/parser.cpp"
    break;

  case 54: /* Stmt: CONTINUE ';'  */
#line 430 "/home/godcc/frontend/sysy.y"
             {
	auto stmt = new StmtAst();
	stmt->type = StmtType::kContinue;
	(yyval.ast_val) = stmt;
}
#line 1812 "/home/godcc/frontend/parser.cpp"
    break;

  case 55: /* Expr: OrExpr  */
#line 438 "/home/godcc/frontend/sysy.y"
           {
    auto Expr = new ExpAst();
    Expr->realExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
    (yyval.ast_val) = Expr;
  }
#line 1822 "/home/godcc/frontend/parser.cpp"
    break;

  case 56: /* AddExpr: MulExpr  */
#line 446 "/home/godcc/frontend/sysy.y"
         {
  (yyval.ast_val) = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAdd);
}
#line 1830 "/home/godcc/frontend/parser.cpp"
    break;

  case 57: /* AddExpr: AddExpr '+' MulExpr  */
#line 449 "/home/godcc/frontend/sysy.y"
                    {
  (yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAdd,"+");
}
#line 1838 "/home/godcc/frontend/parser.cpp"
    break;

  case 58: /* AddExpr: AddExpr '-' MulExpr  */
#line 452 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAdd,"-");
}
#line 1846 "/home/godcc/frontend/parser.cpp"
    break;

  case 59: /* RelExpr: AddExpr  */
#line 457 "/home/godcc/frontend/sysy.y"
        {
 (yyval.ast_val) = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel);
}
#line 1854 "/home/godcc/frontend/parser.cpp"
    break;

  case 60: /* RelExpr: RelExpr LT AddExpr  */
#line 460 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,"<");
}
#line 1862 "/home/godcc/frontend/parser.cpp"
    break;

  case 61: /* RelExpr: RelExpr GT AddExpr  */
#line 463 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,">");
}
#line 1870 "/home/godcc/frontend/parser.cpp"
    break;

  case 62: /* RelExpr: RelExpr LE AddExpr  */
#line 466 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,"<=");
}
#line 1878 "/home/godcc/frontend/parser.cpp"
    break;

  case 63: /* RelExpr: RelExpr GE AddExpr  */
#line 469 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kRel,">=");
}
#line 1886 "/home/godcc/frontend/parser.cpp"
    break;

  case 64: /* EqExpr: RelExpr  */
#line 474 "/home/godcc/frontend/sysy.y"
         {
(yyval.ast_val) = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kEq);
}
#line 1894 "/home/godcc/frontend/parser.cpp"
    break;

  case 65: /* EqExpr: EqExpr EQ RelExpr  */
#line 477 "/home/godcc/frontend/sysy.y"
                  {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kEq,"==");
}
#line 1902 "/home/godcc/frontend/parser.cpp"
    break;

  case 66: /* EqExpr: EqExpr NE RelExpr  */
#line 480 "/home/godcc/frontend/sysy.y"
                  {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kEq,"!=");
}
#line 1910 "/home/godcc/frontend/parser.cpp"
    break;

  case 67: /* AndExpr: EqExpr  */
#line 485 "/home/godcc/frontend/sysy.y"
       {
(yyval.ast_val) = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAnd);
}
#line 1918 "/home/godcc/frontend/parser.cpp"
    break;

  case 68: /* AndExpr: AndExpr AND EqExpr  */
#line 488 "/home/godcc/frontend/sysy.y"
                    {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kAnd,"&&");
}
#line 1926 "/home/godcc/frontend/parser.cpp"
    break;

  case 69: /* OrExpr: AndExpr  */
#line 494 "/home/godcc/frontend/sysy.y"
        {
(yyval.ast_val) = new BinaryExprAst( shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kLor);
}
#line 1934 "/home/godcc/frontend/parser.cpp"
    break;

  case 70: /* OrExpr: OrExpr OR AndExpr  */
#line 497 "/home/godcc/frontend/sysy.y"
                  {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kLor,"||");
}
#line 1942 "/home/godcc/frontend/parser.cpp"
    break;

  case 71: /* MulExpr: UnaryExp  */
#line 502 "/home/godcc/frontend/sysy.y"
         {
  (yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul);
}
#line 1950 "/home/godcc/frontend/parser.cpp"
    break;

  case 72: /* MulExpr: MulExpr '*' UnaryExp  */
#line 505 "/home/godcc/frontend/sysy.y"
                     {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul,"*");
}
#line 1958 "/home/godcc/frontend/parser.cpp"
    break;

  case 73: /* MulExpr: MulExpr '/' UnaryExp  */
#line 508 "/home/godcc/frontend/sysy.y"
                     {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul,"/");
}
#line 1966 "/home/godcc/frontend/parser.cpp"
    break;

  case 74: /* MulExpr: MulExpr '%' UnaryExp  */
#line 511 "/home/godcc/frontend/sysy.y"
                     {
(yyval.ast_val) = new BinaryExprAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)),BinaryType::kMul,"%");
}
#line 1974 "/home/godcc/frontend/parser.cpp"
    break;

  case 75: /* UnaryExp: PrimaryExpr  */
#line 518 "/home/godcc/frontend/sysy.y"
                {
  	auto unaryExp = new UnaryExprAst();
  	unaryExp-> unaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
  	unaryExp->unaryType = UnaryType::kPrimary;
  	(yyval.ast_val) = unaryExp;
  }
#line 1985 "/home/godcc/frontend/parser.cpp"
    break;

  case 76: /* UnaryExp: UnaryOp UnaryExp  */
#line 524 "/home/godcc/frontend/sysy.y"
                   {
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>((yyvsp[-1].ast_val));
        unaryExp->unaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
	unaryExp->unaryType = UnaryType::kUnary;
	(yyval.ast_val) = unaryExp;
  }
#line 1997 "/home/godcc/frontend/parser.cpp"
    break;

  case 77: /* UnaryExp: Identifier '(' ')'  */
#line 531 "/home/godcc/frontend/sysy.y"
                    {
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>((yyvsp[-2].ast_val));
	unaryExp->unaryType = UnaryType::kCall;
	(yyval.ast_val) = unaryExp;
}
#line 2008 "/home/godcc/frontend/parser.cpp"
    break;

  case 78: /* UnaryExp: Identifier '(' FuncRParamList ')'  */
#line 537 "/home/godcc/frontend/sysy.y"
                                  {
	auto unaryExp = new UnaryExprAst();
	unaryExp->unaryOp = shared_ptr<Ast>((yyvsp[-3].ast_val));
    	unaryExp->unaryExpr = shared_ptr<Ast>((yyvsp[-1].ast_val));
	unaryExp->unaryType = UnaryType::kCall;
	(yyval.ast_val) = unaryExp;
}
#line 2020 "/home/godcc/frontend/parser.cpp"
    break;

  case 79: /* FuncRParamList: Expr  */
#line 548 "/home/godcc/frontend/sysy.y"
     {
	auto funcRPUp = new FuncRParamListAst(shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = funcRPUp;
}
#line 2029 "/home/godcc/frontend/parser.cpp"
    break;

  case 80: /* FuncRParamList: FuncRParamList ',' Expr  */
#line 552 "/home/godcc/frontend/sysy.y"
                        {
	auto funcRPUp = new FuncRParamListAst(shared_ptr<Ast>((yyvsp[-2].ast_val)),shared_ptr<Ast>((yyvsp[0].ast_val)));
	(yyval.ast_val) = funcRPUp;
}
#line 2038 "/home/godcc/frontend/parser.cpp"
    break;

  case 81: /* PrimaryExpr: '(' Expr ')'  */
#line 559 "/home/godcc/frontend/sysy.y"
                 {
  auto primaryAst = new PrimaryExprAst();
  primaryAst->primaryExpr = shared_ptr<Ast>((yyvsp[-1].ast_val));
  primaryAst->primaryType = PrimaryType::EXP;
  (yyval.ast_val) = primaryAst;
  }
#line 2049 "/home/godcc/frontend/parser.cpp"
    break;

  case 82: /* PrimaryExpr: Number  */
#line 565 "/home/godcc/frontend/sysy.y"
          {
  auto primaryAst = new PrimaryExprAst();
    primaryAst->primaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
    primaryAst->primaryType = PrimaryType::NUMBER;
    (yyval.ast_val) = primaryAst;
  }
#line 2060 "/home/godcc/frontend/parser.cpp"
    break;

  case 83: /* PrimaryExpr: LVal  */
#line 571 "/home/godcc/frontend/sysy.y"
       {
      auto primaryAst = new PrimaryExprAst();
      primaryAst->primaryType = PrimaryType::IDENTIFIER;
      primaryAst->primaryExpr = shared_ptr<Ast>((yyvsp[0].ast_val));
      (yyval.ast_val) = primaryAst;
  }
#line 2071 "/home/godcc/frontend/parser.cpp"
    break;

  case 84: /* LVal: Identifier  */
#line 580 "/home/godcc/frontend/sysy.y"
           {
	auto lval = new LValAst();
	lval->l_val = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = lval;
}
#line 2081 "/home/godcc/frontend/parser.cpp"
    break;

  case 85: /* LVal: Identifier ArrayExpList  */
#line 585 "/home/godcc/frontend/sysy.y"
                         {
	auto lval = new LValAst();
	lval->l_val = shared_ptr<Ast>((yyvsp[-1].ast_val));
	lval->array_expr_list = shared_ptr<Ast>((yyvsp[0].ast_val));
	(yyval.ast_val) = lval;
}
#line 2092 "/home/godcc/frontend/parser.cpp"
    break;

  case 86: /* UnaryOp: '+'  */
#line 595 "/home/godcc/frontend/sysy.y"
       {
 auto unaryOpAst = new UnaryOpAst();
   unaryOpAst->op = "+";
   (yyval.ast_val) = unaryOpAst;
 }
#line 2102 "/home/godcc/frontend/parser.cpp"
    break;

  case 87: /* UnaryOp: '-'  */
#line 600 "/home/godcc/frontend/sysy.y"
       {
 auto unaryOpAst = new UnaryOpAst();
   unaryOpAst->op = "-";
   (yyval.ast_val) = unaryOpAst;
 }
#line 2112 "/home/godcc/frontend/parser.cpp"
    break;

  case 88: /* UnaryOp: '!'  */
#line 605 "/home/godcc/frontend/sysy.y"
       {
  auto unaryOpAst = new UnaryOpAst();
  unaryOpAst->op = "!";
  (yyval.ast_val) = unaryOpAst;
 }
#line 2122 "/home/godcc/frontend/parser.cpp"
    break;

  case 89: /* Number: INT_CONST  */
#line 613 "/home/godcc/frontend/sysy.y"
              {
  auto numberAst = new NumberAst();
  numberAst->value = ((yyvsp[0].int_val));
  (yyval.ast_val) = numberAst;
  }
#line 2132 "/home/godcc/frontend/parser.cpp"
    break;


#line 2136 "/home/godcc/frontend/parser.cpp"

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

#line 620 "/home/godcc/frontend/sysy.y"


// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
void yyerror(shared_ptr<Ast> &ast, const char *s) {
//  printf("%d:%d '%s'\n",yylloc.first_lien,yylloc.first_colunmn,s);
	printf("%s\n",s);
}
