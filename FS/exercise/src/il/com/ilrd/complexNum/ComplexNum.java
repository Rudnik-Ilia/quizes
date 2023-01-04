package il.com.ilrd.complexNum;

import com.sun.xml.internal.ws.message.stream.StreamHeader;
import java.util.regex.Pattern;
import java.util.regex.Matcher;


public class ComplexNum implements Comparable{
    private double real;
    private double image;

    public ComplexNum() {
    }

    public ComplexNum(double real, double image) {
        this.real = real;
        this.image = image;
    }

    private static boolean check(Object obj){
        return obj instanceof ComplexNum;
    }

    public double getReal() {
        return real;
    }

    public void setReal(double real) {
        this.real = real;
    }

    public double getImage() {
        return image;
    }

    public void setImage(double image) {
        this.image = image;
    }

    @Override
    public String toString() {
        String pos = this.image >= 0 ? "+" : "";
        return "ComplexNum: "+ String.format("%.1f", this.real)  + pos + String.format("%.1f", this.image) + "i";
    }

    public ComplexNum add(ComplexNum other){
        return new ComplexNum(this.real + other.real, this.image + other.image);
    }
    public ComplexNum sub(ComplexNum other){
        return new ComplexNum(this.real - other.real, this.image - other.image);
    }

    private  ComplexNum mul(ComplexNum other) {
        return new ComplexNum((this.real * other.real) - (this.image * other.image), (this.image * other.real) + (this.real * other.image));
    }

    public double magnitude() {
        return Math.sqrt(this.real * this.real + this.image * this.image);
    }

    @Override
    public int compareTo(Object other) {
        int res = 0;
        if(ComplexNum.check(other)){
            ComplexNum tmp = (ComplexNum)other;
            res = (int)(100*this.magnitude()/100.0f  - Math.floor(100*tmp.magnitude()/100.0f));
        }else {
            throw new ClassCastException("BAD IDEA");
        }
        return res;
    }

    @Override
    public boolean equals(Object other){
        if(ComplexNum.check(other)){
                return (this.real == ((ComplexNum) other).real && this.image == ((ComplexNum) other).real);
            }
        return false;
    }

    public static ComplexNum parse(String str)
    {
        String regex = "^([-+]?\\d*\\.?\\d*)[+-]([-+]?\\d*\\.?\\d*)i$";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str);

        if (matcher.matches())
        {
            double x = Double.parseDouble(matcher.group(1));
            double y = Double.parseDouble(matcher.group(2));
            return new ComplexNum(x, y);
        }
        else
        {
            throw new NumberFormatException("TRY AGAINI WITH YOUR STRING" + str);
        }
    }

}
