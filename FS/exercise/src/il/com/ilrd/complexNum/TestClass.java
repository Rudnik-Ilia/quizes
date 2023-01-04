package il.com.ilrd.complexNum;

import org.junit.Assert;
import org.junit.Before;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class TestClass {

    ComplexNum num;
    ComplexNum num1;
    ComplexNum numSame;
    ComplexNum sum;
    ComplexNum div;


    double a = 1.5;
    double b = 5.5;
    double c = -7.5;

    @Before
    public void Start(){
        num = new ComplexNum(a,b);
        numSame = new ComplexNum(a,b);
        num1 = new ComplexNum(b,c);
        sum = num.add(num1);
        div = num1.sub(num);

    }

    @Test
    public void TestEqual(){
        Assertions.assertEquals(num, numSame);
    }

    @Test
    public void TestMath(){
        System.out.println(sum);
    }


}
