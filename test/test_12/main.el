//
// test12.el: semantic error on line 13, "abc_123 undefined"
//

<< "Enter radius>> ";
>> r;

pi = 3.14159;

A = pi*r^2.0;
C = 2*pi*r;

<< "Area: "          << abc_123 << "\n";
<< "Circumference: " << C << "\n";
