#include <iostream>

int main() {
    int a, b, sum;
    std::cout << "请输入两个整数: " << std::endl;
    std::cin >> a >> b;    // 读取用户输入
    sum = a + b;
    std::cout << "它们的和是 " << sum << std::endl;
    return 0;
}
