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

    public List(Object value) {
        head = new Item(value);
    }

    public Item getHead() {
        return head;
    }

    public void append(Object value) {
        Item newItem = new Item(value);
        for (Item tmp = head; tmp != null; tmp = tmp.getNext()) {
            if (tmp.getNext() == null) {
                tmp.setNext(newItem);
                return;
            }
        }
    }

    public void each(Printer printer) {
        for (Item tmp = head; tmp != null; tmp = tmp.getNext()) {
            printer.print(tmp.getValue());
        }
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
    }
}
