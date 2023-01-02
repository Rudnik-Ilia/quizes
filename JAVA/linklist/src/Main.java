import org.opentest4j.AssertionFailedError;

public class Main {
    public static void main(String[] args) {

        SLList slList = new SLList();
        TestClass test = new TestClass();

        test.testSize(slList.size(), 0);
        test.testEmpty(slList.isEmpty(), true);

        slList.pushFront(1);
        slList.pushFront(2);
        slList.pushFront(3);

        test.testSize(slList.size(), 3);
        test.testEmpty(slList.isEmpty(), false);

        test.testFind(slList.find(3).next(), 2);
        test.testFind(slList.find(2).next(), 1);
        test.testFind(slList.find(1).next(), null);

        test.testRemove(slList.popFront(), 3);
        test.testSize(slList.size(), 2);

        test.testRemove(slList.popFront(), 2);
        test.testSize(slList.size(), 1);

        test.testRemove(slList.popFront(), 1);
        test.testSize(slList.size(), 0);

        test.testEmpty(slList.isEmpty(), true);


    }
}