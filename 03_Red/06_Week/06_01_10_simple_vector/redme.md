Задание по программированию
«Оператор присваивания для SimpleVector»
В видеолекции мы с вами познакомились с конструктором копирования и оператором присваивания, а также написали конструктор копирования для SimpleVector. В этой задаче вам нужно реализовать оператор присваивания для SimpleVector.

Напомним, что следующий код вызывает конструктор копирования:

SimpleVector<int> source(5);
SimpleVector<int> dest = source; // Конструктор копирования
А код ниже — оператор присваивания:

SimpleVector<int> source(5);
SimpleVector<int> dest;
dest = source; // Оператор присваивания
Вам дан cpp-файл, который подключает заголовочный файл simple_vector.h и содержит небольшой набор юнит-тестов. Пришлите на проверку файл simple_vector.h с реализацией оператора присваивания.

simple_vector_copy_assignment.cpp