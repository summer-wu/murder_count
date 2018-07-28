//
//  main.m
//  murder_count
//
//  Created by n on 27/07/2018.
//  Copyright © 2018 summerwuOrganization. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
typedef	unsigned int uint;

uint combinationCount(uint totalCount,uint selectCount);
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
//        sum+=combinationCount(totalCount,i);
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

/*
有totalCount个球，取出selectCount个，不重复的组合有几个？
如ABC，其中AB跟BA是相同的组合，可能的组合有AB、AC、BC
一开始不记得Cnk的公式，用代码找出所有的组合个数：
C(n,1)=>n
C(n,2)=>(n-1)+...+1
C(n,3)=>f(n-1,2)+f(n-2,2)+...+f(1,2)
C(n,k)=>f(n-1,k-1)+f(n-2,k-2)+...+f(1,k-2)
*/
uint combinationCount(uint totalCount,uint selectCount){
    assert(selectCount>0);
    assert(totalCount>0);

    uint result = 0;
    if (totalCount<selectCount) {
        result = 0;
    }

    if(1==selectCount){
        result = totalCount;
    } else if (2==selectCount){
        uint sum=0;
        for (uint i=1;i<=totalCount-1;i++){
            sum+=i;
        }
        result = sum;
    } else {
        uint sum=0;
        for (uint i=1;i<totalCount;i++){
            sum+=combinationCount(totalCount-i, selectCount-1);
        }
        result = sum;
    }

//    printf("combinationCount %d %d=>%d\n",totalCount,selectCount,result);
    return result;
}
