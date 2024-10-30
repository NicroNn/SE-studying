| Лабораторная работа №3 | M3104                         | АОВС |
|-----|-------------------------------| ---- |
| Кэш и кодирование команд | Каренин Константин Витальевич | 2024 |

> [!important]  
> Не забудьте указать в шапке свои ФИО и Номер группы

## Инструментарий
C++20

## Что реализовано
~~Отчет написано плохо~~ Надеюсь теперь хорошо)\
3-й вариант параметров системы\
normal версия
1. Задача из условия переведена на RISC-V ассемблер
2. Бинарный код этой задачи полученный программой
3. Программа выполняющая rv32i и rv32m инструкции кроме Zifence, Zicsr, также не поддерживает переходы по меткам, 
эмулирующая кеш с политиками вытеснения LRU и bit-pLRU

## Результат работы на тестовых данных: [ссылка на последний успешный action с актуальными данными](https://github.com/skkv-itmo-comp-arch/se-comp-arch24-cache-isa-NicroNn/actions/runs/9294307926)

# Описание:
## ISA
### C-ASM
Прочитав данную [документацию](https://msyksphinz-self.github.io/riscv-isadoc/html/rvi.html) нетрудно узнать значение 
каждой инструкции из набора RV32I и далее написать аналогичный данному код.\
Подробное сопосталение кодов, чтобы показать как переводился код:

Инициализируем начальные данные:\
C:
```c
#define M 64
#define N 60
#define K 32
int8_t a[M][K];
int16_t b[K][N];
int32_t c[M][N];
```
ASM:
```asm
addi    t0, zero, 0x100  ; t0 = 256, pa = a (адрес начала массива a)
lui     t5, 0x2          ; t5 = 0x20000
addi    t5, t5, -0x800   ; t5 = 0x1F800, b (адрес начала массива b)
addi    t4, zero, 0      ; t4 = 0, y
addi    t2, zero, 0      ; t2 = 0, k
addi    t1, zero, 63     ; t1 = 63, M-1
addi    t6, zero, 59     ; t6 = 59, N-1
lui     t3, 0x1          ; t3 = 0x10000
addi    s0, zero, 0      ; s0 = 0, s (accumulator)
addi    s1, zero, 0      ; s1 = 0, x
addi    s2, zero, 31     ; s2 = 31, K-1
addi    t3, t3, -0x700   ; t3 = 0x0F900, c (адрес начала массива c)
```
Внешний цикл по y:\
C:
```c
int8_t *pa = a;
int32_t *pc = c;
for (int y = 0; y < M; y++)
{
```
ASM:
```asm
addi    s3, t0, s1       ; s3 = t0 + s1, pa + x (адрес текущего элемента a)
```
Внешний цикл по x:\
C:
```c
for (int x = 0; x < N; x++)
{
    int16_t *pb = b;
    int32_t s = 0;
```
ASM:
```asm
addi    s10, zero, 2     ; s10 = 2, чтобы умножить индекс k на 2 для 16-битных элементов
```
Внешний цикл по k:\
C:
```c
for (int k = 0; k < K; k++)
{
    s += pa[k] * pb[x];
    pb += N;
}
```
ASM:
```asm
mul     s4, s10, t2      ; s4 = 2 * k, смещение для текущего элемента b
add     s4, s4, t3       ; s4 = адрес текущего элемента b
lb      s5, 0, s3        ; s5 = *pa, загрузка текущего элемента a
lh      s6, 0, s4        ; s6 = *pb, загрузка текущего элемента b
mul     s3, s5, s6       ; s3 = pa[k] * pb[x]
add     s0, s0, s3       ; s0 += s3, суммирование в аккумуляторе
addi    t3, t3, 120      ; t3 += N*2, переход к следующему элементу pb
addi    s1, s1, 1        ; s1++, x++
bge     s2, s1, -40      ; если x < N, переход к следующему элементу pa
```
Конец внутреннего цикла:\
C:
```c
    pc[x] = s;
  }
  pa += K;
  pc += N;
}
```
ASM:
```asm
addi    s11, zero, 4     ; s11 = 4, чтобы умножить индекс y на 4 для 32-битных элементов
mul     s3, t2, s11      ; s3 = t2 * 4, смещение для текущего элемента c
add     s3, s3, t5       ; s3 = адрес текущего элемента c
sw      s0, 0, s3        ; *pc = s, сохранение результата
addi    t2, t2, 1        ; t2++, k++
bge     t6, t2, -88      ; если k < K, переход к следующему элементу b
addi    t4, t4, 1        ; t4++, y++
addi    t0, t0, 32       ; t0 += K, переход к следующему элементу a
addi    t5, t5, 240      ; t5 += N*2, переход к следующему элементу c
bge     t1, t4, -112     ; если y < M, переход к следующему элементу c
jalr    zero, ra, 0      ; возврат из функции
```

**Краткое описание действий:**
1. Объявления переменных меняем на инициализацию регистров в ассемблере.
2. Циклы реализуем с использованием инструкций условного перехода.
3. Арифметические операции заменяем на аналогичные инструкции.

### ASM-binary
Транслятор ассемблерных инструкций RISC-V в двоичный код реализован как словари для хранения опкодов, funct3 и funct7
и функции кодирования для каждого типа инструкций (R, I, S, B, U, J) и функция, которая определяет тип инструкции и 
вызывает нужное кодирование
## CacheLRU
| Параметр                 | Значение                | Формула по которой вычислил                   |
|--------------------------|-------------------------|-----------------------------------------------|
| MEM_SIZE                 | 262144                  | 256 * 1024                                    |
| ADDR_LEN                 | 18 бит                  | было по условию                               |
| Конфигурация кэша        | look-through write-back | было по условию                               |
| Политика вытеснения кэша | LRU и bit-pLRU          | было по условию                               |
| CACHE_WAY                | 4                       | CACHE_LINE_COUNT / CACHE_SETS                 |
| CACHE_TAG_LEN            | 9                       | ADDR_LEN - CACHE_INDEX_LEN - CACHE_OFFSET_LEN |
| CACHE_INDEX_LEN          | 3 бита                  | было по условию                               |
| CACHE_OFFSET_LEN         | 6                       | log2(CACHE_LINE_SIZE)                         |
| CACHE_SIZE               | 2048                    | CACHE_LINE_SIZE * CACHE_LINE_COUNT            |
| CACHE_LINE_SIZE          | 64 байт                 | было по условию                               |
| CACHE_LINE_COUNT         | 32                      | было по условию                               |
| CACHE_SETS               | 8                       | 2^CACHE_INDEX_LEN                             |

### Работа кеша
***MemoryLRU:***

**Политика вытеснения:** LRU (Least Recently Used) вытеснение значений, которые не использовались дольше всего\
**Конфигурация:** задается через макроопределения в начале файла (CACHE_WAY, CACHE_SIZE, CACHE_LINE_SIZE и т.д.),
их значения были вычислены в таблице выше\
**Реализация:** используем список, чтобы вытеснять последнюю использованную линию\
При запоросе в пробуем получить данные из кеша, если удается засчитываем кеш попадание, если нет то обращаемся к памяти\
**Операции:** get и put для чтения и записи данных в кэш и память соответственно


***MemorypLRU:***

**Политика вытеснения:** bit-pLRU (pseudo-LRU), отличается от LRU дополнительным битом и выбором вытесняемой линии по нему
для оптимизации\
**Конфигурация:** задается через макроопределения в начале файла (CACHE_WAY, CACHE_SIZE, CACHE_LINE_SIZE и т.д.),
их значения были вычислены в таблице выше\
**Реализация:** используем дополнительный бит для отслеживания линии, которую использовали наиболее давно, 
при промахе заменяется строка, у которой этот бит 0\
При запоросе в пробуем получить данные из кеша, если удается засчитываем кеш попадание, если нет то обращаемся к памяти\
**Операции:** get и put для чтения и записи данных в кэш и память соответственно

## Результат работы программы
### При replacement = 0
LRU     hit rate: 80.7821%
### При replacement = 1
pLRU    hit rate: 87.5845%
### При replacement = 2
LRU     hit rate: 80.7821%\
pLRU    hit rate: 87.5845%
### При различных параметрах asm и bin
Читается файл по параметру asm\
Создается файл по параметру bin