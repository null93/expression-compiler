//
// test03.el: raising to a power is right-associative
//
base=2;
>>e1;
>>e2;
>>e3;
result=1+base^e1^e2^e3-1;//1+(base^(e1^(e2^e3)))-1
<<result<<"\n";