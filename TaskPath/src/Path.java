public class Path {
	int x;
	int y;

	public int fact(int f) {
		int num = 1;
		for (int i = 2; i <= f; i++) {
			num *= i;
		}
		return num;
	}

	public int binom() {
		int n = x + y;
		int k = x;
		int c;
		c = fact(n)/(fact(k)*fact(n-k));
		return (c);
	}

}
