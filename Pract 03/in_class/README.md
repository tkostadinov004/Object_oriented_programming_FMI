Напишете програма, която работи с файл с числа, които са кодове на цветове. 
Числата във файла са разеделени с | (пр. 12465237|12465480|13465277|43243243) и коректността на формата е гарантирана.

Да се напише функция, която приема поток към файла, чете числата и превръща всяко число в обект от структура 
Color. Структурата да съдържа 3 цели числа в интервала [0, 255], 
които отговарят съответно за количеството червено, зелено и синьо в цвета. 
Формулата, която превръща 3-те числа в цялостен код, е RGB = (R*65536)+(G*256)+B

Да се напише функция, която приема поток и масив от обекти от Colour и ги записва във файла в същия формат.
