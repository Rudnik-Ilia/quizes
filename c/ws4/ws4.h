
#ifndef __WS4_H__
#define __WS4_H__
typedef void (*p_func)();
int PrintAT_IF();
int PrintAT_SWITCH();
void SpecialFuncA();
void SpecialFuncB();
void SpecialFuncQ();
p_func *FillArray(p_func arrayFunc[], p_func func);
p_func *FillArraySpecial(p_func arrayFunc[], p_func func, int num);

void Function();


#endif


