/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Nodes;

public class Number extends Expression {
	private int mValue;

	public Number(int Value) {
		mValue = Value;
		mType = ExprType.Number;
	}
	
	public int getValue() {
		return mValue;
	}

	@Override
	public Object DeepCopy() {
		return new Number(mValue);
	}

	@Override
	public String toString() {
		return Integer.toString(mValue);
	}
}