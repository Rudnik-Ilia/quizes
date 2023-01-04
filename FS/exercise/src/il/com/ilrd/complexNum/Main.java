package il.com.ilrd.complexNum;

import org.junit.Before;

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
        System.out.println(num4.compareTo(num1));
        System.out.println(num4.equals(num1));

        ComplexNum num5 = ComplexNum.parse("1.2-9.5i");
        ComplexNum num6 = ComplexNum.parse("9.2777777+ 7.5i");
        ComplexNum num7 = ComplexNum.parse("1.2- 3.5777777i");
        ComplexNum num8 = ComplexNum.parse("12.0-111113.5777777i");

        System.out.println(num8);

        double a = 1.5;
        double b = 5.5;
        double c = -7.5;

        ComplexNum num;
        ComplexNum num_1;
        ComplexNum numSame;
        ComplexNum sum;
        ComplexNum div;

        num = new ComplexNum(a,b);
        numSame = new ComplexNum(a,b);
        num_1 = new ComplexNum(b,c);

        sum = num.add(num_1);
        div = num1.sub(num);

        System.out.println(sum);



    }
}
