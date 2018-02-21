//
// test04.el: precendence and associativity
//
a=1.5;
b=2;
c=100.0;
d=0.001;

a=a*b*c*d+a-b+c/d*a^2;

<<a<<"\n";

// done //