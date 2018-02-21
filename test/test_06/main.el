//
// test06.el: expressions...
//
>>e1>>e2>>e3;
result=1+2^e1^e2^e3-1;
<<result<<"\n";

a=1.5;
b=2;
c=100.0;
d=0.001;
a=a*b*c*d+a-b+c/d*a^2;
<<a<<"\n";
