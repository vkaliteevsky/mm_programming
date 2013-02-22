/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.util.Observable;

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

	public Model() {
		player1 = new Player("");
		player2 = new Player("");
		first = true;
		error = false;
		cur = player1;
	}

	public boolean isError() {
		return error;
	}

	public void buyUnit(String s) {
		int gold = cur.getIntGold();
		error = false;
		if ("S".equals(s)) {
			if (gold > Swordsman.Cost) {
				cur.SwordsmanUp();
				cur.army.add(new Swordsman());

				cur.minusGold(Swordsman.Cost);
			} else {
				error = true;
			}
		} else if ("P".equals(s)) {
			if (gold > Pikeman.Cost) {
				cur.PikemanUp();
				cur.army.add(new Pikeman());
				cur.minusGold(Pikeman.Cost);
			} else {
				error = true;
			}
		} else if ("A".equals(s)) {
			if (gold > Archer.Cost) {
				cur.ArcherUp();
				cur.army.add(new Archer());
				cur.minusGold(Archer.Cost);
			} else {
				error = true;
			}
		} else {
			if (gold > Knight.Cost) {
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

	public boolean getFirst() {
		return first;
	}

}
