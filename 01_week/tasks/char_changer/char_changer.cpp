#include <cstddef>
#include <cctype>   // применял isspace, isdigit, isupper, islower, toupper

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    if (size == 0) {
        return 0;
    }

    size_t read  = 0; // это индекс для чтения
    size_t write = 0; // это индекс для запси символов

    // идем по массиву пока не выйдем за него
    // и пока текущий символ не конец строки, конец строки по условию это '\0'
    while (read < size && array[read] != '\0') {
         // в cppreference указано, что isspace должно принимать безнаковый символ,
        // поэтому преобразуем текущий символ из char в unsigned char        
        unsigned char uc = static_cast<unsigned char>(array[read]);
        // если текущий символ пробельный
        if (std::isspace(uc)) {

            // пропускаем все подряд идущие пробельные символы
            while (read < size && array[read] != '\0') {
                unsigned char c = static_cast<unsigned char>(array[read]);
                 if (!std::isspace(c)) {
                 break;          // текущий символ больше не пробел — выходим
                }  
                ++read; // пробел — пропускаем и идём дальше
            }
            // теперь когда мы прочитали все пробелы записывыем в write только один пробел
            array[write++] = delimiter;

        } else {
            // Теперь рассматриваем случай когда у нас идут подряд одинаковые символы
            // Текущий символ массива
            char current = array[read];
            size_t count   = 0; // это как счетчик, то есть сколько повторябщихся символов
            // идем пока текущий символ не превзойдет размер массива и 
            // символ не конец строки и символ на текущей позиции такой же как и currentт
            while (read < size && array[read] != '\0' && array[read] == current) {
                ++count;
                ++read;
            }

            // Определяем, какой символ писать по правилам
            // в cppreference указано, что isdigit,isupper,islower должно принимать безнаковый символ,
            // поэтому преобразуем текущий символ current из char в unsigned char  
            unsigned char cu = static_cast<unsigned char>(current);
            char Char;

            if (std::isdigit(cu)) {   // цифры заменяем на '*'
                Char = '*';
            } else if (std::isupper(cu)) {  //прописные латинские не меняем
                Char = current;
            } else if (std::islower(cu)) {  // строчные на прописные
                Char = static_cast<char>(std::toupper(cu));
            } else {  // остальное на '_'
                Char = '_';
            }

            // записываем символ в write
            array[write++] = Char;

            // пишем количество повторений, если count > 1
            if (count > 1) {
                if (count >= 10) { // Если повторений не менее 10, указывается `0` после символа
                    array[write++] = '0';
                } else {
                    // записываем в write число посторений (то есть елси 2222, то 4), 
                    // Например, если было "2222", то count = 4, и мы должны записать символ '4'.
                    // В кодировке ASCII код символа '0' равен 48
                    // Поэтому, чтобы получить символ '4', берём код '0' (48) и прибавляем 4 (48 + 4 = 52 — это код '4')
                    array[write++] = static_cast<char>('0' + count); // 
                }
            }
        }
    }

    // завершаем строку
    if (write >= size) {
        write = size - 1;
    }
    array[write] = '\0';

    return write;
}



