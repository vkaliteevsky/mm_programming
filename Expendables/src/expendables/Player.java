/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.util.ArrayList;

public class Player {
	private int[] armyAmount;
	private int gold;
	String name;
	ArrayList<Unit> army = new ArrayList();

	Player(String s) {
		armyAmount = new int[4];
		for (int i = 0; i < 4; i++)
			armyAmount[i] = 0;
		// k.Amount = 0;
		// / a.Amount = 0;
		// / p.Amount = 0;
		// s.Amount = 0;
		gold = 1000;
		name = s;
	}

	public void setArmy(int a, int b, int c, int d) {
		armyAmount[0] = a;
		armyAmount[1] = b;
		armyAmount[2] = c;
		armyAmount[3] = d;
	}

	public int getSwordsman() {
		return armyAmount[0];
	}

	public int getPikeman() {
		return armyAmount[1];
	}

	public int getArcher() {
		return armyAmount[2];
	}

	public int getKnight() {
		return armyAmount[3];
	}

	/*
	 * int Army(){//возвращает количество армий int tmp=0; if (k.Amount != 0)
	 * tmp++; if (a.Amount != 0) tmp++; if (p.Amount != 0) tmp++; if (s.Amount
	 * != 0) tmp++; return tmp; }
	 * 
	 * public Boolean isArmy(){//проверяет наличие армий if ((k.Amount == 0) &
	 * (a.Amount == 0) & (p.Amount == 0) & (s.Amount == 0)){ return false; }
	 * else return true; }
	 */
	public int getIntGold() {
		return gold;
	}

	public void SwordsmanUp() {
		armyAmount[0]++;
	}

	public void PikemanUp() {
		armyAmount[1]++;
	}

	public void ArcherUp() {
		armyAmount[2]++;
	}

	public void KnightUp() {
		armyAmount[3]++;
	}

	public String getGold() {
		return String.valueOf(gold);
	}

	public void minusGold(int n) {
		gold -= n;
	}

}
