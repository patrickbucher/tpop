import java.util.Random;

interface Cmp {
    int cmp(Object x, Object y);
}

// Icmp: Integer comparison
class Icmp implements Cmp {
    public int cmp(Object o1, Object o2) {
        int i1 = ((Integer) o1).intValue();
        int i2 = ((Integer) o2).intValue();
        if (i1 < i2) {
            return -1;
        } else if (i1 == i2) {
            return 0;
        } else {
            return 1;
        }
    }
}

// Scmp: String comparison
class Scmp implements Cmp {
    public int cmp(Object o1, Object o2) {
        String s1 = (String) o1;
        String s2 = (String) o2;
        return s1.compareTo(s2);
    }
}

class Quicksort {

    static Random rgen = new Random();

    // Quicksort.rand: return random integer in [left,right]
    static int rand(int left, int right) {
        return left + Math.abs(rgen.nextInt()) % (right - left + 1);
    }

    // Quicksort.sort: quicksort v[left]..v[right]
    static void sort(Object[] v, int left, int right, Cmp cmp) {
        int i, last;

        if (left >= right) {
            return;
        }

        swap(v, left, rand(left, right));

        last = left;
        for (i = left + 1; i <= right; i++) {
            if (cmp.cmp(v[i], v[left]) < 0) {
                swap(v, ++last, i);
            }
        }
        swap(v, left, last);
        sort(v, left, last - 1, cmp);
        sort(v, last + 1, right, cmp);
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
    
        Cmp cmp = new Scmp(); 
        Quicksort.sort(array, 0, array.length - 1, new Scmp());
        for (int i = 0; i < array.length; i++) {
            if (i > 0 && cmp.cmp(array[i-1], array[i]) > 0) {
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
