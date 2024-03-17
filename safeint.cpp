/** @mainpage   SafeInt Library
* <table>
* <tr><th> Project <td> SafeInt
* <tr><th> Author  <td> He Q.Y. Hong X.Y.
* </table>
* @section  项目描述
* 利用bitset实现安全的高精度整数
*
* @section 功能描述
* 可以设置SafeInt的位数，并且进行四则运算，完成高精度操作
*
* @section 用法描述
* @par 示例
* @code
* #include <iostream.h>
* #include "safeint.h"
* int main(){
*     SafeInt<128> a,b,c;
*     a.read();
*     b.fromString("123456");
*     std::cin>>c;
*     SafeInt<128> d=a*b/c;
*     SafeInt<128> n=a+b-c;
*     SafeInt<128> m=(a+b)%c;
*     d.write();
*     printf("\n%s\n",n.tostring().c_str());
*     std::cout<<m<<std::endl;
*     return 0;
* }
* @endcode
* @section 更新日志
* <table>
* <tr><th> Date         <th>Version     <th>Author      <th>Description </tr>
* <tr><td>2024/03/09    <td> 1.0        <td>Hong X.Y.   <td>创建项目    </tr>
* <tr><td>2024/03/10    <td> 1.1        <td>He Q.Y.     <td>提交架构    </tr>
* <tr><td>2024/03/17    <td> 1.2        <td>He Q.Y.     <td>完成部分实现 </tr>
* </table>
*/
#include "safeint.h"
#include <cmath>
/**
* @brief 从标准的整数构造SafeInt,默认为0
*
* @param _val 标准整数(64bits)
*/
template<int n>
SafeInt<n>::SafeInt(const long long _val){
    val=abs(_val);
    if (_val<0){
       opposite();
    }
}

/**
* @brief bitset构造SafeInt
*
* @param _val 长度为n的bitset，直接拷贝至val
*/
template<int n>
SafeInt<n>::SafeInt(const std::bitset<n>_val){
    val=_val;
}

/**
* @brief 由字符串输入SafeInt
*
* @param s 输入的字符串
*/
template<int n>
void SafeInt<n>::fromstring(const std::string &s){

}

/**
* @brief 从控制台输入SafeInt
*/
template<int n>
void SafeInt<n>::read(){

}

/**
* @brief 把SafeInt转为字符串
*
* @return 返回一个数字字符串，与SafeInt储存的值一致
*/
template<int n>
std::string SafeInt<n>::tostring() const{

}

/**
* @brief 输出SafeInt的值
*/
tmeplate <int n>
void SafeInt<n>::print(){

}

/**
* @brief 直接获得bitset val的值
*
* @return 返回bitset，即val的直接值
*/
template <int n>
std::bitset<n> SafeInt<n>::getVal() const{
    return val;
}

/**
* @brief 设置bitset val的值
*
* @param _val 新的val值
*/
template <int n>
void SafeInt<n>::setVal(std::bitset<n> _val){
    val=_val;
}

/**
* @brief 这个数设置为自己的相反数
* @details 可以将自己设为自己的相反数，重点在于补码和反码的转换
* 通过与-1或+1，实现转换。对于负数，得到反码后只需要取反得到原码，
* 正数反之亦然
*/
template <int n>
void SafeInt<n>::opposite(){
    //检测原数的符号
    if (!val[0]){
        //正数，符号位取反同时取反码
        val.flip();
        /*
        a 1的值
        _val 暂存补码的值
        */
        std::bitset<n>a=1,_val;
        // 进位标志
        bool car=0;
        // 模拟加法，_val=val+1
        for (int i=n-1;i>=0;i--){
            _val[i]=val[i]!=a[i]!=car;
            car=val[i]&&a[i]&&car;
        }
        //如果未溢出，则更新val
        if (_val[0])val=_val;
        else 
            //溢出，则撤销取反操作
            val.flip()
    }else{
        //负数，则先减去一，得到反码
        /*
        a，b储存1
        _a 存储a的相反数，即-1
        _val 暂存val的原码
        */
        std::bitset<n>a=1,b=1,_a,_val;
        // 取a的相反数，先取反码
        a.flip();
        // 进位标志
        bool car=0;
        //类似前面，不再解释
        for (int i=n-1;i>=0;i--){
            _a[i]=a[i]!=b[i]!=car;
            car=a[i]&&b[i]&&car;
        }
        //如果溢出、操作直接结束（理论上不可能）
        if (!a[0])return;
        //将进位标志设置为0
        car=0;
        //同样，模拟加法_val=val+_a=val-1
        for (int i=n-1;i>=0;i--){
            _val[i]=val[i]!=_a[i]!=car;
            car=val[i]&&_a[i]&&car;
        }
        //如果没有溢出，更新val的值
        if (!val[0]) val=_val;
        else
            //如果溢出，结束操作
            return;
        val.flip();
    }
}

/**
* @brief 为两个SafeInt重载求和
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a+b的和
*/
template<int n>
SafeInt<n> operator+(const SafeInt<n>& a,const SafeInt<n>& b){

}

/**
* @brief 为两个SafeInt重载求差
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a-b的差
*/
template<int n>
SafeInt<n> operator-(const SafeInt<n>& a,const SafeInt<n>& b){

}

/**
* @brief 为两个SafeInt重载求乘积
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a*b的积
*/
template<int n>
SafeInt<n> operator*(const SafeInt<n>& a,const SafeInt<n>& b){

}

/**
* @brief 为两个SafeInt重载求商
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a/b的商
*/
template<int n>
SafeInt<n> operator/(const SafeInt<n>& a,const SafeInt<n>& b){

}

/**
* @brief 为两个SafeInt重载求模
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a%b的值
*/
template<int n>
SafeInt<n> operator%const SafeInt<n>& a,const SafeInt<n>& b){

}

/**
* @brief 为一个SafeInt和一个标准整数重载求和
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a+b的和
*/
template<int n>
SafeInt<n> operator+(const SafeInt<n>& a,const long long& b){

}

/**
* @brief 为一个SafeInt和一个标准整数重载求差
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a-b的差
*/
template<int n>
SafeInt<n> operator-(const SafeInt<n>& a,const long long& b){

}

/**
* @brief 为一个SafeInt和一个标准整数重载求积
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a*b的积
*/
template<int n>
SafeInt<n> operator*(const SafeInt<n>& a,const long long& b){

}

/**
* @brief 为一个SafeInt和一个标准整数重载求商
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a/b的商
*/
template<int n>
SafeInt<n> operator/(const SafeInt<n>& a,const long long& b

}

/**
* @brief 为一个SafeInt和一个标准整数重载求商
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a%b的值
*/
template<int n>
SafeInt<n> operator%(const SafeInt<n>& a,const long long& b){

}
/**
* @brief 从输入流输入SafeInt
*
* @param in 输入流
* @param b 储存输入的数
*
* @return 返回输入后的输入流
*/
template<int n>
std::istream& operator>>(std::istream &in, SafeInt<n> &b){

}

/**
* @brief 向输出流输出SafeInt
*
* @param out 输出流
* @param b 要被输出的数
*
* @return 返回输出后的输出流
*/
template<int n>
std::ostream& operator<<(std::ostream &in, const SafeInt<n> &b){

}
