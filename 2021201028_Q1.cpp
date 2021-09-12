
// Author  :-> Aman Izardar
// Email   :-> aman.izardar@students.iiit.ac.in
// Roll NO :-> 2021201028

// This is the submission for the Q1 of the assignment i.e. 

// :::::::::::::::::::::::: BIG INTEGER LIBRARY IMPLEMENTATION :::::::::::::::::::::::::::



#include<iostream>
#include<string>
#include<algorithm>
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define phi 3.1415926536
#define mod 1000000007
#define MAX 5000000
using namespace std;


//Code Section : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : :


template<class T>
class mystack
{
    T a[MAX];
    int topp;
    
    public:

    mystack()
    {
        topp=-1;
    }

    void push(T val)
    {
        if(topp==MAX)
            cout<<"STACK OVERFLOW";

        topp++;
        a[topp]=val;
    }

    T top()
    {
        T val=a[topp];
        return val;
    }
    void pop()
    {
        topp--;
    }
    bool empty()
    {
        if(topp==-1)
            return true;
        else
            return false;
    }

    
};




class Bigint
{
    string s;

    public:

    Bigint()
    {
       
    }

    Bigint(string s1)
    {

        string ans2;
        int l=0;
        for(ll i=0;i<s1.length();i++)
        {
            if(s1[i]=='0' and l==i)
                ++l;
            else
                ans2+=(s1[i]);
        }
        if(l==s1.length())
            ans2="0";
 
        s=ans2;
    }

    Bigint(ll a)
    {
        s=to_string(a);
    }
    Bigint(const char * a)
    {
        string s1(a);
        s=s1;
    }


friend ostream& operator <<(ostream &os ,const Bigint &num);
friend istream& operator >>(istream &os ,Bigint &num);

string sum(string s,string s2)
{
    if(s=="0" and s2=="0")
        return "0";
    if(s=="0")
        return s2;
    if(s2=="0")
        return s;
    ll n=s.length()-1;
    ll m=s2.length()-1;
    int carry=0;
    string ans;

    if(n>=m)
    {
        while(m>=0)
        {
            int sum=(s[n]-'0')+(s2[m]-'0')+carry;
            ans+=((sum%10)+'0');
            carry=sum/10;
            n--,m--;
        }
        while(n>=0)
        {
            int sum=(s[n]-'0')+carry;
            ans+=((sum%10)+'0');
            carry=sum/10;
            n--;
        }
        while(carry)
        {
            ans+=(carry%10+'0');
            carry/=10;
        }
        reverse(ans.begin(),ans.end());
    }

    else
    {
        while(n>=0)
        {
            int sum=(s[n]-'0')+(s2[m]-'0')+carry;
            ans+=((sum%10)+'0');
            carry=sum/10;
            n--,m--;
        }
        while(m>=0)
        {
            int sum=(s2[m]-'0')+carry;
            ans+=((sum%10)+'0');
            carry=sum/10;
            m--;
        }
        while(carry)
        {
            ans+=(carry%10+'0');
            carry/=10;
        }
        reverse(ans.begin(),ans.end());
    }

    return ans;

}

string sub(string s,string s2)
{
    ll n=s.length()-1;
    ll m=s2.length()-1;
    int borrow=0;
    string ans;
    int diff=0;

    while(m>=0)
    {
        if((s[n]-'0')>=(s2[m]-'0'))
        {
            diff=(s[n]-'0')-(s2[m]-'0')-borrow;
            borrow=0;
        }
        else
        {
            diff=10+(s[n]-'0')-(s2[m]-'0')-borrow;
            borrow=1;
        }
        ans+=(abs(diff)+'0');
        n--,m--;
    }
    while(n>=0)
    {
        diff=(s[n]-'0')-borrow;
        ans+=(abs(diff)+'0');
        borrow=(diff<0)?1:0;
        n--;
    }
    reverse(ans.begin(),ans.end());

    string ans2;
    int l=0;
    for(ll i=0;i<ans.length();i++)
    {
        if(ans[i]=='0' and l==i)
            ++l;
        else
            ans2+=(ans[i]);
    }
    if(l==ans.length())
        return "0";
    
    return ans2;
}

string mul(string s,string s2)
{
    ll n=s.length()-1;
    ll m=s2.length()-1;
    int arr[n+m+2];

    for (ll i = 0; i < n+m+2; ++i)
        arr[i]=0;

    for(ll i=n;i>=0;i--)
    {
        for(ll j=m;j>=0;j--)
        {
            arr[i+j+1]+=(s[i]-'0')*(s2[j]-'0');
        }
    }
    
    for(ll i=n+m+1;i>=0;i--)
    {
        if(arr[i]>=10)
        {
            arr[i-1]+=arr[i]/10;
            arr[i]=arr[i]%10;
        }
    }

    
    
    string ans;
    int l=0;
    for(ll i=0;i<=n+m+1;i++)
    {
        if(arr[i]==0 and l==i)
            ++l;
        else
            ans+=(arr[i]+'0');
    }
    return ans;
}



string div(string num11,string other)
{
    // cout<<"first no is "<<num11<<" "<<"second no. is "<<other<<endl;

    if(num11==other)
        return "1";
    if(num11.length()<other.length())
        return "0";

    string result="";
    string num1=num11;
    string num2=other;
    int select=num2.length();
    string temp=num1.substr(0,select);
    Bigint tempnum=temp;
    int numberleft=num1.length()-temp.length();
    Bigint mulob="1";
    Bigint othernum=other;

    if(tempnum<othernum)
    {
        temp=num1.substr(0,select+1);
        tempnum=temp;
        numberleft--;
        select++;
    }
    int flag=0;

    do
    {
        mulob="0";
        int index=0;
        while(othernum*mulob<=tempnum)
        {
            index++;
            mulob=index;
        }
        index--;
        mulob=index;
        Bigint minus=tempnum-(othernum*mulob);
        string carry=minus.s;
        if(carry=="0"){
            flag=1;
        }
        result+=(index+'0');
        if(numberleft>0)
        {
            select++;
            carry+=num1[select-1];
            flag=0;
            numberleft--;
        }
        
      
        tempnum=carry;

    }while(numberleft>0);

   

    if(tempnum.s=="0" and flag!=1)
        result+='0';


    if(othernum>tempnum)
        return result;

    mulob="0";
    int index=0;
    while(othernum*mulob<=tempnum)
    {
        index++;
        mulob=index;
    }
    index--;
    mulob=index;
    Bigint carry=tempnum-(othernum*mulob);
    if(numberleft>0)
    {
        select++;
        carry.s+=num1[select-1];
        numberleft--;
    }
    result+=(index+'0');
    tempnum=carry;
    
    return result;

}



string remainder(string num11,string other)
{
    if(other=="1" or num11==other)
        return "0";

    
    if(num11.length()<other.length())
    {
        return num11;
    }

    string result="";
    string num1=num11;
    string num2=other;
    int select=num2.length();
    string temp=num1.substr(0,select);
    Bigint tempnum=temp;
    int numberleft=num1.length()-temp.length();
    Bigint mulob="1";
    Bigint othernum=other;

    if(tempnum<othernum)
    {
        temp=num1.substr(0,select+1);
        tempnum=temp;
        numberleft--;
        select++;
    }

    do
    {
        mulob="0";
        int index=0;
        while(othernum*mulob<=tempnum)
        {
            index++;
            mulob=index;
        }
        index--;
        mulob=index;
        Bigint carry=tempnum-(othernum*mulob);

        if(numberleft>0)
        {
            select++;
            carry.s+=num1[select-1];
            numberleft--;
        }
        result+=(index+'0');
        tempnum=carry.s;
    }while(numberleft>0);

    if(othernum>tempnum)
        return tempnum.s;

    mulob="0";
    int index=0;
    while(othernum*mulob<=tempnum)
    {
        index++;
        mulob=index;
    }
    index--;
    mulob=index;
    Bigint carry=tempnum-(othernum*mulob);
    if(numberleft>0)
    {
        select++;
        carry.s+=num1[select-1];
        numberleft--;
    }
    result+=(index+'0');
    tempnum=carry;
    
    return tempnum.s;

}



Bigint operator+(Bigint num2)
{
    Bigint ans;
    ans.s=sum(s,num2.s);
    return ans;
}
Bigint operator-(Bigint num2)
{
    Bigint ans;
    ans.s=sub(s,num2.s);
    return ans;
}
Bigint operator*(Bigint num2)
{
    Bigint ans;
    ans.s=mul(s,num2.s);
    return ans;
}

Bigint operator/(Bigint num2)
{
    Bigint ans;
    ans.s=div(s,num2.s);
    return ans;
}

Bigint operator%(Bigint num2)
{
    Bigint ans;
    ans.s=remainder(s,num2.s);
    return ans;
}

bool operator>(Bigint num2)
{

    if(s.length()>num2.s.length())
        return true;
    else if(s.length()<num2.s.length())
        return false;
    else
    {
        for(int i=0;i<s.length();i++)
        {
            if(s[i]>num2.s[i])
                return true;
            else if(s[i]<num2.s[i])
                return false;
        }
        return false;
    }

}



bool operator<(Bigint num2)
{

    if(s.length()<num2.s.length())
        return true;
    else if(s.length()>num2.s.length())
        return false;
    else
    {
        for(int i=0;i<s.length();i++)
        {
            if(s[i]<num2.s[i])
                return true;
            else if(s[i]>num2.s[i])
                return false;
        }
        return false;
    }

}

bool operator<=(Bigint num2)
{

    if(s.length()<num2.s.length())
        return true;
    else if(s.length()>num2.s.length())
        return false;
    else
    {
        for(int i=0;i<s.length();i++)
        {
            if(s[i]<num2.s[i])
                return true;
            else if(s[i]>num2.s[i])
                return false;
        }
        return true;
    }

}

bool operator>=(Bigint num2)
{

    if(s.length()>num2.s.length())
        return true;
    else if(s.length()<num2.s.length())
        return false;
    else
    {
        for(int i=0;i<s.length();i++)
        {
            if(s[i]>num2.s[i])
                return true;
            else if(s[i]<num2.s[i])
                return false;
        }
        return true;
    }

}

bool operator==(Bigint num2)
{

    if(s.length()>num2.s.length())
        return false;
    else if(s.length()<num2.s.length())
        return false;
    else
    {
        for(int i=0;i<s.length();i++)
        {
            if(s[i]>num2.s[i])
                return false;
            else if(s[i]<num2.s[i])
                return false;
        }
        return true;
    }

}




Bigint Expo(Bigint b)
{
    
    Bigint res=1;
    Bigint a=s;
    while(b.s!="0")
    {
    if((b.s[b.s.length()-1]-'0')%2==1)
        res=res*a;
    a=a*a;
    b=b/2;
    }
return res;
}






};

// class ends here
//
//

ostream& operator <<(ostream &os ,const Bigint &num)
{
    os<<num.s;
    return os;
}

istream& operator >>(istream &is ,Bigint &num)
{
    is>>num.s;
    return is;
}







int precedence(char i)
{
    if(i=='*' or i=='/')
        return 2;
    else if(i=='+' or i=='-')
        return 1;
    else
        return -1;
}




Bigint calculator(string s)
{
    string postfix;
    mystack<char>s1;

    for(int i=0;i<s.length();i++)
    {

        if(s[i]>='0' and s[i]<='9')
            postfix.push_back(s[i]);
        else
        {
            if(s1.empty()){
                s1.push(s[i]);
                postfix.push_back(' ');
            }
            else
            {
                if(precedence(s1.top())<precedence(s[i]))
                {
                    s1.push(s[i]);
                    postfix.push_back(' ');
                }
                else
                {
                    postfix.push_back(' ');
                    while(!s1.empty() and precedence(s1.top()<precedence(s[i])))
                    {
                        postfix.push_back(s1.top());
                        s1.pop();
                    }
                    s1.push(s[i]);
                }
            }
        }

    }
    postfix.push_back(' ');
    while(!s1.empty())
       {
           postfix.push_back(s1.top());
           s1.pop();
       }

    string num;
    mystack<Bigint>s2; 

    for(int i=0;i<postfix.length();i++)
    {
        
        if(postfix[i]>='0' and postfix[i]<='9')
            num.push_back(postfix[i]);
        else
        {
            // cout<<num<<endl;
            // int val=stoi(num);
            // s2.push(val);
            // num.clear();
            if(postfix[i]==' ')
                {
                    Bigint val=num;
                    s2.push(val);
                    num.clear();
                }
            else
            {
                Bigint num1=s2.top();
                s2.pop();
                Bigint num2=s2.top();
                s2.pop();

                if(postfix[i]=='+')
                    s2.push(num1+num2);
                else if(postfix[i]=='-')
                    s2.push(num2-num1);
                 else if(postfix[i]=='x')
                    s2.push(num2*num1);

            }
        }
    }
    Bigint ans= s2.top();
    return ans;
}







Bigint gcd(Bigint a,Bigint b)
{
    if(b=="0")
        return a;
    return gcd(b,a%b);

}


Bigint fac(Bigint a)
{
    Bigint ans=1;
    Bigint i=1;
    for(i;i<=a;i=i+1)
        ans=ans*i;
    return ans;

}





void solve()
{



// cout<<":::::::::WELCOME TO BIGINTERGER LIBRARY ::::::::::BY AMAN IZARDAR::"<<endl;
// cout<<"Please Enter 1 for Exponentiation\n";
// cout<<"Enter 2 for GCD\n";
// cout<<"Enter 3 for Factorial\n";
// cout<<"Enter 4 for Calculator\n";

int ip;
cin>>ip;

switch(ip)
{
    case 1:{
    // cout<<"Please Enter two numbers Base and Exponent\n";
    Bigint base;
    Bigint exponent;
    cin>>base>>exponent;
    // cout<<"Exponentiation result is := ";
    cout<<base.Expo(exponent)<<endl;
    break;}

    case 2:{
    // cout<<"Please Enter Two Numbers to find the GCD\n";
    Bigint num1,num2;
    cin>>num1>>num2;
    // cout<<"GCD of "<<num1<<" and "<<num2<<" is := ";
    cout<<gcd(num1,num2)<<endl;
    break;}

    case 3:{
    // cout<<"Please Enter the no to find the Factorial\n";
    Bigint num1;
    cin>>num1;
    // cout<<"Factorial is : ";
    cout<<fac(num1)<<endl;
    break;}

    case 4:{
    // cout<<"Please enter a string for Calculator\n";
    string s;
    cin>>s;
    // cout<<"Result of The following Expression is :=\n";
    cout<<calculator(s)<<endl;
    break;}

    default:{
        cout<<"-1  \n";
    }
}



// string tocal;
// cin>>tocal;
// cout<<calculator(tocal);

// Bigint a=85;
// Bigint b=85;
// if(a>=b)
// cout<<"Hi";
// else
// cout<<"Bye";

// Bigint a;
// Bigint b;
// cin>>a;
// cin>>b;
// cout<<a/b;
// cout<<a.Expo(b);
// cout<<remainder("25","6");

// if(b=="0")
//     cout<<"hi";
// else
//     cout<<"Bye";
// cout<<a/b;
// cout<<a%b;
// cout<<gcd(a,b);

// cout<<fac(a);


}














int main()
{

 ios_base::sync_with_stdio(false);
 cin.tie(NULL);
 #ifndef ONLINE_JUDGE
 freopen("input.txt", "r", stdin);
 freopen("output.txt", "w", stdout);
 #endif
ll t=1;
//cin>>t;
while(t--)
{
    solve();
}
return 0;
}
