----LABA 6 -----

----1. ранжирование факультетов по количеству студентов---
SELECT 
    f.id_faculty,
    f.title AS faculty,
    COUNT(s.id_student) AS student_count,
    RANK() OVER (ORDER BY COUNT(s.id_student) DESC) AS rank_by_students,
    DENSE_RANK() OVER (ORDER BY COUNT(s.id_student) DESC) AS dense_rank_by_students,
    ROW_NUMBER() OVER (ORDER BY COUNT(s.id_student) DESC) AS row_num
FROM faculties f
LEFT JOIN students s ON f.id_faculty = s.id_faculty
GROUP BY f.id_faculty, f.title
ORDER BY student_count DESC;


----2. Агрегатные функции, запас оценок студентов и показатели типа средней и максимальной оценки---
SELECT 
    m.id_student,
    s.fio AS student_name,
    sub.title AS subject,
    m.date_m,
    m.mark,
    SUM(m.mark) OVER (PARTITION BY m.id_student, m.id_subject ORDER BY m.date_m) AS mark_value_sum,
    MAX(m.mark) OVER (PARTITION BY m.id_student, m.id_subject ORDER BY m.date_m) AS max_mark_so_far,
    ROUND(AVG(m.mark) OVER (PARTITION BY m.id_student, m.id_subject ORDER BY m.date_m), 2) AS running_avg
FROM marks m
JOIN students s ON m.id_student = s.id_student
JOIN subjects sub ON m.id_subject = sub.id_subject
ORDER BY m.id_student, m.id_subject, m.date_m;


---3. сравнение оценки студента со средней оценкой по предмету на факультете партишн ---
SELECT 
    m.id_student,
    s.fio AS student_name,
    sub.title AS subject,
    f.title AS faculty,
    m.mark,
    ROUND(AVG(m.mark) OVER (PARTITION BY m.id_subject), 2) AS avg_mark_subject,
    m.mark - ROUND(AVG(m.mark) OVER (PARTITION BY m.id_subject), 2) AS diff_from_avg
    --ROUND(AVG(m.mark) OVER (PARTITION BY s.id_faculty), 2) AS avg_mark_faculty
    --RANK() OVER (PARTITION BY m.id_subject ORDER BY m.mark DESC) AS rank_in_subject
FROM marks m
JOIN students s ON m.id_student = s.id_student
JOIN subjects sub ON m.id_subject = sub.id_subject
JOIN faculties f ON s.id_faculty = f.id_faculty
ORDER BY sub.title, m.mark DESC;

-- Анализ прогресса студентов: сравнение текущей оценки с предыдущей и следующей пока оценок мало, можно подобавлять по приколу--- лаг лид---
SELECT 
    m.id_student,
    s.fio AS student_name,
    sub.title AS subject,
    m.date_m,
    m.mark,
    LAG(m.mark) OVER (PARTITION BY m.id_student, m.id_subject ORDER BY m.date_m) AS prev_mark,
    LEAD(m.mark) OVER (PARTITION BY m.id_student, m.id_subject ORDER BY m.date_m) AS next_mark,
    m.mark - LAG(m.mark) OVER (PARTITION BY m.id_student, m.id_subject ORDER BY m.date_m) AS diff_from_prev,
    FIRST_VALUE(m.mark) OVER (PARTITION BY m.id_student, m.id_subject ORDER BY m.date_m) AS first_mark,
    LAST_VALUE(m.mark) OVER (PARTITION BY m.id_student, m.id_subject 
                            ORDER BY m.date_m
                            RANGE BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS last_mark
FROM marks m
JOIN students s ON m.id_student = s.id_student
JOIN subjects sub ON m.id_subject = sub.id_subject
ORDER BY m.id_student, m.id_subject, m.date_m;

INSERT INTO marks(id_mark, mark_type, id_subject, id_student, mark, id_teacher, date_m) VALUES
(27, 'Зачет', 1, 1, 3, 20, '2024-09-20'),
(28, 'Зачет', 1, 1, 4, 18, '2024-10-01'),
(29, 'Зачет', 5, 2, 3, 24, '2024-10-10'),
(30, 'Экзамен', 5, 2, 5, 19, '2024-10-02'),
(31, 'Зачет', 12, 4, 2, 5, '2024-10-02'),
(32, 'Экзамен', 24, 5, 2, 4, '2024-10-02'),
(33, 'Зачет', 3, 6, 5, 22, '2024-10-17'),
(34, 'Зачет', 10, 7, 3, 17, '2024-10-22'),
(35, 'Экзамен', 13, 8, 2, 22, '2024-10-09'),
(36, 'Зачет', 21, 9, 5, 7, '2024-10-17'),
(37, 'Зачет', 2, 10, 5, 2, '2024-10-25'),
(38, 'Зачет', 22, 11, 4, 15, '2024-10-02'),
(39, 'Экзамен', 15, 12, 2, 14, '2024-10-26');


