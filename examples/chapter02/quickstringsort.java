import java.util.Random;

class QuickStringSort {

    static Random rgen = new Random();

    // QuickStringSort.rand: return random integer in [left,right]
    static int rand(int left, int right) {
        return left + Math.abs(rgen.nextInt()) % (right - left + 1);
    }

    // QuickStringSort.sort: quicksort v[left]..v[right]
    static void sort(String[] v, int left, int right) {
        int i, last;

        if (left >= right) {
            return;
        }

        swap(v, left, rand(left, right));

        last = left;
        for (i = left + 1; i <= right; i++) {
            if (v[i].compareTo(v[left]) < 0) {
                swap(v, ++last, i);
            }
        }
        swap(v, left, last);
        sort(v, left, last - 1);
        sort(v, last + 1, right);
    }

    static void swap(Object[] v, int i, int j) {
        Object tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }

    public static void main(String[] args) {
        final int n = 10000000;
        final Random rgen = new Random();
        final int max = 'z' - 'a' + 1;
        final int length = 10;
        String[] array = new String[n];
        for (int i = 0; i < n; i++) {
            array[i] = randomString(rgen, length, max);
        }
    
        QuickStringSort.sort(array, 0, array.length - 1);
        for (int i = 0; i < array.length; i++) {
            if (i > 0 && array[i-1].compareTo(array[i]) > 0) {
                System.out.println("array was not sorted correctly");
                System.exit(-1);
            }
        }
        System.out.printf("%d string elements sorted correctly\n", n);
    }

    public static String randomString(Random rgen, int size, int max) {
        StringBuilder sb = new StringBuilder("");
        for (int i = 0; i < size; i++) {
            sb.append((char)('a' + (Math.abs(rgen.nextInt()) % max)));
        }
        return sb.toString();
    }
}
