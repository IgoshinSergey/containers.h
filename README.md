# s21_containers

Реализация библиотеки s21_containers.h.

### Introduction

В рамках данного проекта написана собственная библиотека, реализующая основные стандартные контейнерные классы языка С++: `list` (список), `map` (словарь), `queue` (очередь), `set` (множество), `stack` (стек) и `vector` (вектор). Реализации предоставляют весь набор стандартных методов и атрибутов для работы с элементами, проверкой заполненности контейнера и итерирования. В качестве дополнительного задания реализованы еще несколько не так часто используемых, но отличающихся деталями реализации контейнерных классов из контейнерной библиотеки C++.

### Information

Каждый вид контейнеров должен предоставить пользователю следующие методы:

- стандартные конструкторы (конструктор по умолчанию, конструктор копирования, конструктор перемещения, конструктор со списком инициализации, см. материалы);

- методы доступа к элементам контейнера (например, осуществление доступа к элементу с индексом i);

- методы проверки наполненности контейнера (например, количество элементов в контейнере, проверка на пустоту контейнера);

- методы изменения контейнера (удаление и добавление новых элементов, очистка контейнера);

- методы для работы с итератором контейнера.

Итераторы обеспечивают доступ к элементам контейнера. Для каждого контейнера конкретный тип итератора будет отличаться. Это связано с различным видом организации наборов объектов в контейнерных классах, а также с фактической реализацией контейнера. Итераторы реализуются в таком виде, чтобы они работали схожим образом с указателем на элемент массива языка С. Именно такой подход через использование итераторов и позволяет взаимодействовать с любыми контейнерами одинаковым образом. Через методы `begin()` и `end()` контейнеры предоставляют итераторы, которые указывают на первый и следующий после последнего элементы контейнера соответственно.

Над итератором `iter` определены следующие операции:

- `*iter`: получение элемента, на который указывает итератор;

- `++iter`: перемещение итератора вперед для обращения к следующему элементу;

- `--iter`: перемещение итератора назад для обращения к предыдущему элементу;

- `iter1 == iter2`: два итератора равны, если они указывают на один и тот же элемент;

- `iter1 != iter2`: два итератора не равны, если они указывают на разные элементы.

Помимо особой организации объектов и предоставления необходимых методов, реализация контейнерных классов требует шаблонизации объектов.

Шаблонные классы или шаблоны классов используются, когда необходимо создать класс, зависящий от дополнительных внешних параметров, которые могут быть другими классами или типами данных. Например, если необходимо создать класс списка, то есть потребность в избежании переписывания реализации списка для всех возможных типов элементов. Конечно, удобнее, написав один класс с параметром, получить сразу несколько конкретных классов списка (списки символов, целых чисел, вещественных, пользовательских типов и т. д.). В C++ контейнеры, вместе с итераторами и некоторыми алгоритмами, входят в стандартную библиотеку шаблонов (STL) именно по этой причине.

Контейнеры подразделяются на два основных типа: последовательные и ассоциативные. Для нахождения элемента в последовательных контейнерах (`list`, `vector`, `array`, `stack`, `queue`) необходимо последовательно просмотреть весь контейнер, в то время как в ассоциативных (`map`, `set`, `multiset`) достаточно обратиться по ассоциированному с значением ключу.

## Basic moments

- Программа должна быть разработана на языке C++ стандарта C++17 с использованием компилятора gcc;
- При написании кода придерживались Google Style;
- Классы являются шаблонными;
- Классы реализованы внутри пространства имен `s21`;
- Полное покрытие unit-тестами методов контейнерных классов c помощью библиотеки GTest;

## Part 1. Реализация библиотеки s21_containers.h

Список классов: `list` (список), `map` (словарь), `queue` (очередь), `set` (множество), `stack` (стек), `vector` (вектор).
- Решение оформлено в виде заголовочного файла `s21_containers.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`s21_list.h`, `s21_map.h` и т.д.);
- Предусмотрен Makefile для тестов написанной библиотеки (с целями clean, test);

### Part 2. Дополнительно. Реализация библиотеки s21_containersplus.h

Список классов, которые реализованы дополнительно: `array` (массив), `multiset` (мультимножество).
- Решение оформлено в виде заголовочного файла `s21_containersplus.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`s21_array.h`, `s21_multiset.h`);
- Предусмотрен Makefile для тестов написанной библиотеки (с целями clean, test);

### Part 3. Дополнительно. Реализация методов `insert_many`

Классы дополнены соответствующими методами согласно таблице:

| Modifiers      | Definition                                      | Containers |
|----------------|-------------------------------------------------| -------------------------------------------|
| `iterator insert_many(const_iterator pos, Args&&... args)`          | Inserts new elements into the container directly before `pos`.  | List, Vector. |
| `void insert_many_back(Args&&... args)`          | Appends new elements to the end of the container.  | List, Vector, Queue. |
| `void insert_many_front(Args&&... args)`          | Appends new elements to the top of the container.  | List, Stack. |
| `vector<std::pair<iterator,bool>> insert_many(Args&&... args)`          | Inserts new elements into the container.  | Map, Set, Multiset. |

В качестве аргументов передаются уже созданные элементы соответствующего контейнера, которые необходимо вставить в этот контейнер.

Каждый из этих методов использует конструкцию Args&&... args - Parameter pack. Эта конструкция позволяет передавать переменное число параметров в функцию или метод. То есть при вызове метода, определенного как `iterator insert_many(const_iterator pos, Args&&... args)`, можно написать как `insert_many(pos, arg1, arg2)`, так и `insert_many(pos, arg1, arg2, arg3)`.
