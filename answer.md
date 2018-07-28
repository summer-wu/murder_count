# answer 答案

## 思路
+ 最简单的，抓1001个，每人看一个；哪个人死了，那么他看的盒子就是杀人盒。
+ 再进一步，实际上抓1000个也可以。如果没人死，那么最后的盒子就是杀人盒。
+ 还能不能再少抓一些人？
+ 似乎不行了，1个盒子必须明确对应1个人！如果张三看多个盒子，然后张三死了，无法确定哪个是杀人盒。（下面的思考会证明这条思路是错的）
+ 用极限法试一下：
+ 假设总共2个盒子（1个杀人盒1个普通盒），最少抓1个人
+ 假设总共3个盒子（1个杀人盒2个普通盒），最少抓2个人
+ 假设总共4个盒子（1个杀人盒3个普通盒），最少抓几个人？3个人？好像抓2个人也行啊！
+ 给盒子贴上标签，从1到4，就像房间号一样。受害者甲看1，受害者乙看2，甲乙同时看3，没有人看4。注意：这里利用了 victim甲 两次。
+ 可能出现的情况是：甲死、乙死、甲乙同时死、没人死。所以：总共4个盒子时，最少抓2个人。
+ 假设总共5个盒子，最少抓3个人
+ 用极限法发现：肯定有小于1000的答案。
+ 找规律：2个受害者可以满足2个普通盒（总共3个盒子）的情况；3个受害者可以满足8个普通盒（总共9个盒子）的情况。4个受害者可以满足x个普通盒的情况
+ 现在题目可以简化了：有n个受害者，可以提取1个、2个...n个，共有多少种提取方式？设有t种提取方式，t>=1000时就满足要求。
+ 写一个函数，叫`int howManyTakeMethods(int victimCount)`。（传入受害者数量n，返回提取方式个数t）
+ 函数的过程就是 Cn1+Cn2+Cn3+...+Cnn。（这里Cn1表示高中数学的排列组合）

## 程序代码（C语言）
```
#include <stdio.h>
#include <assert.h>
typedef	unsigned int uint;

uint factorial(uint x);
uint howManyTakeMethods(uint victim_count);
uint combinationCount_math(uint n,uint k);

int main(int argc, const char * argv[]) {
    for (uint i=1;i<=10;i++){
        uint takeMethods = howManyTakeMethods(i);
        printf("%d个受害者，提取方式%d种\n",i,takeMethods);
    }
    return 0;
}

//传入受害者数量，返回提取方式个数
uint howManyTakeMethods(uint victim_count){
    assert(victim_count>0);
    uint sum = 0;
    for (uint i=1; i<=victim_count; i++) {
        sum+=combinationCount_math(victim_count, i);
    }
    return sum;
}

uint factorial(uint x){
    assert(x>=0);
    uint result = 1;
    for (uint i=1; i<=x; i++) {
        result *= i;
    }
    return result;
}

// 从n个元素中取出k个，不考虑顺序，有多少种取法？这是高中数学，排列组合公式。
// 公式为 Cnk=n!/(k!*(n-k)!)
uint combinationCount_math(uint n,uint k){
    assert(n>0);
    assert(k>0);
    if (k>n) {
        return 0;
    }
    uint result = factorial(n)/(factorial(k)*factorial(n-k));
    return result;
}

```

## 程序输出
```
1个受害者，提取方式1种
2个受害者，提取方式3种
3个受害者，提取方式7种
4个受害者，提取方式15种
5个受害者，提取方式31种
6个受害者，提取方式63种
7个受害者，提取方式127种
8个受害者，提取方式255种
9个受害者，提取方式511种
10个受害者，提取方式1023种
```
所以最终答案是只需要抓10个人。

## 结果分析
+ x个受害者，提取方式有2^x-1个。
+ 如3个受害者，提取方式有2^3-1=7个。
+ 原来每个提取方式都对应了一个二进制数！
+ 给7个盒子贴上标签1-7，三个受害者分别代表二进制的一位。下表中0表示不看，1表示看，受害者死亡后查表可以找到杀人盒。

```
盒子编号  001 002 003 004 005 006 007
受害者排序001 010 011 100 101 110 111

注意:这里不能出现000！000表示都不看。
```
如 甲丙同时死亡，那么005盒子是杀人盒。

