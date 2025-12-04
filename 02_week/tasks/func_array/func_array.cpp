#include <stdexcept>

double ApplyOperations(
    double a,
    double b,
    double (*mathOperations[])(double, double), // массив указателей, который принимает два числа типа double
    size_t size // рамзер массива
) {
    // если массив пуст - возвращаем 0.0
    if (size == 0) {
        return 0.0;
    }
    // переменная для суммы мат операций
    double sum = 0.0;
    // проходим по каждому элементу массива 
    for (size_t i = 0; i < size; ++i) {

        // если один из указателей массива пустой, то пропускаем
        if (mathOperations[i] == nullptr) {
            continue; // пропускаем пустую функцию
        }
        // вызываем i-ю функцию с числами a и b, кладем в v
        double v = mathOperations[i](a, b);
        // прибавляем к общей сумме
        sum += v;
    }

    return sum;
}