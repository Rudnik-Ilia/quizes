package il.com.ilrd.sll;

public class IterImp implements Iter{
    private SLList.Node node;

    public IterImp(SLList.Node node) {
        this.node = node;
    }

    @Override
    public boolean hasNext() {
        return !(this.node.next == null);
    }

    @Override
    public Object next() {

        if(this.hasNext()){
            this.node = node.next;
            return this.node.data;
        }
        return null;

    }
}
