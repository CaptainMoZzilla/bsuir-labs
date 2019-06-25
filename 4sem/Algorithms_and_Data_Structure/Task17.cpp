#include <bits/stdc++.h>

using namespace std;

int main()
{
    bool c1 = false, c2 = false, c3 = false, c4 =false, c5 = false, c6 = false, c7 = false;
    long n, b;
    cin >> n;
    for (;n >= 0;n--) {
        cin >> b;
        if (b == 1021)
            c1 = true;
        
        if (b == 1031)
            c2 = true;
        
        if (b == 1033)
            c3 = true;
        
        if (b == 1052651)
            c4 = true;
            
        if (b == 1054693)
            c5 = true;
                
        if (b == 1065023)
            c6 = true;
    
        if (b == 1087388483)
            c7 = true;
    }
    cout << ( (c1 && c2 && c3) || (c4 && c3) || (c5 && c2) || (c6 && c1) || c7 ? "YES" : "NO");
    
    return 0;
}