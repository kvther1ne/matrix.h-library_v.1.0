# matrix.h-library

### Реализация библиотеки matrix.h на языке С++

В данном проекте z реализовала вторую версию проекта с библиотекой для работы с матрицами, на этот раз используя объектно-ориентированный подход. Объектно-ориентированный подход позволяет реализовать библиотеку для работы с матрицами в виде отдельного класса, над объектами которого определены операции, представленные как методами, так и стандартными операторами +, -, * и т.д.

Библиотека для работы с матрицами включает следующие операции:

1.  Сравнение матриц bool EqMatrix(const S21Matrix& other);
2. Сложение матриц void SumMatrix(const S21Matrix& other);
3. Вычитание матриц void SubMatrix(const S21Matrix& other);
4. Умножение матрицы на скаляр void MulNumber(const double num);
5. Перемножение матриц void MulMatrix(const S21Matrix& other);
6. Транспонирование матрицы S21Matrix Transpose();
7. Матрица алгебраических дополнений S21Matrix CalcComplements();
8. Детерминант матрицы double Determinant();
9. Обратная матрица S21Matrix InverseMatrix();

Помимо реализации данных операций, были реализованы конструкторы и деструкторы:
1. Базовый конструктор S21Matrix();
2. Параметризированный конструктор S21Matrix(int rows, int cols);
3. Конструктор копирования S21Matrix(const S21Matrix& other);
4. Конструктор переноса S21Matrix(S21Matrix&& other);
5. Деструктор ~S21Matrix();

А также были перегружены следующие операторы, частично соответствующие операциям выше:
1. Сложение двух матриц +
2. Вычитание матриц -
3. Умножение матриц и умножение матрицы на число *
4. Проверка на равенство матриц ==
5. Присвоение матрице значений другой матрицы =
6. Присвоение сложения +=
7. Присвоение разности -=
8. Присвоение умножения *=
9. Индексация по элементам матрицы (int i, int j)

* Матрица реализована в виде класса S21Matrix
* Хранятся приватные поля matrix_, rows_ и cols_
* Реализован доступ к приватным полям rows_ и cols_ через accessor и mutator. При увеличении размера - матрица дополняется нулевыми элементами, при уменьшении - лишнее просто отбрасывается
* Решение оформлено как статическая библиотека с заголовочным файлом s21_matrix_oop.h
* Полное покрытие unit-тестами функций библиотеки с помощью библиотеки GTest
* Предусмотрен Makefile для сборки библиотеки и тестов с целями all, clean, test, s21_matrix_oop.a
