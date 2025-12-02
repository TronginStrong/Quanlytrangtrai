#include "DongVat.h"
#include<chrono>

int main() {
    auto start = chrono::high_resolution_clock::now();
    CTrangTrai trangTrai;
    trangTrai.MenuChinh();
    auto end=chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed=end-start;
    cout<<"\n==Thoi gian chuong trinh chay : "<<elapsed.count()<<" giay==\n";
    return 0;
}