/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Nodes;

import Interpreter.Lexer.Operator;

public class BinOp extends Expression{
    private Expression mLeft;
    private Expression mRight;
    private Operator mOp;
    
    public BinOp(Operator Op, Expression Left, Expression Right) {
        this.mLeft = Left;
        this.mRight = Right;
        this.mOp = Op;
        mType = ExprType.BinOp;
    }
    
    public Operator GetOp() {
        return mOp;
    }
    
    public Expression GetLeft() {
        return mLeft;
    }
    
    public Expression GetRight() {
        return mRight;
    }
    
    public void SetRight(Expression Right) {
    	mRight = Right;
    }
    
    public void SetLeft(Expression Left) {
    	mLeft = Left;
    }
    @Override
    public Expression DeepCopy(){
        return new BinOp(mOp, (Expression)mLeft.DeepCopy(), (Expression)mRight.DeepCopy());
    }
    
    public String opString(Operator operator){
        switch(operator){
            case Plus: 
            	return "+";
            case Minus:
            	return "-";
            case Div:
            	return "/";
            case Mult:
            	return "*";
        }
        return "";
    }
    
    @Override
    public String toString(){
        return "(" + mLeft.toString() + opString(mOp) + mRight.toString() + ")";
    }
}