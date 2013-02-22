/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

public class Swordsman extends Unit {
	Swordsman() {
		Damage = 20;
		Health = 50;
		Amount = 0;
		x = 0;
		y = 0;
	}

	static int Cost = 50;
	int Amount;

	Swordsman(int h, int x, int y) {
		Health = h;
		this.x = x;
		this.y = y;
	}

	@Override
	int attack() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	void go() {
		// TODO Auto-generated method stub

	}

	@Override
	String getName() {
		return "Swordsman";
	}
}
