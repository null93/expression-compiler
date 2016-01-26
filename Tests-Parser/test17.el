//
// test17.el: syntax error on line 7, missing 2nd operand => "expecting (, VAR, or NUMERIC_LITERAL"
//
base=2;
>>e1>>e2>>e3;
result=(1-2)*((base^e1)^e2^e3)+1*(2/3);
result=1+2^
<<result<<"\n";