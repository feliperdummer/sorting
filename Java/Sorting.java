public final class Sorting {
	private Sorting() {}

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

	//-------------------------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------------------------

	public static void bubbleSort(byte[] arr) {
		for (int i = 0; i < arr.length-1; i++) { // loop de repetições do algoritmo
			boolean swap = false;
			for (int j = 0; j < arr.length-i-1; j++) { // loop de travessia
				if (arr[j] > arr[j+1]) {
					byte temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
					swap = true;
				}
			}
			// caso swap for true, nenhuma troca foi feita, o array ta ordenado
			if (!swap) {
				break;
			}
		}
	}

	//-------------------------------------------------------------------------------------------

	public static void mergeSort(byte[] arr) {
		int arrLen = arr.length;

		// caso base
		if (arrLen <= 1) {
			return;
		}

		int middle = arrLen / 2; // suponha que o tamanho é 3, isso vai dar 1
		byte[] leftArr = new byte[middle]; // aqui vai ter 1 elemento
		byte[] rightArr = new byte[arrLen - middle]; // aqui vao ter 2 elementos

		int i = 0; // left arr
		int j = 0; // right arr

		// copia os valores do arr para leftArr e rightArr
		for (; i < arrLen; i++) {
			if (i < middle) { // valor na primeira metade do arr
				leftArr[i] = arr[i];
			}
			else { // valor na segunda metade do arr
				rightArr[j++] = arr[i];
			}
		}

		mergeSort(leftArr);
		mergeSort(rightArr);
		merge(leftArr, rightArr, arr);

	}

	// helper, junta as duas metades do arr
	public static void merge(byte[] leftArr, byte[] rightArr, byte[] arr) {
		int leftSize = arr.length / 2;
		int rightSize = arr.length - leftSize;

		int i = 0; // indice arr
		int l = 0; // indice leftArr
		int r = 0; // indice rightArr

		// enquanto tiver pelo menos dois elementos a serem comparados no leftArr e rightArr
		while (l < leftSize && r < rightSize) {
			if (leftArr[l] <= rightArr[r]) { // o (<=)faz com que o mergesort seja estavel
				arr[i] = leftArr[l++];
			}
			else {
				arr[i] = rightArr[r++];
			}
			i++;
		}

		// quando sobra pelo menos um elemento em uma das metades
		while (l < leftSize) {
			arr[i++] = leftArr[l++];
		}
		while (r < rightSize) {
			arr[i++] = rightArr[r++];
		}
	}

	//-------------------------------------------------------------------------------------------

	public static void quickSort(byte[] arr, int start, int end) {
		// caso base
		if (end <= start) {
			return;
		}

		int pivot = partition(arr, start, end);
		quickSort(arr, start, pivot-1);
		quickSort(arr, pivot+1, end);
	}

	// helper, devolve a posicao do pivo 
	public static int partition(byte[] arr, int start, int end) {

		int pivot = arr[end];
		int i = start - 1;

		for (int j = start; j < end; j++) {
			if (arr[j] < pivot) {
				i++;
				byte temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;
			}
		}
		i++;

		byte temp = arr[i];
		arr[i] = arr[end];
		arr[end] = temp;

		return i;
	}
}
