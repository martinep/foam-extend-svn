/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

   Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

// Take the name prefix into account.
#define yylex   velex

#include "ValueExpressionParser.tab.hh"

/* User implementation prologue.  */
#line 61 "ValueExpressionParser.yy"

#include "ValueExpressionDriver.H"
#include "ValueExpressionDriverLogicalTemplates.H"


/* Line 317 of lalr1.cc.  */
#line 49 "ValueExpressionParser.tab.cc"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG							\
  for (bool yydebugcond_ = yydebug_; yydebugcond_; yydebugcond_ = false)	\
    (*yycdebug_)

/* Enable debugging if requested.  */
#if YYDEBUG

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab

namespace ve
{
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  ValueExpressionParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  ValueExpressionParser::ValueExpressionParser (ValueExpressionDriver& driver_yyarg)
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
      driver (driver_yyarg)
  {
  }

  ValueExpressionParser::~ValueExpressionParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  ValueExpressionParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
        case 3: /* "\"scalarID\"" */
#line 146 "ValueExpressionParser.yy"
	{ debug_stream () << *(yyvaluep->name); };
#line 179 "ValueExpressionParser.tab.cc"
	break;
      case 4: /* "\"vectorID\"" */
#line 146 "ValueExpressionParser.yy"
	{ debug_stream () << *(yyvaluep->vname); };
#line 184 "ValueExpressionParser.tab.cc"
	break;
      case 5: /* "\"faceScalarID\"" */
#line 146 "ValueExpressionParser.yy"
	{ debug_stream () << *(yyvaluep->fsname); };
#line 189 "ValueExpressionParser.tab.cc"
	break;
      case 6: /* "\"faceVectorID\"" */
#line 146 "ValueExpressionParser.yy"
	{ debug_stream () << *(yyvaluep->fvname); };
#line 194 "ValueExpressionParser.tab.cc"
	break;
      case 7: /* "\"cellSetID\"" */
#line 146 "ValueExpressionParser.yy"
	{ debug_stream () << *(yyvaluep->setname); };
#line 199 "ValueExpressionParser.tab.cc"
	break;
      case 8: /* "\"cellZoneID\"" */
#line 146 "ValueExpressionParser.yy"
	{ debug_stream () << *(yyvaluep->zonename); };
#line 204 "ValueExpressionParser.tab.cc"
	break;
      case 9: /* "\"number\"" */
#line 149 "ValueExpressionParser.yy"
	{ debug_stream () << (yyvaluep->val); };
#line 209 "ValueExpressionParser.tab.cc"
	break;
      case 10: /* "\"vector\"" */
#line 147 "ValueExpressionParser.yy"
	{ Foam::OStringStream buff; buff << *(yyvaluep->vec); debug_stream () << buff.str().c_str(); };
#line 214 "ValueExpressionParser.tab.cc"
	break;
      case 11: /* "\"sexpression\"" */
#line 149 "ValueExpressionParser.yy"
	{ debug_stream () << (yyvaluep->val); };
#line 219 "ValueExpressionParser.tab.cc"
	break;
      case 12: /* "\"expression\"" */
#line 150 "ValueExpressionParser.yy"
	{ debug_stream () << (yyvaluep->sfield)->name().c_str(); };
#line 224 "ValueExpressionParser.tab.cc"
	break;
      case 13: /* "\"lexpression\"" */
#line 150 "ValueExpressionParser.yy"
	{ debug_stream () << (yyvaluep->sfield)->name().c_str(); };
#line 229 "ValueExpressionParser.tab.cc"
	break;
      case 14: /* "\"flexpression\"" */
#line 150 "ValueExpressionParser.yy"
	{ debug_stream () << (yyvaluep->fsfield)->name().c_str(); };
#line 234 "ValueExpressionParser.tab.cc"
	break;
      case 15: /* "\"vexpression\"" */
#line 150 "ValueExpressionParser.yy"
	{ debug_stream () << (yyvaluep->vfield)->name().c_str(); };
#line 239 "ValueExpressionParser.tab.cc"
	break;
      case 16: /* "\"fsexpression\"" */
#line 150 "ValueExpressionParser.yy"
	{ debug_stream () << (yyvaluep->fsfield)->name().c_str(); };
#line 244 "ValueExpressionParser.tab.cc"
	break;
      case 17: /* "\"fvexpression\"" */
#line 150 "ValueExpressionParser.yy"
	{ debug_stream () << (yyvaluep->fvfield)->name().c_str(); };
#line 249 "ValueExpressionParser.tab.cc"
	break;
       default:
	  break;
      }
  }


  void
  ValueExpressionParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif /* ! YYDEBUG */

  void
  ValueExpressionParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 3: /* "\"scalarID\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->name); };
#line 284 "ValueExpressionParser.tab.cc"
	break;
      case 4: /* "\"vectorID\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->vname); };
#line 289 "ValueExpressionParser.tab.cc"
	break;
      case 5: /* "\"faceScalarID\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->fsname); };
#line 294 "ValueExpressionParser.tab.cc"
	break;
      case 6: /* "\"faceVectorID\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->fvname); };
#line 299 "ValueExpressionParser.tab.cc"
	break;
      case 7: /* "\"cellSetID\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->setname); };
#line 304 "ValueExpressionParser.tab.cc"
	break;
      case 8: /* "\"cellZoneID\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->zonename); };
#line 309 "ValueExpressionParser.tab.cc"
	break;
      case 10: /* "\"vector\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->vec); };
#line 314 "ValueExpressionParser.tab.cc"
	break;
      case 12: /* "\"expression\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->sfield); };
#line 319 "ValueExpressionParser.tab.cc"
	break;
      case 13: /* "\"lexpression\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->sfield); };
#line 324 "ValueExpressionParser.tab.cc"
	break;
      case 14: /* "\"flexpression\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->fsfield); };
#line 329 "ValueExpressionParser.tab.cc"
	break;
      case 15: /* "\"vexpression\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->vfield); };
#line 334 "ValueExpressionParser.tab.cc"
	break;
      case 16: /* "\"fsexpression\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->fsfield); };
#line 339 "ValueExpressionParser.tab.cc"
	break;
      case 17: /* "\"fvexpression\"" */
#line 148 "ValueExpressionParser.yy"
	{ delete (yyvaluep->fvfield); };
#line 344 "ValueExpressionParser.tab.cc"
	break;

	default:
	  break;
      }
  }

  void
  ValueExpressionParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

  std::ostream&
  ValueExpressionParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ValueExpressionParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ValueExpressionParser::debug_level_type
  ValueExpressionParser::debug_level () const
  {
    return yydebug_;
  }

  void
  ValueExpressionParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }


  int
  ValueExpressionParser::parse ()
  {
    /// Look-ahead and look-ahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the look-ahead.
    semantic_type yylval;
    /// Location of the look-ahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    #line 37 "ValueExpressionParser.yy"
{
	     // Initialize the initial location.
	     //     @$.begin.filename = @$.end.filename = &driver.file;
}
  /* Line 555 of yacc.c.  */
#line 426 "ValueExpressionParser.tab.cc"
    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;
    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without look-ahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a look-ahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, driver);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Accept?  */
    if (yyn == yyfinal_)
      goto yyacceptlab;

    /* Shift the look-ahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted unless it is eof.  */
    if (yychar != yyeof_)
      yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:
#line 156 "ValueExpressionParser.yy"
    { driver.setScalarResult((yysemantic_stack_[(1) - (1)].sfield));  ;}
    break;

  case 3:
#line 157 "ValueExpressionParser.yy"
    { driver.setVectorResult((yysemantic_stack_[(1) - (1)].vfield));  ;}
    break;

  case 4:
#line 158 "ValueExpressionParser.yy"
    { driver.setLogicalResult((yysemantic_stack_[(1) - (1)].sfield)); ;}
    break;

  case 5:
#line 161 "ValueExpressionParser.yy"
    { (yyval.vfield) = (yysemantic_stack_[(1) - (1)].vfield); ;}
    break;

  case 6:
#line 162 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(*(yysemantic_stack_[(3) - (1)].vfield) + *(yysemantic_stack_[(3) - (3)].vfield)); delete (yysemantic_stack_[(3) - (1)].vfield); delete (yysemantic_stack_[(3) - (3)].vfield); ;}
    break;

  case 7:
#line 163 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(*(yysemantic_stack_[(3) - (1)].sfield) * *(yysemantic_stack_[(3) - (3)].vfield)); delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].vfield); ;}
    break;

  case 8:
#line 164 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(*(yysemantic_stack_[(3) - (1)].vfield) * *(yysemantic_stack_[(3) - (3)].sfield)); delete (yysemantic_stack_[(3) - (1)].vfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 9:
#line 165 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(*(yysemantic_stack_[(3) - (1)].vfield) / *(yysemantic_stack_[(3) - (3)].sfield)); delete (yysemantic_stack_[(3) - (1)].vfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 10:
#line 166 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(*(yysemantic_stack_[(3) - (1)].vfield) ^ *(yysemantic_stack_[(3) - (3)].vfield)); delete (yysemantic_stack_[(3) - (1)].vfield); delete (yysemantic_stack_[(3) - (3)].vfield); ;}
    break;

  case 11:
#line 167 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(*(yysemantic_stack_[(3) - (1)].vfield) - *(yysemantic_stack_[(3) - (3)].vfield)); delete (yysemantic_stack_[(3) - (1)].vfield); delete (yysemantic_stack_[(3) - (3)].vfield);;}
    break;

  case 12:
#line 168 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(-*(yysemantic_stack_[(2) - (2)].vfield)); delete (yysemantic_stack_[(2) - (2)].vfield); ;}
    break;

  case 13:
#line 169 "ValueExpressionParser.yy"
    { (yyval.vfield) = (yysemantic_stack_[(3) - (2)].vfield); ;}
    break;

  case 14:
#line 170 "ValueExpressionParser.yy"
    { (yyval.vfield) = driver.doConditional((yysemantic_stack_[(5) - (1)].sfield),(yysemantic_stack_[(5) - (3)].vfield),(yysemantic_stack_[(5) - (5)].vfield),driver.makeVectorField(Foam::vector())); delete (yysemantic_stack_[(5) - (1)].sfield); delete (yysemantic_stack_[(5) - (3)].vfield); delete (yysemantic_stack_[(5) - (5)].vfield); ;}
    break;

  case 15:
#line 171 "ValueExpressionParser.yy"
    { (yyval.vfield) = driver.makePositionField(); ;}
    break;

  case 16:
#line 172 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(Foam::fvc::laplacian(*(yysemantic_stack_[(6) - (3)].fsfield),*(yysemantic_stack_[(6) - (5)].vfield))); delete (yysemantic_stack_[(6) - (3)].fsfield); delete (yysemantic_stack_[(6) - (5)].vfield); ;}
    break;

  case 17:
#line 173 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(Foam::fvc::average(*(yysemantic_stack_[(4) - (3)].fvfield))); delete (yysemantic_stack_[(4) - (3)].fvfield); ;}
    break;

  case 18:
#line 174 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(Foam::fvc::surfaceIntegrate(*(yysemantic_stack_[(4) - (3)].fvfield))); delete (yysemantic_stack_[(4) - (3)].fvfield); ;}
    break;

  case 19:
#line 175 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(Foam::fvc::surfaceSum(*(yysemantic_stack_[(4) - (3)].fvfield))); delete (yysemantic_stack_[(4) - (3)].fvfield); ;}
    break;

  case 20:
#line 176 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(Foam::fvc::grad(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 21:
#line 177 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(Foam::fvc::reconstruct(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 22:
#line 178 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(Foam::fvc::curl(*(yysemantic_stack_[(4) - (3)].vfield))); delete (yysemantic_stack_[(4) - (3)].vfield); ;}
    break;

  case 23:
#line 179 "ValueExpressionParser.yy"
    { (yyval.vfield) = new Foam::volVectorField(Foam::fvc::div(*(yysemantic_stack_[(6) - (3)].fsfield),*(yysemantic_stack_[(6) - (5)].vfield))); delete (yysemantic_stack_[(6) - (3)].fsfield); delete (yysemantic_stack_[(6) - (5)].vfield); ;}
    break;

  case 24:
#line 180 "ValueExpressionParser.yy"
    {
            (yyval.vfield)=driver.getVectorField(*(yysemantic_stack_[(1) - (1)].vname));
                    ;}
    break;

  case 25:
#line 185 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.makeSurfaceScalarField((yysemantic_stack_[(4) - (3)].val)); ;}
    break;

  case 26:
#line 186 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(*(yysemantic_stack_[(3) - (1)].fsfield) + *(yysemantic_stack_[(3) - (3)].fsfield)); delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 27:
#line 187 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(*(yysemantic_stack_[(3) - (1)].fsfield) * *(yysemantic_stack_[(3) - (3)].fsfield)); delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 28:
#line 188 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(*(yysemantic_stack_[(3) - (1)].fvfield) & *(yysemantic_stack_[(3) - (3)].fvfield)); delete (yysemantic_stack_[(3) - (1)].fvfield); delete (yysemantic_stack_[(3) - (3)].fvfield); ;}
    break;

  case 29:
#line 189 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(*(yysemantic_stack_[(3) - (1)].fsfield) / *(yysemantic_stack_[(3) - (3)].fsfield)); delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 30:
#line 190 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(*(yysemantic_stack_[(3) - (1)].fsfield) - *(yysemantic_stack_[(3) - (3)].fsfield)); delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield);;}
    break;

  case 31:
#line 191 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::pow(*(yysemantic_stack_[(6) - (3)].fsfield), (yysemantic_stack_[(6) - (5)].val))); delete (yysemantic_stack_[(6) - (3)].fsfield); ;}
    break;

  case 32:
#line 192 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::log(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 33:
#line 193 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::exp(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 34:
#line 194 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::sqr(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 35:
#line 195 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::sqrt(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 36:
#line 196 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::sin(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 37:
#line 197 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::cos(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 38:
#line 198 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::tan(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 39:
#line 199 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.makeSurfaceScalarField(Foam::min(*(yysemantic_stack_[(4) - (3)].fsfield)).value()); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 40:
#line 200 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.makeSurfaceScalarField(Foam::max(*(yysemantic_stack_[(4) - (3)].fsfield)).value()); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 41:
#line 201 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(-*(yysemantic_stack_[(2) - (2)].fsfield)); delete (yysemantic_stack_[(2) - (2)].fsfield); ;}
    break;

  case 42:
#line 202 "ValueExpressionParser.yy"
    { (yyval.fsfield) = (yysemantic_stack_[(3) - (2)].fsfield); ;}
    break;

  case 43:
#line 203 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField((yysemantic_stack_[(3) - (1)].fvfield)->component(0)); delete (yysemantic_stack_[(3) - (1)].fvfield); ;}
    break;

  case 44:
#line 204 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField((yysemantic_stack_[(3) - (1)].fvfield)->component(1)); delete (yysemantic_stack_[(3) - (1)].fvfield); ;}
    break;

  case 45:
#line 205 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField((yysemantic_stack_[(3) - (1)].fvfield)->component(2)); delete (yysemantic_stack_[(3) - (1)].fvfield); ;}
    break;

  case 46:
#line 206 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.doConditional((yysemantic_stack_[(5) - (1)].fsfield),(yysemantic_stack_[(5) - (3)].fsfield),(yysemantic_stack_[(5) - (5)].fsfield),driver.makeSurfaceScalarField(0.)); delete (yysemantic_stack_[(5) - (1)].fsfield); delete (yysemantic_stack_[(5) - (3)].fsfield); delete (yysemantic_stack_[(5) - (5)].fsfield); ;}
    break;

  case 47:
#line 207 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::mag(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 48:
#line 208 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::mag(*(yysemantic_stack_[(4) - (3)].fvfield))); delete (yysemantic_stack_[(4) - (3)].fvfield); ;}
    break;

  case 49:
#line 209 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.makeAreaField(); ;}
    break;

  case 50:
#line 210 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::fvc::snGrad(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 51:
#line 211 "ValueExpressionParser.yy"
    { (yyval.fsfield) = new Foam::surfaceScalarField(Foam::fvc::interpolate(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 52:
#line 212 "ValueExpressionParser.yy"
    {
            (yyval.fsfield)=driver.getFaceScalarField(*(yysemantic_stack_[(1) - (1)].fsname));
                    ;}
    break;

  case 53:
#line 217 "ValueExpressionParser.yy"
    { (yyval.fvfield) = (yysemantic_stack_[(1) - (1)].fvfield) ;}
    break;

  case 54:
#line 218 "ValueExpressionParser.yy"
    { (yyval.fvfield) = new Foam::surfaceVectorField(*(yysemantic_stack_[(3) - (1)].fvfield) + *(yysemantic_stack_[(3) - (3)].fvfield)); delete (yysemantic_stack_[(3) - (1)].fvfield); delete (yysemantic_stack_[(3) - (3)].fvfield); ;}
    break;

  case 55:
#line 219 "ValueExpressionParser.yy"
    { (yyval.fvfield) = new Foam::surfaceVectorField(*(yysemantic_stack_[(3) - (1)].fsfield) * *(yysemantic_stack_[(3) - (3)].fvfield)); delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fvfield); ;}
    break;

  case 56:
#line 220 "ValueExpressionParser.yy"
    { (yyval.fvfield) = new Foam::surfaceVectorField(*(yysemantic_stack_[(3) - (1)].fvfield) * *(yysemantic_stack_[(3) - (3)].fsfield)); delete (yysemantic_stack_[(3) - (1)].fvfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 57:
#line 221 "ValueExpressionParser.yy"
    { (yyval.fvfield) = new Foam::surfaceVectorField(*(yysemantic_stack_[(3) - (1)].fvfield) ^ *(yysemantic_stack_[(3) - (3)].fvfield)); delete (yysemantic_stack_[(3) - (1)].fvfield); delete (yysemantic_stack_[(3) - (3)].fvfield); ;}
    break;

  case 58:
#line 222 "ValueExpressionParser.yy"
    { (yyval.fvfield) = new Foam::surfaceVectorField(*(yysemantic_stack_[(3) - (1)].fvfield) / *(yysemantic_stack_[(3) - (3)].fsfield)); delete (yysemantic_stack_[(3) - (1)].fvfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 59:
#line 223 "ValueExpressionParser.yy"
    { (yyval.fvfield) = new Foam::surfaceVectorField(*(yysemantic_stack_[(3) - (1)].fvfield) - *(yysemantic_stack_[(3) - (3)].fvfield)); delete (yysemantic_stack_[(3) - (1)].fvfield); delete (yysemantic_stack_[(3) - (3)].fvfield);;}
    break;

  case 60:
#line 224 "ValueExpressionParser.yy"
    { (yyval.fvfield) = new Foam::surfaceVectorField(-*(yysemantic_stack_[(2) - (2)].fvfield)); delete (yysemantic_stack_[(2) - (2)].fvfield); ;}
    break;

  case 61:
#line 225 "ValueExpressionParser.yy"
    { (yyval.fvfield) = (yysemantic_stack_[(3) - (2)].fvfield); ;}
    break;

  case 62:
#line 226 "ValueExpressionParser.yy"
    { (yyval.fvfield) = driver.doConditional((yysemantic_stack_[(5) - (1)].fsfield),(yysemantic_stack_[(5) - (3)].fvfield),(yysemantic_stack_[(5) - (5)].fvfield),driver.makeSurfaceVectorField(Foam::vector::zero)); delete (yysemantic_stack_[(5) - (1)].fsfield); delete (yysemantic_stack_[(5) - (3)].fvfield); delete (yysemantic_stack_[(5) - (5)].fvfield); ;}
    break;

  case 63:
#line 227 "ValueExpressionParser.yy"
    { (yyval.fvfield) = driver.makeFacePositionField(); ;}
    break;

  case 64:
#line 228 "ValueExpressionParser.yy"
    { (yyval.fvfield) = driver.makeFaceProjectionField(); ;}
    break;

  case 65:
#line 229 "ValueExpressionParser.yy"
    { (yyval.fvfield) = driver.makeFaceField(); ;}
    break;

  case 66:
#line 230 "ValueExpressionParser.yy"
    { (yyval.fvfield) = new Foam::surfaceVectorField(Foam::fvc::snGrad(*(yysemantic_stack_[(4) - (3)].vfield))); delete (yysemantic_stack_[(4) - (3)].vfield); ;}
    break;

  case 67:
#line 231 "ValueExpressionParser.yy"
    { (yyval.fvfield) = new Foam::surfaceVectorField(Foam::fvc::interpolate(*(yysemantic_stack_[(4) - (3)].vfield))); delete (yysemantic_stack_[(4) - (3)].vfield); ;}
    break;

  case 68:
#line 232 "ValueExpressionParser.yy"
    {
            (yyval.fvfield)=driver.getFaceVectorField(*(yysemantic_stack_[(1) - (1)].fvname));
                    ;}
    break;

  case 69:
#line 237 "ValueExpressionParser.yy"
    { (yyval.val) = (yysemantic_stack_[(1) - (1)].val); ;}
    break;

  case 70:
#line 238 "ValueExpressionParser.yy"
    { (yyval.val) = -(yysemantic_stack_[(2) - (2)].val); ;}
    break;

  case 71:
#line 241 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeScalarField((yysemantic_stack_[(1) - (1)].val)); ;}
    break;

  case 72:
#line 242 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(*(yysemantic_stack_[(3) - (1)].sfield) + *(yysemantic_stack_[(3) - (3)].sfield)); delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 73:
#line 243 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(*(yysemantic_stack_[(3) - (1)].sfield) - *(yysemantic_stack_[(3) - (3)].sfield)); delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 74:
#line 244 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(*(yysemantic_stack_[(3) - (1)].sfield) * *(yysemantic_stack_[(3) - (3)].sfield)); delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 75:
#line 245 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(*(yysemantic_stack_[(3) - (1)].sfield) / *(yysemantic_stack_[(3) - (3)].sfield)); delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 76:
#line 246 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::pow(*(yysemantic_stack_[(6) - (3)].sfield), (yysemantic_stack_[(6) - (5)].val))); delete (yysemantic_stack_[(6) - (3)].sfield); ;}
    break;

  case 77:
#line 247 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::log(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 78:
#line 248 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::exp(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 79:
#line 249 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(*(yysemantic_stack_[(3) - (1)].vfield) & *(yysemantic_stack_[(3) - (3)].vfield)); delete (yysemantic_stack_[(3) - (1)].vfield); delete (yysemantic_stack_[(3) - (3)].vfield);;}
    break;

  case 80:
#line 250 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(-*(yysemantic_stack_[(2) - (2)].sfield)); delete (yysemantic_stack_[(2) - (2)].sfield); ;}
    break;

  case 81:
#line 251 "ValueExpressionParser.yy"
    { (yyval.sfield) = (yysemantic_stack_[(3) - (2)].sfield); ;}
    break;

  case 82:
#line 252 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::sqr(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 83:
#line 253 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::sqrt(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 84:
#line 254 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::sin(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 85:
#line 255 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::cos(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 86:
#line 256 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::tan(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 87:
#line 257 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeScalarField(Foam::min(*(yysemantic_stack_[(4) - (3)].sfield)).value()); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 88:
#line 258 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeScalarField(Foam::max(*(yysemantic_stack_[(4) - (3)].sfield)).value()); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 89:
#line 259 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::mag(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 90:
#line 260 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::fvc::magSqrGradGrad(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 91:
#line 261 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::mag(*(yysemantic_stack_[(4) - (3)].vfield))); delete (yysemantic_stack_[(4) - (3)].vfield); ;}
    break;

  case 92:
#line 262 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::fvc::div(*(yysemantic_stack_[(4) - (3)].vfield))); delete (yysemantic_stack_[(4) - (3)].vfield); ;}
    break;

  case 93:
#line 263 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::fvc::div(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 94:
#line 264 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::fvc::div(*(yysemantic_stack_[(6) - (3)].fsfield),*(yysemantic_stack_[(6) - (5)].sfield))); delete (yysemantic_stack_[(6) - (3)].fsfield); delete (yysemantic_stack_[(6) - (5)].sfield); ;}
    break;

  case 95:
#line 265 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::fvc::laplacian(*(yysemantic_stack_[(4) - (3)].sfield))); delete (yysemantic_stack_[(4) - (3)].sfield); ;}
    break;

  case 96:
#line 266 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::fvc::laplacian(*(yysemantic_stack_[(6) - (3)].sfield),*(yysemantic_stack_[(6) - (5)].sfield))); delete (yysemantic_stack_[(6) - (3)].sfield); delete (yysemantic_stack_[(6) - (5)].sfield); ;}
    break;

  case 97:
#line 267 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::fvc::laplacian(*(yysemantic_stack_[(6) - (3)].fsfield),*(yysemantic_stack_[(6) - (5)].sfield))); delete (yysemantic_stack_[(6) - (3)].fsfield); delete (yysemantic_stack_[(6) - (5)].sfield); ;}
    break;

  case 98:
#line 268 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::fvc::average(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 99:
#line 269 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::fvc::surfaceIntegrate(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 100:
#line 270 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField(Foam::fvc::surfaceSum(*(yysemantic_stack_[(4) - (3)].fsfield))); delete (yysemantic_stack_[(4) - (3)].fsfield); ;}
    break;

  case 101:
#line 271 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField((yysemantic_stack_[(3) - (1)].vfield)->component(0)); delete (yysemantic_stack_[(3) - (1)].vfield); ;}
    break;

  case 102:
#line 272 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField((yysemantic_stack_[(3) - (1)].vfield)->component(1)); delete (yysemantic_stack_[(3) - (1)].vfield); ;}
    break;

  case 103:
#line 273 "ValueExpressionParser.yy"
    { (yyval.sfield) = new Foam::volScalarField((yysemantic_stack_[(3) - (1)].vfield)->component(2)); delete (yysemantic_stack_[(3) - (1)].vfield); ;}
    break;

  case 104:
#line 274 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.doConditional((yysemantic_stack_[(5) - (1)].sfield),(yysemantic_stack_[(5) - (3)].sfield),(yysemantic_stack_[(5) - (5)].sfield),driver.makeScalarField(0.)); delete (yysemantic_stack_[(5) - (1)].sfield); delete (yysemantic_stack_[(5) - (3)].sfield); delete (yysemantic_stack_[(5) - (5)].sfield); ;}
    break;

  case 105:
#line 275 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeScalarField(M_PI); ;}
    break;

  case 106:
#line 276 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeDistanceField(); ;}
    break;

  case 107:
#line 277 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeRDistanceField(*(yysemantic_stack_[(4) - (3)].vfield)); delete (yysemantic_stack_[(4) - (3)].vfield); ;}
    break;

  case 108:
#line 278 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeVolumeField(); ;}
    break;

  case 109:
#line 279 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeRandomField(); ;}
    break;

  case 110:
#line 280 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeGaussRandomField(); ;}
    break;

  case 111:
#line 281 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeCellIdField(); ;}
    break;

  case 112:
#line 282 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeScalarField(driver.runTime().deltaT().value()); ;}
    break;

  case 113:
#line 283 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeScalarField(driver.runTime().time().value()); ;}
    break;

  case 114:
#line 284 "ValueExpressionParser.yy"
    { 
            (yyval.sfield)=driver.getScalarField(*(yysemantic_stack_[(1) - (1)].name));
				;}
    break;

  case 115:
#line 289 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeScalarField(1); ;}
    break;

  case 116:
#line 290 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeScalarField(0); ;}
    break;

  case 117:
#line 291 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeCellSetField(*(yysemantic_stack_[(4) - (3)].setname)); ;}
    break;

  case 118:
#line 292 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.makeCellZoneField(*(yysemantic_stack_[(4) - (3)].zonename)); ;}
    break;

  case 119:
#line 293 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].sfield),std::less<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].sfield));  delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 120:
#line 294 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].sfield),std::greater<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].sfield));  delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 121:
#line 295 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].sfield),std::less_equal<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].sfield));  delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 122:
#line 296 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].sfield),std::greater_equal<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].sfield));  delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 123:
#line 297 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].sfield),std::equal_to<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].sfield));  delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 124:
#line 298 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].sfield),std::not_equal_to<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].sfield));  delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 125:
#line 299 "ValueExpressionParser.yy"
    { (yyval.sfield) = (yysemantic_stack_[(3) - (2)].sfield); ;}
    break;

  case 126:
#line 300 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.doLogicalOp((yysemantic_stack_[(3) - (1)].sfield),std::logical_and<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].sfield));  delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 127:
#line 301 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.doLogicalOp((yysemantic_stack_[(3) - (1)].sfield),std::logical_or<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].sfield));  delete (yysemantic_stack_[(3) - (1)].sfield); delete (yysemantic_stack_[(3) - (3)].sfield); ;}
    break;

  case 128:
#line 302 "ValueExpressionParser.yy"
    { (yyval.sfield) = driver.doLogicalNot((yysemantic_stack_[(2) - (2)].sfield)); delete (yysemantic_stack_[(2) - (2)].sfield); ;}
    break;

  case 129:
#line 305 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.makeSurfaceScalarField(1); ;}
    break;

  case 130:
#line 306 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.makeSurfaceScalarField(0); ;}
    break;

  case 131:
#line 307 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].fsfield),std::less<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].fsfield));  delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 132:
#line 308 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].fsfield),std::greater<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].fsfield));  delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 133:
#line 309 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].fsfield),std::less_equal<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].fsfield));  delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 134:
#line 310 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].fsfield),std::greater_equal<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].fsfield));  delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 135:
#line 311 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].fsfield),std::equal_to<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].fsfield));  delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 136:
#line 312 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.doCompare((yysemantic_stack_[(3) - (1)].fsfield),std::not_equal_to<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].fsfield));  delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 137:
#line 313 "ValueExpressionParser.yy"
    { (yyval.fsfield) = (yysemantic_stack_[(3) - (2)].fsfield); ;}
    break;

  case 138:
#line 314 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.doLogicalOp((yysemantic_stack_[(3) - (1)].fsfield),std::logical_and<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].fsfield));  delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 139:
#line 315 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.doLogicalOp((yysemantic_stack_[(3) - (1)].fsfield),std::logical_or<Foam::scalar>(),(yysemantic_stack_[(3) - (3)].fsfield));  delete (yysemantic_stack_[(3) - (1)].fsfield); delete (yysemantic_stack_[(3) - (3)].fsfield); ;}
    break;

  case 140:
#line 316 "ValueExpressionParser.yy"
    { (yyval.fsfield) = driver.doLogicalNot((yysemantic_stack_[(2) - (2)].fsfield)); delete (yysemantic_stack_[(2) - (2)].fsfield); ;}
    break;

  case 141:
#line 319 "ValueExpressionParser.yy"
    {     (yyval.vfield) = driver.makeVectorField((yysemantic_stack_[(8) - (3)].sfield),(yysemantic_stack_[(8) - (5)].sfield),(yysemantic_stack_[(8) - (7)].sfield));  delete (yysemantic_stack_[(8) - (3)].sfield); delete (yysemantic_stack_[(8) - (5)].sfield); delete (yysemantic_stack_[(8) - (7)].sfield);}
    break;

  case 142:
#line 322 "ValueExpressionParser.yy"
    {     (yyval.fvfield) = driver.makeSurfaceVectorField((yysemantic_stack_[(8) - (3)].fsfield),(yysemantic_stack_[(8) - (5)].fsfield),(yysemantic_stack_[(8) - (7)].fsfield));  delete (yysemantic_stack_[(8) - (3)].fsfield); delete (yysemantic_stack_[(8) - (5)].fsfield); delete (yysemantic_stack_[(8) - (7)].fsfield);}
    break;


    /* Line 675 of lalr1.cc.  */
#line 1256 "ValueExpressionParser.tab.cc"
	default: break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse look-ahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    if (yyn == yyfinal_)
      goto yyacceptlab;

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the look-ahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		   &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyeof_ && yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  ValueExpressionParser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int ValueExpressionParser::yypact_ninf_ = -292;
  const short int
  ValueExpressionParser::yypact_[] =
  {
       365,  -292,  -292,  -292,   -68,  -292,  -292,  -292,   -62,   -58,
     -51,   -38,   -35,   -31,   -22,   -12,    28,    29,    32,    34,
      35,    36,    39,    40,    41,    58,    68,    69,    70,    94,
      95,   118,   119,   122,   123,   126,   127,   130,   132,   365,
     365,   365,    38,    61,  1324,   -40,  -292,   365,   -45,    -1,
      10,    50,    91,   115,   365,    22,   204,   489,   365,   365,
     365,   489,   544,   544,   544,   544,   133,   134,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   137,
    -292,   -40,    92,   620,   -50,    61,  1324,  -292,  -292,   365,
     365,   365,   365,   365,   365,   -20,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   196,
    -292,  -292,  -292,  -292,  -292,  -292,   116,   138,   139,  -292,
    -292,   145,   148,   162,   163,   164,   165,   166,   176,   191,
     194,   197,   209,   212,   213,   217,   218,   219,   220,   221,
     489,   489,   489,   367,    88,   178,   -17,  -292,   637,   483,
     654,   214,   112,   223,   224,   226,   229,   241,   242,   243,
     244,   245,   246,   247,   248,   544,   544,   544,   671,   505,
     688,  1219,   705,  1230,   722,  -292,  -292,   395,   739,   756,
    1241,   773,   790,   807,   824,   841,   858,   875,   892,  -292,
    -292,  -292,   -41,   -41,  -292,  -292,   137,   137,  -292,  -292,
    -292,  1324,  1324,  1324,  1324,  1324,  1324,   -48,   -48,   137,
    -292,  -292,   -19,   413,   154,  -292,   365,  -292,  -292,  -292,
     489,   195,   258,   264,   265,   365,   365,    -5,   489,   489,
     489,   489,   489,   489,   489,   489,   489,   489,   489,  -292,
     268,   909,  1252,   -44,  1334,  -292,  -292,   544,   544,   544,
     544,   544,   544,   544,   544,   544,   544,  -292,   365,   544,
     544,   544,   544,   544,   544,    11,   544,   544,   544,  -292,
    -292,  -292,   365,  -292,   365,   544,   544,   544,   544,   544,
     544,   544,   544,   544,   544,   544,   544,  -292,  -292,  -292,
    -292,  -292,  -292,  -292,    -4,  -292,  -292,  -292,  -292,  -292,
    -292,  -292,  -292,  -292,  -292,  -292,   365,   365,   540,   566,
    -292,  -292,  -292,  -292,  1263,   926,  1274,   943,  -292,   269,
     270,   339,   271,   584,   960,   977,   994,  1285,  1011,  1028,
    1045,  1062,  1079,  1096,  1113,  -292,  -292,  -292,  1334,  1334,
    1334,  1334,  1334,  1334,    15,    15,  -292,   268,  -292,  1296,
    1130,     8,     8,  -292,  -292,   268,   268,  -292,  -292,  -292,
    1215,    51,   289,  -292,  1307,  1147,  1164,   273,    61,  1324,
     365,   544,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,
      -4,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,
    -292,  -292,  -292,  -292,   544,   544,  -292,  -292,  -292,  -292,
    1181,   602,   274,  1334,   178,  -292,   544,  -292,  1198,  -292
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  ValueExpressionParser::yydefact_[] =
  {
         0,   114,    24,    71,     0,   115,   116,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     2,     4,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      80,     0,     0,     0,     0,     0,     0,   128,     1,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,   111,   110,    15,   108,   106,     0,     0,     0,    52,
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
      81,   125,    11,     6,     8,     9,    79,    10,   101,   102,
     103,   124,   123,   119,   120,   122,   121,    73,    72,     7,
      74,    75,     0,     0,   127,   126,     0,   107,   117,   118,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      60,     0,     0,     0,     0,   140,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      22,    90,     0,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99,    18,   100,
      19,    98,    17,    21,     0,    77,    78,    91,    89,    84,
      85,    86,    87,    88,    82,    83,     0,     0,     0,     0,
      63,    64,    65,    49,     0,     0,     0,     0,    69,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,    61,   137,   136,   135,
     131,   132,   134,   133,    30,    26,    27,    55,    29,     0,
       0,    59,    54,    56,    58,    28,    57,    43,    44,    45,
       0,     0,   139,   138,     0,     0,     0,     0,    14,   104,
       0,     0,    66,    50,    67,    51,   129,   130,    70,    25,
       0,    32,    33,    47,    48,    36,    37,    38,    39,    40,
      34,    35,    23,    94,     0,     0,    16,    97,    96,    76,
       0,     0,     0,    46,    62,   141,     0,    31,     0,   142
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  ValueExpressionParser::yypgoto_[] =
  {
      -292,  -292,   200,    81,   -56,  -291,     0,     9,  -140,  -292,
    -292
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  ValueExpressionParser::yydefgoto_[] =
  {
        -1,    42,    85,   244,   145,   322,    86,    81,   146,    46,
     147
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char ValueExpressionParser::yytable_ninf_ = -1;
  const unsigned short int
  ValueExpressionParser::yytable_[] =
  {
        44,   243,   245,   367,   318,   318,   169,   171,   173,    45,
     106,    47,   107,   108,   319,   320,   266,    48,   267,   268,
     106,    49,   107,   108,   104,   105,   243,   245,    50,   117,
     191,    91,    92,    93,    94,   110,   337,    95,    88,    80,
      83,    51,   306,   266,    52,   267,   268,   109,    53,    84,
      87,    89,    90,    91,    92,    93,    94,    54,   148,    95,
     150,   152,   198,   199,   200,   321,   321,    55,   177,   178,
     179,   181,   182,   183,   184,   185,   186,   187,   188,   111,
     261,   262,   263,   264,   240,   242,   265,   255,   256,   402,
     112,   194,   195,   357,   358,   359,   201,   202,   203,   204,
     205,   206,   207,   208,   210,   211,   213,    56,    57,   240,
     242,    58,   395,    59,    60,    61,   214,   215,    62,    63,
      64,   259,   260,   261,   262,   263,   264,   362,   363,   265,
     113,    89,    90,    91,    92,    93,    94,    65,   144,    95,
      80,    83,   151,   168,   170,   172,   174,    66,    67,    68,
      84,    87,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,    89,    90,    91,    92,    93,    94,   257,   258,
      95,   114,   189,    69,    70,   327,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,    89,    90,    91,    92,
      93,    94,   273,   274,    95,   115,   217,    71,    72,   347,
      43,    73,    74,   351,   352,    75,    76,   355,   356,    77,
     361,    78,   118,   175,   176,    95,   308,   108,   218,   219,
     109,   239,   241,   327,   220,   315,   317,   221,   177,   178,
     179,   181,   182,   183,   184,   185,   186,   187,   188,    79,
      82,   222,   223,   224,   225,   226,   239,   241,   259,   260,
     261,   262,   263,   264,   116,   227,   265,   143,   350,   149,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     228,   180,   365,   229,   366,   310,   230,   216,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   231,   192,
     193,   232,   233,   196,   197,   272,   234,   235,   236,   237,
     238,   309,   275,   276,   209,   277,   212,   369,   278,   323,
     324,   325,   326,   328,   329,   330,   331,   332,   333,   334,
     279,   280,   281,   282,   283,   284,   285,   286,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   348,   311,   404,
      79,    82,   353,   354,   312,   313,   265,   360,   378,   376,
     377,   379,   268,   399,   407,     0,   309,   323,   324,   325,
     326,   328,   329,   330,   331,   332,   333,   334,     1,     2,
     400,     0,     0,     0,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,     0,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,    23,     0,    24,
      25,     0,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,   314,   316,     0,     0,     0,
       0,   180,     0,     0,     0,    39,     0,    89,    90,    91,
      92,    93,    94,     0,    40,    95,     0,   246,     0,     0,
      41,     0,   401,     0,     0,     0,     0,     0,   349,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,     0,
       0,     0,   364,     0,   307,   403,   294,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   408,     0,     0,
       0,     0,     1,     2,   119,   120,     0,     0,     3,     0,
       0,     0,     0,     0,     0,     0,   368,   121,     5,     6,
       7,     8,     9,    10,    11,   122,   123,   124,   125,    12,
      13,    14,    15,    16,    17,    18,    19,   126,    20,    21,
      22,    23,   127,    24,    25,   128,    26,    27,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   119,
     120,     0,     0,    89,    90,    91,    92,    93,    94,   140,
       0,    95,   153,   270,     0,     0,     0,     0,   141,     0,
     122,   123,   124,   125,   142,   259,   260,   261,   262,   263,
     264,     0,   126,   265,     0,   288,     0,   127,     0,     0,
     128,     0,     0,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   165,     0,     0,     0,     0,     0,
       0,   370,     0,   166,     0,     0,     0,     0,     0,   167,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
       0,     0,     0,     0,     0,     0,     0,   371,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,     0,     0,
       0,     0,     0,     0,     0,   380,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,     0,     0,     0,     0,
       0,     0,     0,   406,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
     190,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,   269,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,   271,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,     0,     0,     0,     0,     0,
       0,   287,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,     0,     0,     0,     0,     0,     0,   289,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,     0,
       0,     0,     0,     0,     0,   291,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,     0,     0,     0,     0,
       0,     0,   293,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,   295,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,   296,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,   298,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
     299,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,   300,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,   301,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,     0,     0,     0,     0,     0,
       0,   302,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,   303,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,     0,
       0,     0,     0,     0,     0,   304,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,   305,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,     0,     0,     0,     0,     0,     0,   335,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,   373,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,   375,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,     0,     0,     0,     0,     0,     0,
     381,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,     0,     0,     0,     0,     0,     0,   382,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,     0,     0,
       0,     0,     0,     0,   383,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,     0,     0,     0,     0,     0,
       0,   385,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,     0,     0,     0,     0,     0,     0,   386,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,     0,
       0,     0,     0,     0,     0,   387,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,     0,     0,     0,     0,
       0,     0,   388,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,     0,     0,     0,     0,     0,     0,   389,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
       0,     0,     0,     0,     0,     0,   390,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,     0,     0,     0,
       0,     0,     0,   391,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
     393,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,   397,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,   398,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,     0,     0,     0,     0,     0,
       0,   405,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,     0,     0,     0,     0,   394,     0,   409,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   259,
     260,   261,   262,   263,   264,     0,     0,   265,     0,   290,
     259,   260,   261,   262,   263,   264,     0,     0,   265,     0,
     292,    89,    90,    91,    92,    93,    94,     0,     0,    95,
       0,   297,   259,   260,   261,   262,   263,   264,     0,     0,
     265,     0,   336,    89,    90,    91,    92,    93,    94,     0,
       0,    95,     0,   372,    89,    90,    91,    92,    93,    94,
       0,     0,    95,     0,   374,   259,   260,   261,   262,   263,
     264,     0,     0,   265,     0,   384,    89,    90,    91,    92,
      93,    94,     0,     0,    95,     0,   392,    89,    90,    91,
      92,    93,    94,     0,     0,    95,     0,   396,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256
  };

  /* YYCHECK.  */
  const short int
  ValueExpressionParser::yycheck_[] =
  {
         0,   141,   142,   294,     9,     9,    62,    63,    64,     0,
      60,    79,    62,    63,    19,    20,    60,    79,    62,    63,
      60,    79,    62,    63,    72,    73,   166,   167,    79,     7,
      80,    72,    73,    74,    75,    80,    80,    78,     0,    39,
      40,    79,    61,    60,    79,    62,    63,    47,    79,    40,
      41,    70,    71,    72,    73,    74,    75,    79,    58,    78,
      60,    61,    82,    83,    84,    70,    70,    79,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    80,
      72,    73,    74,    75,   140,   141,    78,    72,    73,   380,
      80,    91,    92,    82,    83,    84,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    79,    79,   165,
     166,    79,    61,    79,    79,    79,   107,   108,    79,    79,
      79,    70,    71,    72,    73,    74,    75,   267,   268,    78,
      80,    70,    71,    72,    73,    74,    75,    79,    57,    78,
     140,   141,    61,    62,    63,    64,    65,    79,    79,    79,
     141,   142,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    70,    71,    72,    73,    74,    75,    80,    81,
      78,    80,    80,    79,    79,   231,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    70,    71,    72,    73,
      74,    75,    80,    81,    78,    80,    80,    79,    79,   255,
       0,    79,    79,   259,   260,    79,    79,   263,   264,    79,
     266,    79,     8,    80,    80,    78,   216,    63,    80,    80,
     220,   140,   141,   279,    79,   225,   226,    79,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,    39,
      40,    79,    79,    79,    79,    79,   165,   166,    70,    71,
      72,    73,    74,    75,    54,    79,    78,    57,   258,    59,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      79,    71,   272,    79,   274,    80,    79,    81,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    79,    89,
      90,    79,    79,    93,    94,    81,    79,    79,    79,    79,
      79,   220,    79,    79,   104,    79,   106,   307,    79,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
      79,    79,    79,    79,    79,    79,    79,    79,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,    80,   395,
     140,   141,   261,   262,    80,    80,    78,   266,     9,    80,
      80,    80,    63,    80,    80,    -1,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,     3,     4,
     370,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    39,    40,    41,    42,    -1,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,   225,   226,    -1,    -1,    -1,
      -1,   231,    -1,    -1,    -1,    70,    -1,    70,    71,    72,
      73,    74,    75,    -1,    79,    78,    -1,    80,    -1,    -1,
      85,    -1,   371,    -1,    -1,    -1,    -1,    -1,   258,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,   272,    -1,    61,   394,    81,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,   406,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   306,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,     5,
       6,    -1,    -1,    70,    71,    72,    73,    74,    75,    70,
      -1,    78,    18,    80,    -1,    -1,    -1,    -1,    79,    -1,
      26,    27,    28,    29,    85,    70,    71,    72,    73,    74,
      75,    -1,    38,    78,    -1,    80,    -1,    43,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    79,    -1,    -1,    -1,    -1,    -1,    85,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    -1,    80,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    80,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    -1,    80,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    80,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    -1,    80,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    80,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    -1,    80,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    61,    -1,    80,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    70,
      71,    72,    73,    74,    75,    -1,    -1,    78,    -1,    80,
      70,    71,    72,    73,    74,    75,    -1,    -1,    78,    -1,
      80,    70,    71,    72,    73,    74,    75,    -1,    -1,    78,
      -1,    80,    70,    71,    72,    73,    74,    75,    -1,    -1,
      78,    -1,    80,    70,    71,    72,    73,    74,    75,    -1,
      -1,    78,    -1,    80,    70,    71,    72,    73,    74,    75,
      -1,    -1,    78,    -1,    80,    70,    71,    72,    73,    74,
      75,    -1,    -1,    78,    -1,    80,    70,    71,    72,    73,
      74,    75,    -1,    -1,    78,    -1,    80,    70,    71,    72,
      73,    74,    75,    -1,    -1,    78,    -1,    80,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  ValueExpressionParser::yystos_[] =
  {
         0,     3,     4,     9,    18,    19,    20,    21,    22,    23,
      24,    25,    30,    31,    32,    33,    34,    35,    36,    37,
      39,    40,    41,    42,    44,    45,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    70,
      79,    85,    87,    88,    92,    93,    95,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    88,
      92,    93,    88,    92,    93,    88,    92,    93,     0,    70,
      71,    72,    73,    74,    75,    78,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    60,    62,    63,    92,
      80,    80,    80,    80,    80,    80,    88,     7,     8,     5,
       6,    18,    26,    27,    28,    29,    38,    43,    46,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      70,    79,    85,    88,    89,    90,    94,    96,    92,    88,
      92,    89,    92,    18,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    70,    79,    85,    89,    90,
      89,    90,    89,    90,    89,    80,    80,    92,    92,    92,
      88,    92,    92,    92,    92,    92,    92,    92,    92,    80,
      80,    80,    88,    88,    92,    92,    88,    88,    82,    83,
      84,    92,    92,    92,    92,    92,    92,    92,    92,    88,
      92,    92,    88,    92,    93,    93,    81,    80,    80,    80,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    89,
      90,    89,    90,    94,    89,    94,    80,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    80,    81,    70,
      71,    72,    73,    74,    75,    78,    60,    62,    63,    80,
      80,    80,    81,    80,    81,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    80,    80,    80,
      80,    80,    80,    80,    81,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    61,    61,    92,    89,
      80,    80,    80,    80,    88,    92,    88,    92,     9,    19,
      20,    70,    91,    89,    89,    89,    89,    90,    89,    89,
      89,    89,    89,    89,    89,    80,    80,    80,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    90,    89,    88,
      92,    90,    90,    89,    89,    90,    90,    82,    83,    84,
      89,    90,    94,    94,    88,    92,    92,    91,    88,    92,
      81,    81,    80,    80,    80,    80,    80,    80,     9,    80,
      81,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    61,    61,    80,    80,    80,    80,
      92,    89,    91,    89,    90,    80,    81,    80,    89,    80
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  ValueExpressionParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
      63,    58,   315,   316,   317,   318,    60,    62,   319,   320,
      45,    43,    42,    47,    38,    94,   321,   322,    46,    40,
      41,    44,   120,   121,   122,    33
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  ValueExpressionParser::yyr1_[] =
  {
         0,    86,    87,    87,    87,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    91,
      91,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    95,    96
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  ValueExpressionParser::yyr2_[] =
  {
         0,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     2,     3,     5,     3,     6,     4,     4,     4,
       4,     4,     4,     6,     1,     4,     3,     3,     3,     3,
       3,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     2,     3,     3,     3,     3,     5,     4,     4,     3,
       4,     4,     1,     1,     3,     3,     3,     3,     3,     3,
       2,     3,     5,     3,     3,     3,     4,     4,     1,     1,
       2,     1,     3,     3,     3,     3,     6,     4,     4,     3,
       2,     3,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     6,     4,     6,     6,     4,     4,
       4,     3,     3,     3,     5,     1,     3,     4,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     4,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     4,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     8,     8
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const ValueExpressionParser::yytname_[] =
  {
    "$end", "error", "$undefined", "\"scalarID\"", "\"vectorID\"",
  "\"faceScalarID\"", "\"faceVectorID\"", "\"cellSetID\"",
  "\"cellZoneID\"", "\"number\"", "\"vector\"", "\"sexpression\"",
  "\"expression\"", "\"lexpression\"", "\"flexpression\"",
  "\"vexpression\"", "\"fsexpression\"", "\"fvexpression\"",
  "TOKEN_VECTOR", "TOKEN_TRUE", "TOKEN_FALSE", "TOKEN_pi", "TOKEN_rand",
  "TOKEN_id", "TOKEN_randNormal", "TOKEN_position", "TOKEN_fposition",
  "TOKEN_fprojection", "TOKEN_face", "TOKEN_area", "TOKEN_volume",
  "TOKEN_dist", "TOKEN_rdist", "TOKEN_set", "TOKEN_zone", "TOKEN_div",
  "TOKEN_grad", "TOKEN_curl", "TOKEN_snGrad", "TOKEN_magSqrGradGrad",
  "TOKEN_laplacian", "TOKEN_integrate", "TOKEN_sum", "TOKEN_interpolate",
  "TOKEN_average", "TOKEN_reconstruct", "TOKEN_surf", "TOKEN_deltaT",
  "TOKEN_time", "TOKEN_pow", "TOKEN_log", "TOKEN_exp", "TOKEN_mag",
  "TOKEN_sin", "TOKEN_cos", "TOKEN_tan", "TOKEN_min", "TOKEN_max",
  "TOKEN_sqr", "TOKEN_sqrt", "'?'", "':'", "TOKEN_OR", "TOKEN_AND",
  "TOKEN_NEQ", "TOKEN_EQ", "'<'", "'>'", "TOKEN_GEQ", "TOKEN_LEQ", "'-'",
  "'+'", "'*'", "'/'", "'&'", "'^'", "TOKEN_NOT", "TOKEN_NEG", "'.'",
  "'('", "')'", "','", "'x'", "'y'", "'z'", "'!'", "$accept", "unit",
  "vexp", "fsexp", "fvexp", "scalar", "exp", "lexp", "flexp", "vector",
  "fvector", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const ValueExpressionParser::rhs_number_type
  ValueExpressionParser::yyrhs_[] =
  {
        87,     0,    -1,    92,    -1,    88,    -1,    93,    -1,    95,
      -1,    88,    71,    88,    -1,    92,    72,    88,    -1,    88,
      72,    92,    -1,    88,    73,    92,    -1,    88,    75,    88,
      -1,    88,    70,    88,    -1,    70,    88,    -1,    79,    88,
      80,    -1,    93,    60,    88,    61,    88,    -1,    25,    79,
      80,    -1,    40,    79,    89,    81,    88,    80,    -1,    44,
      79,    90,    80,    -1,    41,    79,    90,    80,    -1,    42,
      79,    90,    80,    -1,    36,    79,    92,    80,    -1,    45,
      79,    89,    80,    -1,    37,    79,    88,    80,    -1,    35,
      79,    89,    81,    88,    80,    -1,     4,    -1,    46,    79,
      91,    80,    -1,    89,    71,    89,    -1,    89,    72,    89,
      -1,    90,    74,    90,    -1,    89,    73,    89,    -1,    89,
      70,    89,    -1,    49,    79,    89,    81,    91,    80,    -1,
      50,    79,    89,    80,    -1,    51,    79,    89,    80,    -1,
      58,    79,    89,    80,    -1,    59,    79,    89,    80,    -1,
      53,    79,    89,    80,    -1,    54,    79,    89,    80,    -1,
      55,    79,    89,    80,    -1,    56,    79,    89,    80,    -1,
      57,    79,    89,    80,    -1,    70,    89,    -1,    79,    89,
      80,    -1,    90,    78,    82,    -1,    90,    78,    83,    -1,
      90,    78,    84,    -1,    94,    60,    89,    61,    89,    -1,
      52,    79,    89,    80,    -1,    52,    79,    90,    80,    -1,
      29,    79,    80,    -1,    38,    79,    92,    80,    -1,    43,
      79,    92,    80,    -1,     5,    -1,    96,    -1,    90,    71,
      90,    -1,    89,    72,    90,    -1,    90,    72,    89,    -1,
      90,    75,    90,    -1,    90,    73,    89,    -1,    90,    70,
      90,    -1,    70,    90,    -1,    79,    90,    80,    -1,    94,
      60,    90,    61,    90,    -1,    26,    79,    80,    -1,    27,
      79,    80,    -1,    28,    79,    80,    -1,    38,    79,    88,
      80,    -1,    43,    79,    88,    80,    -1,     6,    -1,     9,
      -1,    70,     9,    -1,     9,    -1,    92,    71,    92,    -1,
      92,    70,    92,    -1,    92,    72,    92,    -1,    92,    73,
      92,    -1,    49,    79,    92,    81,    91,    80,    -1,    50,
      79,    92,    80,    -1,    51,    79,    92,    80,    -1,    88,
      74,    88,    -1,    70,    92,    -1,    79,    92,    80,    -1,
      58,    79,    92,    80,    -1,    59,    79,    92,    80,    -1,
      53,    79,    92,    80,    -1,    54,    79,    92,    80,    -1,
      55,    79,    92,    80,    -1,    56,    79,    92,    80,    -1,
      57,    79,    92,    80,    -1,    52,    79,    92,    80,    -1,
      39,    79,    92,    80,    -1,    52,    79,    88,    80,    -1,
      35,    79,    88,    80,    -1,    35,    79,    89,    80,    -1,
      35,    79,    89,    81,    92,    80,    -1,    40,    79,    92,
      80,    -1,    40,    79,    92,    81,    92,    80,    -1,    40,
      79,    89,    81,    92,    80,    -1,    44,    79,    89,    80,
      -1,    41,    79,    89,    80,    -1,    42,    79,    89,    80,
      -1,    88,    78,    82,    -1,    88,    78,    83,    -1,    88,
      78,    84,    -1,    93,    60,    92,    61,    92,    -1,    21,
      -1,    31,    79,    80,    -1,    32,    79,    88,    80,    -1,
      30,    79,    80,    -1,    22,    79,    80,    -1,    24,    79,
      80,    -1,    23,    79,    80,    -1,    47,    79,    80,    -1,
      48,    79,    80,    -1,     3,    -1,    19,    -1,    20,    -1,
      33,    79,     7,    80,    -1,    34,    79,     8,    80,    -1,
      92,    66,    92,    -1,    92,    67,    92,    -1,    92,    69,
      92,    -1,    92,    68,    92,    -1,    92,    65,    92,    -1,
      92,    64,    92,    -1,    79,    93,    80,    -1,    93,    63,
      93,    -1,    93,    62,    93,    -1,    85,    93,    -1,    46,
      79,    19,    80,    -1,    46,    79,    20,    80,    -1,    89,
      66,    89,    -1,    89,    67,    89,    -1,    89,    69,    89,
      -1,    89,    68,    89,    -1,    89,    65,    89,    -1,    89,
      64,    89,    -1,    79,    94,    80,    -1,    94,    63,    94,
      -1,    94,    62,    94,    -1,    85,    94,    -1,    18,    79,
      92,    81,    92,    81,    92,    80,    -1,    18,    79,    89,
      81,    89,    81,    89,    80,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  ValueExpressionParser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,     9,    11,    15,    19,    23,
      27,    31,    35,    38,    42,    48,    52,    59,    64,    69,
      74,    79,    84,    89,    96,    98,   103,   107,   111,   115,
     119,   123,   130,   135,   140,   145,   150,   155,   160,   165,
     170,   175,   178,   182,   186,   190,   194,   200,   205,   210,
     214,   219,   224,   226,   228,   232,   236,   240,   244,   248,
     252,   255,   259,   265,   269,   273,   277,   282,   287,   289,
     291,   294,   296,   300,   304,   308,   312,   319,   324,   329,
     333,   336,   340,   345,   350,   355,   360,   365,   370,   375,
     380,   385,   390,   395,   400,   407,   412,   419,   426,   431,
     436,   441,   445,   449,   453,   459,   461,   465,   470,   474,
     478,   482,   486,   490,   494,   496,   498,   500,   505,   510,
     514,   518,   522,   526,   530,   534,   538,   542,   546,   549,
     554,   559,   563,   567,   571,   575,   579,   583,   587,   591,
     595,   598,   607
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  ValueExpressionParser::yyrline_[] =
  {
         0,   156,   156,   157,   158,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   237,
     238,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   319,   322
  };

  // Print the state stack on the debug stream.
  void
  ValueExpressionParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  ValueExpressionParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "), ";
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  ValueExpressionParser::token_number_type
  ValueExpressionParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    85,     2,     2,     2,     2,    74,     2,
      79,    80,    72,    71,    81,    70,    78,    73,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,     2,
      66,     2,    67,    60,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    75,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      82,    83,    84,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    62,    63,    64,    65,    68,
      69,    76,    77
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int ValueExpressionParser::yyeof_ = 0;
  const int ValueExpressionParser::yylast_ = 1407;
  const int ValueExpressionParser::yynnts_ = 11;
  const int ValueExpressionParser::yyempty_ = -2;
  const int ValueExpressionParser::yyfinal_ = 88;
  const int ValueExpressionParser::yyterror_ = 1;
  const int ValueExpressionParser::yyerrcode_ = 256;
  const int ValueExpressionParser::yyntokens_ = 86;

  const unsigned int ValueExpressionParser::yyuser_token_number_max_ = 322;
  const ValueExpressionParser::token_number_type ValueExpressionParser::yyundef_token_ = 2;

} // namespace ve

#line 325 "ValueExpressionParser.yy"


void ve::ValueExpressionParser::error (const ve::ValueExpressionParser::location_type& l,const std::string& m)
{
     driver.error (l, m);
}

