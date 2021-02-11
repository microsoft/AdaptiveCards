//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     ANTLR Version: 4.8
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from AdaptiveCardsTemplateParser.g4 by ANTLR 4.8

// Unreachable code detected
#pragma warning disable 0162
// The variable '...' is assigned but its value is never used
#pragma warning disable 0219
// Missing XML comment for publicly visible type or member '...'
#pragma warning disable 1591
// Ambiguous reference in cref attribute
#pragma warning disable 419

using System;
using System.IO;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;
using Antlr4.Runtime;
using Antlr4.Runtime.Atn;
using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
using DFA = Antlr4.Runtime.Dfa.DFA;

[System.CodeDom.Compiler.GeneratedCode("ANTLR", "4.8")]
[System.CLSCompliant(false)]
public partial class AdaptiveCardsTemplateParser : Parser {
	protected static DFA[] decisionToDFA;
	protected static PredictionContextCache sharedContextCache = new PredictionContextCache();
	public const int
		COMMA=1, COLON=2, LCB=3, RCB=4, LSB=5, RSB=6, TRUE=7, FALSE=8, NULL=9, 
		StringDeclOpen=10, NUMBER=11, WS=12, CLOSE=13, TEMPLATEDATA=14, TEMPLATEWHEN=15, 
		JPATH=16, TEMPLATEROOT=17, STRING=18, TEMPLATELITERAL=19;
	public const int
		RULE_json = 0, RULE_obj = 1, RULE_pair = 2, RULE_array = 3, RULE_value = 4, 
		RULE_templateString = 5, RULE_templateRoot = 6, RULE_templateExpression = 7;
	public static readonly string[] ruleNames = {
		"json", "obj", "pair", "array", "value", "templateString", "templateRoot", 
		"templateExpression"
	};

	private static readonly string[] _LiteralNames = {
		null, "','", "':'", "'{'", "'}'", "'['", "']'", "'true'", "'false'", "'null'", 
		null, null, null, null, "'$data'", "'$when'"
	};
	private static readonly string[] _SymbolicNames = {
		null, "COMMA", "COLON", "LCB", "RCB", "LSB", "RSB", "TRUE", "FALSE", "NULL", 
		"StringDeclOpen", "NUMBER", "WS", "CLOSE", "TEMPLATEDATA", "TEMPLATEWHEN", 
		"JPATH", "TEMPLATEROOT", "STRING", "TEMPLATELITERAL"
	};
	public static readonly IVocabulary DefaultVocabulary = new Vocabulary(_LiteralNames, _SymbolicNames);

	[NotNull]
	public override IVocabulary Vocabulary
	{
		get
		{
			return DefaultVocabulary;
		}
	}

	public override string GrammarFileName { get { return "AdaptiveCardsTemplateParser.g4"; } }

	public override string[] RuleNames { get { return ruleNames; } }

	public override string SerializedAtn { get { return new string(_serializedATN); } }

	static AdaptiveCardsTemplateParser() {
		decisionToDFA = new DFA[_ATN.NumberOfDecisions];
		for (int i = 0; i < _ATN.NumberOfDecisions; i++) {
			decisionToDFA[i] = new DFA(_ATN.GetDecisionState(i), i);
		}
	}

		public AdaptiveCardsTemplateParser(ITokenStream input) : this(input, Console.Out, Console.Error) { }

		public AdaptiveCardsTemplateParser(ITokenStream input, TextWriter output, TextWriter errorOutput)
		: base(input, output, errorOutput)
	{
		Interpreter = new ParserATNSimulator(this, _ATN, decisionToDFA, sharedContextCache);
	}

	public partial class JsonContext : ParserRuleContext {
		public ValueContext value() {
			return GetRuleContext<ValueContext>(0);
		}
		public JsonContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_json; } }
	}

	[RuleVersion(0)]
	public JsonContext json() {
		JsonContext _localctx = new JsonContext(Context, State);
		EnterRule(_localctx, 0, RULE_json);
		try {
			EnterOuterAlt(_localctx, 1);
			{
			State = 16; value();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class ObjContext : ParserRuleContext {
		public ITerminalNode LCB() { return GetToken(AdaptiveCardsTemplateParser.LCB, 0); }
		public PairContext[] pair() {
			return GetRuleContexts<PairContext>();
		}
		public PairContext pair(int i) {
			return GetRuleContext<PairContext>(i);
		}
		public ITerminalNode RCB() { return GetToken(AdaptiveCardsTemplateParser.RCB, 0); }
		public ITerminalNode[] COMMA() { return GetTokens(AdaptiveCardsTemplateParser.COMMA); }
		public ITerminalNode COMMA(int i) {
			return GetToken(AdaptiveCardsTemplateParser.COMMA, i);
		}
		public ObjContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_obj; } }
	}

	[RuleVersion(0)]
	public ObjContext obj() {
		ObjContext _localctx = new ObjContext(Context, State);
		EnterRule(_localctx, 2, RULE_obj);
		int _la;
		try {
			State = 31;
			ErrorHandler.Sync(this);
			switch ( Interpreter.AdaptivePredict(TokenStream,1,Context) ) {
			case 1:
				EnterOuterAlt(_localctx, 1);
				{
				State = 18; Match(LCB);
				State = 19; pair();
				State = 24;
				ErrorHandler.Sync(this);
				_la = TokenStream.LA(1);
				while (_la==COMMA) {
					{
					{
					State = 20; Match(COMMA);
					State = 21; pair();
					}
					}
					State = 26;
					ErrorHandler.Sync(this);
					_la = TokenStream.LA(1);
				}
				State = 27; Match(RCB);
				}
				break;
			case 2:
				EnterOuterAlt(_localctx, 2);
				{
				State = 29; Match(LCB);
				State = 30; Match(RCB);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class PairContext : ParserRuleContext {
		public PairContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_pair; } }
	 
		public PairContext() { }
		public virtual void CopyFrom(PairContext context) {
			base.CopyFrom(context);
		}
	}
	public partial class TemplateWhenContext : PairContext {
		public ITerminalNode StringDeclOpen() { return GetToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public ITerminalNode TEMPLATEWHEN() { return GetToken(AdaptiveCardsTemplateParser.TEMPLATEWHEN, 0); }
		public ITerminalNode CLOSE() { return GetToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public ITerminalNode COLON() { return GetToken(AdaptiveCardsTemplateParser.COLON, 0); }
		public TemplateExpressionContext templateExpression() {
			return GetRuleContext<TemplateExpressionContext>(0);
		}
		public TemplateWhenContext(PairContext context) { CopyFrom(context); }
	}
	public partial class JsonPairContext : PairContext {
		public ITerminalNode StringDeclOpen() { return GetToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public ITerminalNode CLOSE() { return GetToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public ITerminalNode COLON() { return GetToken(AdaptiveCardsTemplateParser.COLON, 0); }
		public ValueContext value() {
			return GetRuleContext<ValueContext>(0);
		}
		public ITerminalNode[] STRING() { return GetTokens(AdaptiveCardsTemplateParser.STRING); }
		public ITerminalNode STRING(int i) {
			return GetToken(AdaptiveCardsTemplateParser.STRING, i);
		}
		public JsonPairContext(PairContext context) { CopyFrom(context); }
	}
	public partial class TemplateDataContext : PairContext {
		public ITerminalNode StringDeclOpen() { return GetToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public ITerminalNode TEMPLATEDATA() { return GetToken(AdaptiveCardsTemplateParser.TEMPLATEDATA, 0); }
		public ITerminalNode CLOSE() { return GetToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public ITerminalNode COLON() { return GetToken(AdaptiveCardsTemplateParser.COLON, 0); }
		public ValueContext value() {
			return GetRuleContext<ValueContext>(0);
		}
		public TemplateDataContext(PairContext context) { CopyFrom(context); }
	}
	public partial class TemplateRootDataContext : PairContext {
		public ITerminalNode[] StringDeclOpen() { return GetTokens(AdaptiveCardsTemplateParser.StringDeclOpen); }
		public ITerminalNode StringDeclOpen(int i) {
			return GetToken(AdaptiveCardsTemplateParser.StringDeclOpen, i);
		}
		public ITerminalNode TEMPLATEDATA() { return GetToken(AdaptiveCardsTemplateParser.TEMPLATEDATA, 0); }
		public ITerminalNode[] CLOSE() { return GetTokens(AdaptiveCardsTemplateParser.CLOSE); }
		public ITerminalNode CLOSE(int i) {
			return GetToken(AdaptiveCardsTemplateParser.CLOSE, i);
		}
		public ITerminalNode COLON() { return GetToken(AdaptiveCardsTemplateParser.COLON, 0); }
		public TemplateRootContext templateRoot() {
			return GetRuleContext<TemplateRootContext>(0);
		}
		public TemplateRootDataContext(PairContext context) { CopyFrom(context); }
	}

	[RuleVersion(0)]
	public PairContext pair() {
		PairContext _localctx = new PairContext(Context, State);
		EnterRule(_localctx, 4, RULE_pair);
		int _la;
		try {
			State = 61;
			ErrorHandler.Sync(this);
			switch ( Interpreter.AdaptivePredict(TokenStream,3,Context) ) {
			case 1:
				_localctx = new JsonPairContext(_localctx);
				EnterOuterAlt(_localctx, 1);
				{
				State = 33; Match(StringDeclOpen);
				State = 37;
				ErrorHandler.Sync(this);
				_la = TokenStream.LA(1);
				while (_la==STRING) {
					{
					{
					State = 34; Match(STRING);
					}
					}
					State = 39;
					ErrorHandler.Sync(this);
					_la = TokenStream.LA(1);
				}
				State = 40; Match(CLOSE);
				State = 41; Match(COLON);
				State = 42; value();
				}
				break;
			case 2:
				_localctx = new TemplateRootDataContext(_localctx);
				EnterOuterAlt(_localctx, 2);
				{
				State = 43; Match(StringDeclOpen);
				State = 44; Match(TEMPLATEDATA);
				State = 45; Match(CLOSE);
				State = 46; Match(COLON);
				State = 47; Match(StringDeclOpen);
				State = 48; templateRoot();
				State = 49; Match(CLOSE);
				}
				break;
			case 3:
				_localctx = new TemplateDataContext(_localctx);
				EnterOuterAlt(_localctx, 3);
				{
				State = 51; Match(StringDeclOpen);
				State = 52; Match(TEMPLATEDATA);
				State = 53; Match(CLOSE);
				State = 54; Match(COLON);
				State = 55; value();
				}
				break;
			case 4:
				_localctx = new TemplateWhenContext(_localctx);
				EnterOuterAlt(_localctx, 4);
				{
				State = 56; Match(StringDeclOpen);
				State = 57; Match(TEMPLATEWHEN);
				State = 58; Match(CLOSE);
				State = 59; Match(COLON);
				State = 60; templateExpression();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class ArrayContext : ParserRuleContext {
		public ITerminalNode LSB() { return GetToken(AdaptiveCardsTemplateParser.LSB, 0); }
		public ValueContext[] value() {
			return GetRuleContexts<ValueContext>();
		}
		public ValueContext value(int i) {
			return GetRuleContext<ValueContext>(i);
		}
		public ITerminalNode RSB() { return GetToken(AdaptiveCardsTemplateParser.RSB, 0); }
		public ITerminalNode[] COMMA() { return GetTokens(AdaptiveCardsTemplateParser.COMMA); }
		public ITerminalNode COMMA(int i) {
			return GetToken(AdaptiveCardsTemplateParser.COMMA, i);
		}
		public ArrayContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_array; } }
	}

	[RuleVersion(0)]
	public ArrayContext array() {
		ArrayContext _localctx = new ArrayContext(Context, State);
		EnterRule(_localctx, 6, RULE_array);
		int _la;
		try {
			State = 76;
			ErrorHandler.Sync(this);
			switch ( Interpreter.AdaptivePredict(TokenStream,5,Context) ) {
			case 1:
				EnterOuterAlt(_localctx, 1);
				{
				State = 63; Match(LSB);
				State = 64; value();
				State = 69;
				ErrorHandler.Sync(this);
				_la = TokenStream.LA(1);
				while (_la==COMMA) {
					{
					{
					State = 65; Match(COMMA);
					State = 66; value();
					}
					}
					State = 71;
					ErrorHandler.Sync(this);
					_la = TokenStream.LA(1);
				}
				State = 72; Match(RSB);
				}
				break;
			case 2:
				EnterOuterAlt(_localctx, 2);
				{
				State = 74; Match(LSB);
				State = 75; Match(RSB);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class ValueContext : ParserRuleContext {
		public ValueContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_value; } }
	 
		public ValueContext() { }
		public virtual void CopyFrom(ValueContext context) {
			base.CopyFrom(context);
		}
	}
	public partial class ValueObjectContext : ValueContext {
		public ObjContext obj() {
			return GetRuleContext<ObjContext>(0);
		}
		public ValueObjectContext(ValueContext context) { CopyFrom(context); }
	}
	public partial class ValueNullContext : ValueContext {
		public ITerminalNode NULL() { return GetToken(AdaptiveCardsTemplateParser.NULL, 0); }
		public ValueNullContext(ValueContext context) { CopyFrom(context); }
	}
	public partial class ValueTemplateStringContext : ValueContext {
		public ITerminalNode StringDeclOpen() { return GetToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public TemplateStringContext[] templateString() {
			return GetRuleContexts<TemplateStringContext>();
		}
		public TemplateStringContext templateString(int i) {
			return GetRuleContext<TemplateStringContext>(i);
		}
		public ITerminalNode CLOSE() { return GetToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public ValueTemplateStringContext(ValueContext context) { CopyFrom(context); }
	}
	public partial class ValueNumberContext : ValueContext {
		public ITerminalNode NUMBER() { return GetToken(AdaptiveCardsTemplateParser.NUMBER, 0); }
		public ValueNumberContext(ValueContext context) { CopyFrom(context); }
	}
	public partial class ValueTrueContext : ValueContext {
		public ITerminalNode TRUE() { return GetToken(AdaptiveCardsTemplateParser.TRUE, 0); }
		public ValueTrueContext(ValueContext context) { CopyFrom(context); }
	}
	public partial class ValueFalseContext : ValueContext {
		public ITerminalNode FALSE() { return GetToken(AdaptiveCardsTemplateParser.FALSE, 0); }
		public ValueFalseContext(ValueContext context) { CopyFrom(context); }
	}
	public partial class ValueStringContext : ValueContext {
		public ITerminalNode StringDeclOpen() { return GetToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public ITerminalNode CLOSE() { return GetToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public ITerminalNode[] STRING() { return GetTokens(AdaptiveCardsTemplateParser.STRING); }
		public ITerminalNode STRING(int i) {
			return GetToken(AdaptiveCardsTemplateParser.STRING, i);
		}
		public ValueStringContext(ValueContext context) { CopyFrom(context); }
	}
	public partial class ValueTemplateStringWithRootContext : ValueContext {
		public ITerminalNode StringDeclOpen() { return GetToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public TemplateRootContext templateRoot() {
			return GetRuleContext<TemplateRootContext>(0);
		}
		public ITerminalNode CLOSE() { return GetToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public ValueTemplateStringWithRootContext(ValueContext context) { CopyFrom(context); }
	}
	public partial class ValueArrayContext : ValueContext {
		public ArrayContext array() {
			return GetRuleContext<ArrayContext>(0);
		}
		public ValueArrayContext(ValueContext context) { CopyFrom(context); }
	}

	[RuleVersion(0)]
	public ValueContext value() {
		ValueContext _localctx = new ValueContext(Context, State);
		EnterRule(_localctx, 8, RULE_value);
		int _la;
		try {
			State = 106;
			ErrorHandler.Sync(this);
			switch ( Interpreter.AdaptivePredict(TokenStream,8,Context) ) {
			case 1:
				_localctx = new ValueTemplateStringContext(_localctx);
				EnterOuterAlt(_localctx, 1);
				{
				State = 78; Match(StringDeclOpen);
				State = 79; templateString();
				State = 83;
				ErrorHandler.Sync(this);
				_la = TokenStream.LA(1);
				while (_la==STRING || _la==TEMPLATELITERAL) {
					{
					{
					State = 80; templateString();
					}
					}
					State = 85;
					ErrorHandler.Sync(this);
					_la = TokenStream.LA(1);
				}
				State = 86; Match(CLOSE);
				}
				break;
			case 2:
				_localctx = new ValueTemplateStringWithRootContext(_localctx);
				EnterOuterAlt(_localctx, 2);
				{
				State = 88; Match(StringDeclOpen);
				State = 89; templateRoot();
				State = 90; Match(CLOSE);
				}
				break;
			case 3:
				_localctx = new ValueStringContext(_localctx);
				EnterOuterAlt(_localctx, 3);
				{
				State = 92; Match(StringDeclOpen);
				State = 96;
				ErrorHandler.Sync(this);
				_la = TokenStream.LA(1);
				while (_la==STRING) {
					{
					{
					State = 93; Match(STRING);
					}
					}
					State = 98;
					ErrorHandler.Sync(this);
					_la = TokenStream.LA(1);
				}
				State = 99; Match(CLOSE);
				}
				break;
			case 4:
				_localctx = new ValueNumberContext(_localctx);
				EnterOuterAlt(_localctx, 4);
				{
				State = 100; Match(NUMBER);
				}
				break;
			case 5:
				_localctx = new ValueObjectContext(_localctx);
				EnterOuterAlt(_localctx, 5);
				{
				State = 101; obj();
				}
				break;
			case 6:
				_localctx = new ValueArrayContext(_localctx);
				EnterOuterAlt(_localctx, 6);
				{
				State = 102; array();
				}
				break;
			case 7:
				_localctx = new ValueTrueContext(_localctx);
				EnterOuterAlt(_localctx, 7);
				{
				State = 103; Match(TRUE);
				}
				break;
			case 8:
				_localctx = new ValueFalseContext(_localctx);
				EnterOuterAlt(_localctx, 8);
				{
				State = 104; Match(FALSE);
				}
				break;
			case 9:
				_localctx = new ValueNullContext(_localctx);
				EnterOuterAlt(_localctx, 9);
				{
				State = 105; Match(NULL);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class TemplateStringContext : ParserRuleContext {
		public TemplateStringContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_templateString; } }
	 
		public TemplateStringContext() { }
		public virtual void CopyFrom(TemplateStringContext context) {
			base.CopyFrom(context);
		}
	}
	public partial class TemplatedStringContext : TemplateStringContext {
		public ITerminalNode TEMPLATELITERAL() { return GetToken(AdaptiveCardsTemplateParser.TEMPLATELITERAL, 0); }
		public ITerminalNode[] STRING() { return GetTokens(AdaptiveCardsTemplateParser.STRING); }
		public ITerminalNode STRING(int i) {
			return GetToken(AdaptiveCardsTemplateParser.STRING, i);
		}
		public TemplatedStringContext(TemplateStringContext context) { CopyFrom(context); }
	}

	[RuleVersion(0)]
	public TemplateStringContext templateString() {
		TemplateStringContext _localctx = new TemplateStringContext(Context, State);
		EnterRule(_localctx, 10, RULE_templateString);
		int _la;
		try {
			int _alt;
			_localctx = new TemplatedStringContext(_localctx);
			EnterOuterAlt(_localctx, 1);
			{
			{
			State = 111;
			ErrorHandler.Sync(this);
			_la = TokenStream.LA(1);
			while (_la==STRING) {
				{
				{
				State = 108; Match(STRING);
				}
				}
				State = 113;
				ErrorHandler.Sync(this);
				_la = TokenStream.LA(1);
			}
			State = 114; Match(TEMPLATELITERAL);
			State = 118;
			ErrorHandler.Sync(this);
			_alt = Interpreter.AdaptivePredict(TokenStream,10,Context);
			while ( _alt!=2 && _alt!=global::Antlr4.Runtime.Atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					State = 115; Match(STRING);
					}
					} 
				}
				State = 120;
				ErrorHandler.Sync(this);
				_alt = Interpreter.AdaptivePredict(TokenStream,10,Context);
			}
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class TemplateRootContext : ParserRuleContext {
		public TemplateRootContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_templateRoot; } }
	 
		public TemplateRootContext() { }
		public virtual void CopyFrom(TemplateRootContext context) {
			base.CopyFrom(context);
		}
	}
	public partial class TemplateStringWithRootContext : TemplateRootContext {
		public ITerminalNode TEMPLATEROOT() { return GetToken(AdaptiveCardsTemplateParser.TEMPLATEROOT, 0); }
		public TemplateStringWithRootContext(TemplateRootContext context) { CopyFrom(context); }
	}

	[RuleVersion(0)]
	public TemplateRootContext templateRoot() {
		TemplateRootContext _localctx = new TemplateRootContext(Context, State);
		EnterRule(_localctx, 12, RULE_templateRoot);
		try {
			_localctx = new TemplateStringWithRootContext(_localctx);
			EnterOuterAlt(_localctx, 1);
			{
			State = 121; Match(TEMPLATEROOT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	public partial class TemplateExpressionContext : ParserRuleContext {
		public TemplateExpressionContext(ParserRuleContext parent, int invokingState)
			: base(parent, invokingState)
		{
		}
		public override int RuleIndex { get { return RULE_templateExpression; } }
	 
		public TemplateExpressionContext() { }
		public virtual void CopyFrom(TemplateExpressionContext context) {
			base.CopyFrom(context);
		}
	}
	public partial class ValueTemplateExpressionContext : TemplateExpressionContext {
		public ITerminalNode StringDeclOpen() { return GetToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public ITerminalNode TEMPLATELITERAL() { return GetToken(AdaptiveCardsTemplateParser.TEMPLATELITERAL, 0); }
		public ITerminalNode CLOSE() { return GetToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public ValueTemplateExpressionContext(TemplateExpressionContext context) { CopyFrom(context); }
	}

	[RuleVersion(0)]
	public TemplateExpressionContext templateExpression() {
		TemplateExpressionContext _localctx = new TemplateExpressionContext(Context, State);
		EnterRule(_localctx, 14, RULE_templateExpression);
		try {
			_localctx = new ValueTemplateExpressionContext(_localctx);
			EnterOuterAlt(_localctx, 1);
			{
			State = 123; Match(StringDeclOpen);
			State = 124; Match(TEMPLATELITERAL);
			State = 125; Match(CLOSE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			ErrorHandler.ReportError(this, re);
			ErrorHandler.Recover(this, re);
		}
		finally {
			ExitRule();
		}
		return _localctx;
	}

	private static char[] _serializedATN = {
		'\x3', '\x608B', '\xA72A', '\x8133', '\xB9ED', '\x417C', '\x3BE7', '\x7786', 
		'\x5964', '\x3', '\x15', '\x82', '\x4', '\x2', '\t', '\x2', '\x4', '\x3', 
		'\t', '\x3', '\x4', '\x4', '\t', '\x4', '\x4', '\x5', '\t', '\x5', '\x4', 
		'\x6', '\t', '\x6', '\x4', '\a', '\t', '\a', '\x4', '\b', '\t', '\b', 
		'\x4', '\t', '\t', '\t', '\x3', '\x2', '\x3', '\x2', '\x3', '\x3', '\x3', 
		'\x3', '\x3', '\x3', '\x3', '\x3', '\a', '\x3', '\x19', '\n', '\x3', '\f', 
		'\x3', '\xE', '\x3', '\x1C', '\v', '\x3', '\x3', '\x3', '\x3', '\x3', 
		'\x3', '\x3', '\x3', '\x3', '\x5', '\x3', '\"', '\n', '\x3', '\x3', '\x4', 
		'\x3', '\x4', '\a', '\x4', '&', '\n', '\x4', '\f', '\x4', '\xE', '\x4', 
		')', '\v', '\x4', '\x3', '\x4', '\x3', '\x4', '\x3', '\x4', '\x3', '\x4', 
		'\x3', '\x4', '\x3', '\x4', '\x3', '\x4', '\x3', '\x4', '\x3', '\x4', 
		'\x3', '\x4', '\x3', '\x4', '\x3', '\x4', '\x3', '\x4', '\x3', '\x4', 
		'\x3', '\x4', '\x3', '\x4', '\x3', '\x4', '\x3', '\x4', '\x3', '\x4', 
		'\x3', '\x4', '\x3', '\x4', '\x5', '\x4', '@', '\n', '\x4', '\x3', '\x5', 
		'\x3', '\x5', '\x3', '\x5', '\x3', '\x5', '\a', '\x5', '\x46', '\n', '\x5', 
		'\f', '\x5', '\xE', '\x5', 'I', '\v', '\x5', '\x3', '\x5', '\x3', '\x5', 
		'\x3', '\x5', '\x3', '\x5', '\x5', '\x5', 'O', '\n', '\x5', '\x3', '\x6', 
		'\x3', '\x6', '\x3', '\x6', '\a', '\x6', 'T', '\n', '\x6', '\f', '\x6', 
		'\xE', '\x6', 'W', '\v', '\x6', '\x3', '\x6', '\x3', '\x6', '\x3', '\x6', 
		'\x3', '\x6', '\x3', '\x6', '\x3', '\x6', '\x3', '\x6', '\x3', '\x6', 
		'\a', '\x6', '\x61', '\n', '\x6', '\f', '\x6', '\xE', '\x6', '\x64', '\v', 
		'\x6', '\x3', '\x6', '\x3', '\x6', '\x3', '\x6', '\x3', '\x6', '\x3', 
		'\x6', '\x3', '\x6', '\x3', '\x6', '\x5', '\x6', 'm', '\n', '\x6', '\x3', 
		'\a', '\a', '\a', 'p', '\n', '\a', '\f', '\a', '\xE', '\a', 's', '\v', 
		'\a', '\x3', '\a', '\x3', '\a', '\a', '\a', 'w', '\n', '\a', '\f', '\a', 
		'\xE', '\a', 'z', '\v', '\a', '\x3', '\b', '\x3', '\b', '\x3', '\t', '\x3', 
		'\t', '\x3', '\t', '\x3', '\t', '\x3', '\t', '\x2', '\x2', '\n', '\x2', 
		'\x4', '\x6', '\b', '\n', '\f', '\xE', '\x10', '\x2', '\x2', '\x2', '\x8D', 
		'\x2', '\x12', '\x3', '\x2', '\x2', '\x2', '\x4', '!', '\x3', '\x2', '\x2', 
		'\x2', '\x6', '?', '\x3', '\x2', '\x2', '\x2', '\b', 'N', '\x3', '\x2', 
		'\x2', '\x2', '\n', 'l', '\x3', '\x2', '\x2', '\x2', '\f', 'q', '\x3', 
		'\x2', '\x2', '\x2', '\xE', '{', '\x3', '\x2', '\x2', '\x2', '\x10', '}', 
		'\x3', '\x2', '\x2', '\x2', '\x12', '\x13', '\x5', '\n', '\x6', '\x2', 
		'\x13', '\x3', '\x3', '\x2', '\x2', '\x2', '\x14', '\x15', '\a', '\x5', 
		'\x2', '\x2', '\x15', '\x1A', '\x5', '\x6', '\x4', '\x2', '\x16', '\x17', 
		'\a', '\x3', '\x2', '\x2', '\x17', '\x19', '\x5', '\x6', '\x4', '\x2', 
		'\x18', '\x16', '\x3', '\x2', '\x2', '\x2', '\x19', '\x1C', '\x3', '\x2', 
		'\x2', '\x2', '\x1A', '\x18', '\x3', '\x2', '\x2', '\x2', '\x1A', '\x1B', 
		'\x3', '\x2', '\x2', '\x2', '\x1B', '\x1D', '\x3', '\x2', '\x2', '\x2', 
		'\x1C', '\x1A', '\x3', '\x2', '\x2', '\x2', '\x1D', '\x1E', '\a', '\x6', 
		'\x2', '\x2', '\x1E', '\"', '\x3', '\x2', '\x2', '\x2', '\x1F', ' ', '\a', 
		'\x5', '\x2', '\x2', ' ', '\"', '\a', '\x6', '\x2', '\x2', '!', '\x14', 
		'\x3', '\x2', '\x2', '\x2', '!', '\x1F', '\x3', '\x2', '\x2', '\x2', '\"', 
		'\x5', '\x3', '\x2', '\x2', '\x2', '#', '\'', '\a', '\f', '\x2', '\x2', 
		'$', '&', '\a', '\x14', '\x2', '\x2', '%', '$', '\x3', '\x2', '\x2', '\x2', 
		'&', ')', '\x3', '\x2', '\x2', '\x2', '\'', '%', '\x3', '\x2', '\x2', 
		'\x2', '\'', '(', '\x3', '\x2', '\x2', '\x2', '(', '*', '\x3', '\x2', 
		'\x2', '\x2', ')', '\'', '\x3', '\x2', '\x2', '\x2', '*', '+', '\a', '\xF', 
		'\x2', '\x2', '+', ',', '\a', '\x4', '\x2', '\x2', ',', '@', '\x5', '\n', 
		'\x6', '\x2', '-', '.', '\a', '\f', '\x2', '\x2', '.', '/', '\a', '\x10', 
		'\x2', '\x2', '/', '\x30', '\a', '\xF', '\x2', '\x2', '\x30', '\x31', 
		'\a', '\x4', '\x2', '\x2', '\x31', '\x32', '\a', '\f', '\x2', '\x2', '\x32', 
		'\x33', '\x5', '\xE', '\b', '\x2', '\x33', '\x34', '\a', '\xF', '\x2', 
		'\x2', '\x34', '@', '\x3', '\x2', '\x2', '\x2', '\x35', '\x36', '\a', 
		'\f', '\x2', '\x2', '\x36', '\x37', '\a', '\x10', '\x2', '\x2', '\x37', 
		'\x38', '\a', '\xF', '\x2', '\x2', '\x38', '\x39', '\a', '\x4', '\x2', 
		'\x2', '\x39', '@', '\x5', '\n', '\x6', '\x2', ':', ';', '\a', '\f', '\x2', 
		'\x2', ';', '<', '\a', '\x11', '\x2', '\x2', '<', '=', '\a', '\xF', '\x2', 
		'\x2', '=', '>', '\a', '\x4', '\x2', '\x2', '>', '@', '\x5', '\x10', '\t', 
		'\x2', '?', '#', '\x3', '\x2', '\x2', '\x2', '?', '-', '\x3', '\x2', '\x2', 
		'\x2', '?', '\x35', '\x3', '\x2', '\x2', '\x2', '?', ':', '\x3', '\x2', 
		'\x2', '\x2', '@', '\a', '\x3', '\x2', '\x2', '\x2', '\x41', '\x42', '\a', 
		'\a', '\x2', '\x2', '\x42', 'G', '\x5', '\n', '\x6', '\x2', '\x43', '\x44', 
		'\a', '\x3', '\x2', '\x2', '\x44', '\x46', '\x5', '\n', '\x6', '\x2', 
		'\x45', '\x43', '\x3', '\x2', '\x2', '\x2', '\x46', 'I', '\x3', '\x2', 
		'\x2', '\x2', 'G', '\x45', '\x3', '\x2', '\x2', '\x2', 'G', 'H', '\x3', 
		'\x2', '\x2', '\x2', 'H', 'J', '\x3', '\x2', '\x2', '\x2', 'I', 'G', '\x3', 
		'\x2', '\x2', '\x2', 'J', 'K', '\a', '\b', '\x2', '\x2', 'K', 'O', '\x3', 
		'\x2', '\x2', '\x2', 'L', 'M', '\a', '\a', '\x2', '\x2', 'M', 'O', '\a', 
		'\b', '\x2', '\x2', 'N', '\x41', '\x3', '\x2', '\x2', '\x2', 'N', 'L', 
		'\x3', '\x2', '\x2', '\x2', 'O', '\t', '\x3', '\x2', '\x2', '\x2', 'P', 
		'Q', '\a', '\f', '\x2', '\x2', 'Q', 'U', '\x5', '\f', '\a', '\x2', 'R', 
		'T', '\x5', '\f', '\a', '\x2', 'S', 'R', '\x3', '\x2', '\x2', '\x2', 'T', 
		'W', '\x3', '\x2', '\x2', '\x2', 'U', 'S', '\x3', '\x2', '\x2', '\x2', 
		'U', 'V', '\x3', '\x2', '\x2', '\x2', 'V', 'X', '\x3', '\x2', '\x2', '\x2', 
		'W', 'U', '\x3', '\x2', '\x2', '\x2', 'X', 'Y', '\a', '\xF', '\x2', '\x2', 
		'Y', 'm', '\x3', '\x2', '\x2', '\x2', 'Z', '[', '\a', '\f', '\x2', '\x2', 
		'[', '\\', '\x5', '\xE', '\b', '\x2', '\\', ']', '\a', '\xF', '\x2', '\x2', 
		']', 'm', '\x3', '\x2', '\x2', '\x2', '^', '\x62', '\a', '\f', '\x2', 
		'\x2', '_', '\x61', '\a', '\x14', '\x2', '\x2', '`', '_', '\x3', '\x2', 
		'\x2', '\x2', '\x61', '\x64', '\x3', '\x2', '\x2', '\x2', '\x62', '`', 
		'\x3', '\x2', '\x2', '\x2', '\x62', '\x63', '\x3', '\x2', '\x2', '\x2', 
		'\x63', '\x65', '\x3', '\x2', '\x2', '\x2', '\x64', '\x62', '\x3', '\x2', 
		'\x2', '\x2', '\x65', 'm', '\a', '\xF', '\x2', '\x2', '\x66', 'm', '\a', 
		'\r', '\x2', '\x2', 'g', 'm', '\x5', '\x4', '\x3', '\x2', 'h', 'm', '\x5', 
		'\b', '\x5', '\x2', 'i', 'm', '\a', '\t', '\x2', '\x2', 'j', 'm', '\a', 
		'\n', '\x2', '\x2', 'k', 'm', '\a', '\v', '\x2', '\x2', 'l', 'P', '\x3', 
		'\x2', '\x2', '\x2', 'l', 'Z', '\x3', '\x2', '\x2', '\x2', 'l', '^', '\x3', 
		'\x2', '\x2', '\x2', 'l', '\x66', '\x3', '\x2', '\x2', '\x2', 'l', 'g', 
		'\x3', '\x2', '\x2', '\x2', 'l', 'h', '\x3', '\x2', '\x2', '\x2', 'l', 
		'i', '\x3', '\x2', '\x2', '\x2', 'l', 'j', '\x3', '\x2', '\x2', '\x2', 
		'l', 'k', '\x3', '\x2', '\x2', '\x2', 'm', '\v', '\x3', '\x2', '\x2', 
		'\x2', 'n', 'p', '\a', '\x14', '\x2', '\x2', 'o', 'n', '\x3', '\x2', '\x2', 
		'\x2', 'p', 's', '\x3', '\x2', '\x2', '\x2', 'q', 'o', '\x3', '\x2', '\x2', 
		'\x2', 'q', 'r', '\x3', '\x2', '\x2', '\x2', 'r', 't', '\x3', '\x2', '\x2', 
		'\x2', 's', 'q', '\x3', '\x2', '\x2', '\x2', 't', 'x', '\a', '\x15', '\x2', 
		'\x2', 'u', 'w', '\a', '\x14', '\x2', '\x2', 'v', 'u', '\x3', '\x2', '\x2', 
		'\x2', 'w', 'z', '\x3', '\x2', '\x2', '\x2', 'x', 'v', '\x3', '\x2', '\x2', 
		'\x2', 'x', 'y', '\x3', '\x2', '\x2', '\x2', 'y', '\r', '\x3', '\x2', 
		'\x2', '\x2', 'z', 'x', '\x3', '\x2', '\x2', '\x2', '{', '|', '\a', '\x13', 
		'\x2', '\x2', '|', '\xF', '\x3', '\x2', '\x2', '\x2', '}', '~', '\a', 
		'\f', '\x2', '\x2', '~', '\x7F', '\a', '\x15', '\x2', '\x2', '\x7F', '\x80', 
		'\a', '\xF', '\x2', '\x2', '\x80', '\x11', '\x3', '\x2', '\x2', '\x2', 
		'\r', '\x1A', '!', '\'', '?', 'G', 'N', 'U', '\x62', 'l', 'q', 'x',
	};

	public static readonly ATN _ATN =
		new ATNDeserializer().Deserialize(_serializedATN);


}
