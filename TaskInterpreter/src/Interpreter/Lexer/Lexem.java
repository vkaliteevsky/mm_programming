/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Lexer;

public class Lexem {
	private LexemType mType;

	public Lexem(LexemType lexem) {
		mType = lexem;
	}

	public LexemType GetType() {
		return mType;
	}
}
