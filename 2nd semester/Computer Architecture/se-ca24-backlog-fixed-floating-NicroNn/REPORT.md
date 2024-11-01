| Лабораторная работа №1 | M3104                         | АОВС |
| ---------------------- |-------------------------------| ---- |
| Представление чисел    | Каренин Константин Витальевич | 2024 |

> [!important]  
> Не забудьте указать в шапке свои ФИО и Номер группы

## Инструментарий
C++20

[Ссылка на actions](https://github.com/skkv-itmo-comp-arch/se-ca24-backlog-fixed-floating-NicroNn/actions/runs/11078094848)

## Что реализовано
Классы числа с фиксированной и плавающей точкой с 4 видами округлений (Normal)

# Описание:
## Округления
Для удобной работы с округлениями в будущем был создан enum `RoundingMode` который содержит названия поддерживаемых видов
округлений: `TowardZero, NearestEven, TowardInfinity, TowardNegInfinity`
### TowardZero
При округлении просто отбрасывается дробная часть до нужного знака.
### NearestEven
Округляется в сторону ближайшего чётного, если при округлении вверх будет чётное, а при округлении вниз нечётное, то округлим
вверх, и наоборот.
### TowardInfinity
Округление к положительной бесконечности, тоесть при положительных числах будем округлять вверх, при отрицательных вниз.
### TowardNegInfinity
Как `TowardInfinity` только к отрицательной бесконечности, соответственно при отрицательных - вверх, при положительных вниз. 
## MyFixedPoint
Класс числа с фиксированной точкой, количество бит под целую часть и под дробную задается при создании переменной класса - 
указываем параметр intSize и fracSize. Также задается начальное значение и вид округления.
### applyRounding
Функция для округления числа в зависимости от выбранного округления, примает резульат операции между value двух чисел, дробную часть этого числа, второго операнда выражения и знак числа.

`TowardZero`: можно ничего не делать.

`NearestEven`:
- Удваиваем дробную часть (frac << 1) и сравниваем с rhs (правым операндом).
- Если удвоенная дробная часть больше rhs, или она равна rhs и текущий result нечётный (result & 1), увеличиваем result на 1.

`TowardInfinity`:
- Если дробная часть не равна нулю (frac != 0) и число не отрицательное (!isNegative), увеличиваем result на 1.

`TowardNegInfinity`:
- Если дробная часть не равна нулю (frac != 0) и число отрицательное (isNegative), увеличиваем result на 1.

### operator+
Возвращает новый экземпляр класса с теми же параметрами, кроме value, оно равно сумме value двух операндов выражения.
### operator-
Аналогично `operator+`, но разница value вместо суммы.
### operator*
1. Сначала проверяем знак результата - xor двух операндов.
2. Для простоты мы берем модули чисел, умножаем их и сдвигаем вправо на количество бит для дробной части - так мы получили 
целую часть результата операции, для получения дробной части нужно применить "побитовое и" с 2^fracSize - 1, например
для дробной части длинной 4 мы сделаем побитовое и с `1111`.
3. Применяем округление при помощи `applyRounding`.
4. Добавляем нужный знак числу.
5. Возвращаем новый экземпляр класса с нужными значениями.
### operator/
1. Делаем проверку деления на 0.
2. Получаем знак результата.
3. Берем модули операндов.
4. Сдвигаем левый операнд на fracSize (тоже самое что умножить на 2^fracSize) для того чтобы получить всё число, а не 
только целую часть.
5. Делим сдвинутого операнда для получения целой части, и берем остаток от деления для получения дробной.
6. Применяем округение.
7. Добавляем знак.
8. Возвращаем новый экземпляр класса с нужными значениями.
### operator<< 
Это перегуженный оператор потока вывода, чтобы можно было выводить `MyFixedPoint` в стандартный поток вывода.
1. Делаем копию числа которое выводим, чтобы работать с ней.
2. Создаем константу `kFracOutLen` для ограничения длинны вывода дробной части - по условию 3.
3. Значение value сдвигается влево и вправо, чтобы корректно учесть и целую, и дробную части в представлении.
4. Если число отрицательное, то записываем это, и инвертируем его.
5. Получаем целую и дробную части числа.
6. Применяем округение.
7. Выводим `-` если число не 0 и отрицательное.
8. Выводим целую часть.
9. Выводим дробную часть, дополняя её до 3 знаков, если необходимо

## Precision
Поскольку требуется реализовать `float` с 2 точностями (`single` и `half`) я создал enum для их "красивого" обозначения.

## FloatComponents
Для объединения компонентов числа с плавающей точкой я создал этот класс, чтобы было удобно отделять части разных чисел в операторах.

# MyFloatPoint
Класс для работы с числами с плавающей точкой, реализованный с двумя точностями: `Half` и `Single`. Выбор точности 
осуществляется через шаблон. В зависимости от точности меняются размеры числа, мантиссы и экспоненты. 
Все биты числа хранятся в переменной `value`, а компоненты числа получаются при помощи `getComps`.

### getComps
Метод, который извлекает из переменной value (в которой хранятся биты числа) отдельные компоненты: мантиссу, экспоненту
и знак. В зависимости от выбранной точности (Half или Single) изменяются размеры этих компонентов:
1. Для Single используются 1 бит на знак, 8 бит на экспоненту, и 23 бита на мантиссу.
2. Для Half используется 1 бит на знак, 5 бит на экспоненту и 10 бит на мантиссу.

### normalizeMantissaExponent
После выполнения операций старший бит мантиссы может оказаться в неправильной позиции, что требует нормализации. 
Этот метод перемещает старший бит мантиссы в нужную позицию и корректирует экспоненту. Если старший бит мантиссы 
выходит за пределы её допустимого диапазона, экспонента увеличивается. В обратном случае, если мантисса слишком мала, 
она сдвигается влево, а экспонента уменьшается. 

### rounding
Методы для округления мантиссы в зависимости от выбранного режима округления (`roundTowardZero`, `roundNearestEven`, `roundTowardInfinity`, 
`roundTowardNegInfinity`.). Методы также корректируют экспоненту, если в результате округления мантисса 
переполнилась (например, если мантисса стала больше, чем максимальное значение для данного формата). Потерянные при округлении биты учитываются, чтобы избежать значительных отклонений в итоговом результате. Знак числа также корректируется, если это необходимо.

### handleSpecialCases
Этот метод обрабатывает специальные случаи:

1. NaN — возникает, когда мантисса не равна нулю при максимальной экспоненте.
2. Infinity — возникает при максимальной экспоненте и нулевой мантиссе.
3. Zero — возникает при нулевой экспоненте и мантиссе. Положительный и отрицательный ноль также различаются.

Метод возвращает пару: bool найден ли специальный случай, и значение числа для него.

### handleLostBits
Нужен для обработки потерянных битов в результате выхода за границы. Работает по разному для операторов `+-` и для `*/`.

### determineAdjustment
Нужен чтобы определить как изменить мантиссу в зависимости от округления.

### operator+
1. Получаем компоненты операндов с помощью метода `getComps`.
2. Проверяем специальные случаи с помощью метода `handleSpecialCases`.
3.  Нормализуем мантиссу операндов через `normalizeMantissaExponent`.
4.  Операнд с меньшей экспонентой сдвигается вправо для выравнивания с числом, имеющим большую экспоненту.
5.  Складываем мантиссы с учётом знаков.
6.  Применяем округление через метод `applyRounding`.
7.  Возвращаем новый экземпляр класса с результатом сложения.

### operator-
1. Инвертируем знак правого операнда.
2. Складываем операнды аналогично оператору `operator+`.

### operator*
1. Получаем компоненты операндов с помощью метода `getComps`.
2. Проверяем специальные случаи с помощью метода `handleSpecialCases`. Если один из операндов является NaN, Infinity или Zero, возвращаем соответствующее значение.
3.  Нормализуем мантиссы с помощью метода `normalizeMantissaExponent`.
4.  Перемножаем мантиссы, складываем экспоненты, а знак результата определяем как XOR знаков операндов.
5.  Применяем округление с помощью метода `applyRounding`.
6.  Возвращаем новый экземпляр класса с результатом умножения.

### operator/
1. Получаем компоненты операндов с помощью метода `getComps`.
2. Проверяем специальные случаи с помощью метода `handleSpecialCases`. Если один из операндов является NaN, Infinity или Zero, возвращаем соответствующее значение.
3. Нормализуем мантиссу делимого с помощью метода `normalizeMantissaExponent`.
4. Мантисса делимого сдвигается влево на количество бит, соответствующее размеру мантиссы, чтобы сохранить дробную часть.
5. Мантиссы делятся (дробная часть округляется аналогично методу `applyRounding` в классе `MyFixedPoint`, поэтому создается 
вспомогательный объект `MyFixedPoint`, чтобы избежать дублирования кода).
6. Вычитаются экспоненты, а знак результата — это XOR знаков операндов.
7. Применяем округление с помощью метода `applyRounding`.
8. Возвращаем новый экземпляр класса с результатом деления.

### operator<<
1. В зависимости от выбранной точности (Half или Single), устанавливается точность вывода: для Half — 3 знака после 
запятой, для Single — 6 знаков. Для этого создаётся переменная `kOutPrecision`.
2. Получаем компоненты числа с помощью метода `getComps`.
3.  Проверяем специальные случаи (NaN, Infinity, Zero):
4.  Если экспонента максимальна и мантисса равна 0, то выводим "inf" или "-inf" в зависимости от знака.
5.  Если экспонента максимальна и мантисса не равна 0, то выводим "nan".
6.  Если экспонента и мантисса равны 0, то выводится строка: "0x0." + `kOutPrecision` нулей + "p+0".
7.  Если экспонента равна 0 (поднормализованное число), мантисса сдвигается влево до тех пор, пока старший бит не станет
равным 1, и экспонента корректируется.
8.  Мантисса выводится в виде шестнадцатеричной строки: "0x1." + значение мантиссы в шестнадцатеричном формате, 
дополненное нулями до `kOutPrecision`. Затем выводится порядок в формате p+N или p-N, где N — значение экспоненты.
