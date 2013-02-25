/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.util.ArrayList;
import java.util.Observable;

import javax.swing.JToggleButton;

/**
 * 
 * @author vkaliteevskiy
 */
public class Model extends Observable {
	Player player1;
	Player player2;
	
	Player cur;
	private boolean first;
	private boolean error;
	
	//private boolean courseFirstPlayer;
	private Unit currFirstUnit;
	private Unit currSecondUnit;
	
	static ArrayList<JToggleButton> field_buttons = new ArrayList();
	
	public void setButtonsUp(){
		for (JToggleButton butt : field_buttons){
			butt.setSelected(false);
		}
	}
	
	public void setName(String s) {
		cur.name = s;
		this.setChanged();
		this.notifyObservers();
	}

	public void setCur1() {
		cur = player1;
		this.setChanged();
		this.notifyObservers();
	}

	public void setCur2() {
		cur = player2;
		this.setChanged();
		this.notifyObservers();
	}
/*
	public Model(String s) {
		player1 = new Player("1");
		player2 = new Player("2");
		first = true;
		error = false;
		cur = player1;
		
		//courseFirstPlayer = true;
		//currFirstUnit = player1.army.get(0);
		//currSecondUnit = player2.army.get(0);
		}*/
	
	public Model() {
		player1 = new Player("1");
		player2 = new Player("2");
		first = true;
		error = false;
		cur = player1;
		
		//courseFirstPlayer = true;
		//currFirstUnit = player1.army.get(0);
		//currSecondUnit = player2.army.get(0);
		}
	
	

	public void setModel (Player p, Unit u1, Unit u2){
		cur = p;
		currFirstUnit = u1;
		currSecondUnit = u2;
	}
	
	
	public boolean isError() {
		return error;
	}

	public void buyUnit(String s) {
		int gold = cur.getIntGold();
		error = false;
		if ("S".equals(s)) {
			if (gold >= Swordsman.Cost) {
				cur.SwordsmanUp();
				cur.army.add(new Swordsman());
				cur.minusGold(Swordsman.Cost);
			} else {
				error = true;
			}
		} else if ("P".equals(s)) {
			if (gold >= Pikeman.Cost) {
				cur.PikemanUp();
				cur.army.add(new Pikeman());
				cur.minusGold(Pikeman.Cost);
			} else {
				error = true;
			}
		} else if ("A".equals(s)) {
			if (gold >= Archer.Cost) {
				cur.ArcherUp();
				cur.army.add(new Archer());
				cur.minusGold(Archer.Cost);
			} else {
				error = true;
			}
		} else {
			if (gold >= Knight.Cost) {
				cur.KnightUp();
				cur.army.add(new Knight());
				cur.minusGold(Knight.Cost);
			} else {
				error = true;
			}
		}
		this.setChanged();
		this.notifyObservers();
	}

	public void setErrorFalse(){
		error = false;
	}
	
	public boolean getFirst() {
		return first;
	}
	

	public Unit currFirstUnit (){
		return currFirstUnit;
	}
	
	public Unit currSecondUnit (){
		return currSecondUnit;
	}
	
	public void setCurrFirstUnit (int x, int y){
		currFirstUnit.x = x;
		currFirstUnit.y = y;
	}
	
	public void setCurrFirstUnit_u (Unit u){
		currFirstUnit = u;
	}
	
	public void setCurrSecondUnit_u (Unit u){
		currSecondUnit = u;
	}
	
	public void setCurrUnit (int x, int y){
		if (cur == player1){
			currFirstUnit.x = x;
			currFirstUnit.y = y;
		} else {
			currSecondUnit.x = x;
			currSecondUnit.y = y;
		}
	}
	
	public void currUnitUp (Player p){
		if (player1 == p ){
			int i = cur.army.indexOf(currFirstUnit()); i++;
			if (i == cur.army.size()){
				currFirstUnit = cur.army.get(0);
			} else {
				currFirstUnit = cur.army.get(i);
			}
		} else {
			int i = cur.army.indexOf(currSecondUnit()); i++;
			if (i == cur.army.size()){
				currSecondUnit = cur.army.get(0);
			} else {
				currSecondUnit = cur.army.get(i);
			}
		}
	}
	
	public Unit currUnit (Player p){
		if (player1 == p ){
			return currFirstUnit();
		} else {
			return currSecondUnit();
		}
	}

	public boolean isEnemy (Player p, int x, int y){
		if (p == player1){
			for (Unit unit : player2.army){
				if ((unit.x == x)&&(unit.y==y)){
					return true;
				}
				
			}
			return false;
		} else {
			for (Unit unit : player1.army){
				if ((unit.x == x)&&(unit.y==y)){
					return true;
				}
				
			}
			return false;
		}
	}

	public Unit unitEnemy (Player p, int x, int y){
		if (p == player1){
			for (Unit unit : player2.army){
				if ((unit.x == x)&&(unit.y==y)){
					return unit;
				}
				
			}
			return null;
		} else {
			for (Unit unit : player1.army){
				if ((unit.x == x)&&(unit.y==y)){
					return unit;
				}
				
			}
			return null;
		}
	}	
	
	public Unit fight (Unit u1, Unit u2){
		while ((u1.Health > 0)||(u2.Health > 0)){
			u2.Health -= u1.Health*u1.Damage;
			u1.Health -= u2.Health*u2.Damage;
		}
		int xx = u2.x; int yy = u2.y;
		
		cur.army.remove(u1);
		noncur().army.remove(u2);
		
		
		if (u1.Health <= 0) {
			noncur().army.add(u2);
			u2.setCoord(xx, yy);
			return u2;
		}
		else {
			cur.army.add(u1);
			u1.setCoord(xx, yy);
			return u1;		
		}
	}


	public Player noncur(){
		if (cur == player1) return player2;
		else return player1;
	}
}