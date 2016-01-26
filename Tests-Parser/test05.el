//
// test05.el: exhaustive test of language
//

<< "Hello, this is test " << 05 << "\n" << "\n";

a = 0
;
b = 0.0
;
c = 000.000
;
e1 = 3.14159
;

>>a>>b>>c>>d>>e1// let's get some input:
;

e123_456
=
a
+
b
-
c
+
d
-
e1
;

f123_
=
e123_456
*
e123_456
*
3.14159
/
2
/
e123_456
*
e1
;

<<
a
<<
b
<<
c
<<
d
<<
e1
<<
e123_456
<<
f123_
<<
3.1
<<
0
<<
"\n"
;

a=a*b-c^d^e1/2-f123_;

<< "\n" << "Done!" << "\n" << "\n";

//
// done
//