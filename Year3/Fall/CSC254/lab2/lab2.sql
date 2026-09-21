CREATE TABLE students(
    student_name VARCHAR(50), 
    student_id SERIAL PRIMARY KEY, 
    student_gpa DECIMAL 
);

INSERT INTO students(student_name)
VALUES
    ('Ryan'),
    ('Ethan');


CREATE TABLE grades(
    grade_id SERIAL PRIMARY KEY,
    student_id INTEGER REFERENCES students(student_id),
    course_name VARCHAR(50),
    grade DECIMAL
);

INSERT INTO grades(student_id, course_name, grade)
VALUES
    (1, 'Computer Science', 3.7),
    (1, 'Math', 3.3),
    (1, 'Physics', 3.0),
    (2, 'Computer Science', 4.0),
    (2, 'Math', 4.0),
    (2, 'English', 3.7);

UPDATE students s
SET student_gpa = (
    SELECT ROUND(AVG(g.grade), 1)
    FROM grades g
    WHERE g.student_id = s.student_id
);

SELECT * FROM students ;

