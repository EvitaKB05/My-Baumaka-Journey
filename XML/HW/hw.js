// Homework Task 3.5
//Кудабаева Эвита ИУ5-42Б
/*Напишите функцию sort, которая будет сортировать слова-анаграммы
*/

function anagram(words) {
  const anagram_groups = {};

  for (const word of words) {
    const sorted_word = word.toLowerCase().split('').sort().join('');
    if (anagram_groups[sorted_word]) {
      anagram_groups[sorted_word].push(word);
    } else {
      anagram_groups[sorted_word] = [word];
    }
  }
  const result_groups = [];
  for (const sorted_word in anagram_groups) {
    if (anagram_groups[sorted_word].length >= 2) {
      const sorted_group = anagram_groups[sorted_word].sort(); // Сортируем слова в группе
      result_groups.push(sorted_group);
    }
  }
  // Сортируем группы по первому слову в каждой группе
  result_groups.sort((group1, group2) => {
    return group1[0].localeCompare(group2[0]);
  });
  return result_groups;
}

// Примеры использования:
console.log("-------------------------");
console.log("Homework 3.5");
console.log("Кудабаева Эвита ИУ5-42Б");
console.log("-------------------------");
console.log("Задание 3.5 (3 уровень)");
console.log("-------------------------");
console.log("Пример 1:");
console.log("-------------------------");
const word_list = ["пила", "спаниель", "спа", "лесниап", "липа", "слинап", "топор","апельсин", "ропот", "кот"];
const anagram_groups = anagram(word_list);
console.log("a) Исходный массив:");
console.log("-------------------------");
console.log(JSON.stringify(word_list));
console.log("-------------------------");
console.log("б) Отсортированный массив:")
console.log("-------------------------");
console.log(JSON.stringify(anagram_groups));
console.log("-------------------------");
console.log("Пример 2:");
console.log("-------------------------");
const word_list2 = ["пила", "лес", "сон", "кабан", "луг", "сила", "нос", "мука", "ток", "шар", "гул", "кума", "липа", "банка", "лапс", "сел", "кот", "спал", "лиса", "раш", "кто"];
const anagram_groups2 = anagram(word_list2);
console.log("a) Исходный массив:")
console.log("-------------------------");
console.log(JSON.stringify(word_list2));
console.log("-------------------------");
console.log("б) Отсортированный массив:")
console.log("-------------------------");
console.log(JSON.stringify(anagram_groups2));
console.log("-------------------------");









/*
function sort(sentence) {
    if (!sentence) {
        return "";
    }

    const words = sentence.split(' ').filter(word => word.trim() !== ""); 

    const sorted_words = words.map(word => {
        const letters = word.toLowerCase().match(/[а-яa-z]/g);
        if (!letters) {
            return word; 
        }
        const sorted_letters = letters.sort().join('');
        let capit_word = sorted_letters;

       /* if (/[а-яa-z]/i.test(word[0])) { 
            capit_word = sorted_letters[0].toUpperCase() + sorted_letters.slice(1);
        }
          просто символ первый, так, чет букву не читал */
          /*
        if (sorted_letters.length > 0) {
            capit_word = sorted_letters[0].toUpperCase() + sorted_letters.slice(1);
        }
        return capit_word; // вот так нормально)
    });


    return sorted_words.sort((a, b) => a.localeCompare(b)).join(' '); 
}

// examples
console.log("Примеры работы:");
// Сортировка + знаки 
console.log("1) Сортировка + знаки:");
const sentence1 = "В чащах юга жил бы цитрус? Да, но фальшивый экземпляр!";
const result1 = sort(sentence1);
console.log(`Исходное предложение: "${sentence1}"`);
console.log(`Отсортированное предложение: "${result1}"`);
// Сортировка с цифрами
console.log("2) Сортировка с цифрами:");
const sentence2 = "1r5456eghf fghjuwsa 12awo";
const result2 = sort(sentence2);
console.log(`Исходное предложение: "${sentence2}"`);
console.log(`Отсортированное предложение: "${result2}"`);
// Возвращение не буковок
console.log("3) Не буковки, возвращаем, наверн, хз:");
const sentence3 = "!@";
const result3 = sort(sentence3);
console.log(`Исходное предложение: "${sentence3}"`);
console.log(`Отсортированное предложение: "${result3}"`);
// Циферки
console.log("4) Циферки, возвращение прост:");
const sentence4 = "17656782";
const result4 = sort(sentence4);
console.log(`Исходное предложение: "${sentence4}"`);
console.log(`Отсортированное предложение: "${result4}"`);
// Проверка множества пробелов
console.log("5) Проверяем много пробельчиков:");
const sentence5 = "  Проверка     кучи   пробелов  ";
const result5 = sort(sentence5);
console.log(`Исходное предложение: "${sentence5}"`);
console.log(`Отсортированное предложение: "${result5}"`);
console.log("Вроде нормик)");
*/
// Homework 3.5
// Кудабаева Эвита ИУ5-42Б
/*Задание 3.5 (3 уровень)
Напишите функцию anagram, которая будет принимать на вход массив слов и группировать его на группы слов-анаграмм. 
Выводить только группы из двух и более слов. 
Слова в группах, как и сами группы, должны быть отсортированными
*/


  