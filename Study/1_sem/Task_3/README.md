        Программа пока не получен конец файла, выполняет в цикле следующие действия:
        
    1) cчитывает из stdin очередную строку
    2) преобразует ее в список слов
    3) выводит в stdout длину полученного списка слов и саму последовательность слов в исходном порядке
    4) выводит слова последовательности в лексикографическом порядке 
    
        
        Полученную из stdin строку программа разделяет по следующим правилам:
    
    1) Встретился пробельный символ ('\n', '\t' или ' ')
    2) Встретился один (одно) из специальных символов (слов): '|', "||", '&', "&&", ';', '>', ">>", '<', 
        '(', ')'.
        
        Последовательность вида ">>>" разбивается на слова >> и >, но не на > и >> или 
        > и > и >, то есть выделяется по возможности максимально длинное специальное слово.
    
    
    Слова представляют из себя массивы с элементами типа char, '\0' - признак конца слова.
    Список слов представляет из себя динамическую структуру данных, признак конца списка - NULL.
    
    Программа разделена на модули. 
    
    В файле char_list.c находится реализация функций для работы со списком.
    
    В заголовочном файле char_list.h находятся описания функций из char_list.c.
    
    В файле prog.c реализовано чтение данных из stdin и их обработка.
    
    Сбор итоговой программы осуществляется при помощи утилиты make, имя исполняемого файла - united.out.
    
    