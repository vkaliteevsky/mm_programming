/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Lexer;

public class IdLexem extends Lexem {
	private String mName;

	public IdLexem(String Name) {
		super(LexemType.Id);
		mName = Name;
	}

	public String GetName() {
		return mName;
	}
}