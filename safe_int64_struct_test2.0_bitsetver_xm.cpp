// The same, don't mind my dogshit English
// By the way, the file "safe_int64_struct_test1.0.cpp" is also made by me! After finished that file, I'll type "_xm" to show the file is made by me. 
#include <iostream>
#include <bitset>
using namespace std;

// I chose struct because we need the pointer of struct to realize the input of the value.
struct safe_int64{
	bitset<64> val; // A bitset for saving data. 64bits means it's the same of datatype longlong.
	safe_int64 operator+(safe_int64 sll){ // Realize operator+ in si64! PS:It can only be used when a+b=c(a>=0,b>=0).
		safe_int64 ans;
		char addi=0;
		for(int i=0;i<63;i++){
			char tmp=val[i]+sll.val[i]+addi;
			ans.val[i] = tmp%2;
			addi = tmp/2;
		}
		if(addi){
			ans.val.set();
			ans.val[63]=0;
		}
		return ans;
	} // By the way, I think it looks like the add of High Accuracy Algorithm! Maybe in the future, we can realize safe_int<16>, safe_int<32>, safe_int<64> and so on!
};

// Try to add si64 to si64!
safe_int64 a,b,c;
int main(){
	scanf("%lld %lld",&a,&b);
	c = a+b;
	printf("%lld\n",a+b);
	for(int i=63;i>=0;i--) cout << c.val[i];
}
/*
Add in binary
32 16 8 4 2 1
      1 1 1 1   15
+         1 1    3
    1 0 0 1 0   18 
*/
