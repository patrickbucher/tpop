class StringSpyPrinter implements Printer {
    private int executions = 0;
    private StringBuilder output = new StringBuilder();

    public void print(Object value) {
        output.append(value.toString());
        executions++;
    }

    public boolean contains(Object value) {
        return output.toString().contains(value.toString());
    }

    public int getExecutions() {
        return executions;
    }
}

class GenericListTest {
    public static void main(String args[]) {
        List list = new List("first");
        assert list != null;
        assert list.size() == 1;
        assert list.get(0) != null;
        assert list.get(0).getValue().equals("first");

        list.append("second");
        assert list.size() == 2;
        assert list.get(0).getValue().equals("first");
        assert list.get(1).getValue().equals("second");

        list.append("third");
        assert list.size() == 3;
        assert list.get(0).getValue().equals("first");
        assert list.get(1).getValue().equals("second");
        assert list.get(2).getValue().equals("third");

        StringSpyPrinter spy = new StringSpyPrinter();
        list.each(spy);

        assert spy.getExecutions() == 3;
        assert spy.contains("first");
        assert spy.contains("second");
        assert spy.contains("third");

        System.out.println("ok");
    }
}
