/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

package Interpreter.Parser;

//import exceptions.*;
import Interpreter.Lexer.*;
import Interpreter.Nodes.*;
import Interpreter.Nodes.Number;

public class Parser {
    private Lexer mLexer;
    private Lexem mCurrLexem;
    
    public Parser() throws Exception{
        
    }
    
    private void NextLexem(){
        this.mCurrLexem = mLexer.NextLexem();
    }
    
    public Node ParseExpr(String expr) throws Exception{
        mLexer = new Lexer(expr);
        NextLexem();
        Node result = Parse();
        if(mCurrLexem.GetType() != LexemType.End){
            throw new Exception();
        }
        return result;
    }
    
    private Node Parse() throws Exception{
    	switch(mCurrLexem.GetType()){
            case Let: 
            	return ParseLet();
            case Fun: 
            	return ParseFun();
            default: 
            	return parseAlExpr();
        }
    }
    
    private Node ParseFun() throws Exception{
        NextLexem();
        if(mCurrLexem.GetType() != LexemType.Id){
            throw new Exception();
        }
        String id = ((IdLexem)mCurrLexem).GetName();
        NextLexem();
        if(mCurrLexem.GetType() != LexemType.Arrow){
            throw new Exception();
        }
        NextLexem();
        return new FunDef(id, (Expression) Parse());
    }
    
    private Node ParseLet() throws Exception{
        NextLexem();
        if(mCurrLexem.GetType() != LexemType.Id){
            throw new Exception();
        }
        String id = ((IdLexem)mCurrLexem).GetName();
        NextLexem();
        if(mCurrLexem.GetType() != LexemType.Assign){
            throw new Exception();
        }
        NextLexem();
        Expression bound = (Expression) Parse();
        if(mCurrLexem.GetType() != LexemType.In){
            throw new Exception();
        }
        NextLexem();
        Expression expr = (Expression) Parse();
        return new Let(id, bound, expr);
    }
    
    private Node parseAlExpr() throws Exception{
        Node left = term();

        if(mCurrLexem.GetType() == LexemType.BinOp){
            Operator operator = ((BinOpLexem)mCurrLexem).GetOp();
            if(operator == Operator.Plus || operator == Operator.Minus){
                NextLexem();
                return new BinOp(operator, (Expression)left, (Expression)parseAlExpr());
            }
        }
        return left;
    }
    
    private Node term() throws Exception {
        Node left = factor();

        if(mCurrLexem.GetType() == LexemType.BinOp){
            Operator operator = ((BinOpLexem)mCurrLexem).GetOp();
            if(operator == Operator.Mult || operator == Operator.Div){
                NextLexem();
                return new BinOp(operator, (Expression)left, (Expression)term());
            }
        }
        return left;
    }

    private Node factor() throws Exception{
        return funcall();
    }
    
    private Node funcall() throws Exception{
        Node n = primary();
        while(mCurrLexem.GetType() == LexemType.Id || 
              mCurrLexem.GetType() == LexemType.OpBrace ||
              mCurrLexem.GetType() == LexemType.Number){
            n = new FunCall((Expression)n, (Expression) primary());
        }
        return n;
    }
    
    private Node primary() throws Exception{
        switch(mCurrLexem.GetType()){
            case Number: int val = ((NumberLexem)mCurrLexem).GetValue();
                       NextLexem();
                       return new Number(val);
            
            case Id: String id = ((IdLexem)mCurrLexem).GetName();
                     NextLexem();
                     return new Identifier(id);
            
            case OpBrace: NextLexem();
                         Node n = Parse();
                         if(mCurrLexem.GetType() != LexemType.ClBrace){
                             throw new Exception();
                         }
                         NextLexem();
                         return n;
            default: throw new Exception();
        }
        
    }
}