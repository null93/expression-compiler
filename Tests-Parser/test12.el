//
// test16.el: syntax error on line 12, invalid comment -> "expecting EOT"
//

>> a >> b;

c = a-b/
    b+a;

<< "The length of the hypotenuse is ";

c = (a^2+b^2)^0.5; / bad comment

<< "Done!" << "\n";
