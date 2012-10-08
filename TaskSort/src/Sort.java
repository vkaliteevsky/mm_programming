public class Sort {
	private static void swap(Object[] arr, int i, int j) {
		Object t = arr[i];
		arr[i] = arr[j];
		arr[j] = t;
	}

	public static void sort(Object[] arr) {
		for (int i = arr.length - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {
				if (Compare.compare(arr[j], arr[j + 1]))
					swap(arr, j, j + 1);
			}
		}
		for (int i = 0; i < arr.length - 1; i++) {
			System.out.print(arr[i] + ",");
		}
		System.out.print(arr.length - 1);
	}

}
