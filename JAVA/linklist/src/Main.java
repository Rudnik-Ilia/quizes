public class Main {
    public static void main(String[] args) {

        SLList slList = new SLList();

        System.out.println("ISEMPTY: " + slList.isEmpty());
        System.out.println("SIZE: " + slList.size());

        slList.pushFront(1);
        System.out.println("HasNEXT: " + slList.begin().hasNext());
        System.out.println("NEXT: " + slList.begin().next());

        slList.pushFront(2);
        System.out.println("NEXT: " + slList.begin().next());
        slList.pushFront(3);

        System.out.println("ISEMPTY: " + slList.isEmpty());
        System.out.println("SIZE: " + slList.size());

//        System.out.println("REMOVED DATA: " + slList.popFront());
//        System.out.println("REMOVED DATA: " + slList.popFront());
//        System.out.println("REMOVED DATA: " + slList.popFront());
//
//        System.out.println("ISEMPTY: " + slList.isEmpty());
//        System.out.println("SIZE: " + slList.size());

        System.out.println("HasNEXT: " + slList.begin().hasNext());

        slList.popFront();
        System.out.println(slList.find(3).next());
        System.out.println(slList.find(2).next());
        System.out.println(slList.find(1).next());


    }
}