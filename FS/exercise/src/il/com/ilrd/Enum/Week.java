package il.com.ilrd.Enum;

public enum Week {
    MONDAY,
    TUESDAY,
    WENSDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY;

    public int getInt(){
        return Week.this.ordinal();
    }

    public static Week fromValue(int x){
        return Week.values()[x];
    }

    public static void Show(){
        for (Week x: Week.values()){
            System.out.println(x.name());
        }
    }

}
