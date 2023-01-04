package il.com.ilrd.complexNum;

import com.sun.xml.internal.ws.message.stream.StreamHeader;

import java.util.Objects;
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
        return "ComplexNum: "+ String.format("%.2f", this.real)  + pos + String.format("%.2f", this.image) + "i";
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
        double res = 0;
        int f = 0;
        if(ComplexNum.check(other)){
            ComplexNum tmp = (ComplexNum)other;
            res = (this.magnitude() - tmp.magnitude());
        }else {
            throw new ClassCastException("BAD IDEA");
        }
        if(res > 0){
            f = 1;
        }
        else if (res < 0){
            f = -1;
        }
        return f;
    }

    @Override
    public boolean equals(Object other){
        if(other == this){
            return true;
        }
        if(ComplexNum.check(other)){
                ComplexNum num = (ComplexNum) other;
                return Double.compare(num.real, this.real) == 0 && Double.compare(num.image, this.image) == 0;
            }
        return false;
    }

    @Override
    public int hashCode() {
        return Objects.hash(real, image);
    }

    public static ComplexNum parse(String str)
    {
        Matcher matcher = Pattern.compile("(\\-?\\d+\\.\\d+)?\\s*([+\\-]?)\\s*(\\d+\\.\\d+)i").matcher(str);

        if (!matcher.find()){
            return null;
        }
        String real = matcher.group(1);
        String oper  = matcher.group(2);
        String imag = matcher.group(3);

        return new ComplexNum(real == null ? 0.0 : Double.parseDouble(real), Double.parseDouble(oper + imag));
    }

    public boolean isReal(){
        return this.real == 0;
    }

    public boolean isImaginary(){
        return this.image == 0;
    }
    
}
