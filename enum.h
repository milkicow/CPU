DEF_CMD(push, 1, 1,
{
    StackPush(&(processor.stk), processor.code[++processor.ip]);
})
DEF_CMD(rpush, 2, 1,
{
    StackPush(&(processor.stk), processor.registr[processor.code[++processor.ip]]);
})
DEF_CMD(mul, 3, 0,
{
    StackPush(&(processor.stk), StackPop(&(processor.stk)) * StackPop(&(processor.stk)));
})
DEF_CMD(pop, 4, 1,
{
    processor.registr[processor.code[++processor.ip]] = StackPop(&(processor.stk));
})
DEF_CMD(rpop, 5, 1,
{
    processor.registr[processor.code[++processor.ip]] = StackPop(&(processor.stk));
})
DEF_CMD(add, 6, 0,
{
    value = StackPop(&(processor.stk));
    StackPush(&(processor.stk), value + StackPop(&(processor.stk)));
})
DEF_CMD(sub, 7, 0,
{
    value = StackPop(&(processor.stk));
    StackPush(&(processor.stk), StackPop(&(processor.stk)) - value);
})
DEF_CMD(out, 8, 0,
{
    value = StackPop(&(processor.stk));
    printf("%lf", value);
})
DEF_CMD(div, 9, 0,
{
    value = StackPop(&(processor.stk));
    StackPush(&(processor.stk), StackPop(&(processor.stk)) / value);
})
DEF_CMD(sqrt, 10, 0,
{
    StackPush(&(processor.stk), sqrt(StackPop(&(processor.stk))));
            
})
DEF_CMD(hlt, -1, 0)