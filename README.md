﻿# Генератор ASCII последовательности
![Animation](https://user-images.githubusercontent.com/32985830/163470667-add56c29-1a2b-476f-9e17-1d78411266c2.gif)


## Правила построения

1. В строковых идентификаторах используются только согласные буквы: B, C, D, F, G … Z и цифры от 1 до 9;
2. Первый строковый идентификатор имеет вид "B1". Второй строковый идентификатор в последовательности - "B2", третий - "B3" и так далее. За "B9" следующий - "C1". Следующий после "Z9" имеет вид "B1-B1", потом "B1-B2" и так далее. После "B1-Z9" следующим идет "B2-B1";
3. Максимальная длина идентификатора - десять групп по два символа.

## Сборка
```bash
mkdir build 
cd build
cmake ..
cmake --build .
ctest -V
```

## etc
http://blog.martincowen.me.uk/unit-testing-embedded-c-on-target-with-minunit-and-off-target-with-ms-test.html
