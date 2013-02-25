/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

public abstract class Unit {
	public int Damage;
	public int Health;
	public int Amount;
	public int Cost;
	public int x;
	public int y;

	abstract String getName();

	public void setCoord (int x, int y){
		this.x = x;
		this.y = y;
	}
	
	abstract int attack();

	abstract void go();
}
/*
 * private float factor_damage(char unit1, char unit2){ switch (unit1){ case
 * 'k': if (unit2 == 'a') return 2; if (unit2 == 'p') return (float) 0.5; break;
 * 
 * case 'a': if (unit2 == 'k') return (float) 0.5; break;
 * 
 * case 'p': if (unit2 == 'k') return 2; if (unit2 == 's') return (float) 0.5;
 * break;
 * 
 * case 's': if (unit2 == 'a') return (float) 1.5; if (unit2 == 'p') return
 * (float) 0.5; break; } return 1; }
 * 
 * // public void attack(char unit1, char unit2) { // int damag = // } }
 */

