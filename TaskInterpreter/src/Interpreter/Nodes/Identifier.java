/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Nodes;

public class Identifier extends Expression {
	private String mName;

	public Identifier(String name) {
		this.mName = name;
		mType = ExprType.Identifier;
	}

	public String GetName() {
		return mName;
	}

	@Override
	public Object DeepCopy() {
		return new Identifier(mName);
	}

	@Override
	public String toString() {
		return mName;
	}
}