/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Nodes;

public abstract class Expression extends Node {
	protected ExprType mType;

	public ExprType GetType() {
		return mType;
	}
}