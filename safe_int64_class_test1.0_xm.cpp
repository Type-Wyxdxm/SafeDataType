// NOT a header file! Dont include it in your program!
// I typed many tips in this programs before, but for some problems, I can't find them!
// It's a big update of Si64. With technology, we find new ways to realize get and out si64 in class.
// So, we changed it into Class!
// By the way, we finished operator*(a*b,a>=0,b>=0) in si64! 
#include <iostream>
#include <bitset>
using namespace std;

class safe_int64{
public:
	safe_int64(){ 
		flowed=0;
		val=0;
	}
	~safe_int64(){}
	
	safe_int64 operator+(safe_int64 sll){
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
			ans.flowed=1;
		}
		return ans;
	} 
	safe_int64 operator*(safe_int64 sll){
		safe_int64 ans;
		for(int i=0;i<63;i++){
			safe_int64 t;
			if(sll.val[i]){
				int tmp=val[63];
				t.val = val<<i;
				t.val[63]=tmp;
				ans = ans+t;
				if(ans.flowed){
					ans.val.set();
					ans.val[63]=0;
					return ans;
				}
			}
		}
		return ans;
	}
	
	void in(){
		scanf("%lld",&val);
		return;
	}
	void out_d(bool enter=0){
		printf("%lld",val);
		if(enter){
			printf("\n");
		}
		return;
	}
	void out_b(bool enter=0){
		for(int i=63;i>=0;i--){
			cout << val[i];
		}
		if(enter){
			cout << endl;
		}
		return;
	}
private:
	bitset<64> val;
	bool flowed;
};

// try to use si64
safe_int64 a,b,c;
int main(){
	a.in();
	a.out_d(1);
	a.out_b(1);
	b.in();
	c=a*b;
	c.out_d(1);
	c.out_b(1);
}
