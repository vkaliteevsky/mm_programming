/**
 * @author vkaliteevskiy
 * Calc
 * (c)2012
 */

public class Parser {
	Lexer mLexer;
	HashTable mHashTable;
	String[] mExprs;

	public Parser(String[] Exprs) {
		mLexer = new Lexer();
		mExprs = Exprs;
		mHashTable = new HashTable(700);
	}

	private int Term() {
		int operand1 = factor();
		LexerElem operation = mLexer.CurrLexerElem();
		while (operation == LexerElem.MULT || operation == LexerElem.DIV) {
			mLexer.nextLexerElem();
			int operand2 = factor();
			switch (operation) {
			case MULT:

				operand1 *= operand2;
				break;
			case DIV:

				operand1 /= operand2;
				break;
			}
			mLexer.nextLexerElem();
			operation = mLexer.CurrLexerElem();
		}
		return operand1;
	}

	public int Expr() {
		int operand1 = Term();
		LexerElem operation = mLexer.CurrLexerElem();
		while (operation == LexerElem.PLUS || operation == LexerElem.MINUS) {
			mLexer.nextLexerElem();
			int operand2 = Term();
			switch (operation) {
			case PLUS:
				operand1 += operand2;
				break;
			case MINUS:
				operand1 -= operand2;
				break;
			}
			operation = mLexer.CurrLexerElem();
		}
		return operand1;
	}

	private int factor() {
		switch (mLexer.CurrLexerElem()) {
			case NUMBER: {
				int res = mLexer.GetLexerElemValue();
				mLexer.nextLexerElem();
				return res;
			}
			case VARIABLE: {
				int res = (Integer) mHashTable.find(mLexer.GetVariableName());
				mLexer.nextLexerElem();
				return res;
			}
			case OBRACE: {
				mLexer.nextLexerElem();
				int res = Expr();
				mLexer.nextLexerElem();
				return res;
			}
			default: {
				return 0;
			}
		}
	}

	private int ParseAssign() throws Exception {
		mLexer.nextLexerElem();
		mLexer.nextLexerElem();
		int result = Expr();
		if (!(mLexer.CurrLexerElem() == LexerElem.EOL)) {
			throw new Exception();
		}
		return result;
	}

	private int Start() throws Exception {
		int result = Expr();
		if (!(mLexer.CurrLexerElem() == LexerElem.EOL)) {
			throw new Exception();
		}
		return result;
	}

	public int[] start() throws Exception {
		int l = mExprs.length;
		int result[] = new int[l];
		int i;
		for (i = 0; i < l; i++) {
			mLexer.newExpr(mExprs[i]);
			mLexer.nextLexerElem();
			if (mLexer.CurrLexerElem() == LexerElem.VARIABLE
					&& mLexer.futureLexerElem() == LexerElem.EQUALS) {
				String id = mLexer.GetVariableName();
				int rslt = ParseAssign();
				mHashTable.add(id, (int) rslt);
				result[i] = rslt;
			} else {
				result[i] = Start();
			}
		}
		return result;
	}
}
