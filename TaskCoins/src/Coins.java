
public class Coins {

	public static int consider(int coins[], int num, int amount ){
			if (num == 0) return 1;
			if (num < 0) return 0;
			if (amount == 0) return 0;
			return consider(coins, num, amount - 1) + consider(coins, num - coins[coins.length - amount], amount);			
	}
}
