package il.com.ilrd.sll;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestClass {

    @Test
    public void testSize(int exp, int act){
        assertEquals(exp, act);
    }
    @Test
    public void testEmpty(boolean exp, boolean act){
        assertEquals(exp, act);
    }
    @Test
    public void testFind(Object exp, Object act){
        assertEquals(exp, act);
    }
    @Test
    public void testRemove(Object exp, Object act){
        assertEquals(exp, act);
    }

}
