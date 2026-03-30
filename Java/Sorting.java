import java.util.Arrays;

public final class Sorting {
	private Sorting() {}

	// a implementação com outros tipos de dados primitivos é basicamente a mesma;

	public static void selectionSort(byte[] arr) {
		for (int i = 0; i < arr.length-1; i++) {
			int min = i;
			for (int j = i+1; j < arr.length; j++) {
				min = arr[j] < arr[min] ? j : min;
			}
			if (min!=i) {
				byte temp = arr[i];
				arr[i] = arr[min];
				arr[min] = temp;
			}
		}
	}

	public static void insertionSort(byte[] arr) {
		for (int i = 1; i < arr.length; i++) {
			byte key = arr[i];
			int j = i-1; 
			while (j >= 0 && arr[j] > key) {
				arr[j + 1] = arr[j];
				--j;
			}
			arr[j+1] = key;
		}
	}
}