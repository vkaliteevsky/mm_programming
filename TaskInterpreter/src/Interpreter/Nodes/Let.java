/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Nodes;

public class Let extends Expression {
	private String mId;
	private Expression mBound;
	private Expression mExpr;

	public Let(String id, Expression bound, Expression expr) {
		this.mBound = bound;
		this.mExpr = expr;
		this.mId = id;
		mType = ExprType.Let;
	}

	public String getId() {
		return mId;
	}

	public Expression getBound() {
		return mBound;
	}

	public Expression getExpr() {
		return mExpr;
	}

	public void setBound(Expression b) {
		mBound = b;
	}

	public void setExpr(Expression e) {
		mExpr = e;
	}

	@Override
	public Object DeepCopy() {
		return new Let(mId, (Expression) mBound.DeepCopy(),
				(Expression) mExpr.DeepCopy());
	}

	@Override
	public String toString() {
		return "(let " + mId + " = (" + mBound.toString() + ")" + " in ("
				+ mExpr.toString() + "))";
	}
}