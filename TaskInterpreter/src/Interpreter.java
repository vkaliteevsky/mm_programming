/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

import Interpreter.Nodes.BinOp;
import Interpreter.Nodes.ExprType;
import Interpreter.Nodes.Expression;
import Interpreter.Nodes.FunCall;
import Interpreter.Nodes.FunDef;
import Interpreter.Nodes.Identifier;
import Interpreter.Nodes.Let;
import Interpreter.Nodes.Number;

public abstract class Interpreter {

	protected int evalCounter;

	public Expression substitute(Expression expr, String id, Expression x)
			throws Exception {
		switch (expr.GetType()) {
		case BinOp:
			BinOp op = (BinOp) expr;
			op.SetLeft(substitute(op.GetLeft(), id, x));
			op.SetRight(substitute(op.GetRight(), id, x));
			return op;

		case Identifier:
			Identifier i = (Identifier) expr;
			if (id.equals(i.GetName())) {
				return (Expression) x.DeepCopy();
			}
			return i;

		case Fundef:
			FunDef f = (FunDef) expr;
			if (!(f.GetId()).equals(id)) {
				f.setBody(substitute(f.GetBody(), id, x));
			}
			return f;

		case FunCall:
			FunCall c = (FunCall) expr;
			c.SetFun(substitute(c.GetFun(), id, x));
			c.SetArg(substitute(c.GetArg(), id, x));
			return c;
		case Number:
			return expr;

		case Let:
			Let l = (Let) expr;
			if (!(l.getId()).equals(id)) {
				l.setBound(substitute(l.getBound(), id, x));
				l.setExpr(substitute(l.getExpr(), id, x));
			}
			return l;
		}
		throw new Exception();
	}

	protected Expression eval(Expression expr) throws Exception {
		evalCounter++;
		switch (expr.GetType()) {
		case BinOp:
			return eval((BinOp) expr);
		case Identifier:
			return eval((Identifier) expr);
		case Fundef:
			return eval((FunDef) expr);
		case FunCall:
			return eval((FunCall) expr);
		case Number:
			return eval((Number) expr);
		case Let:
			return eval((Let) expr);
		}
		throw new Exception();
	}

	private Expression eval(Number n) {
		return n;
	}

	private Expression eval(Identifier id) throws Exception {
		throw new Exception();
	}

	private Expression eval(FunDef f) {
		return f;
	}

	private Expression eval(BinOp b) throws Exception {
		Expression left = eval(b.GetLeft());
		Expression right = eval(b.GetRight());

		if (left.GetType() != ExprType.Number
				|| right.GetType() != ExprType.Number) {
			throw new Exception();
		}

		switch (b.GetOp()) {
		case Plus:
			return new Number(((Number) left).getValue()
					+ ((Number) right).getValue());
		case Minus:
			return new Number(((Number) left).getValue()
					- ((Number) right).getValue());
		case Mult:
			return new Number(((Number) left).getValue()
					* ((Number) right).getValue());
		case Div:
			if (((Number) right).getValue() == 0) {
				throw new Exception();
			}
			return new Number(((Number) left).getValue()
					/ ((Number) right).getValue());
		}
		throw new Exception();
	}

	public Expression evalExpr(Expression e) throws Exception {
		evalCounter = 0;
		return eval(e);
	}

	abstract Expression eval(FunCall func) throws Exception;

	abstract Expression eval(Let l) throws Exception;

	public int getCounter() {
		return evalCounter;
	}

}
