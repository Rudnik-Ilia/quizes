package il.com.ilrd.complexNum;

import com.sun.xml.internal.ws.message.stream.StreamHeader;

public class ComplexNum implements Comparable{
    private double real;
    private double image;

    public ComplexNum() {
    }

    public ComplexNum(double real, double image) {
        this.real = real;
        this.image = image;
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
        ComplexNum tmp = (ComplexNum) other;
        if(100*this.magnitude()/100.0f == Math.floor(100*tmp.magnitude()/100.0f)) {
            return 1;
        }
        return 0;
    }
}
