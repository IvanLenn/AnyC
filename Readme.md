### Nan in C
Nan: sign * 1 + exp * 11 + frac * 52
Nan requirest exp = 2^12 - 1, and frac != 0

After adding bias, consider top 16 bits:
int: FFFC - FFFF
FFF(1100) - FFF(1111)
ptr: 0000
normalized double: before bias, depending on the sign bits it contains:
0000 - 7FEF and 8000 - FFEF
0000 - 7F(1110)(1111)
after bias:
0001 - 7FF0 and 8001 - FFF0

left tags:
7FF1 - 7FFF and FFF1 - FFFB
equivalently, they are:
0111,1111,1111,0001 - 0111,1111,1111,1111
1111,1111,1111,0001 - 1111,1111,1111,1011

2. I think we can also allow infty, but no longer Nan?
3. Do we extend unsigned int to (real) int with signs (enough tag)? 
4. Do we add other basic types such as bool...?
5. Still confused on line 68: "union Any_real_union union { uint64_t i; double d } u; "
   Not sure why we need it.
