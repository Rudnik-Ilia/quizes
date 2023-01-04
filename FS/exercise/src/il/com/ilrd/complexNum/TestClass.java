package il.com.ilrd.complexNum;

import il.com.ilrd.complexNum.ComplexNum;

import org.junit.Assert;
import org.junit.Test;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Assertions;
//import org.junit.jupiter.api.Test;

public class TestClass {
    double DELTA = 0.0001;
    @Test
    public void testCtor()
    {
        ComplexNum num_0 = new ComplexNum();
        Assertions.assertEquals(0, num_0.getReal());
        Assertions.assertEquals(0, num_0.getImage());

        ComplexNum num_1 = new ComplexNum(1, 1);
        Assertions.assertEquals(1, num_1.getReal(), DELTA);
        Assertions.assertEquals(1, num_1.getImage(), DELTA);
        Assertions.assertTrue(num_1.equals(num_1));
        Assertions.assertFalse(num_1.equals(num_0));
    }

    @Test
    public void testSetGet()
    {
        ComplexNum  temp = new ComplexNum();
        Assert.assertEquals(0, temp.getReal(), DELTA);
        Assert.assertEquals(0, temp.getImage(), DELTA);
        temp.setReal(10);
        temp.setImage(20);
        Assert.assertEquals(10, temp.getReal(), DELTA);
        Assert.assertEquals(20, temp.getImage(), DELTA);
    }

    @Test
    public void testEqualsCompare()
    {
        ComplexNum num_0 = new ComplexNum(0, 0);
        ComplexNum num_3_4 = new ComplexNum(3, 4);

        Assert.assertTrue(num_3_4.equals(num_3_4));
        Assert.assertEquals(0, num_3_4.compareTo(num_3_4), DELTA);

        Assert.assertFalse(num_3_4.equals(num_0));
        Assert.assertEquals(1, num_3_4.compareTo(num_0), DELTA);
        Assert.assertEquals(-1, num_0.compareTo(num_3_4), DELTA);
    }

    @Test
    public void testMath()
    {
        ComplexNum result = new ComplexNum();

        //Add & Sub
        ComplexNum num_3 = new ComplexNum(3, 3);
        ComplexNum num_2 = new ComplexNum(2, 2);

        // Add
        result = num_3.add(num_2);
        Assert.assertEquals(5, result.getReal(), DELTA);
        Assert.assertEquals(5, result.getImage(), DELTA);

        // Sub
        result = num_3.sub(num_2);
        Assert.assertEquals(1, result.getReal(), DELTA);
        Assert.assertEquals(1, result.getImage(), DELTA);

        //Multi & Div
        ComplexNum  cNum_1 = new ComplexNum(2, 3); /* 2 + 3i */
        ComplexNum  cNum_2 = new ComplexNum(-1, 1); /* -1 + i */

        // -> Multi
        result = cNum_1.multi(cNum_2);
        Assert.assertEquals(-5, result.getReal(), DELTA);
        Assert.assertEquals(-1, result.getImage(), DELTA);

        // -> Div
    }

    @Test
    public void testRealImag()
    {
        ComplexNum  numZero = new ComplexNum();

        ComplexNum  numReal = new ComplexNum(1, 0);
        Assert.assertTrue(numReal.isReal());
        Assert.assertFalse(numReal.isImaginary());

        ComplexNum  numImag = new ComplexNum(0, 1);
        Assert.assertFalse(numImag.isReal());
        Assert.assertTrue(numImag.isImaginary());

        ComplexNum  numComplex = new ComplexNum(1, 1);
        Assert.assertTrue(numComplex.isReal());
        Assert.assertFalse(numComplex.isImaginary());
    }
    @Test
    public void testParsingToString()
    {
        //without spaces: plus
        ComplexNum numParsed1 = ComplexNum.parse("3.0+4.0i");
        Assert.assertEquals(3, numParsed1.getReal(), DELTA);
        Assert.assertEquals(4, numParsed1.getImage(), DELTA);

        ComplexNum numParsed3 = ComplexNum.parse("4.0i");
        Assert.assertEquals(0, numParsed3.getReal(), DELTA);
        Assert.assertEquals(4, numParsed3.getImage(), DELTA);

        //without spaces: minus
        ComplexNum numParsed5 = ComplexNum.parse("-3.0-4.0i");
        Assert.assertEquals(-3, numParsed5.getReal(), DELTA);
        Assert.assertEquals(-4, numParsed5.getImage(), DELTA);

        //Spaces
        ComplexNum numParsedSpaces = ComplexNum.parse("3.0 + 4.0i");
        Assert.assertEquals(3, numParsedSpaces.getReal(), DELTA);
        Assert.assertEquals(4, numParsedSpaces.getImage(), DELTA);

        //Imag Only
        ComplexNum numParsedImagOnly = ComplexNum.parse("-14.0i");
        Assert.assertEquals(0, numParsedImagOnly.getReal(), DELTA);
        Assert.assertEquals(-14, numParsedImagOnly.getImage(), DELTA);

        //Imag Only
        ComplexNum numParsedImagOnly2 = ComplexNum.parse("10000.0i");
        Assert.assertEquals(0, numParsedImagOnly2.getReal(), DELTA);
        Assert.assertEquals(10000, numParsedImagOnly2.getImage(), DELTA);
    }
}



























//package il.com.ilrd.complexNum;
//
//import org.junit.Assert;
//import org.junit.Before;
//import org.junit.jupiter.api.Assertions;
//import org.junit.jupiter.api.Test;
//
//public class TestClass {
//
//    ComplexNum num;
//    ComplexNum num1;
//    ComplexNum numSame;
//    ComplexNum sum;
//    ComplexNum div;
//
//    double a = 1.5;
//    double b = 5.5;
//    double c = -7.5;
//
//    @Before
//    public void Start(){
//        num = new ComplexNum(a,b);
//        numSame = new ComplexNum(a,b);
//        num1 = new ComplexNum(b,c);
//        sum = num.add(num1);
//        div = num1.sub(num);
//
//    }
//
//    @Test
//    public void TestEqual(){
//        Assertions.assertEquals(num, numSame);
//
//    }
//
//    @Test
//    public void TestMath(){
//
//
//    }
//
//
//}
