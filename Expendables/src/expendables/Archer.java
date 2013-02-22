/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

public class Archer extends Unit {
	Archer() {
		Damage = 5;
		Health = 20;
		Amount = 0;
		x = 0;
		y = 0;
	}

	Archer(int h, int x, int y) {
		Health = h;
		this.x = x;
		this.y = y;
	}

	static int Cost = 100;
	int Amount;

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
		return "Archer";
	}
}
