package il.com.ilrd.Enum;

import org.junit.Assert;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static il.com.ilrd.Enum.Week.*;
import static org.junit.jupiter.api.Assertions.*;

class WeekTest {

    Week one = MONDAY;
    Week two = TUESDAY;
    Week three = WENSDAY;

    @Test
    void getInt() {
        Assert.assertEquals(one.getInt(), 0);
        Assert.assertEquals(two.getInt(), 1);
        Assert.assertEquals(three.getInt(), 2);
    }


    @Test
    void fromValue() {
        Assert.assertEquals(Week.fromValue(0), MONDAY);
        Assert.assertEquals(Week.fromValue(1), TUESDAY);
        Assert.assertEquals(Week.fromValue(2), WENSDAY);
    }

//    @Test
//    void show() {
//        for (int i = 0; i < 7; ++i){
//            Assert.assertEquals(Week.Show(), Week.fromValue(i));
//        }
//    }
}