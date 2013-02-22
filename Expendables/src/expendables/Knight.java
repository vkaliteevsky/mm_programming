/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

public class Knight extends Unit {
	Knight() {
		Damage = 30;
		Health = 50;
		Amount = 0;
		x = 0;
		y = 0;
	}

	Knight(int h, int x, int y) {
		Health = h;
		this.x = x;
		this.y = y;
	}

	static int Cost = 150;
	int Amount;

	// @Override
	// public void attack(){}

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
		return "Knight";

	}

}
