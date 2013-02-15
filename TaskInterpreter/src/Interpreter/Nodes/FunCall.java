/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Nodes;

public class FunCall extends Expression {
	private Expression mFun;
	private Expression mArgument;

	public FunCall(Expression function, Expression argument) {
		mArgument = argument;
		mFun = function;
		mType = ExprType.FunCall;
	}

	public Expression GetFun() {
		return mFun;
	}

	public Expression GetArg() {
		return mArgument;
	}

	public void SetFun(Expression function) {
		mFun = function;
	}

	public void SetArg(Expression argument) {
		mArgument = argument;
	}

	@Override
	public Object DeepCopy() {
		return new FunCall((Expression) mFun.DeepCopy(),
				(Expression) mArgument.DeepCopy());
	}

	@Override
	public String toString() {
		return "(call " + mFun.toString() + " (" + mArgument.toString() + "))";
	}
}