/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Lexer;

//import exceptions.*;
import java.util.ArrayList;
import java.util.List;

public class Lexer {
	private List<Lexem> mLexemeArray;
	private int mPointer;
	private String mExpr;
	private boolean mEol;
	private int lp;

	public Lexer(String expr) throws Exception {
		mLexemeArray = new ArrayList<Lexem>();
		mExpr = expr;
		mPointer = 0;
		lp = 0;
		mEol = false;
		GetLexem();
	}

	private void GetLexem() throws Exception {
		while (!mEol) {
			Lexem l = ReadLexem();
			mLexemeArray.add(l);
		}
		if (mLexemeArray.get(mLexemeArray.size() - 1).GetType() != LexemType.End) {
			mLexemeArray.add(new EndLexem());
		}
	}

	private Lexem ReadLexem() throws Exception {
		if (mPointer > mExpr.length() - 1) {
			mEol = true;
		}

		while (!mEol && mExpr.charAt(mPointer) == ' ') {
			mPointer++;
			if (mPointer == mExpr.length()) {
				mEol = true;
			}
		}

		if (!mEol) {
			switch (mExpr.charAt(mPointer)) {
			case '+':
				mPointer++;
				return new BinOpLexem(Operator.Plus);
			case '-':
				if (mPointer + 1 < mExpr.length() - 1
						&& mExpr.charAt(mPointer + 1) == '>') {
					mPointer += 2;
					return new ArrowLexem();
				} else {
					mPointer++;
					return new BinOpLexem(Operator.Minus);
				}
			case '*':
				mPointer++;
				return new BinOpLexem(Operator.Mult);
			case '/':
				mPointer++;
				return new BinOpLexem(Operator.Div);
			case '=':
				mPointer++;
				return new AssignLexem();
			case '(':
				mPointer++;
				return new OpBraceLexem();
			case ')':
				mPointer++;
				return new ClBraceLexem();
			default:
				if (Character.isDigit(mExpr.charAt(mPointer))) {
					int i = mPointer;
					while (!mEol && Character.isDigit(mExpr.charAt(mPointer))) {
						mPointer++;
						if (mPointer == mExpr.length()) {
							mEol = true;
						}
					}
					return new NumberLexem(Integer.parseInt(mExpr.substring(i,
							mPointer)));
				}
				if (Character.isLetter(mExpr.charAt(mPointer))) {
					int i = mPointer;
					while (!mEol
							&& Character
									.isLetterOrDigit(mExpr.charAt(mPointer))) {
						mPointer++;
						if (mPointer == mExpr.length()) {
							mEol = true;
						}
					}
                    String n = mExpr.substring(i, mPointer);
                    switch (n.toLowerCase()) {
                        case "let":
                            return new LetLexem();
                        case "in":
                            return new InLexem();
                        case "fun":
                            return new FunLexem();
                        default:
                            return new IdLexem(n);
                    }
				} else {
					throw new Exception();
				}
			}
		}
		return new EndLexem();
	}

	public Lexem NextLexem() {
		Lexem i = mLexemeArray.get(lp);
		if (lp < mLexemeArray.size() - 1) {
			lp++;
		}
		return i;
	}
}