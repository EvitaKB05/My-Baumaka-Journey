/*-----LAB-5---------*/
/* 1 ----Процедуру для изменения данных таблицы---- */
-- Процедура для обновления контактных данных преподавателя
SELECT * FROM teachers;
CREATE OR REPLACE PROCEDURE update_teacher_contact(
    teacher_id INT,
    new_contact VARCHAR
)
LANGUAGE SQL
AS $$
    UPDATE teachers 
    SET contacts = new_contact 
    WHERE id_teacher = teacher_id;
$$;

-- Пример вызова процедуры
CALL update_teacher_contact(1, '7(495) 111-11-11');
SELECT * FROM teachers ORDER BY id_teacher; /*--изменился номер телефона преподавателя с id 1 кооректно работает, проверяем--*/

/* 2 ----Процедуру для вставки данных в таблицу.---- */
-- Процедура для добавления нового студента---
CREATE OR REPLACE PROCEDURE add_new_student(
    student_fio VARCHAR,
    student_contacts VARCHAR,
    faculty_id INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    next_id INT;
BEGIN
    -- Находим максимальный текущий ID и увеличиваем на 1
    SELECT COALESCE(MAX(id_student), 0) + 1 INTO next_id FROM students;
    
    -- Вставляем нового студента с явно указанным ID
    INSERT INTO students (id_student, fio, contacts, id_faculty)
    VALUES (next_id, student_fio, student_contacts, faculty_id);
END;
$$;

-- Пример вызова процедуры
CALL add_new_student('Иванов Иван Иванович', '7(999) 123-45-67', 1);
SELECT * FROM students;
----Проверяем добавился ли в конец таблицы новый студент, да, работает корректно----

/* 3 ---Примеры арифметических функций из теоретической части
лабораторной работы--- */
-- 1. Функция среднего балла студента----
CREATE OR REPLACE FUNCTION calculate_student_avg_mark(student_id INT)
RETURNS TABLE(student_fio VARCHAR, average_mark NUMERIC)
LANGUAGE SQL
AS $$
    SELECT s.fio, ROUND(AVG(m.mark), 2)
    FROM marks m
    JOIN students s ON m.id_student = s.id_student
    WHERE m.id_student = student_id
    GROUP BY s.fio;
$$;
SELECT * FROM calculate_student_avg_mark(1); --Работает корректно--
-- 2. Функция общего количества часов обучения----
CREATE OR REPLACE FUNCTION calculate_total_hours(student_id INT)
RETURNS TABLE(student_fio VARCHAR, total_hours NUMERIC)
LANGUAGE SQL
AS $$
    SELECT s.fio, SUM(sub.learning_hours)
    FROM sub_students ss
    JOIN students s ON ss.id_student = s.id_student
    JOIN subjects sub ON ss.id_subject = sub.id_subject
    WHERE ss.id_student = student_id
    GROUP BY s.fio;
$$;
SELECT * FROM calculate_total_hours(1); --Работает корректно--- 
-- 3. Функция успеваемости студента----
CREATE OR REPLACE FUNCTION get_student_performance(student_id INT)
RETURNS TABLE(student_fio VARCHAR, performance VARCHAR, average_mark NUMERIC)
LANGUAGE SQL
AS $$
    SELECT 
        s.fio,
        CASE 
            WHEN AVG(m.mark) >= 4.5 THEN 'Отличник'
            WHEN AVG(m.mark) >= 3.5 THEN 'Хорошист'
            WHEN AVG(m.mark) >= 2.5 THEN 'Троечник'
            ELSE 'Неуспевающий'
        END,
        ROUND(AVG(m.mark), 2)
    FROM marks m
    JOIN students s ON m.id_student = s.id_student
    WHERE m.id_student = student_id
    GROUP BY s.fio;
$$;
SELECT * FROM get_student_performance(1); --работает корректно---
/*----4 Функции для поиска----*/
---1. Функцию для поиска информации по названию факультета----
CREATE OR REPLACE FUNCTION search_faculty_info(faculty_name VARCHAR)
RETURNS TABLE(
    id_faculty INT,
    faculty_title VARCHAR,
    housing_title VARCHAR,
    housing_address VARCHAR,
    teachers_count BIGINT,
    students_count BIGINT
)
LANGUAGE SQL
AS $$
    SELECT 
        f.id_faculty,
        f.title AS faculty_title,
        h.title AS housing_title,
        h.address AS housing_address,
        (SELECT COUNT(*) FROM teachers t WHERE t.id_faculty = f.id_faculty) AS teachers_count,
        (SELECT COUNT(*) FROM students s WHERE s.id_faculty = f.id_faculty) AS students_count
    FROM faculties f
    JOIN housings h ON f.id_housing = h.id_housing
    WHERE f.title ILIKE '%' || faculty_name || '%';
$$;

-- Пример вызова:
SELECT * FROM search_faculty_info('Танцы'); ---Работает корректно---
---2. Поиск предметов по диапазону часов----
CREATE OR REPLACE FUNCTION search_subjects_by_hours_range(
    min_hours NUMERIC DEFAULT 0,
    max_hours NUMERIC DEFAULT 1000
)
RETURNS TABLE(
    id_subject INT,
    subject_title VARCHAR,
    learning_hours NUMERIC,
    faculty_title VARCHAR,
    teachers_count BIGINT,
    students_count BIGINT
)
LANGUAGE SQL
AS $$
    SELECT 
        s.id_subject,
        s.title AS subject_title,
        s.learning_hours,
        f.title AS faculty_title,
        (SELECT COUNT(*) FROM sub_teachers st WHERE st.id_subject = s.id_subject) AS teachers_count,
        (SELECT COUNT(*) FROM sub_students ss WHERE ss.id_subject = s.id_subject) AS students_count
    FROM subjects s
    JOIN faculties f ON s.id_faculty = f.id_faculty
    WHERE s.learning_hours BETWEEN min_hours AND max_hours
    ORDER BY s.learning_hours;
$$;


SELECT * FROM search_subjects_by_hours_range(100, 150);
SELECT * FROM search_subjects_by_hours_range(max_hours => 50);
SELECT * FROM search_subjects_by_hours_range(min_hours => 200); ---	Работает корректно--
----3. Поиск по оценок по диапазону дат выставления оценок---
CREATE OR REPLACE FUNCTION search_marks_by_date(
    exact_date DATE DEFAULT NULL,
    start_date DATE DEFAULT NULL,
    end_date DATE DEFAULT NULL,
    mark_type_filter VARCHAR DEFAULT NULL
)
RETURNS TABLE(
    id_mark INT,
    student_fio VARCHAR,
    subject_title VARCHAR,
    mark NUMERIC,
    mark_type VARCHAR,
    date_m DATE,
    teacher_fio VARCHAR
)
LANGUAGE plpgsql
AS $$
BEGIN
    IF exact_date IS NOT NULL THEN
        RETURN QUERY
        SELECT 
            m.id_mark,
            s.fio AS student_fio,
            sub.title AS subject_title,
            m.mark,
            m.mark_type,
            m.date_m,
            t.fio AS teacher_fio
        FROM marks m
        JOIN students s ON m.id_student = s.id_student
        JOIN subjects sub ON m.id_subject = sub.id_subject
        JOIN teachers t ON m.id_teacher = t.id_teacher
        WHERE m.date_m = exact_date
        AND (mark_type_filter IS NULL OR m.mark_type = mark_type_filter)
        ORDER BY m.date_m;
    ELSIF start_date IS NOT NULL AND end_date IS NOT NULL THEN
        RETURN QUERY
        SELECT 
            m.id_mark,
            s.fio AS student_fio,
            sub.title AS subject_title,
            m.mark,
            m.mark_type,
            m.date_m,
            t.fio AS teacher_fio
        FROM marks m
        JOIN students s ON m.id_student = s.id_student
        JOIN subjects sub ON m.id_subject = sub.id_subject
        JOIN teachers t ON m.id_teacher = t.id_teacher
        WHERE m.date_m BETWEEN start_date AND end_date
        AND (mark_type_filter IS NULL OR m.mark_type = mark_type_filter)
        ORDER BY m.date_m;
    ELSE
        RAISE EXCEPTION 'Необходимо указать либо точную дату, либо диапазон дат';
    END IF;
END;
$$;

-- Поиск по конкретной дате
SELECT * FROM search_marks_by_date(exact_date => '2024-10-02');

-- Поиск по диапазону дат
SELECT * FROM search_marks_by_date(start_date => '2024-10-01', end_date => '2024-10-31');

-- Поиск экзаменов за период
SELECT * FROM search_marks_by_date(
    start_date => '2024-10-01',
    end_date => '2024-10-31',
    mark_type_filter => 'Экзамен'
); -- Работает корректно--

/*---Функции по варианту 10---*/
--- 1. Выбрать все сведения о студентах двух указанных факультетов -----
CREATE OR REPLACE FUNCTION students_by_faculties(faculty1_id INT, faculty2_id INT)
RETURNS TABLE(
    id_student INT,
    fio VARCHAR,
    contacts VARCHAR,
    faculty_title VARCHAR
)
AS $$
    SELECT s.id_student, s.fio, s.contacts, f.title AS faculty_title
    FROM students s
    JOIN faculties f ON s.id_faculty = f.id_faculty
    WHERE s.id_faculty = faculty1_id OR s.id_faculty = faculty2_id;
$$ LANGUAGE sql;

-- Пример вызова функции
SELECT * FROM students_by_faculties(4, 5); ---Работает корректно---
---Получить информацию о том, на каком факультете более активные студенты (среднее количество оценок)---
/* --CREATE OR REPLACE FUNCTION active_faculties()
RETURNS TABLE(
    faculty_title VARCHAR,
    avg_marks NUMERIC
)
AS $$
    SELECT f.title AS faculty_title, ROUND(AVG(mark_count), 2) AS avg_marks
    FROM faculties f
    JOIN (
        SELECT s.id_faculty, COUNT(m.id_mark) AS mark_count
        FROM students s
        LEFT JOIN marks m ON s.id_student = m.id_student
        GROUP BY s.id_student, s.id_faculty
    ) AS student_marks ON f.id_faculty = student_marks.id_faculty
    GROUP BY f.id_faculty, f.title
    ORDER BY avg_marks DESC;
$$ LANGUAGE sql;

-- Пример вызова функции
SELECT * FROM active_faculties();-- */
-- Функция для получения лучших факультетов с средними баллами студентов
CREATE OR REPLACE FUNCTION get_top_faculties_by_avg_mark(
    IN min_avg_mark NUMERIC DEFAULT 0.0,  -- минимальный средний балл для включения в результат
    IN min_students INTEGER DEFAULT 1     -- минимальное количество студентов на факультете
)
RETURNS TABLE(
    faculty_title VARCHAR,     -- название факультета
    avg_mark NUMERIC,         -- средний балл (округленный до 2 знаков)
    student_count BIGINT      -- количество студентов на факультете
)
LANGUAGE SQL
AS $$
    SELECT 
        f.title AS faculty_title, 
        ROUND(AVG(m.mark)::NUMERIC, 2) AS avg_mark,
        COUNT(DISTINCT s.id_student) AS student_count
    FROM faculties f
    JOIN students s ON f.id_faculty = s.id_faculty
    JOIN marks m ON s.id_student = m.id_student
    GROUP BY f.title
    HAVING AVG(m.mark) >= min_avg_mark 
       AND COUNT(DISTINCT s.id_student) >= min_students
    ORDER BY avg_mark DESC;
$$;

-- Примеры вызова функции:
-- 1. Получить все факультеты (с параметрами по умолчанию)
SELECT * FROM get_top_faculties_by_avg_mark();

-- 2. Получить факультеты со средним баллом не ниже 4.0 и минимум 3 студентами
SELECT * FROM get_top_faculties_by_avg_mark(4.0, 3);

-- 3. Вызов с именованными параметрами
SELECT * FROM get_top_faculties_by_avg_mark(min_avg_mark => 3.5, min_students => 2); --Работает корректно--

/*-- 3. Триггер INSERT---*/
-- 3. Триггер INSERT с автоматической генерацией ID
CREATE OR REPLACE FUNCTION insert_student_()
RETURNS TRIGGER AS $$
DECLARE
    next_id integer;
BEGIN
    -- Получаем следующий ID
    SELECT COALESCE(MAX(id_student), 0) + 1 INTO next_id FROM students;
    
    -- Устанавливаем ID для новой записи
    NEW.id_student := next_id;
    
    -- Проверки данных
    IF NEW.fio IS NULL OR NEW.fio = '' THEN
        RAISE EXCEPTION 'ФИО студента не может быть пустым';
    END IF;
    
    IF NEW.contacts IS NULL OR NEW.contacts = '' THEN
        RAISE EXCEPTION 'Контакты студента должны быть указаны';
    END IF;
    
    IF NOT EXISTS (SELECT 1 FROM faculties WHERE id_faculty = NEW.id_faculty) THEN
        RAISE EXCEPTION 'Указанный факультет не существует';
    END IF;
    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

-- Триггер BEFORE INSERT для установки ID
CREATE TRIGGER tr_insert_student_
BEFORE INSERT ON students
FOR EACH ROW
EXECUTE FUNCTION insert_student_();

-- Добавляем нового студента (ID будет назначен автоматически)
INSERT INTO students (fio, contacts, id_faculty) 
VALUES ('Автоновый Студент Генераторович', '7(999) 999-99-99', 1);

-- Проверяем последнюю запись
SELECT * FROM students ORDER BY id_student; --Работает корректно--

/*-- 4. Триггер DELETE для удаления последней записи---*/
CREATE OR REPLACE FUNCTION delete_last_student()
RETURNS TRIGGER AS $$
BEGIN
    -- Удаляем связанные оценки
    DELETE FROM marks WHERE id_student = OLD.id_student;
    
    -- Удаляем связи с предметами
    DELETE FROM sub_students WHERE id_student = OLD.id_student;
    
    RAISE NOTICE 'Удален студент % (ID: %)', OLD.fio, OLD.id_student;
    
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER tr_delete_last_student
BEFORE DELETE ON students
FOR EACH ROW
EXECUTE FUNCTION delete_last_student();

-- Удаляем последнего добавленного студента
DELETE FROM students 
WHERE id_student = (SELECT MAX(id_student) FROM students);

-- Проверяем, что студент удален
SELECT * FROM students ORDER BY id_student;

-- 3. Создаем функцию для триггера INSERT---
CREATE OR REPLACE FUNCTION insert_student_trigger()
RETURNS TRIGGER AS $$
BEGIN
    -- Автоматически назначаем id_student следующий после максимального
    NEW.id_student := (SELECT COALESCE(MAX(id_student), 0) + 1 FROM students);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE TRIGGER trg_insert_student
BEFORE INSERT ON students
FOR EACH ROW
EXECUTE FUNCTION insert_student_trigger();
INSERT INTO students (fio, contacts, id_faculty) 
VALUES ('Автоновый Студент Генераторович', '7(999) 999-99-99', 1);
SELECT * FROM students;

-- 5. Триггер UPDATE для проверки изменений данных студента
CREATE OR REPLACE FUNCTION check_student_update()
RETURNS TRIGGER AS $$
BEGIN
    -- Проверка, что ФИО не пустое
    IF NEW.fio IS NULL OR NEW.fio = '' THEN
        RAISE EXCEPTION 'ФИО студента не может быть пустым';
    END IF;
    
    -- Проверка, что контакты указаны
    IF NEW.contacts IS NULL OR NEW.contacts = '' THEN
        RAISE EXCEPTION 'Контакты студента должны быть указаны';
    END IF;
    
    -- Логирование изменений
    IF OLD.fio <> NEW.fio THEN
        RAISE NOTICE 'Изменено ФИО студента с "%" на "%"', OLD.fio, NEW.fio;
    END IF;
    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER tr_check_student_update
BEFORE UPDATE ON students
FOR EACH ROW
EXECUTE FUNCTION check_student_update();

-- Пример обновления данных студента
UPDATE students 
SET fio = 'Иванов Иван Николаевич', contacts = '7(987) 654-32-10'
WHERE fio = 'Иванов Иван Иванович';

-- Проверяем изменения
SELECT * FROM students WHERE fio LIKE 'Иванов Иван%';

-- 5. Триггер UPDATE для проверки изменений контактов студента
CREATE OR REPLACE FUNCTION check_student_contacts_update()
RETURNS TRIGGER AS $$
BEGIN
    -- Проверка, что ФИО не пустое (оставляем как обязательное поле)
    IF NEW.fio IS NULL OR NEW.fio = '' THEN
        RAISE EXCEPTION 'ФИО студента не может быть пустым';
    END IF;
    
    -- Проверка формата номера телефона (базовая валидация)
    IF NEW.contacts !~ '^7\(\d{3}\) \d{3}-\d{2}-\d{2}$' THEN
        RAISE EXCEPTION 'Номер телефона должен быть в формате: 7(XXX) XXX-XX-XX';
    END IF;
    
    -- Логирование изменения контактов
    IF OLD.contacts <> NEW.contacts THEN
        RAISE NOTICE 'Изменены контакты студента % (ID: %) с "%" на "%"', 
                     OLD.fio, OLD.id_student, OLD.contacts, NEW.contacts;
    END IF;
    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER tr_check_student_contacts_update
BEFORE UPDATE ON students
FOR EACH ROW
EXECUTE FUNCTION check_student_contacts_update();

-- Добавляем тестового студента
INSERT INTO students (fio, contacts, id_faculty) 
VALUES ('Петров Петр Петрович', '7(123) 456-78-90', 2)
RETURNING *;

-- Пример обновления номера телефона студента
UPDATE students 
SET contacts = '7(987) 654-32-10'
WHERE fio = 'Петров Петр Петрович';

-- Проверяем изменения контактов
SELECT id_student, fio, contacts FROM students WHERE fio = 'Петров Петр Петрович';

-- Попытка ввести неверный формат телефона (вызовет ошибку)
-- UPDATE students 
-- SET contacts = 'неправильный формат'
-- WHERE fio = 'Петров Петр Петрович';
-- 6. Триггер для каскадного удаления записей при удалении студента с выводом информации
-- При удалении записи из таблицы students сначала удаляет все связанные записи из marks и sub_students
CREATE OR REPLACE FUNCTION delete_student_related()
RETURNS TRIGGER AS $$
BEGIN
    -- Выводим информацию об удаляемом студенте
    RAISE NOTICE 'Удаление студента: % (ID: %)', OLD.fio, OLD.id_student;
    
    -- Удаляем оценки этого студента
    DELETE FROM marks WHERE id_student = OLD.id_student;
    RAISE NOTICE 'Удалено % оценок студента', (SELECT COUNT(*) FROM marks WHERE id_student = OLD.id_student);
    
    -- Удаляем связи студента с предметами
    DELETE FROM sub_students WHERE id_student = OLD.id_student;
    RAISE NOTICE 'Удалено % записей о предметах студента', (SELECT COUNT(*) FROM sub_students WHERE id_student = OLD.id_student);
    
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

-- Создаем триггер, который срабатывает перед удалением записи из таблицы students
CREATE TRIGGER tr_delete_student_related
BEFORE DELETE ON students
FOR EACH ROW
EXECUTE FUNCTION delete_student_related();

-- Проверка триггера
-- Показываем информацию о студенте перед удалением
SELECT id_student, fio FROM students WHERE id_student = 10;

-- Показываем связанные записи перед удалением
SELECT m.id_mark, m.mark, s.title as subject 
FROM marks m 
JOIN subjects s ON m.id_subject = s.id_subject 
WHERE m.id_student = 10;

SELECT ss.id_sub_student, sub.title as subject 
FROM sub_students ss 
JOIN subjects sub ON ss.id_subject = sub.id_subject 
WHERE ss.id_student = 10;

-- Удаляем студента
DELETE FROM students WHERE id_student = 10;

-- Проверяем, что студент и связанные записи удалены
SELECT * FROM students WHERE id_student = 10;
SELECT * FROM marks WHERE id_student = 10;
SELECT * FROM sub_students WHERE id_student = 10;

---работает----

-- 7. Триггер для логирования добавления новых оценок
CREATE OR REPLACE FUNCTION log_new_mark()
RETURNS TRIGGER AS $$
BEGIN
    -- Используем данные из временной таблицы NEW
    RAISE NOTICE 'Добавлена новая оценка: студент %, предмет %, оценка %, тип %, дата %', 
        (SELECT fio FROM students WHERE id_student = NEW.id_student),
        (SELECT title FROM subjects WHERE id_subject = NEW.id_subject),
        NEW.mark,
        NEW.mark_type,
        NEW.date_m;
    
    -- Проверяем, что оценка в допустимом диапазоне
    IF NEW.mark < 2 OR NEW.mark > 5 THEN
        RAISE EXCEPTION 'Оценка должна быть в диапазоне от 2 до 5';
    END IF;
    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

-- Создаем триггер, который срабатывает после вставки
CREATE TRIGGER tr_log_new_mark
AFTER INSERT ON marks
FOR EACH ROW
EXECUTE FUNCTION log_new_mark();

-- Добавляем новую оценку
INSERT INTO marks (id_mark, mark_type, id_subject, id_student, mark, id_teacher, date_m) 
VALUES (27, 'Зачет', 1, 1, 5, 1, '2024-12-01');

-- Проверяем добавленную оценку
SELECT * FROM marks WHERE id_mark = 27; --- работает----

-- 8. Функция для предотвращения изменений структуры БД---
CREATE OR REPLACE FUNCTION prevent_ddl_changes()
RETURNS EVENT_TRIGGER
LANGUAGE plpgsql AS $$
DECLARE
    obj record;
BEGIN
    FOR obj IN SELECT * FROM pg_event_trigger_ddl_commands() LOOP
        IF obj.command_tag IN ('DROP TABLE', 'ALTER TABLE', 'TRUNCATE TABLE') THEN
            RAISE EXCEPTION 'Изменение структуры базы данных запрещено!';
        END IF;
    END LOOP;
END;
$$;

-- Создаем триггер события
CREATE EVENT TRIGGER tr_prevent_ddl_changes
ON ddl_command_start
EXECUTE FUNCTION prevent_ddl_changes();

-- Попытка изменить структуру таблицы (вызовет ошибку)
-- ALTER TABLE students ADD COLUMN test_column INT;
ALTER TABLE students ADD COLUMN test_column INT;