import math
def howManyTakeMethods(victim_count):
	assert victim_count>0,"victim_count must great than 0"
	sum=0
	#注意range(start,stop)返回的是 [start,stop)，为了包含stop，需要加1
	for i in range(1,victim_count+1):
		sum+=combinationCount(victim_count,i)
	return sum

def combinationCount(n,k):
	assert n>0
	assert k>0
	if k>n:
		return 0
	result=math.factorial(n)/(math.factorial(k)*math.factorial(n-k))
	return result

def main():
	for i in range(1,11):
		takeMethods=howManyTakeMethods(i)
		print("victim_count=%d,takeMethods:%d"%(i,takeMethods))

if __name__ == '__main__':
	main()