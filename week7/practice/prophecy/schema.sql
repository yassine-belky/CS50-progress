CREATE TABLE students (
    id INTEGER,
    name TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    id INTEGER,
    name TEXT,
    head TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE assignments (
    student_id INTEGER,
    house_id INTEGER,
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(house_id) REFERENCES houses(id)
);