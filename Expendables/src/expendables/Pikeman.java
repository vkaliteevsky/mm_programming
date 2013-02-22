/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

public class Pikeman extends Unit {
	Pikeman() {
		Damage = 20;
		Health = 30;
		Amount = 0;
		x = 0;
		y = 0;
	}

	Pikeman(int h, int x, int y) {
		Health = h;
		this.x = x;
		this.y = y;
	}

	static int Cost = 75;
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
		return "Pikeman";
	}
}
