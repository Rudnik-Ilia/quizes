import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestClass {
    @Test
    public void testSize(int exp, int act){
        assertEquals(exp, act);
    }

}
