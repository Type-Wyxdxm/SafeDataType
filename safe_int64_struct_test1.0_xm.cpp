// NOT a header file, it's only a test!
// Don't mind my dogshit English
// I tried to realize safe_int64 with struct, but there are still many problems. 
#include <iostream>
using namespace std;

struct safe_int64{
	bool val[8];
};
safe_int64 a;

int main(){
  // Get a.
	scanf("%lld",&a);
  // print the number as "a1 a2 a3 a4 a5 a6 a7 a8", 0<= an <= 255, "n n 0 0 0 0 0 0" means (n*255^0)+(n*255^1).
	for(int i=7;i>=0;i--) cout << a.val[i] << ' ';
	return 0;
}
