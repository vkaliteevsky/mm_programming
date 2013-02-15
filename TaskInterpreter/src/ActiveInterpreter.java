/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

import Interpreter.Nodes.ExprType;
import Interpreter.Nodes.Expression;
import Interpreter.Nodes.FunCall;
import Interpreter.Nodes.FunDef;
import Interpreter.Nodes.Let;

public class ActiveInterpreter extends Interpreter {

	@Override
	Expression eval(FunCall func) throws Exception {
		Expression f = eval(func.GetFun());

		if (f.GetType() != ExprType.Fundef) {
			throw new Exception();
		}

		FunDef fun = (FunDef) f;

		return eval(substitute(fun.GetBody(), fun.GetId(), eval(func.GetArg())));
	}

	@Override
	Expression eval(Let l) throws Exception {
		return eval(substitute(l.getExpr(), l.getId(), eval(l.getBound())));
	}
}
