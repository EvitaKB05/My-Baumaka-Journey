-- 1. Ранжирование студентов по среднему баллу на каждом факультете
SELECT 
    s.id_student,
    s.fio AS student_name,
    f.title AS faculty,
    ROUND(AVG(m.mark), 2) AS avg_mark,
    ROW_NUMBER() OVER (PARTITION BY f.id_faculty ORDER BY AVG(m.mark) DESC) AS row_num,
    RANK() OVER (PARTITION BY f.id_faculty ORDER BY AVG(m.mark) DESC) AS rank,
    DENSE_RANK() OVER (PARTITION BY f.id_faculty ORDER BY AVG(m.mark) DESC) AS dense_rank
FROM students s
JOIN faculties f ON s.id_faculty = f.id_faculty
JOIN marks m ON s.id_student = m.id_student
GROUP BY s.id_student, s.fio, f.title, f.id_faculty
ORDER BY f.title, avg_mark DESC;

--2. Накопленные оценки студентов по датам для каждого предмета
SELECT 
    m.id_student,
    s.fio AS student_name,
    sub.title AS subject,
    m.date_m,
    m.mark,
    SUM(m.mark) OVER (PARTITION BY m.id_student, m.id_subject ORDER BY m.date_m) AS cumulative_sum,
    MAX(m.mark) OVER (PARTITION BY m.id_student, m.id_subject ORDER BY m.date_m) AS max_mark_so_far,
    ROUND(AVG(m.mark) OVER (PARTITION BY m.id_student, m.id_subject ORDER BY m.date_m), 2) AS running_avg
FROM marks m
JOIN students s ON m.id_student = s.id_student
JOIN subjects sub ON m.id_subject = sub.id_subject
ORDER BY m.id_student, m.id_subject, m.date_m;

-- 2. Накопленные оценки студентов по датам для каждого предмета
WITH student_marks AS (
    SELECT 
        m.id_student,
        s.fio AS student_name,
        sub.title AS subject,
        m.date_m,
        (SELECT STRING_AGG(m2.mark::TEXT, ', ' ORDER BY m2.date_m)
         FROM marks m2
         WHERE m2.id_student = m.id_student AND m2.id_subject = m.id_subject) AS all_marks,
        COUNT(*) OVER (PARTITION BY m.id_student, m.id_subject) AS marks_count,
        MAX(m.mark) OVER (PARTITION BY m.id_student, m.id_subject) AS max_mark,
        AVG(m.mark) OVER (PARTITION BY m.id_student, m.id_subject) AS avg_mark
    FROM marks m
    JOIN students s ON m.id_student = s.id_student
    JOIN subjects sub ON m.id_subject = sub.id_subject
)

SELECT DISTINCT
    sm.id_student,
    sm.student_name,
    sm.subject,
    sm.all_marks,
    sm.marks_count,
    sm.max_mark,
    ROUND(sm.avg_mark, 2) AS avg_mark_rounded
FROM student_marks sm
ORDER BY sm.id_student, sm.subject;
-- Сравнение оценки студента со средней оценкой по предмету на факультете
WITH faculty_avg AS (
    SELECT 
        s.id_faculty,
        ROUND(AVG(m.mark), 2) AS faculty_avg_mark
    FROM marks m
    JOIN students s ON m.id_student = s.id_student
    GROUP BY s.id_faculty
)

SELECT 
    m.id_student,
    s.fio AS student_name,
    f.title AS faculty,
    sub.title AS subject,
    m.mark,
    fa.faculty_avg_mark,
    m.mark - fa.faculty_avg_mark AS diff_from_faculty_avg,
    CASE 
        WHEN m.mark > fa.faculty_avg_mark THEN 'Выше среднего по направлению'
        WHEN m.mark < fa.faculty_avg_mark THEN 'Ниже среднего по направлению'
        ELSE 'Соответствует среднему'
    END AS performance_status,
    RANK() OVER (PARTITION BY s.id_faculty ORDER BY m.mark DESC) AS faculty_rank
FROM marks m
JOIN students s ON m.id_student = s.id_student
JOIN subjects sub ON m.id_subject = sub.id_subject
JOIN faculties f ON s.id_faculty = f.id_faculty
JOIN faculty_avg fa ON s.id_faculty = fa.id_faculty
ORDER BY f.title, m.mark DESC;

-- Анализ прогресса студентов: сравнение текущей оценки с предыдущей и следующей
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



------допчики-----
---ранг факультетов по кол-ву студентов----
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

---реййтинг препов по ср баллу студентиков---
SELECT 
    t.id_teacher,
    t.fio AS teacher_name,
    f.title AS faculty,
    ROUND(AVG(m.mark), 2) AS avg_mark,
    COUNT(DISTINCT m.id_student) AS students_taught,
    RANK() OVER (ORDER BY AVG(m.mark) DESC) AS overall_rank,
    RANK() OVER (PARTITION BY t.id_faculty ORDER BY AVG(m.mark) DESC) AS faculty_rank
FROM teachers t
JOIN marks m ON t.id_teacher = m.id_teacher
JOIN faculties f ON t.id_faculty = f.id_faculty
GROUP BY t.id_teacher, t.fio, f.title, t.id_faculty
ORDER BY avg_mark DESC;

---предметы по кол-ву часов топ три--
SELECT *
FROM (
    SELECT 
        f.title AS faculty,
        s.title AS subject,
        s.learning_hours,
        RANK() OVER (PARTITION BY f.id_faculty ORDER BY s.learning_hours DESC) AS rank_by_hours
    FROM subjects s
    JOIN faculties f ON s.id_faculty = f.id_faculty
) ranked_subjects
WHERE rank_by_hours <= 3
ORDER BY faculty, rank_by_hours;
