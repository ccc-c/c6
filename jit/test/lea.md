# lea(load effective address)

* https://stackoverflow.com/questions/46597055/using-lea-on-values-that-arent-addresses-pointers
* https://courses.cs.washington.edu/courses/cse351/17wi/lectures/CSE351-L09-x86-II_17wi.pdf

Example: leaq (%rdx,%rcx,4), %rax

rax = rcx*4+rdx

範例: p = &x[i]; 

=> x+k*i

lea (see Intel's instruction-set manual entry) is a shift-and-add instruction that uses memory-operand syntax and machine encoding. This explains the name, but it's not the only thing it's good for. It never actually accesses memory, so it's like using & in C.