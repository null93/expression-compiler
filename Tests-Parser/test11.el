//
// test17.el: syntax error on line 10, extra + => "expecting EOT"
//
base=2;
>>e1;
>>e2;
>>e3;
result=1+base^e1^e2^e3-1;//1+(base^(e1^(e2^e3)))-1
<<result<<"\n";
+