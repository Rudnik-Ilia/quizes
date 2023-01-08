/**********************
 * Title : SLList
 * Author: Ilia Rudnik
 * Reviewer: Kate
 * Date : 3/01/2023
 ***********************/
package il.com.ilrd.sll;

public class SLList {
    private Node head;

    static class Node {
        Object data;
        Node next;

        public Node(Object data, Node next) {
            this.data = data;
            this.next = next;
        }
    }

    public void pushFront(Object data){
        this.head = new Node(data, this.head);;
    }
//inintemsional object retension?
    public Object popFront(){
        Object data = this.head.data;
        this.head = this.head.next;
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
        return (this.head == null);
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