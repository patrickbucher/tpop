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
        String[] array = new String[]{"One", "Two", "Three", "Four", "Five", "Six", "Seven"};
        Quicksort.sort(array, 0, array.length - 1, new Scmp());
        for (int i = 0; i < array.length; i++) {
            System.out.printf("%s ", array[i]);
        }
        System.out.println("");
    }
}
