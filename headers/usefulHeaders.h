#include <string>
#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <conio.h>
#include <windows.h>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
using namespace std;
using namespace sf;


long power2(int n) {
    if (n == 0)
        return 1;
    else return power2(n - 1) * 2;
}

long x_to_power_n(int x, int n) {
    if (n == 0) return 1;
    else return x_to_power_n(x, n - 1) * x;
}

int GCD(int x, int y)
{
    int r = x % y;
    while (r != 0)
    {
        x = y;
        y = r;
        r = x % y;
    }
    return y;
}

void show_binary(int u)
{
    while(u > 1){
        if((u % 2) == 0){
            cout << "0";
        }else{
            cout << "1";
        }
        u = u >> 1;
    }
    cout << "1\n";
}

void ten_to_bin(int n, int p){
    int k;
    if (p==1) cout << n;
    else {
        k=n%2;
        ten_to_bin(n/2,p-1);
        cout << k;
    }
}

int max_of_array (int a, int *ar[])
{

    int count = 0;
    int max = *ar[0];
    for (count ; count < a; count++) {
        if( *ar[count] > max){
            max = *ar[count];
        }
    }

    return max;
}