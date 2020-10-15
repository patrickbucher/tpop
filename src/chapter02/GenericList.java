class Item {
    private Object value;
    private Item next;

    public Item(Object value) {
        this.value = value;
    }

    public Object getValue() {
        return value;
    }

    public Item getNext() {
        return next;
    }

    public void setNext(Item next) {
        this.next = next;
    }
}

interface Printer {
    public void print(Object value);
}

class LinePrinter implements Printer {
    public void print(Object value) {
        System.out.println(value);
    }
}

class List {
    private Item head;
    private int n;

    public List(Object value) {
        head = new Item(value);
        n = 1;
    }

    public Item getHead() {
        return head;
    }

    public void append(Object value) {
        Item newItem = new Item(value);
        for (Item tmp = head; tmp != null; tmp = tmp.getNext()) {
            if (tmp.getNext() == null) {
                tmp.setNext(newItem);
                n++;
                return;
            }
        }
    }

    public void each(Printer printer) {
        for (Item tmp = head; tmp != null; tmp = tmp.getNext()) {
            printer.print(tmp.getValue());
        }
    }

    public int size() {
        return n;
    }

    public Item get(int i) {
        Item item = null;

        if (i < 0 || i >= n) {
            return null;
        }

        for (item = head; item != null; item = item.getNext()) {
            if (i == 0) {
                return item;
            }
            i--;
        }

        return null;
    }
}

class GenericList {
    public static void main(String args[]) {
        List list = new List("everything");
        list.append("that");
        list.append("begins");
        list.append("also");
        list.append("ends");
        list.each(new LinePrinter());
        System.out.println(list.size() + " words");
        System.out.println("first word: " + list.get(0).getValue());
        System.out.println("second word: " + list.get(1).getValue());
        System.out.println("third word: " + list.get(2).getValue());
        System.out.println("fourth word: " + list.get(3).getValue());
        System.out.println("fifth word: " + list.get(4).getValue());
    }
}
