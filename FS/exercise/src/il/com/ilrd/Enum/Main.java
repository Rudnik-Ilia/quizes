package il.com.ilrd.Enum;

public class Main {
    public static void main(String[] args) {
        Week one = Week.MONDAY;
        Week two = Week.TUESDAY;
        Week three = Week.MONDAY;
//        System.out.println(one.name());

        System.out.println(Week.valueOf("FRIDAY").ordinal());
        System.out.println(Week.values()[1]);

        System.out.println(Week.fromValue(0));

        System.out.println(one.getInt());
        System.out.println(two.getInt());
        System.out.println(three.getInt());


    }

}
