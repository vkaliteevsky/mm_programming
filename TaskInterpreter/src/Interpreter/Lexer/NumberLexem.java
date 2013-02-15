/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Lexer;

public class NumberLexem extends Lexem {
	private int mValue;

	public NumberLexem(int Value) {
		super(LexemType.Number);
		mValue = Value;
	}

	public int GetValue() {
		return mValue;
	}
}
