package il.com.ilrd.sll;

public class SLList {
    private Node head;

    public void pushFront(Object data){

        Node newNode;

        if(this.head == null){
            newNode = new Node(data);
            this.head = newNode;
        }
        else{
            Node tmp = this.head;
            newNode = new Node(data, tmp);
            this.head = newNode;
        }
    }

    public Object popFront(){
        if(this.isEmpty()){
            return null;
        }
        Node tmp = this.head;
        Object data = this.head.data;
        this.head = tmp.next;
        tmp = null;

        return data;
    }

    public int size(){

        Node tmp = this.head;
        int count = 0;

        while (tmp != null){
            ++count;
            tmp = tmp.next;
        }

        return count;
    }

    public boolean isEmpty(){
        return !(this.size() > 0);
    }

    public IterImp find(Object data){
        Node iter = this.head;
        while (iter != null){
            if(data.equals(iter.data)){
                return new IterImp(iter);
            }
            iter = iter.next;
        }
        return null;
    }

    public IterImp begin(){
        return new IterImp(this.head);
    }

}