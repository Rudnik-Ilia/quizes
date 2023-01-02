public class IterImp implements Iter{

    private Node node;

    public IterImp(Node node) {
        this.node = node;
    }

    @Override
    public boolean hasNext() {

        return !(this.node.next == null);
    }

    @Override
    public Object next() {

        if(this.hasNext()){
            return this.node.next.data;
        }
        return null;

    }
}
