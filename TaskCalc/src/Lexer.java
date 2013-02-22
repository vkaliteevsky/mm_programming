/**
 * @author vkaliteevskiy
 * Calc
 * (c)2012
 */

public class Lexer {
	private LexerElem mCurrLexerElem;
	private int mPointer;
	private int mNumberValue;
	private String mVariable;
	private boolean mEOL;
	protected String mExp;

	public int GetLexerElemValue() {
		return mNumberValue;
	}

	public String GetVariableName() {
		return mVariable;
	}

	public LexerElem CurrLexerElem() {
		return mCurrLexerElem;
	}

	public Lexer() {
		mCurrLexerElem = LexerElem.START;
		mEOL = false;
	}

	public void newExpr(String Exp) {
		mEOL = false;
		mExp = Exp;
		mCurrLexerElem = LexerElem.START;
		mPointer = 0;
	}

	public void nextLexerElem() {
		if (mPointer == mExp.length()) {
			mEOL = true;
		}

		while (!mEOL && mExp.charAt(mPointer) == ' ') {
			mPointer++;
			if (mPointer == mExp.length()) {
				mEOL = true;
			}
		}

		if (!mEOL) {
			switch (mExp.charAt(mPointer)) {
			case '+':
				mCurrLexerElem = LexerElem.PLUS;
				mPointer++;
				break;
			case '-':
				mCurrLexerElem = LexerElem.MINUS;
				mPointer++;
				break;
			case '*':
				mCurrLexerElem = LexerElem.MULT;
				mPointer++;
				break;
			case '/':
				mCurrLexerElem = LexerElem.DIV;
				mPointer++;
				break;
			case '=':
				mCurrLexerElem = LexerElem.EQUALS;
				mPointer++;
				break;
			case '(':
				mCurrLexerElem = LexerElem.OBRACE;
				mPointer++;
				break;
			case ')':
				mCurrLexerElem = LexerElem.CBRACE;
				mPointer++;
				break;
			case '\n':
				mEOL = true;
				mPointer++;
				break;
			default:
				if (Character.isDigit(mExp.charAt(mPointer))) {
					mCurrLexerElem = LexerElem.NUMBER;
					int i = mPointer;
					while (!mEOL && Character.isDigit(mExp.charAt(mPointer))) {
						mPointer++;
						if (mPointer == mExp.length()) {
							mEOL = true;
						}
					}
					mNumberValue = Integer.parseInt(mExp.substring(i, mPointer));
					break;
				}
				if (Character.isLetter(mExp.charAt(mPointer))) {
					mCurrLexerElem = LexerElem.VARIABLE;
					int i = mPointer;
					while (!mEOL && Character.isLetterOrDigit(mExp.charAt(mPointer))) {
						mPointer++;
						if (mPointer == mExp.length()) {
							mEOL = true;
						}
					}
					mVariable = mExp.substring(i, mPointer);
					break;
				}
			}
		} else {
			mCurrLexerElem = LexerElem.EOL;
		}
	}

	public LexerElem futureLexerElem() {
		boolean e = mEOL;
		LexerElem c = mCurrLexerElem;
		int i = mPointer;
		int n = mNumberValue;
		String v = mVariable;
		nextLexerElem();
		LexerElem next = mCurrLexerElem;
		mEOL = e;
		mCurrLexerElem = c;
		mPointer = i;
		mNumberValue = n;
		mVariable = v;
		return next;
	}
}
