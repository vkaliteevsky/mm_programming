/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Lexer;

public class BinOpLexem extends Lexem {
	private Operator mOperator;

	public BinOpLexem(Operator operator) {
		super(LexemType.BinOp);
		mOperator = operator;
	}

	public Operator GetOp() {
		return mOperator;
	}

}