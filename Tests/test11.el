//
// test11.el: semantic error on line 11, "R undefined"
//

<< "Enter radius>> ";
>> r;

pi = 3.14159;

A = pi*r^2.0;
C = 2*pi*R;

<< "Area: "          << A << "\n";
<< "Circumference: " << C << "\n";
