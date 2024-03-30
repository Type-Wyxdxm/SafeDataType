// A great step!
// We finished operator+-*/% (si64) and operator<< >> (si64 << int)
// In CT2.x, we will find a way to finish the changing between int/ll/ull/ui/long ans si64.
// After that, we will possibly try safe_int<int size>.
// Stxq-Yang and I thinks it is a very good exercise for our studies of C++. (Maybe Ye thinks so)
// Let's celebrate it. DONT WORRY ABOUT MY dogshit ENGLISH!
// By the way, since this version, you can use it as a header file.
// 啊啊啊不想敲英语了. 总之是把四则和取余 左右移搞好了. 下一步就是搞标准输入输出流.
// 其实我根本没有好好测试过这些函数的bug, 虽然也没人发现这些代码.
// 关于长整型si(safe_int), 我觉得问题不大. 难点就在于输入输出问题. 不过今天(2024.3.30)从何奇阳那里看到了他写的输入输出, 茅塞顿开.
// 所以这也是我为啥想起来搞用ll和int初始化si64的一大原因.
// 关于未来si64和其他想法的走向, 引用一个编剧的话: "且行且看, 尽力而为".
// 鬼知道中考这离我还有两年远的玩意, 离何奇阳他们还有一年的玩意什么时候要把我的业余时间搞垮.
// 顺带提一嘴, 我已经把所有测试部分迁移了, 理论上从这个版本开始你就能把这玩意当头文件使了.

#include <iostream>
#include <bitset>

#define si64 safe_int64

class safe_int64{
public:
	// 构造函数 & 析构函数 
	safe_int64(){ 
		flowed=0;
		val=0;
	}
	safe_int64(long long vll){
		if(vll<0){
			val=-vll;
			*this = -(*this);
		}
		else val=vll;
		flowed=0;
	}
	safe_int64(int vi){
		if(vi<0){
			val=-vi;
			*this = -(*this);
		}
		else val=vi;
		flowed=0;
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
	
	// 运算 
	safe_int64 operator+(safe_int64 sll){
		safe_int64 ans;
		bool s1=val[63],s2=sll.val[63];
		if(s1&&s2){
			ans = (-(*this))+(-sll);
			if(ans.flowed){
				ans.val=0;
				ans.val[63]=1;
			}else{
				ans = -ans;
			}
			return ans;
		}
		if(s1){
			ans = sll-(-(*this));
			return ans;
		}
		if(s2){
			ans = (*this)-(-sll);
			return ans;
		}
		
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
		bool s1=val[63],s2=sll.val[63];
		if(s1&&s2){
			ans = (-sll)-(-(*this));
			return ans;
		}
		if(s1){
			ans = (-(*this))+sll;
			if(ans.flowed){
				ans.val=0;
				ans.val[63]=1;
			}else{
				ans = -ans;
			}
			return ans;
		}
		if(s2){
			ans = (*this)+(-sll);
			return ans;
		}
		if(sll>(*this)){
			ans = sll-(*this);
			if(ans.flowed){
				ans.val=0;
				ans.val[63]=1;
			}else{
				ans = -ans;
			}
			return ans;
		}
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
	safe_int64 operator/(safe_int64 sll){
		safe_int64 ans,tmp=(*this),ONE;
		bool s1=val[63],s2=sll.val[63];
		if(s1&&s2){
			ans = (-(*this))/(-sll);
			return ans;
		}
		if(s1){
			ans = (-(*this))/sll;
			if(ans.flowed){
				ans.val=0;
				ans.val[63]=1;
			}else{
				ans = -ans;
			}
			return ans;
		}
		if(s2){
			ans = (*this)/(-sll);
			if(ans.flowed){
				ans.val=0;
				ans.val[63]=1;
			}else{
				ans = -ans;
			}
			return ans;
		}
		
		if(sll>(*this)){
			ans.val=0;
			return ans; 
		}
		ONE.val=0;
		ONE.val[0]=1;
		tmp-=sll;
		while(!tmp.val[63]){
			tmp = tmp-sll;
			ans+=ONE;
		}
		return ans;
	}
	safe_int64 operator%(safe_int64 sll){
		safe_int64 ans;
		ans = sll*((*this)/sll);
		ans = (*this)-ans;
		return ans;
	}
	safe_int64 operator<<(int vi){ // 临时替补 si64版 
		if(*this<0) return -((-(*this))<<vi);
		safe_int64 ans;
		ans.val = val<<vi;
		return ans; 
	}
	safe_int64 operator>>(int vi){ // 同上
		if(*this<0) return -((-(*this))>>vi);
		safe_int64 ans;
		ans.val = val>>vi;
		return ans; 
	}
	
	// 比较
	bool operator==(safe_int64 sll){
		for(int i=63;i>=0;i--){
			if(val[i]!=sll.val[i]) return 0;
		}
		return 1;
	}
	bool operator>(safe_int64 sll){
		if(*this==sll) return 0;
		bool s1=val[63],s2=sll.val[63];
		if(s1&&s2){
			return !((-(*this))>(-sll));
		}
		if(s1){
			return 0;
		}
		if(s2){
			return 1;
		}
		
		for(int i=62;i>=0;i--){
			if(val[i]<sll.val[i]) return 0;
			else if(val[i]>sll.val[i]) return 1;
		}
	}
	bool operator<(safe_int64 sll){
		if((!(*this>sll))&&(!(*this==sll))) return 1;
		return 0;
	}
	bool operator!=(safe_int64 sll){
		return !(*this==sll);
	}
	bool operator>=(safe_int64 sll){
		return (*this>sll) || (*this==sll);
	}
	bool operator<=(safe_int64 sll){
		return (*this<sll) || (*this==sll);
	}
	
	// 单目
	safe_int64 operator-(){
		safe_int64 ONE,ans;
		ONE.val=0;
		ONE.val[0]=1;
		if(val[63]){
			ans = *this;
			ans.val[63]=0;
			for(int i=0;i<63;i++){
				ans.val[i] = !val[i];
			}
			ans = ans+ONE;
		}else{
			if(*this == ONE){
				ans.val.set();
				return ans;
			}
			bool is_zero=1;
			ans = *this-ONE;
			for(int i=0;i<64;i++){
				if(ans.val[i]) is_zero=0;
				ans.val[i] = !ans.val[i];
			}
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
	void out(std::string type="d",bool mode=0){
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
			std::cout << val[i];
		}
		if(enter){
			printf("\n");
		}
		return;
	}
	
	// 补充函数 (内置整型转化等)
	void operator=(long long vll){
		val = vll;
		flowed = 0;
	}
	void operator=(int vi){
		val = vi;
		flowed = 0;
	}
	bool operator<(long long vll){
		safe_int64 tmp=vll;
		return *this<tmp;
	}
	bool operator<(int vi){
		safe_int64 tmp=vi;
		out_d(1);
		tmp.out_d(1);
		return *this<tmp;
	}
private:
	std::bitset<64> val;
	bool flowed;
};
