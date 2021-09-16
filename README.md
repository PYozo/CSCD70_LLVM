# CSCD70_LLVM
LLVM learn\n
##Assignment1-introduction_to_LLVM
在写Multi-Instruction Optimization的优化时，遇到了一点小问题，本来打算利用vector每次都遍历Instruction的，但当我写到一半时，发现这是不行的，不过通过后续的编译原理学习，发现可以通过可用表达式和活跃变量来达到该效果，这两种方法是通过遍历某个Block里的指令，并将每次指令的更新都记录到一个容器中，所以在每次扫描到相关Add或者Sub指令时，都会遍历一遍容器，查看其变量是否可以进行优化，如果可以则直接进行优化替换

