/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Nodes;

public class FunDef extends Expression {
	private String mId;
	private Expression mBody;

	public FunDef(String Id, Expression Bound) {
		mId = Id;
		mBody = Bound;
		mType = ExprType.Fundef;
	}

	public String GetId() {
		return mId;
	}

	public Expression GetBody() {
		return mBody;
	}

	public void setBody(Expression Bound) {
		mBody = Bound;
	}

	@Override
	public Object DeepCopy() {
		return new FunDef(mId, (Expression) mBody.DeepCopy());
	}

	@Override
	public String toString() {
		return "(fun " + mId + " -> " + mBody.toString() + ")";
	}
}