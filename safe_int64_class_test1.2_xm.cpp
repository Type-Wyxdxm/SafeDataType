// si64_classtest_1.2 : a test of the new brench "Type-Wyxdxm_Version"
// some easy functions such as += -= *= = and * for negative and si64.Out("Type",if_endl);
// 懒得把英文注释写下去了. 把+=这种大致直接copy四则的搞上去了,再把整数乘法搞定.
// 新东西不多, 主要是测试新分支.
// 哦, 顺便搞了个输出的整合版.
// 没好好测试过, 有bug再说.

#include <iostream>
#include <bitset>
using namespace std;

class safe_int64{
public:
	// 构造函数 & 析构函数 
	safe_int64(){ 
		flowed=0;
		val=0;
	}
	~safe_int64(){}
	
	//赋值
	void operator=(safe_int64 sll){
		val = sll.val;
		flowed = sll.flowed;
		return;
	}
	void operator+=(safe_int64 sll){
		*this = *this + sll;
		return;
	}
	void operator-=(safe_int64 sll){
		*this = *this - sll;
		return;
	}
	void operator*=(safe_int64 sll){
		*this = *this * sll;
		return;
	}
	
	// 四则 
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
	safe_int64 operator-(safe_int64 sll){
		safe_int64 ans;
		char subi=0;
		for(int i=0;i<63;i++){
			int tmp=subi+sll.val[i];
			if(tmp>val[i]){
				subi = 1;
				ans.val[i] = val[i]+2-tmp;
			}else{
				subi = 0;
				ans.val[i] = val[i]-tmp;
			}
		}
		return ans;
	} 
	safe_int64 operator*(safe_int64 sll){
		safe_int64 ans;
		bool s1=val[63],s2=sll.val[63];
		if(s1&&s2){
			ans = (-(*this))*(-sll);
			return ans;
		}
		if(s1){
			ans = (-(*this))*sll;
			if(ans.flowed){
				ans.val=0;
				ans.val[63]=1;
			}else{
				ans = -ans;
			}
			return ans;
		}
		if(s2){
			ans = (*this)*(-sll);
			if(ans.flowed){
				ans.val=0;
				ans.val[63]=1;
			}else{
				ans = -ans;
			}
			return ans;
		}
		for(int i=0;i<63;i++){
			safe_int64 t;
			if(sll.val[i]){
				int tmp=val[63];
				t.val = val<<i;
				t.val[63]=tmp;
				ans = ans+t;
				if(ans.flowed){
					ans.val.set();
					ans.val[63] = 0;
					return ans;
				}
			}
		}
		return ans;
	}
	
	// 单目
	safe_int64 operator-(){
		safe_int64 ONE,ans;
		ONE.val[0]=1;
		if(val[63]){
			ans = *this;
			ans.val[63]=0;
			for(int i=0;i<63;i++){
				ans.val[i] = !val[i];
			}
			ans = ans+ONE;
		}else{
			bool is_zero=1;
			ans = *this;
			for(int i=0;i<64;i++){
				if(val[i]) is_zero=0; 
				ans.val[i] = !val[i];
			}
			ans = ans+ONE;
			ans.val[63]=1;
			if(is_zero) return *this;
		}
		return ans;
	}
	
	// 输入输出 
	void in(){
		scanf("%lld",&val);
		return;
	}
	void out(string type="d",bool mode=0){
		if(type=="d"){
			out_d(mode);
		}
		if(type=="b"){
			out_b(mode);
		}
		if(type=="a"){
			out_d(1);
			out_b(mode);
		}
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

safe_int64 a,b,c;
int main(){
	a.in();
	b.in();
	c = a*b;
	a.out("a",1);
	b.out("a",1);
	c.out("a",1);
}
