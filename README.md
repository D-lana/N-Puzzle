# N-Puzzle
Головоломка пазл (пятнашки)
Задание:
Решить головоломку с помощью алгоритма А*.
Вам предстоит управлять головоломками различных размеров (3, 4, 5, 17 и т.д.). Чем выше сможет подняться ваша программа, не умирая ужасной смертью, тем лучше.
Стоимость, связанная с каждым переходом, всегда равна 1.
Нужно реализовать по крайней мере 3 эвристических ф-ции (Эвристика на расстоянии Манхэттена обязательна).
В конце поиска программа должна предоставить следующие значения:
- Общее количество состояний, когда-либо выбранных в "открытом" наборе (сложность по времени)
- Максимальное количество состояний, когда-либо представленных в памяти одновременно во время поиска (сложность по размеру)
- Количество ходов, необходимых для перехода из начального состояния в конечное
- Упорядоченная последовательность состояний, составляющих решение
- Головоломка может оказаться неразрешимой, и в этом случае вы должны сообщить об этом пользователю и выйти

Что еще нужно сделать:
#добавить агрументы: имя файла и флаги на выбор эвристической ф-ции
#добавить проверку на корректность файла
#потестить еще невалидные входные данные
#приступить к разбору самого алгоритма
#добавить еще эвристических ф-ций


