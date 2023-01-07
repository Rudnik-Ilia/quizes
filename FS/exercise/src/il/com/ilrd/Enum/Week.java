package il.com.ilrd.Enum;

public enum Week {
    MONDAY,
    TUESDAY,
    WENSDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY;

    int x;

    public static void Show(){
        for (Week x: Week.values()){
            System.out.println(x.name());
        }
    }

}
