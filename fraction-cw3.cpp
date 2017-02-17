
#include <iostream>
#include <cmath>

using namespace std;

/******************* Class declaration *******************/

class fraction {
    friend ostream &operator<< (ostream &os, const fraction &f);
public:
    fraction(int n = 0,int d = 1):numerator(n), denominator(d){
        reduce();
    };
    
    //overload double operator
    operator double(){ return 1.0*numerator/denominator; };

    //fraction1 +,-,*,/ fraction2
    fraction operator+ (const fraction &f) const;
    fraction operator- (const fraction &f) const;
    fraction operator* (const fraction &f) const;
    fraction operator/ (const fraction &f) const;
    
    //fraction +,-,*,/ integer
    fraction operator+ (const int i) const;
    fraction operator- (const int i) const;
    fraction operator* (const int i) const;
    fraction operator/ (const int i) const;
    
    //integer +,-,*,/ fraction
    friend fraction operator+ (const int i, const fraction &f){
        return f+i;
    };
    friend fraction operator* (const int i, const fraction &f){
        return f*i;
    };
    friend fraction operator- (const int i, const fraction &f){
        fraction k0 = f-i,k;
        k = k0 * (-1);
        return k;
    };
    friend fraction operator/ (const int i, const fraction &f){
        fraction k;
        k.numerator = i * f.denominator;
        k.denominator = f.numerator;
        if (k.denominator<0){
            k.numerator = -k.numerator;
            k.denominator = -k.denominator;
        } //keep denominator positive
        return k;
    };
    
    //fraction1 +=,-=,*=,/= fraction2
    fraction &operator+= (const fraction &f);
    fraction &operator-= (const fraction &f);
    fraction &operator*= (const fraction &f);
    fraction &operator/= (const fraction &f);
    
    //fraction1 <,>,<=,>=,!=,== fraction2
    bool operator< (const fraction &f) const;
    bool operator> (const fraction &f) const;
    bool operator<= (const fraction &f) const;
    bool operator>= (const fraction &f) const;
    bool operator!= (const fraction &f) const;
    bool operator== (const fraction &f) const;
    
    //fraction <,>,<=,>=,!=,== double integer
    bool operator< (const double d) const;
    bool operator> (const double d) const;
    bool operator<= (const double d) const;
    bool operator>= (const double d) const;
    bool operator!= (const double d) const;
    bool operator== (const double d) const;
    
    fraction operator- () const;
    
private:
    int numerator, denominator;
    void reduce();
};

/*********************************************************/
/********** Define the member functions ******************/

std::ostream &operator<< (ostream &os, const fraction &f){
    if (f.denominator!=1 && f.numerator!=0)
        return os<<f.numerator<<"/"<<f.denominator;
    else
        return os<<f.numerator<<endl;
}

//simplify the fraction
void fraction::reduce(){
    
    //check for error
    if (denominator==0){
        cout<<"Illegal denominator!"<<endl;
        exit(EXIT_FAILURE);
    }
    
    //make the denominator always positive
    if (denominator<0){
        denominator = -denominator;
        numerator = -numerator;
    }
    
    //find the largest common divisor n
    int temp;
    int n = abs(numerator);
    int d = abs(denominator);
    if (n<d){
        temp = n;
        n = d;
        d = temp;
    }
    while (d!=0){
        temp = n%d;
        n = d;
        d = temp;
    }
    
    //thus get the simplified fraction
    numerator /= n;
    denominator /= n;
}


fraction fraction::operator- () const {
    fraction k(-numerator, denominator);
    return k;
};


fraction fraction::operator+ (const fraction &f) const {
    fraction k;
    k.numerator = numerator * f.denominator + f.numerator * denominator;
    k.denominator = denominator * f.denominator;
    k.reduce();
    return k;
}
fraction fraction::operator- (const fraction &f) const {
    fraction k;
    k.numerator = numerator * f.denominator - f.numerator * denominator;
    k.denominator = denominator * f.denominator;
    k.reduce();
    return k;
}
fraction fraction::operator* (const fraction &f) const {
    fraction k;
    k.numerator = numerator * f.numerator;
    k.denominator = denominator * f.denominator;
    k.reduce();
    return k;
}
fraction fraction::operator/ (const fraction &f) const {
    fraction k;
    k.numerator = numerator * f.denominator;
    k.denominator = denominator * f.numerator;
    k.reduce();
    return k;
}
fraction fraction::operator+ (const int i) const {
    fraction k;
    k.numerator = i * denominator + numerator;
    k.denominator = denominator;
    k.reduce();
    return k;
}
fraction fraction::operator- (const int i) const {
    fraction k;
    k.numerator = numerator - i * denominator;
    k.denominator = denominator;
    k.reduce();
    return k;
}
fraction fraction::operator* (const int i) const {
    fraction k;
    k.numerator = i * numerator;
    k.denominator = denominator;
    k.reduce();
    return k;
}
fraction fraction::operator/ (const int i) const {
    fraction k;
    k.numerator = numerator;
    k.denominator = i * denominator;
    k.reduce();
    return k;
}


fraction& fraction::operator+= (const fraction &f){
    return *this = (*this + f);
};
fraction& fraction::operator-= (const fraction &f){
    return *this = (*this - f);
};
fraction& fraction::operator*= (const fraction &f){
    return *this = (*this * f);
};
fraction& fraction::operator/= (const fraction &f){
    return *this = (*this / f);
};


bool fraction::operator< (const fraction &f) const {
    int the_nume, f_nume;
    f_nume = f.numerator * denominator;
    the_nume = numerator * f.denominator;
    return (the_nume<f_nume);
}
bool fraction::operator> (const fraction &f) const {
    int the_nume, f_nume;
    f_nume = f.numerator * denominator;
    the_nume = numerator * f.denominator;
    return (the_nume>f_nume);
}
bool fraction::operator<= (const fraction &f) const {
    int the_nume, f_nume;
    f_nume = f.numerator * denominator;
    the_nume = numerator * f.denominator;
    return (the_nume<=f_nume);
}
bool fraction::operator>= (const fraction &f) const {
    int the_nume, f_nume;
    f_nume = f.numerator * denominator;
    the_nume = numerator * f.denominator;
    return (the_nume>=f_nume);
}
bool fraction::operator!= (const fraction &f) const {
    int the_nume, f_nume;
    f_nume = f.numerator * denominator;
    the_nume = numerator * f.denominator;
    return (the_nume!=f_nume);
}
bool fraction::operator== (const fraction &f) const {
    int the_nume, f_nume;
    f_nume = f.numerator * denominator;
    the_nume = numerator * f.denominator;
    return (the_nume==f_nume);
}


bool fraction::operator< (const double d) const {
    double b = 1.0*numerator/denominator;
    return b<d;
}
bool fraction::operator> (const double d) const {
    double b = 1.0*numerator/denominator;
    return b>d;
}
bool fraction::operator<= (const double d) const {
    double b = 1.0*numerator/denominator;
    return b<=d;
}
bool fraction::operator>= (const double d) const {
    double b = 1.0*numerator/denominator;
    return b>=d;
}
bool fraction::operator!= (const double d) const {
    double b = 1.0*numerator/denominator;
    return b!=d;
}
bool fraction::operator== (const double d) const {
    double b = 1.0*numerator/denominator;
    return b==d;
}

/*********************************************************/
/********** main function (test algorithms) **************/

int main() {

    fraction a(1,12), b(1,25), c(1,300), e(3,4), f(2,5), g(7,2), h;
    cout << a << " + " << b << " + " << c << " = " << a+b+c << endl;
    if (-a < b) cout << -a << " < " << b << endl;
    else cout << -a << " >= " << b << endl;
    h = e*f-g;
    cout << e << " * " << f << " - " << g << " = " << h << endl;
    fraction i(-1,6), j(5,17), k(3,5);
    cout << i << " + " << j << " / " << k << " = " << i+j/k << endl;
    int m = 2, q = 1;
    fraction n(1,3), p(4,5), s(a), t(b), u(c), w(e), x(f), y(g), v, z;
    cout << m << " + " << n << " = " << m+n << endl;
    cout << p << " - " << q << " = " << p-q << endl;
    v = (a+=b-=u);
    cout << s << " += " << t << " -= " << u << " = " << v << endl;
    z = (e*=f/=g);
    cout << w << " *= " << x << " /= " << y << " = " << z << endl;
    double d = e;
    if (d < f) cout << d << " < " << f << endl;
    else cout << d << " >= " << f << endl;
   
    return 0;
}
