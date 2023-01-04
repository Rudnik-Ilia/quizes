package il.com.ilrd.complexNum;

public class Main {
    public static void main(String[] args) {
        ComplexNum num1 = new ComplexNum(2.3, 6);
        ComplexNum num2 = new ComplexNum(-7, -13.3);
        ComplexNum num4 = new ComplexNum(2.3, 6);
        String ex = "ilia";


        System.out.println(num1);
        System.out.println(num2);
        ComplexNum num3 = num2.add(num1);
        System.out.println(num3);
        System.out.println(num4);

        System.out.println(num1.magnitude());
        System.out.println(num2.magnitude());
        System.out.println(num3.magnitude());
        System.out.println(num4.magnitude());
        System.out.println(num4.compareTo(ex));

    }
}
